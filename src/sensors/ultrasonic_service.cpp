#include <time.h>
#include <chrono>
#include <thread>
#include <functional>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include "distance_sensor.h"
#include "ultrasonic_service.h"

using namespace std::placeholders;

#define SPEED_OF_SOUND 340

namespace lupus::sensors
{

UltrasonicService::UltrasonicService (std::shared_ptr<gpio::GpioDriver> gpio, int frequency)
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }

  this->gpio = std::move(gpio);
  this->isRunning = true;

  this->measuringThread = std::thread(
    &UltrasonicService::measuringLoop, this, frequency);
}

UltrasonicService::~UltrasonicService ()
{
  this->isRunning = false;
  this->measuringThread.join();
}

void UltrasonicService::measuringLoop(int frequency)
{
  auto time = std::chrono::system_clock::now();
  auto period = std::chrono::milliseconds((int) (1000.0 / frequency));

  while(this->isRunning)
  {
    std::this_thread::sleep_until(time);
    time += period;

    std::set<int> triggers;

    this->registryMutex.lock();
    for(auto &kv: this->registry)
    {
      int trigger, echo;
      std::tie(trigger, echo) = kv.second;

      triggers.insert(trigger);
    }
    this->registryMutex.unlock();

    for(int trigger: triggers)
    {
      this->gpio->write(trigger, true);
    }
    // sleepForTriggerLength
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    for(int trigger: triggers)
    {
      this->gpio->write(trigger, false);
    }

    this->lastMassTrigger = std::chrono::system_clock::now();
  }
}

void UltrasonicService::onEchoChange(
  int id,
  int pin,
  int level,
  std::chrono::high_resolution_clock::time_point echoTime)
{
  // policy.isNotRisingEdge...
  if(level == 1) return;

  auto triggerTime = this->lastMassTrigger;
  float newDistance = std::chrono::duration_cast<std::chrono::microseconds>(
    echoTime - triggerTime).count() / 2 / 1000000.0 * SPEED_OF_SOUND;

  //if policy.distanceInRange(sensor, newDistance):
  float maxReliableDistance = 4.0;
  float minRelibaleDistance = 0.3;
  if(newDistance > maxReliableDistance || newDistance < minRelibaleDistance)
  {
    this->data[id] = IDistanceSensor::DistanceOutOfRange;
    return;
  }
  this->data[id] = newDistance;
}

int UltrasonicService::registerSensor(int trigger, int echo)
{
  this->gpio->setMode(trigger, gpio::PinMode::Output);
  this->gpio->setMode(echo, gpio::PinMode::Input);
  // register on change event
  int id = this->gpio->registerOnChange(
    echo,
    std::bind(&UltrasonicService::onEchoChange, this, _1, _2, _3, _4));
  this->registryMutex.lock();

  this->registry[id] = std::make_tuple(trigger, echo);
  this->data[id] = IDistanceSensor::DistanceUnknown;

  this->registryMutex.unlock();

  return id;
}

void UltrasonicService::deregisterSensor(int id)
{
  this->registryMutex.lock();
  this->registry.erase(id);
  this->registryMutex.unlock();
}

float UltrasonicService::getDistance(int id)
{
  //if data->timePoint < lastMassTrigger || lastMassTrigger > maxReliableDistance:
  //  return IDistanceSensor::DistanceUnknown;
  return this->data.at(id);
}

} // namespace lupus::sensors
