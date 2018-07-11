#include <time.h>
#include <chrono>
#include <thread>
#include <future>
#include <map>
#include <tuple>
#include <vector>

#include "distance_sensor.h"
#include "ultrasonic_service.h"

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
  this->idCounter = 0;

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
  std::map<int, std::future<int>> futures;

  while(this->isRunning)
  {
    futures.clear();
    time += period;

    this->registryMutex.lock();
    for(auto &kv: this->registry)
    {
      auto sensorId = kv.first;
      int trigger, echo;
      std::tie(trigger, echo) = kv.second;

      auto future = std::async(
          std::launch::async,
          UltrasonicService::measure,
          this->gpio, trigger, echo, &time);

      futures[sensorId] = std::move(future);
    }

    this->registryMutex.unlock();
    this->dataMutex.lock();
    for(auto &kv: futures)
    {
      int sensorId = kv.first;
      auto distance = &kv.second;
      if(std::future_status::ready == distance->wait_until(time + std::chrono::milliseconds(75)))
      {
        this->data[sensorId] = distance->get();
      }
      else
      {
        this->data[sensorId] = IDistanceSensor::DistanceUnknown;
      }
    }
    this->dataMutex.unlock();

  }
}

int UltrasonicService::measure(
    std::shared_ptr<gpio::GpioDriver> gpio,
    int trigger, int echo,
    std::chrono::time_point<std::chrono::system_clock>* startTime)
{
  if(startTime)
  {
    std::this_thread::sleep_until(*startTime);
  }

  if(!gpio->read(trigger))
  {
    gpio->write(trigger, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    gpio->write(trigger, false);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - *startTime).count();
  while(!gpio->read(echo) && duration < 30000)
  {
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - *startTime).count();
  }

  auto start = end;
  duration = 0;
  while(gpio->read(echo) && duration < 40000)
  {
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }


  if(duration > 35000)
  {
    return IDistanceSensor::DistanceOutOfRange;
  }

  return duration / 1000000.0 * SPEED_OF_SOUND / 2;
}

int UltrasonicService::registerSensor(int trigger, int echo)
{
  this->registryMutex.lock();
  this->dataMutex.lock();

  int id = this->idCounter++;
  this->gpio->setMode(trigger, gpio::GpioPinMode::InputPin);
  this->gpio->setMode(echo, gpio::GpioPinMode::OutputPin);
  this->registry[id] = std::make_tuple(trigger, echo);
  this->data[id] = IDistanceSensor::DistanceUnknown;

  this->dataMutex.unlock();
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
  this->dataMutex.lock();
  int data = this->data.at(id);
  this->dataMutex.unlock();
  return data;
}

} // namespace lupus::sensors
