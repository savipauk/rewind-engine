#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

#include "common/byte_buffer.h"

namespace sim {

struct Snapshot {
  std::uint64_t tick{0};
  std::vector<std::byte> bytes;
};

class SnapshotWriter {
 public:
  explicit SnapshotWriter(std::span<std::byte> buffer);

  bool write_bytes(std::span<const std::byte> bytes);

  template <typename T>
  bool write_pod(const T& value) {
    return writer_.write_pod(value);
  }

  std::size_t bytes_written() const;
  std::size_t bytes_remaining() const;

 private:
  common::ByteWriter writer_;
};

class SnapshotReader {
 public:
  explicit SnapshotReader(std::span<const std::byte> buffer);

  bool read_bytes(std::span<std::byte> bytes);

  template <typename T>
  bool read_pod(T& value) {
    return reader_.read_pod(value);
  }

  std::size_t bytes_read() const;
  std::size_t bytes_remaining() const;

 private:
  common::ByteReader reader_;
};

}  // namespace sim
