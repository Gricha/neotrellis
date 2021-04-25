#include "on_off_game.h"

#include "../utils.h"

OnOffGame::OnOffGame() {
  for (int i = 0; i < X_DIM * Y_DIM; ++i) {
    buttonState[i] = false;
  }
}

bool OnOffGame::isOn(uint16_t buttonIndex) {
  if (buttonIndex < 0 || buttonIndex >= Y_DIM * X_DIM) {
    return false;
  } else {
    return buttonState[buttonIndex];
  }
}

void OnOffGame::setButton(uint16_t buttonIndex, bool isOn) {
  if (buttonIndex < 0 || buttonIndex >= Y_DIM * X_DIM) {
    return;
  }
  buttonState[buttonIndex] = isOn;
}

void OnOffGame::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    if (isOn(event.bit.NUM)) {
      driver.setPixelColor(event.bit.NUM, 0);
      setButton(event.bit.NUM, false);
    } else {
      uint32_t color = Wheel(map(event.bit.NUM, 0, X_DIM * Y_DIM, 0, 255));
      color = adjustBrightness(color, 0.1);
      driver.setPixelColor(event.bit.NUM, color);
      setButton(event.bit.NUM, true);
    }
  }
  driver.show();
}

void OnOffGame::loop(BoardDriver &driver) {}