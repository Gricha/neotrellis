
#include "intro.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

void intro(Adafruit_MultiTrellis &trellis) {
  const int boardSize = Y_DIM * X_DIM;
  const int numberOfPasses = 3;
  const int passModifier = 255 / numberOfPasses;
  for (int j = 0; j < numberOfPasses; ++j) {
    const int passModifierForLoop = j * passModifier;
    for (int i = 0; i < boardSize; i++) {
      const int positionOnTheColorWheel = (i + passModifierForLoop) % boardSize;
      trellis.setPixelColor(
          i, adjustBrightness(
                 Wheel(map(positionOnTheColorWheel, 0, boardSize, 0, 255)),
                 0.1)); // addressed with keynum
      trellis.show();
      delay(TRELLIS_INTERVAL_MS);
    }
  }

  for (int y = 0; y < Y_DIM; y++) {
    for (int x = 0; x < X_DIM; x++) {
      trellis.setPixelColor(x, y, BUTTON_OFF); // addressed with x,y
      trellis.show();                          // show all LEDs
      delay(TRELLIS_INTERVAL_MS);
    }
  }
}

std::vector<int> getRandomVectorOfSize(int size) {
  std::vector<int> v;

  // set some values:
  for (int i = 0; i < size; ++i) {
    v.push_back(i);
  }

  // using built-in random generator:
  auto seed = random();
  std::seed_seq seed_sequence = {seed};
  std::mt19937 g(seed_sequence);

  std::shuffle(v.begin(), v.end(), g);
  return v;
}

void randomized_intro(BoardDriver &driver) {
  const int boardSize = Y_DIM * X_DIM;
  const int numberOfPasses = 3;
  const int passModifier = 255 / numberOfPasses;
  const std::vector<int> randomVector = getRandomVectorOfSize(boardSize);
  for (int j = 0; j < numberOfPasses; ++j) {
    const int passModifierForLoop = j * passModifier;
    for (int i = 0; i < boardSize; i++) {
      int actualPosition = randomVector[i];
      const int positionOnTheColorWheel =
          (actualPosition + passModifierForLoop) % boardSize;
      driver.setPixelColor(actualPosition,
                           adjustBrightness(Wheel(map(positionOnTheColorWheel,
                                                      0, boardSize, 0, 255)),
                                            0.1)); // addressed with keynum
      driver.show();
      delay(TRELLIS_INTERVAL_MS);
    }
  }

  for (int i = 0; i < boardSize; i++) {
    int actualPosition = randomVector[i];
    driver.setPixelColor(actualPosition, BUTTON_OFF);
    driver.show();
    delay(TRELLIS_INTERVAL_MS);
  }
}
