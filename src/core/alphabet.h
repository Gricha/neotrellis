#ifndef Alphabet_H
#define Alphabet_H

#include "arduino_header.h"
#include <vector>

/**
 * This file has utilities for displaying actual letters/numbers on the board.
 */

// Will not respect Y_DIM/X_DIM, converts it to up to 8 pixels height, unbounded
// x
std::vector<std::vector<bool>> convert_string_to_bitmap(const char *text);

void log_bitmap_human_readable(std::vector<std::vector<bool>> &bitmap);

#endif