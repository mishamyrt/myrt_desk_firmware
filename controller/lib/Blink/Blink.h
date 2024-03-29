// Copyright 2022, Mikhael Khrustik <misha@myrt.co>
//
// All components of Myrt Desk Firmware are licensed under the BSD 3-Clause
// License. See LICENSE.txt for details.

#pragma once

#include "Arduino.h"

#ifdef ESP32
#define LED_BUILTIN 2
#endif

/// Simple function, that uses internal LED for
void blink(uint8_t times = 1);
