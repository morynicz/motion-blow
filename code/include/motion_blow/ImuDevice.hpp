#pragma once
#include <iosfwd>
#include <cstdint>
#include "motion_blow/Device.hpp"

class RTIMUSettings;
class RTIMU;

class ImuDevice: public Device
{
  public:
    ImuDevice(const std::string &);
    int getPollIntervalMs() const override;
    bool readMeasurement() override;
    Measurement getLastMeasurement() const override;
    ~ImuDevice();

  private:
    RTIMUSettings *settings;
    RTIMU *imu;
    friend std::ostream &operator<<(std::ostream &, const Measurement &);
};