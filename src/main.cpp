#include <iostream>
#include <chrono>
#include <thread>

#include "simulated_control_unit.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include "lupus.h"

using namespace lupus;

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

  for(int i = 0; i < 16; i++) {
    lupus->setDirection(1);
    lupus->setPower(0.1);
    std::cout << "direction: " << lupus->getDirection() << std::endl;
    std::cout << "power: " << lupus->getPower() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lupus->setDirection(0);
    lupus->setPower(0.1);
    std::cout << "direction: " << lupus->getDirection() << std::endl;
    std::cout << "power: " << lupus->getPower() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lupus->setDirection(-1);
    lupus->setPower(-0.1);
    std::cout << "direction: " << lupus->getDirection() << std::endl;
    std::cout << "power: " << lupus->getPower() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lupus->setDirection(0);
    lupus->setPower(0);
    std::cout << "direction: " << lupus->getDirection() << std::endl;
    std::cout << "power: " << lupus->getPower() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
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
