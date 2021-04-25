#ifndef AnimationRunner_h
#define AnimationRunner_h

#include "../activity.h"
#include "../board_driver.h"

#include <functional>

/**
 * AnimationRunner is an Activity meant to wrap simple function-based
 * animations. It's useful when you want to quickly write up an
 * animation and don't care about interruptions/user input.
 *
 * The function provided will then be run and after finishing, transition
 * back to main menu.
 *
 * Ideally, if the animation is long running, it would not use this wrapper.
 * Since the function cannot be "interrupted", it means that you won't be
 * able to quit the activity by triple-pressing the left-top button.
 */
class AnimationRunner : public Activity {
public:
  AnimationRunner(std::function<void(BoardDriver &)> animation)
      : _animation(animation) {}
  void loop(BoardDriver &driver);
  void handleEvent(keyEvent event, BoardDriver &driver);

private:
  std::function<void(BoardDriver &)> _animation;
};

#endif
