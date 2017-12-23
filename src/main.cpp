#include <iostream>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <thread>

#include "simulated_control_unit.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include "lupus.h"

using namespace lupus;

void output_loop(bool*, construction::Lupus*);
void input_loop(bool*, construction::Lupus*);

int main()
{
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

  auto lupus = new construction::Lupus(
    steeringUnitLeft,
    steeringUnitRight,
    propulsionUnitFrontLeft,
    propulsionUnitFrontRight,
    propulsionUnitBackLeft,
    propulsionUnitBackRight
  );


  // start input and output thread
  bool isActive = true;
  auto input_thread = std::thread(input_loop, &isActive, lupus);
  auto output_thread = std::thread(output_loop, &isActive, lupus);

  // wait for user input and exit
	getchar();
	isActive = false;
  input_thread.join();
	output_thread.join();

  delete lupus;

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

  return 0;
}

void input_loop(bool* isActive, construction::Lupus *lupus)
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
            lupus->setDirection(event->value / magic_value);
            break;
          case 5:
            lupus->setPower(event->value / (magic_value*2) + 0.5f);
            break;
        }
      }
      else if (event->type & JS_EVENT_BUTTON)
      {
        switch (event->number)
        {
          case 5:
            lupus->setPower(-0.2f);
            break;
        }
      }
    }
  }
}

void output_loop(bool* isActive, construction::Lupus *lupus)
{
  while (*isActive)
  {
    std::cout << "Power: " << lupus->getPower() << std::endl;
    std::cout << "Direction: " << lupus->getDirection() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
