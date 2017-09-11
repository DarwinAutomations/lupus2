#include "pwm_driver.h"
#include "pwm_control_unit.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include <chrono>
#include <thread>

const int address   = 0x40;
const int frequency = 60;

using namespace lupus;

int main()
{
  auto pwmDriver = new pwm::PwmDriver(address);
  pwmDriver->setPwmFrequency(frequency);

  // navigation units:
  // navigation unit left:
  auto controlUnitLeft =
    new pwm::PwmControlUnit(pwmDriver, 0, 220, 565);
  auto steeringUnitLeft =
    new navigation::SteeringUnit(controlUnitLeft);

  // navigation unit right:
  auto controlUnitRight =
    new pwm::PwmControlUnit(pwmDriver, 1, 220, 565);
  auto steeringUnitRight =
    new navigation::SteeringUnit(controlUnitRight);


  // propulsion units:
  // propulsion unit front left:
  auto cuPropulsionFrontLeft =
    new pwm::PwmControlUnit(pwmDriver, 4, 240, 460);
  auto propulsionUnitFrontLeft =
    new navigation::PropulsionUnit(cuPropulsionFrontLeft);

  // propulsion unit front right:
  auto cuPropulsionFrontRight =
    new pwm::PwmControlUnit(pwmDriver, 5, 240, 460);
  auto propulsionUnitFrontRight =
    new navigation::PropulsionUnit(cuPropulsionFrontRight);

  // propulsion unit back left:
  auto cuPropulsionBackLeft =
    new pwm::PwmControlUnit(pwmDriver, 6, 240, 460);
  auto propulsionUnitBackLeft =
    new navigation::PropulsionUnit(cuPropulsionBackLeft);

  // propulsion unit back right:
  auto cuPropulsionBackRight =
    new pwm::PwmControlUnit(pwmDriver, 7, 240, 460);
  auto propulsionUnitBackRight =
    new navigation::PropulsionUnit(cuPropulsionBackRight);

  for(int i = 0; i < 16; i++) {
    steeringUnitLeft->setDirection(-1);
    steeringUnitRight->setDirection(-1);
    propulsionUnitFrontLeft->setPower(0.1);
    propulsionUnitFrontRight->setPower(0.1);
    propulsionUnitBackLeft->setPower(0.1);
    propulsionUnitBackRight->setPower(0.1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    steeringUnitLeft->setDirection(0);
    steeringUnitRight->setDirection(0);
    propulsionUnitFrontLeft->setPower(0);
    propulsionUnitFrontRight->setPower(0);
    propulsionUnitBackLeft->setPower(0);
    propulsionUnitBackRight->setPower(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    steeringUnitLeft->setDirection(1);
    steeringUnitRight->setDirection(1);
    propulsionUnitFrontLeft->setPower(-0.1);
    propulsionUnitFrontRight->setPower(-0.1);
    propulsionUnitBackLeft->setPower(-0.1);
    propulsionUnitBackRight->setPower(-0.1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    steeringUnitLeft->setDirection(0);
    steeringUnitRight->setDirection(0);
    propulsionUnitFrontLeft->setPower(0);
    propulsionUnitFrontRight->setPower(0);
    propulsionUnitBackLeft->setPower(0);
    propulsionUnitBackRight->setPower(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

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

  delete pwmDriver;

  return 0;
}
