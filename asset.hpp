#ifndef OBS_ASSET_HPP
#define OBS_ASSET_HPP

#include <array>
#include <tuple>

#include "player.hpp"

namespace obs::assets {
class asset {
private:
  static constexpr std::pair<uint32_t, uint32_t> cm_s = {25, 25};

public:
  virtual std::array<int, asset::cm_s.first> collision_map();
};
} // namespace obs::assets

#endif
