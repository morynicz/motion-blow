#include "RTIMULib.h"
#include <fstream>

std::ostream &operator<<(std::ostream &stream, const RTVector3 &vector)
{
	stream<<vector.x()<<" "<<vector.y()<<" "<<vector.z();
	return stream;
}

int main(int argc, char **argv)
{
	RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

	RTIMU *imu = RTIMU::createIMU(settings);

	imu->IMUInit();

	imu->setSlerpPower(0.02);
	imu->setGyroEnable(true);
	imu->setAccelEnable(true);
	imu->setCompassEnable(true);

    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

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
    		fs << imuData.timestamp << " " << imuData.fusionPose << " " << imuData.accel<< "\n";
    	}

    }
    fs << "];";
    fs.close();

}
