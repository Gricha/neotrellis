#ifndef Circles_h
#define Circles_h

#include "../activity.h"
#include "../board_driver.h"
#include "../core/arduino_header.h"

#include <vector>

/**
 * Simple animation that shows lines of colors going around the grid from
 * outside towards inside.
 */

class CirclesAnimation : public Activity {
public:
  CirclesAnimation();
  void loop(BoardDriver &);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  bool shouldEnd(BoardDriver &driver);

  std::vector<std::pair<int, int>> order;
  int currentStep;
  int numberOfSteps;
  int boardSize;
  int breakBetweenColors;
  int numberOfBreaks;
};

#endif