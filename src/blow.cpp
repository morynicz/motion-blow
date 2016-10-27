#include "RTIMULib.h"
#include <fstream>
#include <iostream>

std::ostream &operator<<(std::ostream &stream, const RTVector3 &vector)
{
    stream<<vector.x()<<" "<<vector.y()<<" "<<vector.z();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const RTQuaternion &q)
{
    stream<<q.scalar()<<" "<<q.x()<<" "<<q.y()<<" "<<q.z();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const RTIMU_DATA &data)
{
    stream<<data.fusionQPose<< " " << data.accel;
    return stream;
}

int main(int argc, char **argv)
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    RTIMU *imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
      std::cerr<<"No IMU found\n"<<std::endl;
      exit(1);
    }

    imu->IMUInit();

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    std::fstream fs;

    fs.open("output.m", std::fstream::out);

    fs << "[\n";
    rateTimer = RTMath::currentUSecsSinceEpoch();

    for (int i = 0; i < 1000; ++i)
    {
    	usleep(imu->IMUGetPollInterval() * 1000);

    	while(imu->IMURead())
    	{
	  RTIMU_DATA imuData = imu->getIMUData();
	  fs << imuData.timestamp << " " << imuData << std::endl;
    	}

    }
    fs << "];";
    fs.close();

    delete imu;
    delete settings;
}
