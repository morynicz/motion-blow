#include "motion_blow/Device.hpp"
#include <ostream>

std::ostream &operator<<(std::ostream &os,
                         const Device::Measurement &measurement)
{
    return os << measurement.timestamp << " " << measurement.qx << " "
              << measurement.qy << " " << measurement.qz << " "
              << measurement.qs << " " << measurement.x << " " << measurement.y
              << " " << measurement.z;
}
