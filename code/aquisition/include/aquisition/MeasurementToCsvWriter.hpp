#pragma once
#include "aquisition/MeasurementHandler.hpp"
#include <fstream>

class MeasurementToCsvWriter : public MeasurementHandler
{
  public:
    MeasurementToCsvWriter(const std::string &fileName);
    void handle(const Device::Measurement &meas) override;
    ~MeasurementToCsvWriter();

  private:
    std::fstream fs;
};