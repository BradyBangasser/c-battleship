#include "../asset.hpp"

namespace obs::assets {
class battleship : public obs::assets::asset {
private:
  static constexpr std::array<std::array<obs::assets::shape_t, 5>, 1> _shape = {
      {{{1, 1, 1, 1, 1}}}};

public:
  virtual shape_view_t shape() { return shape_view_t(_shape); }
};
} // namespace obs::assets
