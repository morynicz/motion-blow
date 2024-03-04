#pragma once
#include <cstdint>
#include <iosfwd>

class Device
{
  public:
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
    };
    virtual int getPollIntervalMs() const = 0;
    virtual bool readMeasurement() = 0;
    virtual Measurement getLastMeasurement() const = 0;
    virtual ~Device() = default;

  private:
    friend std::ostream &operator<<(std::ostream &,
                                    const Measurement::Accelerations &);
    friend std::ostream &operator<<(std::ostream &, const Measurement::Pose &);
    friend std::ostream &operator<<(std::ostream &, const Measurement &);
};
