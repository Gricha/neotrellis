#ifndef Trees_h
#define Trees_h

#include "../board_driver.h"
#include "../core/arduino_header.h"
#include "../utils.h"
#include "pulsating_effect.h"

ColorScheme trees_scheme();

/**
 * Green-brown pulsation.
 */
PulsatingEffect get_trees_config();

#endif