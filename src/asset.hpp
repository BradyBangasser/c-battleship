#ifndef OBS_ASSET_HPP
#define OBS_ASSET_HPP

#include <array>
#include <tuple>

#include "bstype.hpp"
#include "player.hpp"

#ifndef SHAPE_TYPE_INDEX
#define SHAPE_TYPE_INDEX 0
#endif

namespace obs::assets {

using _shape_l = types::type_list<int8_t, uint8_t, float, double>;
using shape_t = types::type_list_at<SHAPE_TYPE_INDEX, _shape_l>::type;

using shape_view_t = struct shape_view {
  const std::size_t h;
  const std::size_t w;

  const shape_t *const shape;

  constexpr shape_t get(std::size_t x, std::size_t y) const {
    return shape[x * w + y];
  }

  template <std::size_t H, std::size_t W>
  constexpr shape_view(const std::array<std::array<shape_t, W>, H> &shape)
      : h(H), w(W), shape(&shape[0][0]) {}
};

class asset {

public:
  virtual constexpr shape_view_t shape() = 0;
};
} // namespace obs::assets

#endif
