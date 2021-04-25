#ifndef ChangingPulsation_h
#define ChangingPulsation_h

#include "../utils.h"
#include "pulsating_effect.h"
#include <vector>

struct ColorConfiguration {
  PulsationConfiguration config;
  std::vector<uint32_t> colors;
};

/**
 * ColorChangingPulsation is a version of PulsatingEffect that changes the color
 * scheme on hitting a button. The color schemes available must be predefined in
 * a constructor. Check RandomColorChangingPulsation for randomized version of
 * this.
 */
class ColorChangingPulsation : public PulsatingEffect {
public:
  ColorChangingPulsation();
  void handleEvent(keyEvent event, BoardDriver &driver);
  bool shouldEnd(BoardDriver &driver);

private:
  std::vector<ColorConfiguration> colorSchemes;
  int currentColorScheme;
};

#endif