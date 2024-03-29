// Copyright 2022, Mikhael Khrustik <misha@myrt.co>
//
// All components of Myrt Desk Firmware are licensed under the BSD 3-Clause
// License. See LICENSE.txt for details.

#pragma once

#include <Arduino.h>
#include <Store.h>
#include "../DapMaster/DapMaster.h"
#include "../AVRLord/AVRLord.h"
#include "../../constants.h"

#define LIGHTSTRIP_CONNECT_ATTEMPTS 3

struct RGB {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

struct BacklightState {
  ColorMode mode = MODE_RGB;
  RGB color;
  uint8_t temperature = 0;
  uint8_t brightness = 100;
  uint8_t effect = 0;
  bool enabled = false;
};

class BacklightController : public DapController {
 public:
  BacklightController(DapMaster *connection, AVRLord *board);

  // State getters
  ColorMode mode() {
    return _state.mode;
  }
  RGB color() {
    return _state.color;
  }
  uint8_t temperature() {
    return _state.temperature;
  }
  uint8_t brightness() {
    return _state.brightness;
  }
  bool enabled() {
    return _state.enabled;
  }
  uint8_t effect() {
    return _state.effect;
  }

  // DapController hooks
  void onError();
  void onConnect();

  void connect();
  void handle();
  void updateFirmware(FirmwareReader *reader);

  // State setter
  bool setColor(uint8_t r, uint8_t g, uint8_t b);
  bool setBrightness(uint8_t brightness);
  bool setTemperature(uint8_t temperature);
  bool setTransition(uint16_t transition);
  bool setEffect(uint8_t effect_code);
  bool setEffect(uint8_t effect_code, uint8_t *args, uint8_t length);
  bool setEffectData(uint8_t *data, uint8_t length);
  bool powerOn();
  bool powerOff();


 private:
  // Internal variables
  bool _connected;
  uint8_t _connect_attempts;

  // External connections
  DapMaster *_data;
  AVRLord *_board;

  BacklightState _state;
  Stored _descriptor = Stored(_state, DOMAIN_BACKLIGHT);

  FirmwareReader *_firmware = NULL;

  void _tryConnect();
  void _applyState();
};
