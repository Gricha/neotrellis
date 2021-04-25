#include "trees.h"
#include "../consts.h"
#include "../utils.h"
#include "pulsating_effect.h"

#include <vector>

ColorScheme trees_scheme() {
  return {
      0x19270d, 0x25591f, 0x818c3c, 0x72601b, 0x593a0e,
  };
}

PulsatingEffect get_trees_config() {
  auto obj = PulsatingEffect();
  obj.initialize(trees_scheme(), {
                                     .lowBrightness = 0.01,
                                     .highBrightness = 0.2,
                                     .lowIncrement = 0.01,
                                     .highIncrement = 0.03,
                                 });
  return obj;
}