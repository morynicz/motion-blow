#pragma once
#include "motion_blow/MeasurementHandler.hpp"
#include <fstream>

class MeasurementToJsonWriter : public MeasurementHandler
{
  public:
    MeasurementToJsonWriter(const std::string &fileName);
    void handle(const Device::Measurement &meas) override;
    ~MeasurementToJsonWriter();

  private:
    std::fstream fs;
};