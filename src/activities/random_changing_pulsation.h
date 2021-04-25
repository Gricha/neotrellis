#ifndef RandomChangingPulsation_h
#define RandomChangingPulsation_h

#include "../utils.h"
#include "changing_pulsation.h"
#include "pulsating_effect.h"
#include <vector>

/**
 * RandomColorChangingPulsation is a PulsatingEffect where color schemes are
 * randomized and change for every button press. While the color scheme is
 * random, the code attempts to "tint" it, so it's not completely random and
 * follows a "theme".
 */
class RandomColorChangingPulsation : public PulsatingEffect {
public:
  RandomColorChangingPulsation();
  void handleEvent(keyEvent event, BoardDriver &driver);
  bool shouldEnd(BoardDriver &driver);
};

#endif