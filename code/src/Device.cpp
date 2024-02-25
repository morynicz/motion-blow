#include "motion_blow/Device.hpp"
#include "RTIMULib/RTIMULib.h"
#include <iostream>

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

int Device::getPollIntervalMs() const { return imu->IMUGetPollInterval(); }

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