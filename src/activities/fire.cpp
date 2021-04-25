#include "fire.h"
#include "../consts.h"
#include "../utils.h"

#include <algorithm>
#include <random>
#include <vector>

#define LOW_RANGE 0.01
#define HIGH_RANGE 0.6
#define FIRE_INCREMENT_LOW 0.04
#define FIRE_INCREMENT_HIGH 0.08

ColorScheme fire_scheme() {
  return {0x801100, 0xb62203, 0xd73502, 0xfc6400, 0xff7500};
}

PulsatingEffect get_fire_config() {
  auto obj = PulsatingEffect();
  obj.initialize(fire_scheme(), {
                                    .lowBrightness = LOW_RANGE,
                                    .highBrightness = HIGH_RANGE,
                                    .lowIncrement = FIRE_INCREMENT_LOW,
                                    .highIncrement = FIRE_INCREMENT_HIGH,
                                });
  return obj;
}