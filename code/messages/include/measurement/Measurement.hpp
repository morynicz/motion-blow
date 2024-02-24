#pragma once
#include <iosfwd>

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

