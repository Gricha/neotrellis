#include "board_states.h"

const char *name_for_state(BoardState state) {
  switch (state) {
  case BoardState::activity:
    return "activity";
  case BoardState::mainMenu:
    return "main menu";
  case BoardState::idle:
    return "idle";
  }
  return "unknown";
}