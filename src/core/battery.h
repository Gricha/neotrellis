#ifndef Battery_h
#define Battery_h

#include "../board_driver.h"
#include "arduino_header.h"

/**
 * This is an actual animation that encodes the state of battery charge.
 * Assumes existence of battery!
 */
void battery_check(BoardDriver &driver);

#endif