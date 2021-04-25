#include "utils.h"
#include "consts.h"
#include "core/arduino_header.h"

void clearBoard(BoardDriver &driver) {
  for (int i = 0; i < X_DIM * Y_DIM; ++i) {
    driver.setPixelColor(i, BUTTON_OFF);
  }
}

uint32_t adjustBrightness(uint32_t color, float ratio) {
  if (ratio == 0) {
    return color;
  }

  uint8_t red = color >> 16;
  uint8_t green = color >> 8;
  uint8_t blue = color;
  red = red * ratio;
  green = green * ratio;
  blue = blue * ratio;
  uint32_t finalColor = red;
  finalColor <<= 8;
  finalColor |= green;
  finalColor <<= 8;
  finalColor |= blue;
  return finalColor;
}

uint32_t Wheel(uint8_t WheelPos) {
  if (WheelPos < 85) {
    return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

std::pair<int, int> index_to_coordinates(int index) {
  int x = index % X_DIM;
  int y = index / X_DIM;

  return std::make_pair(x, y);
}

int coordinates_distance(std::pair<int, int> t, std::pair<int, int> h) {
  return abs(t.second - h.second) + abs(t.first - h.first);
}
