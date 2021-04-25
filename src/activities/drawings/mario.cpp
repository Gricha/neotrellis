#include "mario.h"

#include "../../consts.h"
#include "../../core/arduino_header.h"
#include "../../utils.h"
#include <vector>

Drawing mario() {
  uint32_t marioClothes = adjustBrightness(0xfa3802, 0.6);
  uint32_t marioHair = adjustBrightness(0xac7c00, 0.6);
  uint32_t marioSkin = adjustBrightness(0xfca244, 0.6);

  // clang-format off
  std::vector<std::vector<int>> displayMap = {
    {0, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 3, 2, 3, 3, 0},
    {2, 3, 2, 3, 3, 2, 3, 3},
    {0, 3, 3, 3, 2, 2, 2, 0},
    {0, 2, 1, 2, 1, 2, 0, 0},
    {3, 1, 3, 1, 3, 1, 3, 0},
    {0, 1, 1, 0, 1, 1, 0, 0},
    };
  // clang-format on

  return Drawing(displayMap, {BUTTON_OFF, marioClothes, marioHair, marioSkin});
}