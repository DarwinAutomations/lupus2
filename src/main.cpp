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
#include "acceleration_service.h"
#include "local_construction.h"
#include "local_construction_factory.h"
#include "controller.h"
#include "raw_controller.h"

#define ULTRASONIC_TRIGGER 18

using namespace lupus;

void input_loop(
  bool* isActive,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking);

void engine_loop(
  bool* isActive,
  constructions::IConstruction* construction,
  controllers::IController* controller,
  profiles::IProfile* profile,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking);

void output_loop(
  bool* isActive,
  controllers::IController* controller,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking);

int main()
{
  // pigpio initialise
  if(gpioInitialise() < 0)
  {
    puts("gpio init failed");
    return 0;
  }
  gpioSetMode(19, PI_INPUT);
  gpioSetMode(13, PI_INPUT);
  gpioSetMode(6, PI_INPUT);
  gpioSetMode(5, PI_INPUT);

  gpioSetMode(18, PI_OUTPUT);
  gpioSetMode(18, PI_OUTPUT);
  gpioSetMode(16, PI_OUTPUT);
  gpioSetMode(12, PI_OUTPUT);

  auto profile = new profiles::GrannyProfile();
  auto ultrasonicService = new sensors::UltrasonicService(1);
  auto construction = dynamic_cast<constructions::IConstruction*> (constructions::LocalConstructionFactory::create(ultrasonicService));
  auto controller = dynamic_cast<controllers::IController*> (new controllers::RawController(std::shared_ptr<constructions::IConstruction>(construction)));

  // ensure power and direction are nutral before starting
  controller->setPower(0);
  controller->setDirection(0);

  // start input and output thread
  bool isActive = true;
  float input_power = 0;
  float input_direction = 0;
  bool input_isbreaking = false;

  auto engine_thread = std::thread(
    engine_loop, &isActive,
    construction, controller, profile,
    &input_power, &input_direction,
    &input_isbreaking);

  auto input_thread = std::thread(
    input_loop, &isActive,
    &input_power, &input_direction,
    &input_isbreaking);

  auto output_thread = std::thread(
    output_loop, &isActive,
    controller, &input_power,
    &input_direction, &input_isbreaking);

  // wait for user input and exit
  getchar();
  isActive = false;
  input_thread.join();
  output_thread.join();
  engine_thread.join();

  delete profile;
  delete construction;
  delete ultrasonicService;

  gpioTerminate();

  return 0;
}

void input_loop(
  bool* isActive,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking)
{
  js_event* event = new js_event();
  int fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
  float magic_value = 32767.0f;

  while(*isActive)
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
            *input_direction = event->value / magic_value;
            break;
          case 13:
            *input_power = event->value / (magic_value*2) + 0.5f;
            break;
        }
      }
      if (event->type & JS_EVENT_BUTTON)
      {
        switch (event->number) {
          case 11:
            *input_isbreaking = event->value == 1;
        }
      }
    }
  }
}

void engine_loop(
  bool* isActive,
  constructions::IConstruction* construction,
  controllers::IController* controller,
  profiles::IProfile* profile,
  float *input_power,
  float *input_direction,
  bool* input_isbreaking)
{
  auto service = new navigation::AccelerationService(
    construction, profile);

  float deltatime = 0.0f; // passed time in seconds
  auto lasttime = std::chrono::steady_clock::now();
  while(*isActive)
  {
    auto currenttime = std::chrono::steady_clock::now();
    deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(currenttime - lasttime).count();
    lasttime = currenttime;

    service->setAcceleration(*input_power, deltatime);
    controller->setDirection(*input_direction);
    if (*input_isbreaking) {
      service->decelerate(deltatime);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  delete service;
}

void output_loop(
  bool* isActive,
  controllers::IController* controller,
  float *input_power,
  float *input_direction,
  bool *input_isbreaking)
{
  while (*isActive)
  {
    //std::system("clear");
    std::cout << "Is breaking: " << *input_isbreaking << std::endl;
    std::cout << "Input power: " << *input_power << std::endl;
    std::cout << "Input direction: " << *input_direction << std::endl;
    std::cout << "Power: " << controller->getPower() << std::endl;
    std::cout << "Direction: " << controller->getDirection() << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
