#include "warmer_warmer.h"
#include "../consts.h"
#include "../utils.h"
#include "text.h"

#include <random>

WarmerWarmer::WarmerWarmer() {
  auto seed = random();
  std::seed_seq seed_sequence = {seed};
  std::mt19937 gen(seed_sequence);
  std::uniform_int_distribution<int> indexCoord(0, (X_DIM * Y_DIM) - 1);

  targetIndex = indexCoord(gen);
  numberOfHits = 0;

  for (int i = 0; i < X_DIM * Y_DIM; ++i) {
    hits[i] = false;
  }
}

void WarmerWarmer::loop(BoardDriver &driver) {}

static uint32_t colorsByDistance[5] = {
    0xff0000, 0xff2200, 0xffdd00, 0x00aaff, 0xeeeeff,
};

uint32_t color_for_distance(int distance) {
  if (distance == 0) {
    return adjustBrightness(0xff0000, 0.2);
  } else if (distance < 5) {
    return adjustBrightness(colorsByDistance[distance], 0.2);
  } else {
    return adjustBrightness(colorsByDistance[4], 0.2);
  }
}

void WarmerWarmer::finishingSequence(BoardDriver &driver) {
  driver.show(); // Let the red button be seen for a while
  delay(80);

  auto targetCoordinates = index_to_coordinates(targetIndex);

  int numberOfStepsX =
      max(targetCoordinates.first, X_DIM - targetCoordinates.first - 1);
  int numberOfStepsY =
      max(targetCoordinates.second, Y_DIM - targetCoordinates.second - 1);
  int numberOfSteps = numberOfStepsX + numberOfStepsY;

  for (int i = 0; i < numberOfSteps; ++i) {
    // for each coordinate calculate its distance
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist =
            coordinates_distance(targetCoordinates, std::make_pair(x, y));
        if (dist == (i + 1)) {
          auto color = color_for_distance(dist);
          driver.setPixelColor(x, y, color);
        }
      }
    }

    driver.show();
    delay(80);
  }

  for (int i = 0; i < 5; ++i) {
    // Blink everything
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist =
            coordinates_distance(targetCoordinates, std::make_pair(x, y));
        uint32_t color = color_for_distance(dist);
        if (i % 2 != 0) {
          color = adjustBrightness(color, 0.2);
        }
        driver.setPixelColor(x, y, color);
      }
    }
    driver.show();
    delay(300);
  }

  delay(400);

  driver.finishActivity();
}

void WarmerWarmer::handleEvent(keyEvent event, BoardDriver &driver) {
  Serial.println("WarmerWarmer::handleEvent");
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    Serial.print("WarmerWarmer::handleEvent index ");
    Serial.println(event.bit.NUM);
    if (hits[event.bit.NUM]) {
      return;
    }
    hits[event.bit.NUM] = true;
    numberOfHits += 1;

    auto targetCoordinates = index_to_coordinates(targetIndex);
    auto hitCoordinates = index_to_coordinates(event.bit.NUM);

    auto distance = coordinates_distance(targetCoordinates, hitCoordinates);

    auto color = color_for_distance(distance);
    driver.setPixelColor(event.bit.NUM, color);

    if (distance == 0) {
      finishingSequence(driver);
    }

    driver.show();
  }
}