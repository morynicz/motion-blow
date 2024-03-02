
#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>

class TcpConnection;
class TcpServer
{
  public:
    TcpServer(boost::asio::io_context &io_context,
              std::function<std::optional<std::string>()> getDataToSend,
              int port);

  private:
    void startAccept();
    void handleAccept(std::shared_ptr<TcpConnection>,
                      const boost::system::error_code &);

    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::function<std::optional<std::string>()> getDataToSend;
};
