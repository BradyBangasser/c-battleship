#ifndef OBS_BOARD_HPP
#define OBS_BOARD_HPP

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "asset.hpp"
#include "player.hpp"

using namespace obs::assets;

namespace obs {

#define OBS_BOARD_SIZE_X 25
#define OBS_BOARD_SIZE_Y 25
#define OBS_BOARD_SIZE_Z 25

template <typename T, T X, T Y, T Z> class _board {
private:
  using _ctype = int;

public:
  using coordinate = std::tuple<T, T, T>;

  struct chash {
    size_t operator()(const coordinate &c) { return 0; }
  };

private:
  using _placed_asset = std::pair<coordinate, std::shared_ptr<asset>>;
  std::vector<_placed_asset> assets;

public:
  std::string to_string() {
    std::array<std::array<char, X>, Y> render_matrix = {'*'};

    for (const _placed_asset &pa : assets) {
      shape_view_t shape = pa.second->shape();
    }

    return "";
  }
};

using board = _board<int, OBS_BOARD_SIZE_X, OBS_BOARD_SIZE_Y, OBS_BOARD_SIZE_Z>;

} // namespace obs

#endif
