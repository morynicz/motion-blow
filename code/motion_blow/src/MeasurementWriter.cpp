#include "motion_blow/MeasurementWriter.hpp"

MeasurementWriter::MeasurementWriter(const std::string &fileName)
{
    fs.open("output.m", std::fstream::out);
    fs << "[\n";
}
void MeasurementWriter::handle(const Device::Measurement &meas)
{
    fs << meas << std::endl;
}

MeasurementWriter::~MeasurementWriter()
{
    fs << "];";
    fs.close();
}
