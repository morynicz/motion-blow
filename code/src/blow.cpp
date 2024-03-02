#include <utility> //boost asio needs this to exist before its include

#include "messages/Measurement.hpp"
#include "motion_blow/Device.hpp"
#include "motion_blow/ImuDevice.hpp"
#include "motion_blow/Queue.hpp"
#include "network/TcpServer.hpp"
#include <chrono>
#include <condition_variable>
#include <deque>
#include <fstream>
#include <iostream>
#include <optional>
#include <stop_token>
#include <thread>

class DummyDevice : public Device
{
  public:
    Measurement getLastMeasurement() const override
    {
        return {frameCounter, 0, 0, 0, 0, 0, 0};
    }
    int getPollIntervalMs() const override { return 10; }
    bool readMeasurement() override
    {
        if (read)
        {
            ++frameCounter;
        }
        read = not read;

        return read;
    }

  private:
    bool read{true};
    uint64_t frameCounter{0};
};

void runDevice(Queue<Device::Measurement> &queue, std::stop_source stop)
{
    auto stoken = stop.get_token();
    // auto device = std::make_unique<ImuDevice>("RTIMULib");
    auto device = std::make_unique<DummyDevice>();
    while (not stoken.stop_requested())
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(device->getPollIntervalMs()));

        while (device->readMeasurement())
        {
            auto measurement = device->getLastMeasurement();
            queue.push(measurement);
        }
        std::cout << "dev token " << stoken.stop_requested() << " source "
                  << stop.stop_requested() << " pos " << stop.stop_possible()
                  << std::endl;
    }
}

void saveToFile(Queue<Device::Measurement> &inputQeue,
                Queue<Device::Measurement> &serverQueue, std::stop_source stop)
{
    auto stoken = stop.get_token();
    std::fstream fs;

    fs.open("output.m", std::fstream::out);

    fs << "[\n";

    do
    {
        if (auto measurement = inputQeue.pop())
        {
            serverQueue.push(*measurement);
            fs << *measurement << std::endl;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "wr token " << stoken.stop_requested() << " source "
                  << stop.stop_requested() << " pos " << stop.stop_possible()
                  << std::endl;
    } while (not stoken.stop_requested());
    fs << "];";
    fs.close();
}

int main(int argc, char **argv)
{
    const uint buffSize = 10000;
    Queue<Device::Measurement> inputQueue{10000};
    Queue<Device::Measurement> serverQueue{10000};
    std::stop_source stop;
    std::jthread devThread{runDevice, std::ref(inputQueue), stop};
    std::jthread writeThread{saveToFile, std::ref(inputQueue),
                             std::ref(serverQueue), stop};

    boost::asio::io_context io_context;
    TcpServer server(
        io_context,
        [&serverQueue]() -> std::optional<std::string>
        {
            while (auto meas = serverQueue.pop())
            {
                messages::Measurement measurement{
                    meas->timestamp, meas->qx, meas->qy, meas->qz,
                    meas->qs,        meas->x,  meas->y,  meas->z};
                return measurement.serialize();
            }
            return std::nullopt;
        },
        9219);
    std::jthread serverThread{[&io_context]() { io_context.run(); }};

    char input = '1';
    while (input != 'q')
    {
        std::cout << "q <enter> to quit" << std::endl;
        std::cin >> input;
    }
    std::cout << "Requesting stop" << std::endl;
    stop.request_stop();
    io_context.stop();
}
