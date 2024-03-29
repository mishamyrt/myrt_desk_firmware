// Copyright 2022, Mikhael Khrustik <misha@myrt.co>
//
// All components of Myrt Desk Firmware are licensed under the BSD 3-Clause
// License. See LICENSE.txt for details.

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "OTAListener.h"

class OTAController {
 public:
  void initialize() {
    ArduinoOTA.setPort(6100);
    ArduinoOTA.setHostname("MyrtDesk");
    ArduinoOTA.begin();
    ArduinoOTA.onStart([this](){
      this->onStart();
    });
    // TODO: Add password (18+ symbols)
  }

  void setListener(OTAListener *listener) {
    this->listener = listener;
  }

  void onStart() {
    if (listener != NULL) {
      listener->onOTAStart();
    }
  }

  void handle() {
    ArduinoOTA.handle();
  }

 private:
  OTAListener *listener;
};

extern OTAController OTA;
