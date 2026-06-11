#include "sim/snapshot.h"

namespace sim {

SnapshotWriter::SnapshotWriter(std::span<std::byte> buffer) : writer_(buffer) {}

bool SnapshotWriter::write_bytes(std::span<const std::byte> bytes) {
  return writer_.write_bytes(bytes);
}

std::size_t SnapshotWriter::bytes_written() const {
  return writer_.bytes_written();
}

std::size_t SnapshotWriter::bytes_remaining() const {
  return writer_.bytes_remaining();
}

SnapshotReader::SnapshotReader(std::span<const std::byte> buffer)
    : reader_(buffer) {}

bool SnapshotReader::read_bytes(std::span<std::byte> bytes) {
  return reader_.read_bytes(bytes);
}

std::size_t SnapshotReader::bytes_read() const {
  return reader_.bytes_read();
}

std::size_t SnapshotReader::bytes_remaining() const {
  return reader_.bytes_remaining();
}

}  // namespace sim
