#pragma once

typedef enum {
  COMMAND_SET_COLOR = 1,
  COMMAND_SET_BRIGHTNESS = 2,
  COMMAND_SET_WHITE_TEMPERATURE = 3,
  COMMAND_SET_TRANSITION = 4,
  COMMAND_SET_EFFECT = 5
} BacklightCommand;

typedef enum {
  MODE_RGB = 0,
  MODE_TEMPERATURE = 1
} ColorMode;