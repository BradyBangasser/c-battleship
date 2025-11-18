#ifndef OBS_PLAYER_HPP
#define OBS_PLAYER_HPP

#include <inttypes.h>

namespace obs {
class player {
public:
  using pid_t = uint32_t;

private:
  static pid_t pid;
};
} // namespace obs

#endif
