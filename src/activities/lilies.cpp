#include "lilies.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

ColorScheme lilies_scheme() {
  return {0xc85e84, 0x4b1359, 0x9c5cac, 0xd9aecf, 0x5c2c5c};
}

PulsatingEffect get_lilies_config() {
  auto obj = PulsatingEffect();
  obj.initialize(lilies_scheme(), {
                                      .lowBrightness = 0.02,
                                      .highBrightness = 0.3,
                                      .lowIncrement = 0.02,
                                      .highIncrement = 0.05,
                                  });
  return obj;
}