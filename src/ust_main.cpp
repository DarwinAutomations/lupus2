#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>

#include "ultrasonic_service.h"
#include "ultrasonic_sensor.h"

using namespace lupus;

int main()
{
  if(gpioInitialise() < 0) return 0;
  gpioSetMode(19, PI_INPUT);
  gpioSetMode(13, PI_INPUT);
  gpioSetMode(6, PI_INPUT);
  gpioSetMode(5, PI_INPUT);

  gpioSetMode(18, PI_OUTPUT);
  gpioSetMode(18, PI_OUTPUT);
  gpioSetMode(16, PI_OUTPUT);
  gpioSetMode(12, PI_OUTPUT);

  gpioWrite(18, 0);
  gpioWrite(18, 0);
  gpioWrite(16, 0);
  gpioWrite(12, 0);

  auto service = new sensors::UltrasonicService(1);
  auto sensor1 = new sensors::UltrasonicSensor(service, 0,0,0, 18, 19);
  auto sensor2 = new sensors::UltrasonicSensor(service, 0,0,0, 18, 13);
  auto sensor3 = new sensors::UltrasonicSensor(service, 0,0,0, 16, 6);
  auto sensor4 = new sensors::UltrasonicSensor(service, 0,0,0, 12, 5);
  bool isActive = true;

  auto output_thread = std::thread([&isActive, sensor1, sensor2, sensor3, sensor4](){
    while(isActive)
    {
      int distance1 = sensor1->getDistance();
      int distance2 = sensor2->getDistance();
      int distance3 = sensor3->getDistance();
      int distance4 = sensor4->getDistance();

      std::cout << "18 " << distance1 << "mm" << std::endl;
      std::cout << "18 " << distance2 << "mm" << std::endl;
      std::cout << "16 " << distance3 << "mm" << std::endl;
      std::cout << "12 " <<distance4 << "mm" << std::endl;
      std::cout << std::endl;

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  getchar();
  isActive = false;
  output_thread.join();

  delete(sensor2);
  delete(sensor1);
  delete(service);
  return 0;
}
