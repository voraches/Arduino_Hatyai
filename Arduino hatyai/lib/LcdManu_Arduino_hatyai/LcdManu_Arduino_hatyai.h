#ifndef LCDMENU_H
#define LCDMENU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <button_Arduino_hatyai.h>

#define INT   0
#define FLOAT 1
#define BOOL  2
#define TIME  3

struct createMenu {
  String name;
  int type;
  void *value;
  float step;
};

// class LCDMenu {
//   public:
//     LCDMenu(LiquidCrystal_I2C &lcd, ButtonControl &ok, ButtonControl &up, ButtonControl &down, int numMenu, int numDisplay);
//     ~LCDMenu(); // เพิ่ม destructor

//     void setMenu(int index, String name, int type, void *value, float step = 1);
//     void setDisplay(int index, String name, int type, void *value);

//     void begin();
//     void update();

//   private:
//     LiquidCrystal_I2C &_lcd;
//     ButtonControl &_okButton;
//     ButtonControl &_upButton;
//     ButtonControl &_downButton;

//     int _indexMenu;
//     int _indexDisplay;   // เพิ่มตัวแปรสำหรับเลื่อนใน display mode
//     bool _editMode;
//     bool _displayMode;   // false = menu (แก้ไข), true = display (ดูอย่างเดียว)

//     int _numMenu;
//     int _numDisplay;
//     createMenu *_menu;
//     createMenu *_display;
    
//     unsigned long _lastRefresh;


//     void okClick();
//     void okHold();
//     void upClick();
//     void downClick();

//     void action();
//     void drawMenu();
//     void drawDisplay();

//     String printTimeFormat(long totalSeconds);
//     void printStatus(int state);
//     void printValue(const createMenu &item, int precision = 1);
// };
// ... (ส่วนบนเหมือนเดิม)

class LCDMenu {
  public:
    LCDMenu(LiquidCrystal_I2C &lcd, ButtonControl &ok, ButtonControl &up, ButtonControl &down, int numMenu, int numDisplay);
    ~LCDMenu();

    void setMenu(int index, String name, int type, void *value, float step = 1);
    void setDisplay(int index, String name, int type, void *value);

    void begin();
    void update();

    // ✅ เพิ่ม callback
    typedef void (*CallbackFunction)();
    void onValueChanged(CallbackFunction cb) { _onChange = cb; }

  private:
    LiquidCrystal_I2C &_lcd;
    ButtonControl &_okButton;
    ButtonControl &_upButton;
    ButtonControl &_downButton;

    int _indexMenu;
    int _indexDisplay;
    bool _editMode;
    bool _displayMode;

    int _numMenu;
    int _numDisplay;
    createMenu *_menu;
    createMenu *_display;
    
    unsigned long _lastRefresh;

    CallbackFunction _onChange = nullptr;   // ✅ callback

    void okClick();
    void okHold();
    void upClick();
    void downClick();

    void action();
    void drawMenu();
    void drawDisplay();

    String printTimeFormat(long totalSeconds);
    void printStatus(int state);
    void printValue(const createMenu &item, int precision = 1);
};


#endif