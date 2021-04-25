#include "main_menu.h"

#include "../utils.h"

#include "../activities/intro.h"
#include "../registry.h"

MainMenuEngine::MainMenuEngine() : lastSwitchTimestamp(0), isHigh(false) {}

// Changelog
// Moving from steady changes to 2-state changes every 1 second

static std::pair<int, int> index_to_coordinates_with_border(int index) {
  int x = index % (X_DIM - 2);
  int y = index / (X_DIM - 2);

  return std::make_pair(x + 1, y + 1);
}

void MainMenuEngine::loop(EngineDriver &driver) {
  unsigned long currentTime = millis();

  unsigned long elapsedTime = currentTime - lastSwitchTimestamp;

  if (elapsedTime > 1000) {
    auto activities = allActivities();

    float adjustment;
    // 1s passed
    if (isHigh == true) {
      // Change back to low
      isHigh = false;
      adjustment = 0.05;
    } else {
      // Change back to high
      isHigh = true;
      adjustment = 0.1;
    }
    auto size = activities.size();
    for (int i = 0; i < size; ++i) {
      auto coordinates = index_to_coordinates_with_border(i);
      auto color = activities[i].config.menuButtonColor;
      auto finalColor = adjustBrightness(color, adjustment);
      driver.setPixelColor(coordinates.first, coordinates.second, finalColor);
    }

    for (int x = 0; x < X_DIM; ++x) {
      for (int y = 0; y < Y_DIM; ++y) {
        if (x == 0 || y == 0 || x == X_DIM - 1 || y == Y_DIM - 1) {
          driver.setPixelColor(x, y, 0x111111);
        }
      }
    }

    driver.show();
    lastSwitchTimestamp = currentTime;
  }
}

void MainMenuEngine::handleEvent(keyEvent event, EngineDriver &driver) {
  if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    // Let's convert to the index in minimized space
    auto coordinates = index_to_coordinates(event.bit.NUM);
    if (coordinates.first == 0 || coordinates.first == X_DIM - 1 ||
        coordinates.second == 0 || coordinates.second == Y_DIM - 1) {
      // Buttons on the rim are borders
      return;
    }

    // correct for ordered buttons
    coordinates.first -= 1;
    coordinates.second -= 1;

    // reverse the indexing operation
    // int x = index % (X_DIM - 2);
    // int y = index / (X_DIM - 2);

    auto index = (coordinates.second * (X_DIM - 2)) + coordinates.first;
    Serial.print("Converted coordinates (");
    Serial.print(coordinates.first);
    Serial.print(", ");
    Serial.print(coordinates.second);
    Serial.print(") to index ");
    Serial.println(index);

    auto activities = allActivities();

    auto size = activities.size();
    if (index >= size) {
      Serial.println("Pressed inactive button");
      return;
    }

    if (activities[index].config.menuButtonColor == BUTTON_OFF) {
      // Special hack - if there is no color, that activity is a spacer
      return;
    }
    driver.startActivity(activities[index]);
  }
}