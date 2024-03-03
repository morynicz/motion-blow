#include <utility> //boost is buggy

#include "messages/Measurement.hpp"
#include "motion_blow/Device.hpp"
#include "motion_blow/MeasurementPrinter.hpp"
#include "motion_blow/MeasurementToJsonWriter.hpp"
#include <array>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    boost::program_options::options_description desc;
    boost::program_options::variables_map vm;

    std::string host{};
    int port{0};
    std::string outputFile{};

    desc.add_options()("help,h", "Print this help message and exit")(
        "output,o", boost::program_options::value<std::string>(&outputFile),
        "output file to save measurements locally")(
        "server,s", boost::program_options::value<std::string>(&host),
        "server to connect to")("verbose,v", "print measurements to stdout")(
        "port,p", boost::program_options::value<int>(&port),
        "port for tcp connection");

    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    std::vector<std::unique_ptr<MeasurementHandler>> handlers;

    if (not vm.count("server") * vm.count("port"))
    {
        std::cout << "Missing host and port" << std::endl << desc << std::endl;
        return 1;
    }

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("verbose"))
    {
        handlers.push_back(std::make_unique<MeasurementPrinter>());
    }

    if (vm.count("output"))
    {
        handlers.push_back(
            std::make_unique<MeasurementToJsonWriter>(outputFile));
    }

    try
    {

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve(host, std::to_string(port));

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        for (;;)
        {
            std::array<char, 1024> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
            {
                std::cout << "Transmission ended" << std::endl;
                break; // Connection closed cleanly by peer.
            }
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::string interrim(buf.begin(), buf.begin() + len);
            messages::Measurement meas =
                messages::Measurement::deserialize(interrim);

            Device::Measurement m{
                meas.timestamp,
                {meas.pose.x, meas.pose.y, meas.pose.z, meas.pose.s},
                {meas.accelerations.x, meas.accelerations.y,
                 meas.accelerations.z, meas.accelerations.a,
                 meas.accelerations.b, meas.accelerations.c}};

            for (auto &handler : handlers)
            {
                handler->handle(m);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}