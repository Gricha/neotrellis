#include "text.h"

#include "../consts.h"
#include "../core/alphabet.h"
#include "../utils.h"
#include <random>
#include <string>
#include <vector>

void display_text_bitmap(BoardDriver &driver,
                         std::vector<std::vector<bool>> &bitmap,
                         uint32_t color) {
  if (bitmap.size() == 0) {
    return;
  }

  auto numberOfColumns = bitmap[0].size();
  auto expectedNumberOfRefreshes = numberOfColumns + 2 * X_DIM;

  int bitmapOffset = -X_DIM; // Always start right behind the fold

  for (int i = 0; i < expectedNumberOfRefreshes; ++i) {
    auto iterationOffset = bitmapOffset + i;
    for (int x = 0; x < X_DIM; ++x) {
      int bitmapCoordinateX = x + iterationOffset;
      for (int y = 0; y < Y_DIM; ++y) {
        // For each cell, print what bit would be there, minus the offset
        if (bitmapCoordinateX < 0 || bitmapCoordinateX >= numberOfColumns) {
          driver.setPixelColor(x, y, BUTTON_OFF); // Clean up cells
        } else {
          if (bitmap[y][bitmapCoordinateX]) {
            driver.setPixelColor(x, y, color);
          } else {
            driver.setPixelColor(x, y, BUTTON_OFF);
          }
        }
      }
    }

    driver.show();
    delay(100);
  }
}

void display_text(BoardDriver &driver, char *text, uint32_t color) {
  auto bitmap = convert_string_to_bitmap(text);
  display_text_bitmap(driver, bitmap, color);
}

void display_text_example(BoardDriver &driver) {
  const char *text_example = "Hello!";

  auto bitmap = convert_string_to_bitmap(text_example);

  log_bitmap_human_readable(bitmap);

  auto seed = random();
  std::seed_seq seed_sequence = {seed};
  std::mt19937 gen(seed_sequence);
  std::uniform_int_distribution<int> colorRandomizer(
      0, 100); // because we don't want very bright tints on this device
  auto r = colorRandomizer(gen);
  auto g = colorRandomizer(gen);
  auto b = colorRandomizer(gen);
  uint32_t c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;

  display_text_bitmap(driver, bitmap, c);
}