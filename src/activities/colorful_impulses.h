#ifndef ColorfulImpulses_h
#define ColorfulImpulses_h

#include "../activity.h"
#include "../board_driver.h"
#include "../utils.h"

#include <vector>

#include "impulses.h"

/**
 * ColorfulImpulses is an activity in which upon pressing a button, an impulse
 * of a pressed color is generated and spread across the board from the origin
 * point.
 */
class ColorfulImpulses : public Activity {
public:
  ColorfulImpulses();
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  std::vector<Impulse> impulses;
};

#endif