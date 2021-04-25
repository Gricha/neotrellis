#ifndef Lilies_h
#define Lilies_h

#include "../board_driver.h"
#include "../core/arduino_header.h"
#include "../utils.h"
#include "pulsating_effect.h"

ColorScheme lilies_scheme();

/**
 * Purple-pink based pulsation.
 */
PulsatingEffect get_lilies_config();

#endif