#pragma once
#include <iosfwd>
#include <cstdint>

class RTIMUSettings;
class RTIMU;

class Device
{
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

    friend std::ostream &operator<<(std::ostream &, const Measurement &);

  public:
    Device(const std::string &);
    int getPollIntervalMs() const;
    bool readMeasurement();
    Measurement getLastMeasurement() const;
    ~Device();

  private:
    RTIMUSettings *settings;
    RTIMU *imu;
};