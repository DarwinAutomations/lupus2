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
#include "lupus.h"

#define ULTRASONIC_TRIGGER 18

using namespace lupus;

void input_loop(
  bool* isActive,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking);
void engine_loop(
  bool* isActive,
  construction::Lupus* construction,
  profiles::IProfile* profile,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking);
void output_loop(
  bool* isActive,
  construction::Lupus* construction,
  float* input_power,
  float* input_direction,
  bool* input_isbreaking,
  sensors::IDistanceSensor* fl,
  sensors::IDistanceSensor* fcl,
  sensors::IDistanceSensor* fcr,
  sensors::IDistanceSensor* fr);

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


  // navigation units:
  // navigation unit left:
  auto controlUnitLeft = new simulations::SimulatedControlUnit();
  auto steeringUnitLeft =
    new navigation::SteeringUnit(controlUnitLeft);

  // navigation unit right:
  auto controlUnitRight = new simulations::SimulatedControlUnit();
  auto steeringUnitRight =
    new navigation::SteeringUnit(controlUnitRight);


  // propulsion units:
  // propulsion unit front left:
  auto cuPropulsionFrontLeft = new simulations::SimulatedControlUnit();
  auto propulsionUnitFrontLeft =
    new navigation::PropulsionUnit(cuPropulsionFrontLeft);

  // propulsion unit front right:
  auto cuPropulsionFrontRight = new simulations::SimulatedControlUnit();
  auto propulsionUnitFrontRight =
    new navigation::PropulsionUnit(cuPropulsionFrontRight);

  // propulsion unit back left:
  auto cuPropulsionBackLeft = new simulations::SimulatedControlUnit();
  auto propulsionUnitBackLeft =
    new navigation::PropulsionUnit(cuPropulsionBackLeft);

  // propulsion unit back right:
  auto cuPropulsionBackRight = new simulations::SimulatedControlUnit();
  auto propulsionUnitBackRight =
    new navigation::PropulsionUnit(cuPropulsionBackRight);

  // sensors:
  // ultrasonic:
  // ultrasonic service;
  auto ultrasonicService = new sensors::UltrasonicService(1);

  // ultrasnoic sensor front left:
  auto ultrasonicSensorFrontLeft = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */,
      ULTRASONIC_TRIGGER, 19);

  // ultrasnoic sensor front center left:
  auto ultrasonicSensorFrontCenterLeft = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, 13);

  // ultrasnoic sensor front center right:
  auto ultrasonicSensorFrontCenterRight = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      16, 6);

  // ultrasnoic sensor front right:
  auto ultrasonicSensorFrontRight = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      12, 5);

  // ultrasnoic sensor back left:
  auto ultrasonicSensorBackLeft = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */,
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 1);

  // ultrasnoic sensor back center left:
  auto ultrasonicSensorBackCenterLeft = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 2);

  // ultrasnoic sensor back center right:
  auto ultrasonicSensorBackCenterRight = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 3);

  // ultrasnoic sensor back right:
  auto ultrasonicSensorBackRight = new sensors::UltrasonicSensor(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 4);


  // consutruction:
  auto construction = new construction::Lupus(
    steeringUnitLeft,
    steeringUnitRight,

    propulsionUnitFrontLeft,
    propulsionUnitFrontRight,
    propulsionUnitBackLeft,
    propulsionUnitBackRight,

    ultrasonicSensorFrontLeft,
    ultrasonicSensorFrontCenterLeft,
    ultrasonicSensorFrontCenterRight,
    ultrasonicSensorFrontRight,
    ultrasonicSensorBackLeft,
    ultrasonicSensorBackCenterLeft,
    ultrasonicSensorBackCenterRight,
    ultrasonicSensorBackRight
  );

  // ensure power and direction are nutral before starting
  construction->setPower(0);
  construction->setDirection(0);

  auto profile = new profiles::GrannyProfile();

  // start input and output thread
  bool isActive = true;
  float input_power = 0;
  float input_direction = 0;
  bool input_isbreaking = false;
  auto engine_thread = std::thread(
    engine_loop, &isActive,
    construction, profile,
    &input_power, &input_direction,
    &input_isbreaking);
  auto input_thread = std::thread(
    input_loop, &isActive,
    &input_power, &input_direction,
    &input_isbreaking);
  auto output_thread = std::thread(
    output_loop, &isActive,
    construction, &input_power,
    &input_direction, &input_isbreaking,
    ultrasonicSensorFrontLeft,
    ultrasonicSensorFrontCenterLeft,
    ultrasonicSensorFrontCenterRight,
    ultrasonicSensorFrontRight);

  // wait for user input and exit
  getchar();
  isActive = false;
  input_thread.join();
  output_thread.join();
  engine_thread.join();

  delete profile;
  delete construction;

  delete ultrasonicSensorFrontLeft;
  delete ultrasonicSensorFrontLeft;
  delete ultrasonicSensorFrontCenterRight;
  delete ultrasonicSensorFrontCenterRight;
  delete ultrasonicSensorBackLeft;
  delete ultrasonicSensorBackCenterLeft;
  delete ultrasonicSensorBackCenterRight;
  delete ultrasonicSensorBackRight;

  delete ultrasonicService;

  delete cuPropulsionFrontLeft;
  delete propulsionUnitFrontLeft;
  delete cuPropulsionFrontRight;
  delete propulsionUnitFrontRight;
  delete cuPropulsionBackLeft;
  delete propulsionUnitBackLeft;
  delete cuPropulsionBackRight;
  delete propulsionUnitBackRight;

  delete steeringUnitLeft;
  delete controlUnitLeft;
  delete steeringUnitRight;
  delete controlUnitRight;

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
  construction::Lupus* construction,
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
    construction->setDirection(*input_direction);
    if (*input_isbreaking) {
      service->decelerate(deltatime);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  delete service;
}

void output_loop(
  bool* isActive,
  construction::Lupus* construction,
  float *input_power,
  float *input_direction,
  bool *input_isbreaking,
  sensors::IDistanceSensor* fl,
  sensors::IDistanceSensor* fcl,
  sensors::IDistanceSensor* fcr,
  sensors::IDistanceSensor* fr)
{
  while (*isActive)
  {
    int fld = fl->getDistance();
    int fcld = fcl->getDistance();
    int fcrd = fcr->getDistance();
    int frd = fr->getDistance();

    //std::system("clear");
    std::cout << "Is breaking: " << *input_isbreaking << std::endl;
    std::cout << "Input power: " << *input_power << std::endl;
    std::cout << "Input direction: " << *input_direction << std::endl;
    std::cout << "Power: " << construction->getPower() << std::endl;
    std::cout << "Direction: " << construction->getDirection() << std::endl;
    
    std::cout << "Front Left: " << fld << "mm" << std::endl;
    std::cout << "Front Center Left: " << fcld << "mm" << std::endl;
    std::cout << "Front Center Right: " << fcrd << "mm" << std::endl;
    std::cout << "Front Right: " << frd << "mm" << std::endl;
    
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
