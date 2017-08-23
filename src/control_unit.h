#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

namespace lupus
{

class IControlUnit {
  public:
    virtual ~IControlUnit() = default;
    virtual void setPower(float power) = 0;
};

} // namespace lupus

#endif /* CONTROL_UNIT_H */
