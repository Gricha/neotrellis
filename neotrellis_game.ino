#include "src/core/engine.h"

void setup() {
  randomSeed(millis());
  get_global_engine().setup();
}

void loop() {
  get_global_engine().loop();
  delay(TRELLIS_INTERVAL_MS);
}
