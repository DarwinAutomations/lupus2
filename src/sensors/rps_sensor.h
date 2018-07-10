#ifndef SENSORS_RPS_SENSOR_H
#define SENSORS_RPS_SENSOR_H

namespace lupus::sensors
{

class IRpsSensor
{
  public:
    virtual ~IRpsSensor() = default;
    virtual float getRps() = 0;
};

} // namespace lupus::sensors

#endif /* SENSORS_RPS_SENSOR_H */
