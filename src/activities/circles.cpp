#include "circles.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

CirclesAnimation::CirclesAnimation() {
  int cursorX = 0;
  int cursorY = 0;
  int steps = 0;
  Direction currentDirection = Direction::right;
  int directionalStepsX = X_DIM;
  int directionalStepsY = Y_DIM;

  int stepsInDirectionTaken = 0;

  // We can do at most X_DIM * Y_DIM steps
  boardSize = X_DIM * Y_DIM;
  while (steps < boardSize) {
    // in order to make a circles pattern you need to change directions of lines
    // and with each direction change you reduce number of steps in this
    // iteration if that direction change is vertical (you got either up or
    // down)

    // color first
    order.push_back(std::make_pair(cursorX, cursorY));
    stepsInDirectionTaken += 1;

    if (currentDirection == Direction::right ||
        currentDirection == Direction::left) {
      if (stepsInDirectionTaken >= directionalStepsX) {
        // Time to stop and change direction
        stepsInDirectionTaken = 0;
        if (currentDirection == Direction::right) {
          currentDirection = Direction::down;
        } else if (currentDirection == Direction::left) {
          currentDirection = Direction::up;
        }

        // Since we are changing direction towards vertical, reduce number of
        // steps needed
        directionalStepsX -= 1;
        directionalStepsY -= 1;
      }
    } else {
      if (stepsInDirectionTaken >= directionalStepsY) {
        stepsInDirectionTaken = 0;
        if (currentDirection == Direction::up) {
          currentDirection = Direction::right;
        } else if (currentDirection == Direction::down) {
          currentDirection = Direction::left;
        }
      }
    }

    // now do the move according to direction
    switch (currentDirection) {
    case Direction::right:
      cursorX += 1;
      break;
    case Direction::down:
      cursorY += 1;
      break;
    case Direction::left:
      cursorX -= 1;
      break;
    case Direction::up:
      cursorY -= 1;
      break;
    }

    steps += 1;
  }

  breakBetweenColors = 24;
  numberOfBreaks = 18; // colors - 1

  currentStep = 0;
  numberOfSteps = boardSize + (breakBetweenColors * numberOfBreaks);
}

void CirclesAnimation::loop(BoardDriver &driver) {
  // Here I wan't to have a couple of solid lines chasing each other with a
  // proper break
  uint32_t colors[19] = {
      0x17deee,   // blue
      0xff7f50,   // orange
      0xff4162,   // pink
      0xf2e50b,   // yellow
      0x21b20c,   // green
      0x8200ac,   // purple
      0x17deee,   // blue
      0xff7f50,   // orange
      0xff4162,   // pink
      0xf2e50b,   // yellow
      0x21b20c,   // green
      0x8200ac,   // purple
      0x17deee,   // blue
      0xff7f50,   // orange
      0xff4162,   // pink
      0xf2e50b,   // yellow
      0x21b20c,   // green
      0x8200ac,   // purple
      BUTTON_OFF, // clear
  };

  if (currentStep < numberOfSteps) {
    // main loop
    for (int j = 0; j < 19; ++j) {
      // Each color position must be checked
      int colorPosition = currentStep - (j * breakBetweenColors);
      if (colorPosition >= boardSize) {
        continue;
      }
      if (colorPosition < 0) {
        continue;
      }
      driver.setPixelColor(order[colorPosition].first,
                           order[colorPosition].second,
                           adjustBrightness(colors[j], 0.1));
    }
  }

  currentStep += 1;

  if (shouldEnd(driver)) {
    driver.finishActivity();
  }
}

bool CirclesAnimation::shouldEnd(BoardDriver &driver) {
  return (currentStep >= numberOfSteps);
}

void CirclesAnimation::handleEvent(keyEvent event, BoardDriver &driver) {}