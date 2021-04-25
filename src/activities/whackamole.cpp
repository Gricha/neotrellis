#include "whackamole.h"
#include "../consts.h"

void Whackamole::generateNewTarget() {
  std::uniform_int_distribution<int> xCoordinateRandomizer(1, X_DIM - 2);
  std::uniform_int_distribution<int> yCoordinateRandomizer(1, Y_DIM - 2);
  auto x = xCoordinateRandomizer(randomnessGenerator);
  auto y = yCoordinateRandomizer(randomnessGenerator);
  currentTarget = {x, y};
}

Whackamole::Whackamole(TimeInterval expectedWaitDuration,
                       TimeInterval expectedButtonDuration)
    : successfulHits(0), waitPeriodStart(millis()), buttonShownStart(millis()),
      targetValid(false), waitDuration(expectedWaitDuration),
      buttonDuration(expectedButtonDuration) {
  randomSeed(millis());
  auto seed = random();
  std::seed_seq seedSequence = {seed};
  randomnessGenerator = std::mt19937(seedSequence);

  generateNewTarget();
}

void Whackamole::loop(BoardDriver &driver) {
  auto now = millis();
  if (!targetValid) {
    if (now - waitPeriodStart > waitDuration) {
      targetValid = true;
      buttonShownStart = now;
      redraw(driver);
    }
  } else {
    if (now - buttonShownStart > buttonDuration) {
      targetValid = false;
      waitPeriodStart = now;
      generateNewTarget();
      redraw(driver);
    }
  }
}

static uint32_t target_color(int numberOfHits) {
  return adjustBrightness(Wheel(map(numberOfHits, 0, 10, 100, 255)), 0.3);
}

void Whackamole::redraw(BoardDriver &driver) {
  clearBoard(driver);
  if (targetValid) {
    driver.setPixelColor(currentTarget.first, currentTarget.second,
                         target_color(successfulHits));
  }

  for (int x = 0; x < X_DIM; ++x) {
    for (int y = 0; y < Y_DIM; ++y) {
      if (x == 0 || x == X_DIM - 1 || y == 0 || y == Y_DIM - 1) {
        driver.setPixelColor(x, y, 0x222222);
      }
    }
  }
  driver.show();
}

static void splash_screen(BoardDriver &driver, Coordinates centerCoordinates,
                          uint32_t primeColor, TimeInterval stepInterval) {

  int numberOfStepsX =
      max(centerCoordinates.first, X_DIM - centerCoordinates.first - 1);
  int numberOfStepsY =
      max(centerCoordinates.second, Y_DIM - centerCoordinates.second - 1);
  int numberOfSteps = numberOfStepsX + numberOfStepsY + 1;

  uint32_t colorsByDistance[4] = {
      adjustBrightness(primeColor, 0.3),
      adjustBrightness(primeColor, 0.15),
      adjustBrightness(primeColor, 0.05),
      adjustBrightness(primeColor, 0.02),
  };
  for (int i = 0; i < numberOfSteps; ++i) {
    // for each coordinate calculate its distance
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist =
            coordinates_distance(centerCoordinates, std::make_pair(x, y));
        if (dist == (i + 1)) {
          // if (x != 0 && x != X_DIM - 1 && y != 0 && y != Y_DIM - 1) {
          driver.setPixelColor(x, y, primeColor);
          // }
        } else {
          if (x != 0 && y != 0 && x != X_DIM - 1 && y != Y_DIM - 1) {
            driver.setPixelColor(x, y, BUTTON_OFF);
          } else {
            driver.setPixelColor(x, y, 0x222222);
          }
        }
      }
    }

    driver.show();
    delay(stepInterval);
  }
  delay(200);
}

void Whackamole::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    if (!targetValid) {
      return;
    }

    auto coordinates = index_to_coordinates(event.bit.NUM);
    if (currentTarget == coordinates) {
      // We've got a hit
      auto targetColor =
          target_color(successfulHits); // taking before increment
      successfulHits += 1;
      splash_screen(driver, currentTarget, targetColor, 20);
      if (successfulHits == 10) {
        driver.finishActivity();
        return;
      } else {
        generateNewTarget();
        targetValid = false;
        waitPeriodStart = millis();
      }
    }
  }
}