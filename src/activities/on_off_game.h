#ifndef OnOffGame_h
#define OnOffGame_h

#include "../activity.h"
#include "../board_driver.h"
#include "../consts.h"
#include "../core/arduino_header.h"

/**
 * A very simple animation that, based on the color wheel, determines the color
 * for each button and then turns them on and off on presses.
 */
class OnOffGame : public Activity {
public:
  OnOffGame();
  bool isOn(uint16_t buttonIndex);
  void setButton(uint16_t buttonIndex, bool isOn);

  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

  bool buttonState[X_DIM * Y_DIM];
};

#endif