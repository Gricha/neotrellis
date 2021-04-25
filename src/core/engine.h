#ifndef Engine_h
#define Engine_h

#include "../activities/changing_pulsation.h"
#include "../activities/circles.h"
#include "../activities/on_off_game.h"
#include "../activities/pulsating_effect.h"
#include "../activities/random_changing_pulsation.h"
#include "../activities/warmer_warmer.h"
#include "../activity.h"
#include "../board_driver.h"
#include "../consts.h"
#include "arduino_header.h"
#include "main_menu.h"

/**
 * Engine is the "operation center" of the toy. It will hold the current state
 * and delegate loop calls and events to the activities directly. Engine is
 * responsible for handling interruptions and redirecting them to main menu.
 */
class Engine : public EngineDriver {
public:
  Engine();
  ~Engine() {}

  void setup();
  void loop();

  void setPixelColor(uint16_t buttonIndex, uint32_t color);
  void setPixelColor(uint8_t x, uint8_t y, uint32_t color);
  void changeState(BoardState newState);
  void show();

  void finishActivity();
  void startActivity(ActivitySpecification &specification);

  ///

  Adafruit_MultiTrellis trellis;
  BoardState state;

  // For different activities, we can have different states
  // currently this is represented as a union of all types
  std::shared_ptr<Activity> currentActivity;
  ActivityConfig currentActivityConfig;

  MainMenuEngine mainMenuEngine;

  // Fallback - if any corner button is held for > 3 seconds - break the game
  // and go to main menu
  unsigned long cornerButtonPress[3];
  int pressCount;

  // This is used for falling back from idle state
  // Idle state is introduced to consume all events from the buffer when moving
  // between activities
  int idleLoopCount;

  // Last input read marks a timestamp for when was the last time the engine
  // called trellis.read() Normally this operation is a bit expensive and
  // shouldn't happen
  unsigned long lastInputRead;

private:
  void readInput();
};

// Global Engine because I have to have static press handler
Engine &get_global_engine();

#endif