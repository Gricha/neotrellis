#ifndef WarmerWarmer_h
#define WarmerWarmer_h

#include "../activity.h"
#include "../board_driver.h"
#include "../consts.h"
#include "../core/arduino_header.h"

/**
 * At the beginning of this activity, all buttons are turned off. One of them is
 * chosen to be the target. The player has to try and hit it. As they get
 * closer, the colors will get warmer and closer to "red".
 */
class WarmerWarmer : public Activity {
public:
  WarmerWarmer();
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  void finishingSequence(BoardDriver &driver);
  int targetIndex;
  int numberOfHits;

  bool hits[X_DIM * Y_DIM];
};

#endif
