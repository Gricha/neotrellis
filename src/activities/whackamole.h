#ifndef Whackamole_h
#define Whackamole_h

#include "../activity.h"
#include "../board_driver.h"
#include "../utils.h"
#include <random>

/**
 * A whackamole game with configurable speed.
 *
 * In this game, a button will show up and will have to be hit within specified
 * time interval. After 10 correct hits, the game is finished.
 */
class Whackamole : public Activity {
public:
  Whackamole(TimeInterval expectedWaitDuration,
             TimeInterval expectedButtonDuration);
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  // After hitting 10, the game quits
  int successfulHits;
  TimeInterval waitPeriodStart;
  TimeInterval buttonShownStart;

  TimeInterval waitDuration;
  TimeInterval buttonDuration;

  void generateNewTarget();
  void redraw(BoardDriver &driver);

  std::mt19937 randomnessGenerator;

  bool targetValid;
  Coordinates currentTarget;
};

#endif