#include "registry.h"
#include "activities/animation_runner.h"
#include "activities/changing_pulsation.h"
#include "activities/circles.h"
#include "activities/colorful_impulses.h"
#include "activities/drawings/drawing.h"
#include "activities/drawings/heart.h"
#include "activities/drawings/mario.h"
#include "activities/drawings/smile.h"
#include "activities/fire.h"
#include "activities/impulses.h"
#include "activities/intro.h"
#include "activities/lilies.h"
#include "activities/ocean.h"
#include "activities/on_off_game.h"
#include "activities/random_changing_pulsation.h"
#include "activities/snake.h"
#include "activities/text.h"
#include "activities/trees.h"
#include "activities/warmer_warmer.h"
#include "activities/wave.h"
#include "activities/whackamole.h"
#include "core/battery.h"

std::function<void(BoardDriver &)> changeState(BoardState desiredState) {
  return
      [desiredState](BoardDriver &driver) { driver.changeState(desiredState); };
}

ActivitySpecification circles_animation() {
  return {
      .factory = []() { return std::make_shared<CirclesAnimation>(); },
      .config =
          {
              .name = "circles_animation",
              .inputReadIntervalMs = 1000,
              .menuButtonColor = 0xff7f50,
          },
  };
}

ActivitySpecification snake() {
  return {
      .factory = []() { return std::make_shared<Snake>(); },
      .config =
          {
              .name = "snake",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0x00dd00,
          },
  };
}

ActivitySpecification whackamole() {
  return {
      .factory = []() { return std::make_shared<Whackamole>(400, 4000); },
      .config =
          {
              .name = "whackamole",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xff1144,
          },
  };
}

ActivitySpecification impulses() {
  return {
      .factory = []() { return std::make_shared<Impulses>(); },
      .config =
          {
              .name = "impulses",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xffff00,
          },
  };
}

ActivitySpecification colorful_impulses() {
  return {
      .factory = []() { return std::make_shared<ColorfulImpulses>(); },
      .config =
          {
              .name = "colorful_impulses",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xffff00,
          },
  };
}

ActivitySpecification whackamole_fast() {
  return {
      .factory = []() { return std::make_shared<Whackamole>(100, 1000); },
      .config =
          {
              .name = "whackamole_fast",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xff1144,
          },
  };
}

ActivitySpecification whackamole_challenge() {
  return {
      .factory = []() { return std::make_shared<Whackamole>(100, 500); },
      .config =
          {
              .name = "whackamole_challenge",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xff1144,
          },
  };
}

ActivitySpecification fire_animation() {
  return {
      .factory =
          []() {
            // Will invoke copy constructor *shrug*
            return std::make_shared<PulsatingEffect>(get_fire_config());
          },
      .config =
          {
              .name = "fire_animation",
              .inputReadIntervalMs = 500,
              .menuButtonColor = 0xb62203,
          },
  };
}

ActivitySpecification lilies_animation() {
  return {.factory =
              []() {
                // Will invoke copy constructor
                return std::make_shared<PulsatingEffect>(get_lilies_config());
              },
          .config = {
              .name = "lilies_animation",
              .inputReadIntervalMs = 500,
              .menuButtonColor = 0xff30ff,
          }};
}

ActivitySpecification ocean_animation() {
  return {
      .factory =
          []() {
            // Will invoke copy constructor *shrug*
            return std::make_shared<PulsatingEffect>(get_ocean_config());
          },
      .config =
          {
              .name = "ocean_animation",
              .inputReadIntervalMs = 500,
              .menuButtonColor = 0x045cc4,
          },
  };
}

ActivitySpecification trees_animation() {
  return {
      .factory =
          []() {
            // Will invoke copy constructor *shrug*
            return std::make_shared<PulsatingEffect>(get_trees_config());
          },
      .config =
          {
              .name = "trees_animation",
              .inputReadIntervalMs = 500,
              .menuButtonColor = 0x00dd00,
          },
  };
}

ActivitySpecification color_changing_pulsation() {
  return {
      .factory = []() { return std::make_shared<ColorChangingPulsation>(); },
      .config =
          {
              .name = "color_changing_pulsation",
              .inputReadIntervalMs = 200,
              .menuButtonColor = 0x40cc80,
          },
  };
}

ActivitySpecification random_color_changing_pulsation() {
  return {
      .factory =
          []() { return std::make_shared<RandomColorChangingPulsation>(); },
      .config =
          {
              .name = "random_color_changing_pulsation",
              .inputReadIntervalMs = 200,
              .menuButtonColor = 0x70cc50,
          },
  };
}

ActivitySpecification
wrap_animation(const char *name, std::function<void(BoardDriver &)> animation) {
  return {
      .factory =
          [animation]() {
            return std::make_shared<AnimationRunner>(animation);
          },
      .config =
          {
              .name = name,
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0x3030ff,
          },
  };
}

ActivitySpecification on_and_off_game() {
  return {
      .factory = []() { return std::make_shared<OnOffGame>(); },
      .config =
          {
              .name = "on_and_off",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0x32dd64,
          },
  };
}

ActivitySpecification warmer_warmer_game() {
  return {
      .factory = []() { return std::make_shared<WarmerWarmer>(); },
      .config =
          {
              .name = "warmer_warmer",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xec0804,
          },
  };
}

ActivitySpecification battery_check_activity() {
  return {
      .factory =
          []() { return std::make_shared<AnimationRunner>(battery_check); },
      .config =
          {
              .name = "battery_check",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xff30ff,
          },
  };
}

ActivitySpecification wave_animation() {
  return {
      .factory = []() { return std::make_shared<AnimationRunner>(wave); },
      .config =
          {
              .name = "wave",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0x54acc4,
          },
  };
}

ActivitySpecification text_animation() {
  return {
      .factory =
          []() {
            return std::make_shared<AnimationRunner>(display_text_example);
          },
      .config =
          {
              .name = "text",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xf16de1,
          },
  };
}

ActivitySpecification spacer() {
  // This is a hack, it's a spacer to space out animations, games and battery
  // check. The way the hack works is we register under BUTTON_OFF color.
  // MainMenu interpret it one off as lack of activity.

  return {.factory = []() { return std::make_shared<PlaceholderActivity>(); },
          .config = {
              .name = "placeholder",
              .inputReadIntervalMs = 10,
              .menuButtonColor = BUTTON_OFF,
          }};
}

ActivitySpecification heart_drawing() {
  return {
      .factory = []() { return std::make_shared<Drawing>(heart()); },
      .config =
          {
              .name = "heart",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xff0000,
          },
  };
}

ActivitySpecification mario_drawing() {
  return {
      .factory = []() { return std::make_shared<Drawing>(mario()); },
      .config =
          {
              .name = "mario",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xfa3802,
          },
  };
}

ActivitySpecification smile_drawing() {
  return {
      .factory = []() { return std::make_shared<Drawing>(smile()); },
      .config =
          {
              .name = "smile",
              .inputReadIntervalMs = 10,
              .menuButtonColor = 0xffff00,
          },
  };
}

std::vector<ActivitySpecification> allActivities() {
  std::vector<ActivitySpecification> activities;

  activities.push_back(circles_animation());
  activities.push_back(wrap_animation("randomized_intro", randomized_intro));
  activities.push_back(color_changing_pulsation());
  activities.push_back(random_color_changing_pulsation());
  activities.push_back(wave_animation());
  activities.push_back(text_animation());
  activities.push_back(fire_animation());
  activities.push_back(ocean_animation());
  activities.push_back(trees_animation());
  activities.push_back(lilies_animation());
  activities.push_back(heart_drawing());
  activities.push_back(smile_drawing());
  for (int i = 0; i < 6; ++i) {
    activities.push_back(spacer());
  }
  activities.push_back(on_and_off_game());
  activities.push_back(warmer_warmer_game());
  activities.push_back(snake());
  activities.push_back(whackamole());
  activities.push_back(whackamole_fast());
  activities.push_back(whackamole_challenge());
  activities.push_back(impulses());
  activities.push_back(colorful_impulses());
  for (int i = 0; i < 9; ++i) {
    activities.push_back(spacer());
  }
  activities.push_back(battery_check_activity());

  return activities;
}