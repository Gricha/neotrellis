#ifndef Impulses_h
#define Impulses_h

#include "../activity.h"
#include "../board_driver.h"
#include "../utils.h"
#include <random>

#include <vector>

struct Impulse {
  Coordinates center;
  int numberOfSteps;
  int currentStep;
  uint32_t color;
};

/**
 * Impulses is an activity in which upon pressing a button, an impulse
 * of a random color is generated and spread across the board from the origin
 * point.
 *
 * Main difference between this and ColorfulImpulses is in this version,
 * the board is blank and the colors are chosen at random.
 */
class Impulses : public Activity {
public:
  Impulses();
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  std::vector<Impulse> impulses;
  std::mt19937 randomnessGenerator;
};

#endif