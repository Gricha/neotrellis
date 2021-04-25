
#include "random_changing_pulsation.h"

#include <algorithm>
#include <random>
#include <vector>

uint32_t combine_color(uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color = red;
  color <<= 8;
  color |= green;
  color <<= 8;
  color |= blue;
  return color;
}

ColorConfiguration random_color_scheme() {
  std::vector<uint32_t> colors;

  // Randomize dominant color
  auto seed = random();
  std::seed_seq seed_sequence = {seed};
  std::mt19937 gen(seed_sequence);
  std::uniform_int_distribution<int> colorRandomizer(
      0, 100); // because we don't want very bright tints on this device

  uint8_t red = colorRandomizer(gen);
  uint8_t green = colorRandomizer(gen);
  uint8_t blue = colorRandomizer(gen);

  for (int i = 0; i < 5; ++i) {
    uint8_t r = colorRandomizer(gen);
    uint8_t g = colorRandomizer(gen);
    uint8_t b = colorRandomizer(gen);

    uint8_t mixed_r = (r + red) / 2;
    uint8_t mixed_g = (g + green) / 2;
    uint8_t mixed_b = (b + blue) / 2;

    colors.push_back(combine_color(mixed_r, mixed_g, mixed_b));
  }

  return {
      .config =
          {
              .lowBrightness = 0.04,
              .highBrightness = 0.5,
              .lowIncrement = 0.02,
              .highIncrement = 0.05,
          },
      .colors = colors,
  };
}

RandomColorChangingPulsation::RandomColorChangingPulsation()
    : PulsatingEffect() {
  auto randomScheme = random_color_scheme();
  initialize(randomScheme.colors, randomScheme.config);
}

void RandomColorChangingPulsation::handleEvent(keyEvent event,
                                               BoardDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    Serial.println("Changing the displayed color scheme");
    auto randomScheme = random_color_scheme();

    setConfig(randomScheme.config);
    setColorScheme(randomScheme.colors);
  }
}

bool RandomColorChangingPulsation::shouldEnd(BoardDriver &driver) {
  return false;
}