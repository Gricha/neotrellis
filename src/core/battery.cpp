#include "battery.h"
#include "../activities/text.h"
#include "../consts.h"
#include "../utils.h"

#define VBATPIN A6

void show_vbat_warning(BoardDriver &driver, float measuredvbat) {
  Serial.println("VBAT WARNING");
  Serial.println(measuredvbat);
  char message[80];
  // arv-gcc doesn't like floats and embedding math libraries
  int intgr = int(measuredvbat);
  int frac = int((measuredvbat - intgr) * 10);
  auto len = sprintf(message, "Voltage Error %d.%dV", intgr, frac);
  Serial.println(len);
  char *msg = message;
  display_text(driver, msg, adjustBrightness(0xff0000, 0.5));
}

void battery_check(BoardDriver &driver) {
  // Using context from:
  // https://learn.adafruit.com/adafruit-feather-m4-express-atsamd51/power-management
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;
  measuredvbat *= 3.3;
  measuredvbat /= 1024;

  Serial.print("VBat: ");
  Serial.println(measuredvbat);
  float maximumCharge = 4.2f;
  float minimumCharge = 2.9f;
  float batteryLevel = 0.0f;
  float errorMargin = 0.2f;

  if (measuredvbat <= maximumCharge && measuredvbat >= minimumCharge) {
    batteryLevel =
        (measuredvbat - minimumCharge) / (maximumCharge - minimumCharge);
    Serial.print("Measured VBAT as capacity percentage: ");
    Serial.print(batteryLevel * 100);
    Serial.println("%");
  } else if (measuredvbat > maximumCharge &&
             measuredvbat < maximumCharge + errorMargin) {
    batteryLevel = 1.0f;
  } else if (measuredvbat < minimumCharge &&
             measuredvbat > minimumCharge - errorMargin) {
    batteryLevel = 0.0f;
  } else {
    show_vbat_warning(driver, measuredvbat);
    return;
  }

  // Now we know we can visualize a battery level
  int numberOfRowsToHighlight = batteryLevel * Y_DIM;
  uint32_t fullyChargedGreen = 0x24f00d;
  uint32_t midChargeYellow = 0xffff00;
  uint32_t lowChargeRed = 0xff0000;
  bool shouldBlink = false;

  uint32_t colorToShow = fullyChargedGreen;
  if (batteryLevel > 0.88f) {
    // Correct for rounding errors
    numberOfRowsToHighlight = Y_DIM;
  } else if (batteryLevel > 0.8) {
    numberOfRowsToHighlight = Y_DIM - 1;
  } else if (batteryLevel < 0.08f) {
    numberOfRowsToHighlight = 1;
    shouldBlink = true;
  }

  if (batteryLevel > 0.5f) {
    colorToShow = fullyChargedGreen;
  } else if (batteryLevel > 0.2f) {
    colorToShow = midChargeYellow;
  } else {
    colorToShow = lowChargeRed;
  }

  auto startedAt = millis();
  bool shouldShowOnNextCycle = false;

  while (millis() - startedAt < 3000) {
    for (int i = 0; i < X_DIM; ++i) {
      for (int j = 0; j < Y_DIM; ++j) {
        if (j >= Y_DIM - numberOfRowsToHighlight) {
          if (shouldShowOnNextCycle || !shouldBlink) {
            driver.setPixelColor(i, j, adjustBrightness(colorToShow, 0.2f));
          } else {
            driver.setPixelColor(i, j, BUTTON_OFF);
          }
        } else {
          driver.setPixelColor(i, j, BUTTON_OFF);
        }
      }
    }
    shouldShowOnNextCycle = !shouldShowOnNextCycle;

    driver.show();
    if (shouldBlink) {
      delay(80);
    } else {
      delay(300);
    }
  }
}