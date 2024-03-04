#pragma once
#include "aquisition/MeasurementHandler.hpp"
#include <iosfwd>

class MeasurementPrinter : public MeasurementHandler
{
  public:
    MeasurementPrinter() = default;
    void handle(const Device::Measurement &meas) override;
    ~MeasurementPrinter() = default;
};