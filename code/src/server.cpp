#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <boost/asio.hpp>
#include <functional>
#include <optional>

using boost::asio::ip::tcp;


std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection
  : public std::enable_shared_from_this<tcp_connection>
{
    struct Blocker{};
public:
  typedef std::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context& io_context, std::function<std::optional<std::string>()> getDataToSend)
  {
    return std::make_shared<tcp_connection>(io_context, getDataToSend, Blocker{});
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    while(auto msg = getDataToSend())
    {
    boost::asio::async_write(socket_, boost::asio::buffer(*msg),
        std::bind(&tcp_connection::handle_write, shared_from_this(),
          std::placeholders::_1,//boost::asio::placeholders::error,
          std::placeholders::_2));//boost::asio::placeholders::bytes_transferred));
    }
  }

  tcp_connection(boost::asio::io_context& io_context, std::function<std::optional<std::string>()> getDataToSend, Blocker)
    : socket_(io_context), getDataToSend(getDataToSend)
  {
  }
private:
  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
  std::function<std::optional<std::string>()> getDataToSend;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_context& io_context, std::function<std::optional<std::string>()> getDataToSend)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), 13)),
      getDataToSend(getDataToSend)
  {
    start_accept();
  }

private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(io_context_, getDataToSend);

    acceptor_.async_accept(new_connection->socket(),
        std::bind(&tcp_server::handle_accept, this, new_connection,
          std::placeholders::_1/*boost::asio::placeholders::error*/));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  boost::asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  std::function<std::optional<std::string>()> getDataToSend;
};

int main()
{
    int count = 0;
  try
  {
    boost::asio::io_context io_context;
    tcp_server server(io_context, [&count]()->std::optional<std::string>{
        if(count++ < 7)
        {
            return make_daytime_string();
        }
        return std::nullopt;
    });
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
