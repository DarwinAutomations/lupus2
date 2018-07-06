#include <iostream>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <thread>
#include <pigpio.h>
#include <cstdlib>

#include "simulated_control_unit.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_service.h"
#include "profile.h"
#include "granny_profile.h"
#include "propulsion_service.h"
#include "local_construction.h"
#include "local_construction_factory.h"
#include "controller.h"
#include "intelligent_controller.h"
#include "gpio_driver.h"

#define ULTRASONIC_TRIGGER 18

using namespace lupus;

void input_loop(
  bool& isActive,
  std::shared_ptr<controllers::IController> controller);

void output_loop(
  bool& isActive,
  std::shared_ptr<controllers::IController> controller,
  std::shared_ptr<constructions::IConstruction> construciton);

int main()
{
  const int i2cAddress = 0x40;
  const int frequency = 60;

  auto gpioDriver = std::make_shared<gpio::GpioDriver>();
  auto pwmDriver = std::make_shared<pwm::PwmDriver>(i2cAddress);
  pwmDriver->setPwmFrequency(frequency);

  auto ultrasonicService = std::make_shared<sensors::UltrasonicService>(
      gpioDriver, 1);

  auto construction = constructions::LocalConstructionFactory::create(
      pwmDriver,
      gpioDriver,
      ultrasonicService);

  construction->setPropulsionFrontLeftPower(0);
  construction->setPropulsionFrontRightPower(0);
  construction->setPropulsionBackLeftPower(0);
  construction->setPropulsionBackRightPower(0);

  auto profile = std::make_shared<profiles::GrannyProfile>();
  auto propulsionService = 
    std::make_shared<navigation::PropulsionService>(construction, profile);

  auto controller = 
    std::make_shared<controllers::IntelligentController>(
      construction,
      propulsionService);

  // start input and output thread
  bool isActive = true;

  auto input_thread = std::thread(
    input_loop, 
    std::ref(isActive),
    controller);

  auto output_thread = std::thread(
    output_loop, 
    std::ref(isActive),
    controller,
    construction); 

  // wait for user input and exit
  while(getchar() != 'q');
  isActive = false;
  input_thread.join();
  output_thread.join();

  return 0;
}

void input_loop(
  bool& isActive,
  std::shared_ptr<controllers::IController> controller)
{
  js_event* event = new js_event();
  int fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
  float magic_value = 32767.0f;

  while(isActive)
  {
    int bytes = read(fd, event, sizeof(js_event));
    if (bytes > 0)
    {
      event->type &= ~JS_EVENT_INIT;

      if (event->type & JS_EVENT_AXIS)
      {
        switch (event->number)
        {
          case 0:
            controller->setDirection(event->value / magic_value);
            break;
          case 5:
            controller->setAcceleration(event->value / (magic_value*2) + 0.5f);
            break;
        }
      }
      if (event->type & JS_EVENT_BUTTON)
      {
        switch (event->number) {
          case 4:
            if(event->value == 1)
      	      controller->setAcceleration(-0.5);
            else
	      controller->setAcceleration(0);
	    break;
          case 5:
            if(event->value == 1)
	      controller->decelerate();
	    else
	      controller->setAcceleration(0);
        }
      }
    }
  }
}

void output_loop(
  bool& isActive,
  std::shared_ptr<controllers::IController> controller,
  std::shared_ptr<constructions::IConstruction> construction)
{
  while (isActive)
  {
    std::system("clear");
    std::cout << "Direction: " << controller->getDirection() << std::endl;
    std::cout << "Power: " << construction->getPropulsionFrontLeftPower() << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
