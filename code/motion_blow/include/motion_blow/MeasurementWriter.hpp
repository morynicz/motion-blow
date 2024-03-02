#pragma once
#include "motion_blow/MeasurementHandler.hpp"
#include <fstream>

class MeasurementWriter : public MeasurementHandler
{
  public:
    MeasurementWriter(const std::string &fileName);
    void handle(const Device::Measurement &meas) override;
    ~MeasurementWriter();

  private:
    std::fstream fs;
};