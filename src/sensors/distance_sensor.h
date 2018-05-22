#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

namespace lupus::sensors
{

class IDistanceSensor
{
  public:
    virtual ~IDistanceSensor() = default;
    virtual int getDistance() = 0;
    virtual int getAccuracy() = 0;
    virtual float getAngle() = 0;
    virtual int getRange() = 0;

    const static int DistanceUnknown = -2;
    const static int DistanceOutOfRange = -1;
};

} // namespace lupus::sensors

#endif /* DISTANCE__SENSOR_H */
