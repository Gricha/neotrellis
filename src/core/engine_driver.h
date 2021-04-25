#ifndef EngineDriver_h
#define EngineDriver_h

#include "../activity.h"
#include "../board_driver.h"

/**
 * This class exists only because we need to break a circular dependency between
 * Activity and BoardDriver Engine driver only must be known for MainMenu.
 */
class EngineDriver : public BoardDriver {
public:
  // Can start activity. NOTE: It will only work from Main Menu
  virtual void startActivity(ActivitySpecification &specification);
};

#endif