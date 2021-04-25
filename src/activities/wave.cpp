#include "wave.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

using CellMatrix = std::vector<std::vector<uint32_t>>;

#define WAVE_RADIUS 5

void wave(BoardDriver &driver) {
  CellMatrix matrix;
  for (int i = 0; i < X_DIM; ++i) {
    std::vector<uint32_t> newVector;
    for (int j = 0; j < Y_DIM; ++j) {
      newVector.push_back(BUTTON_OFF);
    }
    matrix.push_back(newVector);
  }

  float brightnessCoefficient = 0.2;
  uint32_t colors[5] = {
      adjustBrightness(0x045c84, 0.3),  adjustBrightness(0x045c84, 0.1),
      adjustBrightness(0x045c84, 0.08), adjustBrightness(0x045c84, 0.03),
      adjustBrightness(0x045c84, 0.01),
  };

  // pre-init
  for (int i = 0; i < WAVE_RADIUS; ++i) {
    uint32_t color = colors[i]; // reverse at first

    for (int j = 0; j < Y_DIM; ++j) {
      matrix[i][j] = color;
    }
  }

  unsigned long animationDurationMs = 8000;
  unsigned long currentTimestamp = millis();

  int spinePosition = 0;
  while (millis() - currentTimestamp <= animationDurationMs) {

    // First clear up board
    for (int i = 0; i < X_DIM; ++i) {
      for (int j = 0; j < Y_DIM; ++j) {
        driver.setPixelColor(i, j, BUTTON_OFF);
      }
    }

    for (int i = 0; i < WAVE_RADIUS; ++i) {
      uint32_t color = colors[i];

      for (int j = 0; j < Y_DIM; ++j) {
        int leftPos = (Y_DIM + spinePosition - i) % Y_DIM;
        int rightPos = (spinePosition + i) % Y_DIM;
        if (leftPos >= 0) {
          matrix[leftPos][j] = color;
          driver.setPixelColor(leftPos, j, color);
        }
        if (rightPos < Y_DIM) {
          matrix[rightPos][j] = color;
          driver.setPixelColor(rightPos, j, color);
        }
      }
    }

    spinePosition += 1;
    if (spinePosition >= X_DIM) {
      spinePosition = 0;
    }

    driver.show();
    delay(20);
  }
}