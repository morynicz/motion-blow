#include <utility> //Boost is buggy

#include "messages/Measurement.hpp"
#include "network/TcpServer.hpp"
#include <boost/asio.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    std::list<messages::Measurement> buffer{
        {1234, 11.1, 12.1, 13.3, 14.4, 15.5, 16.6, 17.7},
        {5678, 21.1, 22.1, 23.3, 24.4, 25.5, 26.6, 27.7},
        {9012, 31.1, 32.1, 33.3, 34.4, 35.5, 36.6, 37.7}};

    int count = 0;
    try
    {
        boost::asio::io_context io_context;
        TcpServer server(
            io_context,
            [&buffer]() -> std::optional<std::string>
            {
                while (not buffer.empty())
                {
                    auto measurement = buffer.front();
                    buffer.pop_front();
                    return measurement.serialize();
                }
                return std::nullopt;
            },
            9219);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
