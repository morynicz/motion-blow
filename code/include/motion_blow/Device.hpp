#pragma once
#include <iosfwd>
#include <cstdint>


class Device
{
  public:
    struct Measurement
    {
        uint64_t timestamp;
        double qx;
        double qy;
        double qz;
        double qs;
        double x;
        double y;
        double z;
    };

    virtual int getPollIntervalMs() const = 0;
    virtual bool readMeasurement() = 0;
    virtual Measurement getLastMeasurement() const = 0;
    virtual ~Device() = default;
private:
    friend std::ostream &operator<<(std::ostream &, const Measurement &);
};
