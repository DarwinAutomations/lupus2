#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

namespace lupus::sensors
{

enum DistanceSensor
{
  FrontLeft,
  FrontCenterLeft,
  FrontCenterRight,
  FrontRight,
  BackLeft,
  BackCenterLeft,
  BackCenterRight,
  BackRight
};

class IDistanceSensor
{
public:
  virtual ~IDistanceSensor() = default;
  virtual float getDistance() = 0;
  virtual float getAccuracy() = 0;
  virtual float getAngle() = 0;
  virtual float getRangeStart() = 0;
  virtual float getRangeEnd() = 0;

  const static int DistanceUnknown = -2;
  const static int DistanceOutOfRange = -1;
};

} // namespace lupus::sensors

#endif /* DISTANCE__SENSOR_H */
