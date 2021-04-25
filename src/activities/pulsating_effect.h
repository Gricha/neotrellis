
#ifndef PulsatingEffect_h
#define PulsatingEffect_h

#include "../activity.h"
#include "../board_driver.h"
#include "../core/arduino_header.h"

#include <vector>

struct PulsationConfiguration {
  float lowBrightness;
  float highBrightness;
  float lowIncrement;
  float highIncrement;
};

enum class CellGrowthDirection {
  Up,
  Down,
};

using CellState = std::tuple<float, CellGrowthDirection, float,
                             uint32_t>; // (brightness, direction, increment)
using CellMatrix = std::vector<std::vector<CellState>>;

/**
 * PulsatingEffect is an activity that will randomize colors and intensity of
 * them and display them on the board.
 */
class PulsatingEffect : public Activity {
public:
  /**
   * Before running, initialize() must be called.
   */
  PulsatingEffect();

  /**
   * Proper initialization, used for subclasses setting up custom configs. Must
   * be run after constructing.
   */
  void initialize(std::vector<uint32_t> colorScheme,
                  PulsationConfiguration config);
  virtual void loop(BoardDriver &driver);
  virtual bool shouldEnd(BoardDriver &driver);
  virtual void handleEvent(keyEvent event, BoardDriver &driver);

protected:
  void setColorScheme(std::vector<uint32_t> newColorScheme);
  void setConfig(PulsationConfiguration config);
  void refreshConfiguration();
  float flatAdjustmentModifier;

private:
  CellMatrix matrix;
  PulsationConfiguration configuration;
  std::vector<uint32_t> colorScheme;
  unsigned long startTime;
};

#endif