#include "common/byte_buffer.h"

#include <cstring>

namespace common {

ByteWriter::ByteWriter(std::span<std::byte> buffer) : buffer_(buffer) {}

bool ByteWriter::write_bytes(std::span<const std::byte> bytes) {
  if (bytes.size() > bytes_remaining()) {
    return false;
  }

  std::memcpy(buffer_.data() + cursor_, bytes.data(), bytes.size());
  cursor_ += bytes.size();
  return true;
}

std::size_t ByteWriter::bytes_written() const {
  return cursor_;
}

std::size_t ByteWriter::bytes_remaining() const {
  return buffer_.size() - cursor_;
}

ByteReader::ByteReader(std::span<const std::byte> buffer) : buffer_(buffer) {}

bool ByteReader::read_bytes(std::span<std::byte> bytes) {
  if (bytes.size() > bytes_remaining()) {
    return false;
  }

  std::memcpy(bytes.data(), buffer_.data() + cursor_, bytes.size());
  cursor_ += bytes.size();
  return true;
}

std::size_t ByteReader::bytes_read() const {
  return cursor_;
}

std::size_t ByteReader::bytes_remaining() const {
  return buffer_.size() - cursor_;
}

}  // namespace common
