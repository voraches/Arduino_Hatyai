#ifndef Control_Arduino_hatyai_H
#define Control_Arduino_hatyai_H

#include <Arduino.h>

class CreateCondition {
  public:
    CreateCondition();

    bool inBetween(double *sensor, double low, double high, bool resultTarget, bool *result);
    bool onChangeState(double *sensor, double low, double high, bool resultTarget, bool *result);

    void setOnChangeInitial(bool s) { lastResult = s; }
    bool getOnChangeState() const { return lastResult; }

  private:
    double _sensor;
    double _low;
    double _high;
    bool   _resultTarget;
    bool   lastResult;
};

#endif
