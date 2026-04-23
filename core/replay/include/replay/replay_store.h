#pragma once

#include <cstddef>

namespace replay {

class ReplayStore {
public:
    void clear();
    std::size_t frame_count() const;

private:
    std::size_t frame_count_{0};
};

}  // namespace replay
