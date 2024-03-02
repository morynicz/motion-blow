#include "motion_blow/ImuDevice.hpp"
#include "RTIMULib/RTIMULib.h"
#include <iostream>

ImuDevice::ImuDevice(const std::string &iniFile)
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

int ImuDevice::getPollIntervalMs() const { return imu->IMUGetPollInterval(); }

bool ImuDevice::readMeasurement() { return imu->IMURead(); }

ImuDevice::Measurement ImuDevice::getLastMeasurement() const
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

ImuDevice::~ImuDevice()
{
    delete imu;
    delete settings;
}
