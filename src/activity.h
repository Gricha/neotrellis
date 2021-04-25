#ifndef Activity_h
#define Activity_h

#include "board_driver.h"
#include "core/arduino_header.h"

#include <functional>
#include <memory>

/**
 * Activity is a base virtual class for the actual Activity that can be defined
 * to run on the Engine.
 */
class Activity {
public:
  // Invoked every 20ms. Has a chance to refresh what's displayed.
  virtual void loop(BoardDriver &driver){};

  // Handle actual events (button presses).
  virtual void handleEvent(keyEvent event, BoardDriver &driver){};
};

using ActivityFactory = std::function<std::shared_ptr<Activity>(void)>;

struct ActivityConfig {
  const char *name;
  // Minimum trellis refresh rate is 20ms. Anything lower than that means that
  // we will refresh input every loop. This is perfect for any games, but for
  // animations can end up being very expensive and lag them. If it's not a
  // blocker, bumping it to 200-500ms will result in better performance
  unsigned long inputReadIntervalMs;
  // Describes the color used on main menu for this activity
  uint32_t menuButtonColor;
};

struct ActivitySpecification {
  ActivityFactory factory;
  ActivityConfig config;
};

class PlaceholderActivity : public Activity {
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);
};

static ActivityConfig placeholderConfig = {
    .name = "placeholder",
    .inputReadIntervalMs = 10,
    .menuButtonColor = 0x555555,
};

#endif