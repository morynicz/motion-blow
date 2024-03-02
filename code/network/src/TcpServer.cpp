#include "network/TcpServer.hpp"
#include <boost/asio.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>

using boost::asio::ip::tcp;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
    struct Blocker
    {
    };

  public:
    static std::shared_ptr<TcpConnection>
    create(boost::asio::io_context &io_context,
           std::function<std::optional<std::string>()> getDataToSend)
    {
        return std::make_shared<TcpConnection>(io_context, getDataToSend,
                                               Blocker{});
    }

    tcp::socket &getSocket() { return socket; }

    void start()
    {
        while (auto msg = getDataToSend())
        {
            std::cout << msg->size() << "to send " << std::endl;
            boost::asio::async_write(
                socket, boost::asio::buffer(*msg),
                std::bind(&TcpConnection::handleWrite, shared_from_this(),
                          std::placeholders::_1, std::placeholders::_2));
        }
    }

    TcpConnection(boost::asio::io_context &io_context,
                  std::function<std::optional<std::string>()> getDataToSend,
                  Blocker)
        : socket(io_context), getDataToSend(getDataToSend)
    {
    }

  private:
    void handleWrite(const boost::system::error_code &error, size_t transferred)
    {
        std::cout << transferred << " transferred" << std::endl;
        if (error.failed())
        {
            std::cerr << "Failure " << error << ": " << error.message()
                      << std::endl;
        }
    }

    tcp::socket socket;
    std::function<std::optional<std::string>()> getDataToSend;
};

TcpServer::TcpServer(boost::asio::io_context &io_context,
                     std::function<std::optional<std::string>()> getDataToSend,
                     int port)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      getDataToSend(getDataToSend)
{
    startAccept();
}

void TcpServer::startAccept()
{
    auto newConnection = TcpConnection::create(io_context_, getDataToSend);

    acceptor_.async_accept(newConnection->getSocket(),
                           std::bind(&TcpServer::handleAccept, this,
                                     newConnection, std::placeholders::_1));
}

void TcpServer::handleAccept(std::shared_ptr<TcpConnection> newConnection,
                             const boost::system::error_code &error)
{
    if (!error)
    {
        newConnection->start();
    }

    startAccept();
}
