#include "animation_runner.h"
#include "../consts.h"
#include "../utils.h"

void AnimationRunner::loop(BoardDriver &driver) {
  clearBoard(driver);
  driver.show();
  delay(TRELLIS_INTERVAL_MS);

  _animation(driver);

  driver.finishActivity();
}

void AnimationRunner::handleEvent(keyEvent event, BoardDriver &driver) {
  // No-op
}