#include "net/channel.h"

#include <system_error>

namespace net {

Channel::Channel() : socket_(io_context_) {}

bool Channel::bind(std::uint16_t port) {
  std::error_code ec;

  socket_.open(asio::ip::udp::v4(), ec);
  if (ec) {
    return false;
  }

  socket_.set_option(asio::socket_base::reuse_address(true), ec);
  if (ec) {
    return false;
  }

  socket_.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), port), ec);
  return !ec;
}

bool Channel::is_open() const {
  return socket_.is_open();
}

std::size_t Channel::receive(std::span<std::byte> buffer,
                             asio::ip::udp::endpoint& sender) {
  std::error_code ec;
  const std::size_t received = socket_.receive_from(
      asio::buffer(buffer.data(), buffer.size()), sender, 0, ec);
  if (ec) {
    return 0;
  }

  return received;
}

std::size_t Channel::send(std::span<const std::byte> buffer,
                          const asio::ip::udp::endpoint& destination) {
  std::error_code ec;
  const std::size_t sent = socket_.send_to(
      asio::buffer(buffer.data(), buffer.size()), destination, 0, ec);
  if (ec) {
    return 0;
  }

  return sent;
}

}  // namespace net
