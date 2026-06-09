#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <type_traits>

namespace common {

class ByteWriter {
 public:
  explicit ByteWriter(std::span<std::byte> buffer);

  bool write_bytes(std::span<const std::byte> bytes);

  template <typename T>
  bool write_pod(const T& value) {
    static_assert(std::is_trivially_copyable_v<T>);

    return write_bytes(std::span<const std::byte>{
        reinterpret_cast<const std::byte*>(&value), sizeof(T)});
  }

  std::size_t bytes_written() const;
  std::size_t bytes_remaining() const;

 private:
  std::span<std::byte> buffer_;
  std::size_t cursor_{0};
};

class ByteReader {
 public:
  explicit ByteReader(std::span<const std::byte> buffer);

  bool read_bytes(std::span<std::byte> bytes);

  template <typename T>
  bool read_pod(T& value) {
    static_assert(std::is_trivially_copyable_v<T>);

    return read_bytes(std::span<std::byte>{
        reinterpret_cast<std::byte*>(&value), sizeof(T)});
  }

  std::size_t bytes_read() const;
  std::size_t bytes_remaining() const;

 private:
  std::span<const std::byte> buffer_;
  std::size_t cursor_{0};
};

}  // namespace common
