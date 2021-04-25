#include "drawing.h"

void Drawing::loop(BoardDriver &driver) {
  if (!displayed) {
    displayed = true;
    clearBoard(driver);

    for (int x = 0; x < 8; ++x) {
      for (int y = 0; y < 8; ++y) {
        driver.setPixelColor(x, y, colorScheme[displayMap[y][x]]);
      }
    }
    driver.show();
  }
}

void Drawing::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    driver.finishActivity();
  }
}