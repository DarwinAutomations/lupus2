#ifndef SENSORS_RPS_SENSOR_H
#define SENSORS_RPS_SENSOR_H

namespace lupus::construction::rpsSensor
{

class IRpsSensor
{
  public:
    virtual ~IRpsSensor() = default;
    virtual float getRps() = 0;
};

}

#endif /* SENSORS_RPS_SENSOR_H */
