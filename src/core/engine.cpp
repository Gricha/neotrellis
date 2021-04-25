#include "engine.h"
#include "../activities/changing_pulsation.h"
#include "../activities/fire.h"
#include "../activities/intro.h"
#include "../activities/ocean.h"
#include "../activities/trees.h"
#include "../utils.h"
#include <cassert>

static Engine engine = {};

Engine &get_global_engine() { return engine; }

bool isButtonCorner(int index) {
  const int leftTopCorner = 0;

  return (index == leftTopCorner);
}

TrellisCallback handlePress(keyEvent event) {
  BoardDriver &bd = engine;
  EngineDriver &ed = engine;
  // Depends on a state!
  switch (engine.state) {
  case BoardState::activity:
    engine.currentActivity->handleEvent(event, bd);
    break;
  case BoardState::mainMenu:
    engine.mainMenuEngine.handleEvent(event, ed);
    break;
  case BoardState::idle:
    break;
  }

  if (isButtonCorner(event.bit.NUM)) {
    Serial.println("Corner button event");
    unsigned long currentTimestamp = millis();
    if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
      // Clean up older presses
      for (int i = 0; i < 3; ++i) {
        if (engine.pressCount > i &&
            currentTimestamp - engine.cornerButtonPress[i] > 2000) {
          engine.pressCount = i;
          break;
        }
      }

      engine.pressCount += 1;
      engine.cornerButtonPress[2] = engine.cornerButtonPress[1];
      engine.cornerButtonPress[1] = engine.cornerButtonPress[0];
      engine.cornerButtonPress[0] = currentTimestamp;

      if (engine.pressCount >= 3) {
        Serial.println("Pressed corner button more than 3 times in 2 seconds, "
                       "falling back");
        engine.pressCount = 0;
        engine.changeState(
            BoardState::idle); // idle state transforms into mainMenu evenutally
      } else {
        Serial.println("Stopped pressing corner button. Add one to the list");
      }
    }
  }

  return 0;
}

void Engine::finishActivity() { changeState(BoardState::idle); }

void Engine::startActivity(ActivitySpecification &specification) {
  if (state != BoardState::mainMenu) {
    return;
  }

  Serial.print("Initializing activity: ");
  Serial.println(specification.config.name);

  currentActivity = specification.factory();
  currentActivityConfig = specification.config;
  engine.changeState(BoardState::activity);
}

void Engine::show() { trellis.show(); }

void Engine::setPixelColor(uint16_t buttonIndex, uint32_t color) {
  if (buttonIndex < 0 || buttonIndex >= X_DIM * Y_DIM) {
    return;
  }
  trellis.setPixelColor(buttonIndex, color);
}

void Engine::setPixelColor(uint8_t x, uint8_t y, uint32_t color) {
  trellis.setPixelColor(x, y, color);
}

void Engine::changeState(BoardState newState) {
  Serial.print("Engine::changeState ");
  Serial.println(name_for_state(newState));
  // If state changes, no matter what, we will clean up potentially leaving - we
  // don't care at this point
  engine.pressCount = 0;

  engine.state = BoardState::idle;

  BoardDriver &bd = engine;
  clearBoard(bd);
  engine.show();
  engine.state = newState;
}

void Engine::setup() {
  Serial.begin(9600);

  if (!trellis.begin()) {
    Serial.println("failed to begin trellis");
    while (1)
      ;
  }

  BoardDriver &bd = engine;
  randomized_intro(engine);

  for (int y = 0; y < Y_DIM; y++) {
    for (int x = 0; x < X_DIM; x++) {
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
      trellis.registerCallback(x, y, handlePress);
      trellis.setPixelColor(x, y, BUTTON_OFF);
      trellis.show();
      delay(TRELLIS_INTERVAL_MS);
    }
  }
}

Adafruit_NeoTrellis t_array[Y_DIM / 4][X_DIM / 4] = {
    {Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x2E)},
    {Adafruit_NeoTrellis(0x31), Adafruit_NeoTrellis(0x30)}

};

Engine::Engine()
    : trellis(Adafruit_MultiTrellis((Adafruit_NeoTrellis *)t_array, Y_DIM / 4,
                                    X_DIM / 4)),
      state(BoardState::mainMenu), mainMenuEngine({}),
      currentActivity(
          std::make_shared<PlaceholderActivity>(PlaceholderActivity())),
      currentActivityConfig(placeholderConfig), pressCount(0),
      idleLoopCount(0) {
  auto current = millis();
  cornerButtonPress[0] = current;
  cornerButtonPress[1] = current;
  cornerButtonPress[2] = current;
}

void Engine::readInput() {
  lastInputRead = millis();
  trellis.read();
}

void Engine::loop() {
  auto inputInterval = millis() - lastInputRead;

  // input reading
  switch (state) {
  case BoardState::activity:
    if (inputInterval > currentActivityConfig.inputReadIntervalMs) {
      readInput();
    }
    break;
  default:
    readInput();
    break;
  }

  BoardDriver &bd = engine;
  EngineDriver &ed = engine;
  // Within a state you have an opportunity to take an action on loop
  switch (state) {
  case BoardState::activity:
    currentActivity->loop(bd);
    break;
  case BoardState::mainMenu:
    mainMenuEngine.loop(ed);
    break;
  case BoardState::idle:
    // This allows for all the inputs done during animations to clear themselves
    // up within 20ms break
    if (idleLoopCount > 2) {
      idleLoopCount = 0;
      changeState(BoardState::mainMenu);
    } else {
      clearBoard(bd);
      bd.show();
      idleLoopCount += 1;
    }
    break;
  }

  bd.show();

  return;
}