#include "Control_Arduino_hatyai.h"

CreateCondition::CreateCondition()
  : _sensor(0), _low(0), _high(0), _resultTarget(false), lastResult(false) {}

bool CreateCondition::inBetween(double *sensor, double low, double high, bool resultTarget, bool *result) {
  _sensor = (sensor != nullptr) ? *sensor : 0;
  _low = low;
  _high = high;
  _resultTarget = resultTarget;

  bool output = (_sensor >= _low && _sensor <= _high) ? _resultTarget : !_resultTarget;
  if (result) *result = output;
  return output;
}

bool CreateCondition::onChangeState(double *sensor, double low, double high, bool resultTarget, bool *result) {
  _sensor = (sensor != nullptr) ? *sensor : 0;
  _low = low;
  _high = high;
  _resultTarget = resultTarget;

  if (_sensor > _high && lastResult != _resultTarget) {
    lastResult = _resultTarget;
  } else if (_sensor < _low && lastResult != !_resultTarget) {
    lastResult = !_resultTarget;
  }

  if (result) *result = lastResult;
  return lastResult;
}
