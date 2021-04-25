
#include "changing_pulsation.h"
#include "fire.h"
#include "lilies.h"
#include "ocean.h"
#include "trees.h"

ColorChangingPulsation::ColorChangingPulsation() : PulsatingEffect() {
  // Add more potential fun color schemes here
  colorSchemes = {
      {
          // Purple
          .config =
              {
                  .lowBrightness = 0.02,
                  .highBrightness = 0.3,
                  .lowIncrement = 0.02,
                  .highIncrement = 0.05,
              },
          .colors = lilies_scheme(),
      },
      {
          // brown
          .config =
              {
                  .lowBrightness = 0.02,
                  .highBrightness = 0.3,
                  .lowIncrement = 0.02,
                  .highIncrement = 0.05,
              },
          .colors = {0xb57b4a, 0xe2c198, 0x563414, 0xa67952, 0x5b4331},
      },
      {
          // Fire
          .config =
              {
                  .lowBrightness = 0.01,
                  .highBrightness = 0.5,
                  .lowIncrement = 0.04,
                  .highIncrement = 0.08,
              },
          .colors = fire_scheme(),
      },
      {
          // Ocean
          .config =
              {
                  .lowBrightness = 0.01,
                  .highBrightness = 0.4,
                  .lowIncrement = 0.01,
                  .highIncrement = 0.04,
              },
          .colors = ocean_scheme(),
      },
      {
          // Nostalgic Blend
          .config =
              {
                  .lowBrightness = 0.02,
                  .highBrightness = 0.3,
                  .lowIncrement = 0.02,
                  .highIncrement = 0.05,
              },
          .colors = {0x494c7d, 0xb3617b, 0x9bb797, 0x5c9a95, 0xd0ceac},
      },
      {
          // Forest
          .config =
              {
                  .lowBrightness = 0.01,
                  .highBrightness = 0.3,
                  .lowIncrement = 0.01,
                  .highIncrement = 0.03,
              },
          .colors = trees_scheme(),

      },
  };

  currentColorScheme = 0;
  initialize(colorSchemes[0].colors, colorSchemes[0].config);
}

void ColorChangingPulsation::handleEvent(keyEvent event, BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    Serial.println("Changing the displayed color scheme");
    currentColorScheme += 1;
    if (currentColorScheme >= colorSchemes.size()) {
      currentColorScheme = 0;
    }

    setConfig(colorSchemes[currentColorScheme].config);
    setColorScheme(colorSchemes[currentColorScheme].colors);
  }
}

bool ColorChangingPulsation::shouldEnd(BoardDriver &driver) { return false; }