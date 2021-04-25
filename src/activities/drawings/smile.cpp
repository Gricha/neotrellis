#include "smile.h"

#include "../../consts.h"
#include "../../core/arduino_header.h"
#include "../../utils.h"
#include <vector>

Drawing smile() {
  uint32_t smileColor = adjustBrightness(0xffffff, 0.2);
  uint32_t insideColor = adjustBrightness(0xffff00, 0.2);

  // clang-format off
  std::vector<std::vector<int>> displayMap = {
    {0, 0, 2, 2, 2, 2, 0, 0},
    {0, 2, 2, 2, 2, 2, 2, 0},
    {2, 2, 1, 2, 2, 1, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 2, 2, 2, 2, 1, 2},
    {2, 2, 1, 2, 2, 1, 2, 2},
    {0, 2, 2, 1, 1, 2, 2, 0},
    {0, 0, 2, 2, 2, 2, 0, 0},
    };
  // clang-format on

  return Drawing(displayMap, {BUTTON_OFF, smileColor, insideColor});
}