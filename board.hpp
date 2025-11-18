#ifndef OBS_BOARD_HPP
#define OBS_BOARD_HPP

#include <tuple>
#include <unordered_map>
#include <vector>

#include "player.hpp"

namespace obs {

#define OBS_BOARD_SIZE_X 25
#define OBS_BOARD_SIZE_Y 25
#define OBS_BOARD_SIZE_Z 25

class asset;

template <typename T, T X, T Y, T Z> class _board {
private:
  using _ctype = int;

public:
  using coordinate = std::tuple<T, T, T>;

  struct chash {
    size_t operator()(const coordinate &c) { return 0; }
  };

private:
  std::unordered_map<coordinate, std::vector<asset>, chash> assets = {};

  std::array<std::array<T, X>, Y> collision_map = {{0}};
};

using board = _board<int, OBS_BOARD_SIZE_X, OBS_BOARD_SIZE_Y, OBS_BOARD_SIZE_Z>;

} // namespace obs

#endif
