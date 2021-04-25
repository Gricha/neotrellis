#include "colorful_impulses.h"
#include "../consts.h"

#include <algorithm>
#include <random>

ColorfulImpulses::ColorfulImpulses() {}

void ColorfulImpulses::loop(BoardDriver &driver) {
  // Happens every 20ms

  uint32_t recommendedColors[X_DIM][Y_DIM];
  for (int x = 0; x < X_DIM; ++x) {
    for (int y = 0; y < Y_DIM; ++y) {
      auto index = y * X_DIM + x;
      auto c = Wheel(map(index, 0, X_DIM * Y_DIM, 0, 255));
      recommendedColors[x][y] = adjustBrightness(c, 0.1);
    }
  }

  for (auto it = impulses.begin(); it != impulses.end(); ++it) {
    auto center = (*it).center;
    auto color = (*it).color;
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist = coordinates_distance(center, std::make_pair(x, y));
        if (dist == (*it).currentStep) {
          recommendedColors[x][y] = color;
        }
      }
    }
    it->currentStep += 1;
  }

  // Removes finished elements
  if (impulses.size() > 0) {
    for (auto it = impulses.begin(); it != impulses.end();) {
      if ((*it).currentStep > (*it).numberOfSteps) {
        it = impulses.erase(it);
      } else {
        ++it;
      }
    }
  }

  for (int x = 0; x < X_DIM; ++x) {
    for (int y = 0; y < Y_DIM; ++y) {
      driver.setPixelColor(x, y, recommendedColors[x][y]);
    }
  }
  driver.show();
}

void ColorfulImpulses::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    auto center = index_to_coordinates(event.bit.NUM);
    auto c = Wheel(map(event.bit.NUM, 0, X_DIM * Y_DIM, 0, 255));
    uint32_t color = adjustBrightness(c, 0.3);
    int numberOfStepsX = max(center.first, X_DIM - center.first - 1);
    int numberOfStepsY = max(center.second, Y_DIM - center.second - 1);
    int numberOfSteps = numberOfStepsX + numberOfStepsY + 1;

    impulses.push_back({
        .center = center,
        .numberOfSteps = numberOfSteps,
        .currentStep = 0,
        .color = color,
    });
  }
}