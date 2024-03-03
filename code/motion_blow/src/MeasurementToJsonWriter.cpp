#include "motion_blow/MeasurementToJsonWriter.hpp"

MeasurementToJsonWriter::MeasurementToJsonWriter(const std::string &fileName)
{
    fs.open(fileName, std::fstream::out);
    fs << "[\n" << std::endl;
}
void MeasurementToJsonWriter::handle(const Device::Measurement &meas)
{
    fs << "{" << meas << "}," << std::endl;
}

MeasurementToJsonWriter::~MeasurementToJsonWriter()
{
    fs << "]";
    fs.close();
}
