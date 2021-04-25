#include "pulsating_effect.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

void PulsatingEffect::refreshConfiguration() {
  auto colorNum = colorScheme.size();

  auto seed = random();
  std::seed_seq seed_sequence = {seed};
  std::mt19937 gen(seed_sequence);
  std::uniform_real_distribution<> dis(configuration.lowBrightness,
                                       configuration.highBrightness);
  std::uniform_int_distribution<int> colorDis(
      0, colorNum - 1); // distribution is inclusive
  std::uniform_real_distribution<> grw(configuration.lowIncrement,
                                       configuration.highIncrement);
  std::bernoulli_distribution d(0.5);

  CellMatrix newMatrix;
  for (int i = 0; i < X_DIM; ++i) {
    std::vector<CellState> newVector;
    for (int j = 0; j < Y_DIM; ++j) {
      float fireBrightness = dis(gen);
      bool fireDirectionGrowing = d(gen);
      float fireIncrement = grw(gen);
      CellGrowthDirection growthDirection;
      if (fireDirectionGrowing) {
        growthDirection = CellGrowthDirection::Up;
      } else {
        growthDirection = CellGrowthDirection::Down;
      }
      uint32_t color = colorScheme[colorDis(gen)];
      newVector.push_back(std::make_tuple(fireBrightness, growthDirection,
                                          fireIncrement, color));
    }

    newMatrix.push_back(newVector);
  }
  matrix = newMatrix;
}

void PulsatingEffect::setColorScheme(std::vector<uint32_t> newColorScheme) {
  colorScheme = newColorScheme;
  refreshConfiguration();
}

void PulsatingEffect::setConfig(PulsationConfiguration config) {
  Serial.println("PulsatingEffect::setConfig");

  Serial.print("lowBrightness ");
  Serial.println(config.lowBrightness);
  Serial.print("highBrightness ");
  Serial.println(config.highBrightness);
  Serial.print("lowIncrement ");
  Serial.println(config.lowIncrement);
  Serial.print("highIncrement ");
  Serial.println(config.highIncrement);
  configuration = config;
  refreshConfiguration();
}

PulsatingEffect::PulsatingEffect() : flatAdjustmentModifier(0.0f) {
  // must call initialize afterwards
}

void PulsatingEffect::initialize(std::vector<uint32_t> desiredColorScheme,
                                 PulsationConfiguration config) {
  /**
   * Each button will start glowing red from small to medium and back.
   * Each one will start at different position in cycle
   * The cycle for each one of the buttons will be the same.
   */

  colorScheme = desiredColorScheme;
  configuration = config;

  refreshConfiguration();
  startTime = millis();
}

void PulsatingEffect::loop(BoardDriver &driver) {
  for (int i = 0; i < X_DIM; ++i) {
    for (int j = 0; j < Y_DIM; ++j) {
      auto value = std::get<0>(matrix[i][j]);
      auto direction = std::get<1>(matrix[i][j]);
      auto increment = std::get<2>(matrix[i][j]);

      if (direction == CellGrowthDirection::Up) {
        value += increment;
        if (value > configuration.highBrightness) {
          std::get<1>(matrix[i][j]) = CellGrowthDirection::Down;
          value = configuration.highBrightness;
        }
      } else {
        value -= increment;
        if (value < configuration.lowBrightness) {
          std::get<1>(matrix[i][j]) = CellGrowthDirection::Up;
          value = configuration.lowBrightness;
        }
      }
      std::get<0>(matrix[i][j]) = value;
      auto color = std::get<3>(matrix[i][j]);

      auto adjustment = min(value + flatAdjustmentModifier, 1.0f);

      driver.setPixelColor(i, j, adjustBrightness(color, adjustment));
    }
  }

  if (shouldEnd(driver)) {
    driver.finishActivity();
  }
}

bool PulsatingEffect::shouldEnd(BoardDriver &driver) {
  auto elapsedTime = millis();
  unsigned long animationDurationMs = 10000; // 10 sec todo config this
  if (elapsedTime - startTime > animationDurationMs) {
    return true;
  }
  return false;
}

void PulsatingEffect::handleEvent(keyEvent event, BoardDriver &driver) {}