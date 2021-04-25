#ifndef BoardDriver_h
#define BoardDriver_h

#include <inttypes.h>

#include "core/board_states.h"

class BoardDriver {
public:
  virtual void setPixelColor(uint16_t buttonIndex, uint32_t color);
  virtual void setPixelColor(uint8_t x, uint8_t y, uint32_t color);
  virtual void changeState(BoardState newState);

  // Forces the board to show the refreshed setup after changing pixel state
  virtual void show();

  // Given activity can quit back to Main Menu using this callback
  virtual void finishActivity();
};

#endif