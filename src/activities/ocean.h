#ifndef Ocean_h
#define Ocean_h

#include "../board_driver.h"
#include "../core/arduino_header.h"
#include "../utils.h"
#include "pulsating_effect.h"

ColorScheme ocean_scheme();

/**
 * Blue/dark blue pulsation.
 */
PulsatingEffect get_ocean_config();

#endif