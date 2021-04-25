#ifndef Drawing_h
#define Drawing_h

#include "../../activity.h"
#include "../../board_driver.h"
#include "../../utils.h"

#include <functional>
#include <vector>

using DisplayMap = std::vector<std::vector<int>>;

/**
 * Drawing is a simple wrapper around Activity that displays a static set
 * of colored pixels that will be quit upon pressing any button.
 */
class Drawing : public Activity {
public:
  Drawing(DisplayMap _displayMap, ColorScheme _color)
      : displayMap(_displayMap), colorScheme(_color), displayed(false) {}
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  DisplayMap displayMap;
  ColorScheme colorScheme;
  bool displayed;
};

#endif