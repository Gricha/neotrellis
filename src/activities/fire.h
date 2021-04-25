#ifndef Fire_h
#define Fire_h

#include "../board_driver.h"
#include "../core/arduino_header.h"
#include "../utils.h"
#include "pulsating_effect.h"

ColorScheme fire_scheme();

/**
 * Yellow-Orange-Red-ish pulsation.
 */
PulsatingEffect get_fire_config();

#endif