// Copyright 2022, Mikhael Khrustik <misha@myrt.co>
//
// All components of Myrt Desk Firmware are licensed under the BSD 3-Clause
// License. See LICENSE.txt for details.
#pragma once

#include <Adafruit_VL53L0X.h>

class SensorReader {
  public:
    bool connect();
    bool connected();

    bool setCorrection(uint16_t correction);
    uint16_t getValue(uint8_t resolution);

  private:
    bool _connected = false;
    uint8_t _i = 0;
    uint16_t _correction = 0;
    uint16_t _value = 0;
    uint32_t _summ = 0;
    Adafruit_VL53L0X _sensor = Adafruit_VL53L0X();
    VL53L0X_RangingMeasurementData_t _measure;

    bool _measureDistance();
    uint16_t _getCorrected();
};
