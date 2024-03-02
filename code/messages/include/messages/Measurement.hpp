#pragma once
#include <iosfwd>
#include <cstdint>

namespace messages
{
struct Measurement
{
    const uint64_t timestamp;
    const double qx;
    const double qy;
    const double qz;
    const double qs;
    const double x;
    const double y;
    const double z;

    std::string serialize() const;
    static Measurement deserialize(const std::string&);
    friend std::ostream& operator<<(std::ostream& os, const Measurement& in);
};
} // namespace messages