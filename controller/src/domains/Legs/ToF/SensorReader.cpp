// Copyright 2022, Mikhael Khrustik <misha@myrt.co>
//
// All components of Myrt Desk Firmware are licensed under the BSD 3-Clause
// License. See LICENSE.txt for details.

#include "SensorReader.h"
#include <ArduinoSort.h>

bool SensorReader::connect() {
  if (_connected) {
    return true;
  } else if (_sensor.begin()) {
    _connected = true;
    return true;
  }
  return false;
}

bool SensorReader::setCorrection(uint16_t correction) {
  _correction = correction;
  return true;
}

bool SensorReader::connected() {
  return _connected;
}

bool SensorReader::_measureDistance() {
  _sensor.rangingTest(&_measure, false);
  if (_measure.RangeMilliMeter <= _correction) {
    _correction = _measure.RangeMilliMeter;
    _value = 0;
  } else {
    _value = _measure.RangeMilliMeter - _correction;
  }
  return _measure.RangeStatus != 4;
}

uint16_t SensorReader::getValue(uint8_t resolution) {
  if (!_connected || resolution > 32 || resolution == 0) {
    return 0;
  }
  if (resolution == 1) {
    if (_measureDistance()) {
      return _value;
    }
    return 0;
  }

  uint16_t *values = new uint16_t[resolution];
  for (_i = 0; _i < resolution; _i++) {
    if (!_measureDistance()) {
      return 0;
    }
    values[_i] = _value;
  }
  sortArray(values, resolution);
  uint16_t median = values[uint8_t(resolution / 2)];
  delete [] values;
  return median;
}
