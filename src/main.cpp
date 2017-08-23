#include "pwm_driver.h"
#include "pwm_control_unit.h"
#include "steering_unit.h"
#include "control_unit.h"
#include <chrono>
#include <thread>

#define ADDRESS 0x40
#define FREQUENCY 60
#define RIGHT   +1
#define LEFT    -1

using namespace lupus;

int main()
{
  auto pwmDriver = new pwm::PwmDriver(ADDRESS);
  pwmDriver->setPwmFrequency(FREQUENCY);
  auto controlUnitLeft = new pwm::PwmControlUnit(pwmDriver, 0, 220, 565);
  auto controlUnitRight = new pwm::PwmControlUnit(pwmDriver, 1, 220, 565);
  auto steeringUnitLeft = new navigation::SteeringUnit(controlUnitLeft);
  auto steeringUnitRight = new navigation::SteeringUnit(controlUnitRight);

  for(int i = 0; i < 16; i++) {
    steeringUnitLeft->setDirection(LEFT);
    steeringUnitRight->setDirection(LEFT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    steeringUnitLeft->setDirection(RIGHT);
    steeringUnitRight->setDirection(RIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  delete steeringUnitLeft;
  delete steeringUnitRight;
  delete controlUnitLeft;
  delete controlUnitRight;
  delete pwmDriver;

  return 0;
}
