#ifndef BoardStates_H
#define BoardStates_H

enum class BoardState {
  mainMenu,
  activity,
  idle,
};

const char *name_for_state(BoardState state);

#endif