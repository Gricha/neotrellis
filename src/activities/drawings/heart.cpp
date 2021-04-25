#include "heart.h"

#include "../../consts.h"
#include "../../core/arduino_header.h"
#include "../../utils.h"
#include <vector>

Drawing heart() {
  uint32_t heartColor = adjustBrightness(0xFF6347, 0.2);

  // clang-format off
  std::vector<std::vector<int>> displayMap = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    };
  // clang-format on

  return Drawing(displayMap, {BUTTON_OFF, heartColor});
}