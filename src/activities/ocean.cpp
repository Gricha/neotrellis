#include "ocean.h"
#include "../consts.h"
#include "../utils.h"
#include "pulsating_effect.h"

#include <vector>

ColorScheme ocean_scheme() {
  return {0x045c84, 0x04749c, 0x87b8ce, 0x5395b1, 0x6c9cb4};
}

PulsatingEffect get_ocean_config() {
  auto obj = PulsatingEffect();
  obj.initialize(ocean_scheme(), {
                                     .lowBrightness = 0.01,
                                     .highBrightness = 0.4,
                                     .lowIncrement = 0.01,
                                     .highIncrement = 0.04,
                                 });
  return obj;
}