#include "messages/Measurement.hpp"
#include <fstream>
#include "motion_blow/Device.hpp"
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    Device device("RTIMULib");

    std::fstream fs;

    fs.open("output.m", std::fstream::out);

    fs << "[\n";
    // rateTimer = RTMath::currentUSecsSinceEpoch();

    for (int i = 0; i < 1000; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(device.getPollIntervalMs()));

        while (device.readMeasurement())
        {
            auto measurement = device.getLastMeasurement();
            fs << measurement << std::endl;
        }
    }
    fs << "];";
    fs.close();
}
