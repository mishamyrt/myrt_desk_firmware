#pragma once

typedef enum {
  COMMAND_POWER_OFF = 0,
  COMMAND_POWER_ON = 1,
  COMMAND_SET_COLOR = 2,
  COMMAND_SET_COLOR_ZONES = 3,
  COMMAND_START_EFFECT = 4,
  COMMAND_SET_TEMPERATURE = 5,
} LightstripCommand;

typedef enum {
  MODE_RGB,
  MODE_TEMPERATURE,
  MODE_EFFECT
} ColorMode;