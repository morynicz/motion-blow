#include <utility> //boost asio needs this to exist before its include

#include "messages/Measurement.hpp"
#include "motion_blow/Device.hpp"
#include "motion_blow/ImuDevice.hpp"
#include "motion_blow/Queue.hpp"
#include "network/TcpServer.hpp"
#include <boost/program_options.hpp>
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

void runDevice(Queue<Device::Measurement> &queue, std::stop_source stop,
               std::unique_ptr<Device> &&device)
{
    auto stoken = stop.get_token();
    while (not stoken.stop_requested())
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(device->getPollIntervalMs()));

        while (device->readMeasurement())
        {
            auto measurement = device->getLastMeasurement();
            queue.push(measurement);
        }
    }
}

class MeasurementHandler
{
  public:
    virtual void handle(const Device::Measurement &) = 0;
    virtual ~MeasurementHandler() = default;
};

class MeasurementWriter : public MeasurementHandler
{
  public:
    MeasurementWriter(const std::string &fileName)
    {
        fs.open("output.m", std::fstream::out);
        fs << "[\n";
    }
    void handle(const Device::Measurement &meas) { fs << meas << std::endl; }
    ~MeasurementWriter()
    {
        fs << "];";
        fs.close();
    }

  private:
    std::fstream fs;
};

class ServerQueueFeeder : public MeasurementHandler
{
  public:
    ServerQueueFeeder(Queue<Device::Measurement> &serverQueue)
        : serverQueue(serverQueue)
    {
    }
    void handle(const Device::Measurement &meas) override
    {
        serverQueue.push(meas);
    }

  private:
    Queue<Device::Measurement> &serverQueue;
};

void saveToFile(Queue<Device::Measurement> &inputQeue, std::stop_source stop,
                std::vector<std::unique_ptr<MeasurementHandler>> &&handlers)
{
    auto stoken = stop.get_token();

    do
    {
        if (auto measurement = inputQeue.pop())
        {
            for (auto &handler : handlers)
            {
                handler->handle(*measurement);
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } while (not stoken.stop_requested());
}

std::unique_ptr<Device> makeDevice(bool useDummy,
                                   const std::string &calibrationFile)
{
    if (useDummy)
    {
        return std::make_unique<DummyDevice>();
    }
    return std::make_unique<ImuDevice>(calibrationFile);
}

int main(int argc, char **argv)
{
    const std::string defaultCalibrationfile = "RTIMULib";
    const uint defaultBufferSize = 10000;
    std::string calibrationFile;
    std::string outputfile;
    bool useDummy = false;
    int port;
    uint buffSize;

    boost::program_options::options_description desc;
    boost::program_options::variables_map vm;

    desc.add_options()("help,h", "Print this help message and exit")(
        "output,o", boost::program_options::value<std::string>(),
        "output file to save readings locally")(
        "calib,c",
        boost::program_options::value<std::string>(&calibrationFile)
            ->default_value(defaultCalibrationfile),
        "file with calibration settings for the device")(
        "dummy,d", "use dummy device instead of a real one")(
        "port,p", boost::program_options::value<int>(),
        "port for tcp connection")(
        "buffer,b",
        boost::program_options::value<uint>(&buffSize)->default_value(
            defaultBufferSize),
        "buffer size");

    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    std::vector<std::unique_ptr<MeasurementHandler>> handlers;

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("buffer"))
    {
        buffSize = vm["buffer"].as<uint>();
        std::cout << "Buffer: " << buffSize << std::endl;
    }

    Queue<Device::Measurement> inputQueue{buffSize};
    Queue<Device::Measurement> serverQueue{buffSize};

    if (vm.count("output"))
    {
        auto outputFile = vm["output"].as<std::string>();
        std::cout << outputFile << std::endl;
        handlers.push_back(std::make_unique<MeasurementWriter>(outputFile));
    }

    if (vm.count("calib"))
    {
        calibrationFile = vm["calib"].as<std::string>();
        std::cout << calibrationFile << std::endl;
    }

    if (vm.count("dummy"))
    {
        std::cout << "Use dummy" << std::endl;
        useDummy = true;
    }

    boost::asio::io_context io_context;
    std::unique_ptr<std::jthread> serverThread;
    std::unique_ptr<TcpServer> server;
    if (vm.count("port"))
    {
        port = vm["port"].as<int>();
        std::cout << "Port: " << port << std::endl;
        handlers.push_back(std::make_unique<ServerQueueFeeder>(serverQueue));

        server = std::make_unique<TcpServer>(
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
            port);
        serverThread = std::make_unique<std::jthread>([&io_context]()
                                                      { io_context.run(); });
    }

    auto device = makeDevice(useDummy, calibrationFile);

    std::stop_source stop;
    std::jthread devThread{runDevice, std::ref(inputQueue), stop,
                           std::move(device)};
    std::jthread writeThread{saveToFile, std::ref(inputQueue), stop,
                             std::move(handlers)};

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
