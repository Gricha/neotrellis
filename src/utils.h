#ifndef Utils_h
#define Utils_h

#include <cstdint>
#include <utility>
#include <vector>

#include "board_driver.h"

// Common type definitions
using Coordinates = std::pair<int, int>;
using TimeInterval = unsigned long;

using ColorScheme = std::vector<uint32_t>;

enum class Direction { left, right, up, down };

// Common functionalities

// Reduces color by ratio on each axes (r, g, b). In Trellis that's the only
// way to control brightness directly
uint32_t adjustBrightness(uint32_t color, float ratio);

void clearBoard(BoardDriver &driver);

uint32_t Wheel(uint8_t WheelPos);

Coordinates index_to_coordinates(int index);

int coordinates_distance(std::pair<int, int> t, std::pair<int, int> h);

#endif