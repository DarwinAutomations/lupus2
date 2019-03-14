#include <stdexcept>
#include <memory>
#include <time.h>
#include <chrono>
#include <thread>
#include <functional>
#include <map>
#include <set>

#include "distance_sensor.h"
#include "ultrasonic_service.h"

using namespace std::placeholders;

#define SPEED_OF_SOUND 340

namespace lupus::construction::distanceSensor
{

UltrasonicService::UltrasonicService (
  std::shared_ptr<drivers::gpio::GpioDriver> gpio,
  int frequency)
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
    for(auto &entry: this->registry)
    {
      triggers.insert(entry.second->getConfiguration().triggerPin);
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

  auto sensor = registry[id];
  if(!sensor)
  {
    throw std::invalid_argument("sensor cannot be null");
  }

  auto config = sensor->getConfiguration();

  auto triggerTime = this->lastMassTrigger;
  float newDistance = std::chrono::duration_cast<std::chrono::microseconds>(
    echoTime - triggerTime).count() / 2 / 1000000.0 * SPEED_OF_SOUND;

  //if policy.distanceInRange(sensor, newDistance):
  if(newDistance < config.measurementRangeMin
    || newDistance > config.measurementRangeMax)
  {
    newDistance = IDistanceSensor::DistanceOutOfRange;
  }

  sensor->setDistance(newDistance);
}

int UltrasonicService::registerSensor(std::shared_ptr<IDistanceSensor> sensor)
{
  if(!sensor)
  {
    throw std::invalid_argument("sensor cannot be null");
  }

  auto config = sensor->getConfiguration();
  setupPins(config);

  // register on change event
  int id = gpio->registerOnChange(
    config.echoPin,
    std::bind(&UltrasonicService::onEchoChange, this, _1, _2, _3, _4));

  std::lock_guard<std::mutex> lock(registryMutex);
  registry[id] = std::move(sensor);

  return id;
}

void UltrasonicService::deregisterSensor(int id)
{
  this->registryMutex.lock();
  this->registry.erase(id);
  this->registryMutex.unlock();
}

void UltrasonicService::setupPins(DistanceSensorConfiguration config)
{
  gpio->setMode(config.triggerPin, drivers::gpio::PinMode::Output);
  gpio->setMode(config.echoPin, drivers::gpio::PinMode::Input);
}

}
