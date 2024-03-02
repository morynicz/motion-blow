#pragma once
#include "motion_blow/Device.hpp"

class MeasurementHandler
{
  public:
    virtual void handle(const Device::Measurement &) = 0;
    virtual ~MeasurementHandler() = default;
};