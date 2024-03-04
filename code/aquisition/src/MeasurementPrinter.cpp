#include "aquisition/MeasurementPrinter.hpp"
#include <iostream>

void MeasurementPrinter::handle(const Device::Measurement &meas)
{
    std::cout << meas << std::endl;
}
