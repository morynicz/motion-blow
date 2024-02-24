#pragma once
#include <iosfwd>

namespace messages
{
struct Measurement
{
    const long timestamp;
    const double qx;
    const double qy;
    const double qz;
    const double qs;
    const double x;
    const double y;
    const double z;
};
} // namespace messages