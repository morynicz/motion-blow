#pragma once
#include "aquisition/Device.hpp"

class MeasurementHandler
{
  public:
    virtual void handle(const Device::Measurement &) = 0;
    virtual ~MeasurementHandler() = default;
};