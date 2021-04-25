#ifndef MainMenu_h
#define MainMenu_h

#include "../consts.h"
#include "arduino_header.h"
#include "engine_driver.h"

/**
 * Displays available activites from the registry.cpp.
 *
 * Manages state transitions.
 */
class MainMenuEngine {
public:
  MainMenuEngine();
  void loop(EngineDriver &driver);
  void handleEvent(keyEvent event, EngineDriver &driver);

private:
  bool isHigh;
  unsigned long lastSwitchTimestamp;
};

#endif