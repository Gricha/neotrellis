#ifndef Snake_h
#define Snake_h

#include "../activity.h"
#include "../utils.h"

#include <queue>
#include <random>
#include <set>

/**
 * An actual Snake game.
 */
class Snake : public Activity {
public:
  Snake();
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  Coordinates generateApplePosition();
  // Gives coordinate that is in front of snake in a direction its moving.
  // Wraps board over both horizontally and vertically.
  Coordinates coordinateInFrontOfHead();
  void setStartingPosition();

  // Game management
  Coordinates applePosition;
  std::queue<Coordinates> snakePosition;
  std::set<Coordinates> snakeTakenFields;
  std::set<Coordinates> emptyPositions;
  Direction snakeDirection;
  void addToHead(Coordinates field);
  void popTheTail();

  std::mt19937 randomnessGenerator;

  // Tick management
  TimeInterval gameTickInterval;
  TimeInterval lastGameTick; // When did the last game tick happened
  void gameTick(BoardDriver &driver);
  bool shouldMove;
  bool shouldAcceptInput;
  void redraw(BoardDriver &driver);
  void move(BoardDriver &driver);
  void startRestartingSequence(BoardDriver &driver);
  void startWinningSequence(BoardDriver &driver);
};

#endif