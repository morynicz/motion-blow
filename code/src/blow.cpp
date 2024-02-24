#include "RTIMULib/RTIMULib.h"
#include "messages/Measurement.hpp"
#include <fstream>
#include <iostream>
#include <memory>

std::ostream &operator<<(std::ostream &stream, const RTVector3 &vector)
{
    stream << vector.x() << " " << vector.y() << " " << vector.z();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const RTQuaternion &q)
{
    stream << q.scalar() << " " << q.x() << " " << q.y() << " " << q.z();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const RTIMU_DATA &data)
{
    stream << data.fusionQPose << " " << data.accel;
    return stream;
}

class Device
{
    struct Measurement
    {
        unsigned long timestamp;
        double qx;
        double qy;
        double qz;
        double qs;
        double x;
        double y;
        double z;
    };

    friend std::ostream &operator<<(std::ostream &, const Measurement &);

  public:
    Device(const std::string &);
    int getPollInterval() const;
    bool readMeasurement();
    Measurement getLastMeasurement() const;
    ~Device();

  private:
    RTIMUSettings *settings;
    RTIMU *imu;
};

Device::Device(const std::string &iniFile)
{
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
    {
        std::cerr << "No IMU found\n" << std::endl;
        exit(1);
    }

    imu->IMUInit();

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);
}

int Device::getPollInterval() const { return imu->IMUGetPollInterval(); }

bool Device::readMeasurement() { return imu->IMURead(); }

Device::Measurement Device::getLastMeasurement() const
{
    RTIMU_DATA imuData = imu->getIMUData();
    return {imuData.timestamp,
            imuData.fusionQPose.x(),
            imuData.fusionQPose.y(),
            imuData.fusionQPose.z(),
            imuData.fusionQPose.scalar(),
            imuData.accel.x(),
            imuData.accel.y(),
            imuData.accel.z()};
}

Device::~Device()
{
    delete imu;
    delete settings;
}

std::ostream &operator<<(std::ostream &os,
                         const Device::Measurement &measurement)
{
    return os << measurement.timestamp << " " << measurement.qx << " "
              << measurement.qy << " " << measurement.qz << " "
              << measurement.qs << " " << measurement.x << " " << measurement.y
              << " " << measurement.z;
}

int main(int argc, char **argv)
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    // RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    // RTIMU *imu = RTIMU::createIMU(settings);

    // if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
    // {
    //     std::cerr << "No IMU found\n" << std::endl;
    //     exit(1);
    // }

    // imu->IMUInit();

    // imu->setSlerpPower(0.02);
    // imu->setGyroEnable(true);
    // imu->setAccelEnable(true);
    // imu->setCompassEnable(true);

    Device device("RTIMULib");

    std::fstream fs;

    fs.open("output.m", std::fstream::out);

    fs << "[\n";
    // rateTimer = RTMath::currentUSecsSinceEpoch();

    for (int i = 0; i < 1000; ++i)
    {
        usleep(device.getPollInterval() * 1000);

        while (device.readMeasurement())
        {
            auto measurement = device.getLastMeasurement();
            fs << measurement << std::endl;
            // RTIMU_DATA imuData = imu->getIMUData();
            // fs << imuData.timestamp << " " << imuData << std::endl;
        }
    }
    fs << "];";
    fs.close();

    // delete imu;
    // delete settings;
}
