#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include <asio.hpp>

namespace net {

class Channel {
 public:
  Channel();

  bool bind(std::uint16_t port);
  bool is_open() const;

  std::size_t receive(std::span<std::byte> buffer,
                      asio::ip::udp::endpoint& sender);
  std::size_t send(std::span<const std::byte> buffer,
                   const asio::ip::udp::endpoint& destination);

 private:
  asio::io_context io_context_;
  asio::ip::udp::socket socket_;
};

}  // namespace net
