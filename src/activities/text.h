#ifndef Text_h
#define Text_h

#include "../board_driver.h"
#include <string>

/**
 * Utility functions to display the actual text.
 *
 * Note that these utilities are displaying the text as a function call,
 * meaning this cannot introduce interruptions.
 *
 * TODO: Turn display_text into interruptable animations.
 */

void display_text(BoardDriver &driver, char *text, uint32_t color);

void display_text_example(BoardDriver &driver);

#endif