#include "aquisition/Device.hpp"
#include <ostream>

std::ostream &operator<<(std::ostream &os,
                         const Device::Measurement::Pose &pose)
{
    return os << "\"x\": " << pose.x << ", \"y\": " << pose.y
              << ", \"z\": " << pose.z << ", \"s\": " << pose.s;
}

std::ostream &operator<<(std::ostream &os,
                         const Device::Measurement::Accelerations &accel)
{
    return os << "\"x\": " << accel.x << ", \"y\": " << accel.y
              << ", \"z\": " << accel.z << ", \"a\": " << accel.a
              << ", \"b\": " << accel.b << ", \"c\": " << accel.c;
}

std::ostream &operator<<(std::ostream &os,
                         const Device::Measurement &measurement)
{
    return os << "\"ts\": " << measurement.timestamp << ", \"pose\": {"
              << measurement.pose << " },  \"accel\": {"
              << measurement.accelerations << " }";
}
