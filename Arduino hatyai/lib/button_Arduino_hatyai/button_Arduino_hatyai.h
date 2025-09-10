/*---------------------------------------------------------
  Program  : ButtonControl
  Descr    : Library to control push button click times
  Author   : Fellipe Couto [ http://www.efeitonerd.com.br ]
  GitHub   : https://github.com/fellipecouto/ButtonControl
  Date     : 2023-08-20
  ---------------------------------------------------------*/
#ifndef button_Arduino_hatyai_h
#define button_Arduino_hatyai_h
#include "Arduino.h"

class ButtonControl {
public:
  //Library instance with pin number the button is connected to
  //Optional parameters if not declared assume default values
  ButtonControl(uint8_t buttonPin, bool internalPullup = true, bool logicSignal = LOW);

  //Returns true if the button is pressed. Only short clicks and no click counts. Default parameter true to keep clicks while the button is pressed
  bool fastClick(bool continuous = true);

  //Returns true if the button is pressed. Short or long click
  bool click();

  //Returns true if a double click is pressed
  bool doubleClick();

  //Returns true only if there is a long click (after button is released)
  bool longClick();

  //Returns true if button is currently being long-pressed (real-time detection)
  bool isLongClickPressed();

  //Debug function to check current press time
  unsigned long getCurrentPressTime();

  /* GETS */
  //Returns the number of short clicks
  int getButtonClicks();

  //Returns the elapsed time of the long click in milliseconds
  long getLongClickTime();

  //Returns the configured minimum time for the long click
  int getMinLongClickTime();

  //Returns the time range for continuous clicks
  int getFastClickContinuousTime();

  /* SETS */
  //Sets the minimum time for the long click. Default value 1000 milliseconds
  void setMinLongClickTime(int minimumTime = 1000);

  //Sets the time of continuous clicks. Default value 200 milliseconds
  void setFastClickContinuousTime(int continuousTime = 200);

private:
  uint8_t _pin;
  bool _longClick;
  long _buttonTimes;
  int _buttonClicks;
  int _longMinClickTime = 1000;
  bool _continuous;
  int _continuousTime = 200;
  int _debounceTime = 40;
  bool _signal;
  unsigned long _pressStartTime = 0;
  bool _buttonPressed = false;
  bool _longClickTriggered = false;
  
  void verifyButton(bool fast, bool doubleClick);
  void updateButtonState();
};
#endif