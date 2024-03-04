#include "aquisition/MeasurementToCsvWriter.hpp"

MeasurementToCsvWriter::MeasurementToCsvWriter(const std::string &fileName)
{
    fs.open(fileName, std::fstream::out);
}
void MeasurementToCsvWriter::handle(const Device::Measurement &meas)
{
    fs << meas.timestamp << ", " << meas.pose.x << ", " << meas.pose.y << ", "
       << meas.pose.z << ", " << meas.pose.s << ", " << meas.accelerations.x
       << ", " << meas.accelerations.y << ", " << meas.accelerations.z << ", "
       << meas.accelerations.a << ", " << meas.accelerations.b << ", "
       << meas.accelerations.c << std::endl;
}

MeasurementToCsvWriter::~MeasurementToCsvWriter() { fs.close(); }
