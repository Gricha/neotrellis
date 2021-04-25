#include "snake.h"

#include "../consts.h"
#include "text.h"

#define INITIAL_GAME_TICK 400

static uint32_t snake_body_color() { return adjustBrightness(0xffffff, 0.4); }
static uint32_t apple_color() { return adjustBrightness(0xff1100, 0.3); }

Snake::Snake() : gameTickInterval(INITIAL_GAME_TICK) {
  auto seed = random();
  std::seed_seq seedSequence = {seed};
  randomnessGenerator = std::mt19937(seedSequence);

  setStartingPosition();
}

Coordinates Snake::coordinateInFrontOfHead() {
  auto head = snakePosition.back(); // back == newest

  Coordinates inFrontOfHead = head;

  switch (snakeDirection) {
  case Direction::left:
    inFrontOfHead.first -= 1;
    if (inFrontOfHead.first < 0) {
      inFrontOfHead.first = X_DIM - 1;
    }
    break;
  case Direction::right:
    inFrontOfHead.first += 1;
    if (inFrontOfHead.first >= X_DIM) {
      inFrontOfHead.first = 0;
    }
    break;
  case Direction::up:
    inFrontOfHead.second -= 1;
    if (inFrontOfHead.second < 0) {
      inFrontOfHead.second = Y_DIM - 1;
    }
    break;
  case Direction::down:
    inFrontOfHead.second += 1;
    if (inFrontOfHead.second >= Y_DIM) {
      inFrontOfHead.second = 0;
    }
    break;
  }

  return inFrontOfHead;
}

Coordinates Snake::generateApplePosition() {
  if (emptyPositions.size() == 0) {
    // Being careful here, ideally this should never be called
    return {0, 0};
  }

  // Takes into account a position of snake and will not place an apple directly
  // in front of it. Unless necessary.
  auto inFrontOfHead = coordinateInFrontOfHead();

  emptyPositions.erase(inFrontOfHead);
  if (emptyPositions.size() == 0) {
    emptyPositions.insert(inFrontOfHead);
  }

  std::uniform_int_distribution<int> coordinateRandomizer(
      0, emptyPositions.size() - 1);
  auto iteratorChoice = coordinateRandomizer(randomnessGenerator);
  auto element = std::next(emptyPositions.begin(), iteratorChoice);

  Serial.print("Empty positions: ");
  Serial.println(emptyPositions.size());
  Serial.println(iteratorChoice);

  emptyPositions.insert(inFrontOfHead);
  Serial.print("Apple Position: ");
  Serial.print((*element).first);
  Serial.print(" ");
  Serial.println((*element).second);

  if ((*element).first >= 8) {
    for (auto it = emptyPositions.begin(); it != emptyPositions.end(); ++it) {
      Serial.println("Elt: ");
      Serial.print((*element).first);
      Serial.print(" ");
      Serial.println((*element).second);
    }
  }

  return *element; // copies over
}

void Snake::addToHead(Coordinates field) {
  snakePosition.push(field);
  snakeTakenFields.insert(field);
  emptyPositions.erase(field);
}

void Snake::popTheTail() {
  auto elt = snakePosition.front(); // oldest element
  snakePosition.pop();
  snakeTakenFields.erase(elt);
  emptyPositions.insert(elt);
}

void Snake::setStartingPosition() {
  // Clean up our queue
  snakePosition = std::queue<Coordinates>();
  snakeTakenFields = std::set<Coordinates>();
  emptyPositions = std::set<Coordinates>();
  snakeDirection = Direction::right;

  for (int i = 0; i < X_DIM; ++i) {
    for (int j = 0; j < Y_DIM; ++j) {
      emptyPositions.insert({i, j});
    }
  }

  addToHead({2, 3});
  addToHead({3, 3});
  addToHead({4, 3});

  applePosition = generateApplePosition();
  shouldMove = false;
  shouldAcceptInput = true;
}

void Snake::redraw(BoardDriver &driver) {
  clearBoard(driver);

  for (auto it = snakeTakenFields.begin(); it != snakeTakenFields.end(); ++it) {
    driver.setPixelColor((*it).first, (*it).second, snake_body_color());
  }
  driver.setPixelColor(applePosition.first, applePosition.second,
                       apple_color());
}

void Snake::startWinningSequence(BoardDriver &driver) {
  auto centerCoordinates = snakePosition.back(); // newest

  int numberOfStepsX =
      max(centerCoordinates.first, X_DIM - centerCoordinates.first - 1);
  int numberOfStepsY =
      max(centerCoordinates.second, Y_DIM - centerCoordinates.second - 1);
  int numberOfSteps = numberOfStepsX + numberOfStepsY;

  uint32_t colorsByDistance[4] = {
      adjustBrightness(0x00aa22, 0.3),
      adjustBrightness(0x00aa22, 0.15),
      adjustBrightness(0x00aa22, 0.05),
      adjustBrightness(0x00aa22, 0.02),
  };

  for (int i = 0; i < numberOfSteps; ++i) {
    // for each coordinate calculate its distance
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist =
            coordinates_distance(centerCoordinates, std::make_pair(x, y));
        if (dist == (i + 1)) {
          uint32_t color = adjustBrightness(0x229922, 0.3);

          driver.setPixelColor(x, y, color);
        }
      }
    }

    driver.show();
    delay(150);
  }

  delay(200);

  display_text(driver, "Congratulations!", adjustBrightness(0xaaaaff, 0.4));

  driver.finishActivity();
}

void Snake::startRestartingSequence(BoardDriver &driver) {
  for (int i = 0; i < 5; ++i) {
    // Blink everything
    for (auto it = snakeTakenFields.begin(); it != snakeTakenFields.end();
         ++it) {
      uint32_t color = snake_body_color();
      if (i % 2 != 0) {
        color = adjustBrightness(color, 0.2);
      }
      driver.setPixelColor((*it).first, (*it).second, color);
    }

    driver.show();
    delay(300);
  }

  auto centerCoordinates = snakePosition.back(); // newest

  int numberOfStepsX =
      max(centerCoordinates.first, X_DIM - centerCoordinates.first - 1);
  int numberOfStepsY =
      max(centerCoordinates.second, Y_DIM - centerCoordinates.second - 1);
  int numberOfSteps = numberOfStepsX + numberOfStepsY;

  uint32_t colorsByDistance[4] = {
      adjustBrightness(0x00aa22, 0.3),
      adjustBrightness(0x00aa22, 0.15),
      adjustBrightness(0x00aa22, 0.05),
      adjustBrightness(0x00aa22, 0.02),
  };
  for (int i = 0; i < numberOfSteps; ++i) {
    // for each coordinate calculate its distance
    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        auto dist =
            coordinates_distance(centerCoordinates, std::make_pair(x, y));
        if (dist == (i + 1)) {
          uint32_t color = adjustBrightness(0x229922, 0.3);

          if (snakeTakenFields.find({x, y}) != snakeTakenFields.end()) {
            driver.setPixelColor(x, y, snake_body_color());
          } else {
            driver.setPixelColor(x, y, color);
          }
        }
      }
    }

    driver.show();
    delay(150);
  }

  delay(200);
  setStartingPosition();
}

void Snake::move(BoardDriver &driver) {
  // 4 possible cases:
  // 1. Empty field in front
  // 2. Apple in front
  // 3. Snek in front
  //    a. Snek will move out of the way
  //    b. We crash into snek

  auto fieldInFront = coordinateInFrontOfHead();
  if (fieldInFront == applePosition) {
    // We're eating the apple
    addToHead(fieldInFront);

    // Before we generate the apple, are there any other empty fields?
    if (emptyPositions.size() == 0) {
      // This is it, we won
      startWinningSequence(driver);
      return;
    }

    // Otherwise we have to generate an apple position and carry on
    applePosition = generateApplePosition();
  } else if (emptyPositions.find(fieldInFront) != emptyPositions.end()) {
    // Empty field in front
    addToHead(fieldInFront);
    popTheTail();
  } else if (snakeTakenFields.find(fieldInFront) != snakeTakenFields.end()) {
    if (fieldInFront == snakePosition.front()) {
      // We know it's snek in front of us, but if its the tail, we are still
      // fine!
      popTheTail();
      addToHead(fieldInFront);
    } else {
      // Unfortunately, we have a crash here. We're going to start an animation
      // for refresh and then restart the game
      startRestartingSequence(driver);
    }
  }
}

void Snake::gameTick(BoardDriver &driver) {
  if (shouldMove) {
    move(driver);
  } else {
    shouldMove = true;
  }

  redraw(driver);
  shouldAcceptInput = true;
}

void Snake::loop(BoardDriver &driver) {
  // Game tick logic
  auto now = millis();
  if (now - lastGameTick >= gameTickInterval) {
    lastGameTick = now;
    gameTick(driver);
  }
}

void Snake::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING && shouldAcceptInput) {
    auto buttonCoordinates = index_to_coordinates(event.bit.NUM);
    auto head = snakePosition.back(); // the latest

    // Eliminate hitting the same line
    if (snakeDirection == Direction::left ||
        snakeDirection == Direction::right) {
      if (buttonCoordinates.second == head.second) {
        // No move
        return;
      } else if (buttonCoordinates.second < head.second) {
        snakeDirection = Direction::up;
      } else if (buttonCoordinates.second > head.second) {
        snakeDirection = Direction::down;
      }
    } else if (snakeDirection == Direction::up ||
               snakeDirection == Direction::down) {
      if (buttonCoordinates.first == head.first) {
        return;
      } else if (buttonCoordinates.first < head.first) {
        snakeDirection = Direction::left;
      } else if (buttonCoordinates.first > head.first) {
        snakeDirection = Direction::right;
      }
    }
    shouldAcceptInput = false;
  }
}