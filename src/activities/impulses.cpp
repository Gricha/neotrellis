#include "impulses.h"
#include "../consts.h"

#include <algorithm>
#include <random>

Impulses::Impulses() {
  randomSeed(millis());
  auto seed = random();
  std::seed_seq seedSequence = {seed};
  randomnessGenerator = std::mt19937(seedSequence);
}

void Impulses::loop(BoardDriver &driver) {
  // Happens every 20ms

  uint32_t recommendedColors[X_DIM][Y_DIM];
  for (int x = 0; x < X_DIM; ++x) {
    for (int y = 0; y < Y_DIM; ++y) {
      recommendedColors[x][y] = BUTTON_OFF;
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

void Impulses::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    std::uniform_int_distribution<int> wheelSelect(0, 255);
    int selected = wheelSelect(randomnessGenerator);
    auto center = index_to_coordinates(event.bit.NUM);
    uint32_t color = adjustBrightness(Wheel(selected), 0.5);
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