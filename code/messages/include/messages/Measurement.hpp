#pragma once
#include <cstdint>
#include <iosfwd>

namespace messages
{
struct Measurement
{
    const uint64_t timestamp;
    struct Pose
    {
        const double x;
        const double y;
        const double z;
        const double s;
    } pose;
    struct Accelerations
    {
        const double x;
        const double y;
        const double z;
        const double a;
        const double b;
        const double c;
    } accelerations;
    std::string serialize() const;
    static Measurement deserialize(const std::string &);
    friend std::ostream &operator<<(std::ostream &os, const Measurement &in);
};
} // namespace messages