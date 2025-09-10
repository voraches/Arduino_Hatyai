#include "LcdManu_Arduino_hatyai.h"

LCDMenu::LCDMenu(LiquidCrystal_I2C &lcd, ButtonControl &ok, ButtonControl &up, ButtonControl &down, int numMenu, int numDisplay)
    : _lcd(lcd), _okButton(ok), _upButton(up), _downButton(down), _numMenu(numMenu), _numDisplay(numDisplay)
{
  _indexMenu = 0;
  _indexDisplay = 0;
  _editMode = false;
  _displayMode = false;
  _lastRefresh = 0; // ✅ เริ่มต้นเวลา
  _menu = new createMenu[_numMenu];
  _display = new createMenu[_numDisplay];
}

// เพิ่ม destructor เพื่อป้องกัน memory leak
LCDMenu::~LCDMenu()
{
  delete[] _menu;
  delete[] _display;
}

void LCDMenu::setMenu(int index, String name, int type, void *value, float step)
{
  if (index < 0 || index >= _numMenu || value == nullptr)
    return; // เพิ่ม error checking
  _menu[index] = {name, type, value, step};
}

void LCDMenu::setDisplay(int index, String name, int type, void *value)
{
  if (index < 0 || index >= _numDisplay || value == nullptr)
    return; // เพิ่ม error checking
  _display[index] = {name, type, value, 0};
}

void LCDMenu::begin()
{
  Wire.setPins(21, 22);
  Wire.begin();
  _lcd.init();
  _lcd.backlight();

  // สร้าง custom characters
  byte customChar1[] = {
      B00100, B01110, B11111, B00000,
      B00000, B11111, B01110, B00100};
  byte customChar2[] = {
      B10000, B11000, B11100, B11110,
      B11110, B11100, B11000, B10000};
  _lcd.createChar(0, customChar1);
  _lcd.createChar(1, customChar2);

  // เริ่มแสดงผลเมนูหรือ display
  // _okButton.setMinLongClickTime(300);
  _okButton.setFastClickContinuousTime(200);
  _okButton.setMinLongClickTime(1000);
  action();
}

void LCDMenu::update()
{
  // ตรวจสอบปุ่ม OK
  if (_okButton.click())
  {
    okClick();
  }
  if (_okButton.longClick())
  {
    okHold();
  }
  // if (_okButton.isLongClickPressed()) {
  //   okHold();
  // }

  // ตรวจสอบปุ่ม UP
  if (_upButton.fastClick(true))
  {
    upClick();
  }

  // ตรวจสอบปุ่ม DOWN
  if (_downButton.fastClick(true))
  {
    downClick();
  }

  // ✅ รีเฟรชทุกครึ่งวินาทีเมื่ออยู่ใน display mode
  if (_displayMode)
  {
    unsigned long now = millis();
    if (now - _lastRefresh >= 500)
    {
      _lastRefresh = now;
      drawDisplay();
    }
  }
}

void LCDMenu::okClick()
{
  if (!_displayMode)
  {
    _editMode = !_editMode;
    action();
  }
}

void LCDMenu::okHold()
{
  // Serial.println(_okButton.getLongClickTime());
  _displayMode = !_displayMode;
  _editMode = false;
  _lcd.clear();
  action();
}

void LCDMenu::upClick()
{
  if (_displayMode)
  {
    if (_numDisplay > 4)
    {
      _indexDisplay += 4;
      if (_indexDisplay >= _numDisplay)
        _indexDisplay = _numDisplay - 4;
      //===========================
      // แสดง scroll indicator ถ้ามีมากกว่า 4 รายการ
      if (_numDisplay > 4)
      {
        _lcd.clear();
        // แสดงตำแหน่งปัจจุบัน เช่น "1/3" (หน้า 1 จาก 3)
        // int currentPage = (_indexDisplay / 4) + 1;
        // int totalPages = (_numDisplay + 3) / 4;  // round up
        _lcd.setCursor(16, 0);
        _lcd.print("NEXT");
        _lcd.setCursor(16, 1);
        _lcd.print("-->");
        // _lcd.print(String(currentPage) + "/" + String(totalPages));
      }
      delay(500);
      //===================
      action();
    }
    return;
  }

  if (_editMode)
  {
    if (_menu[_indexMenu].type == INT)
    {
      (*(int *)_menu[_indexMenu].value) += (int)_menu[_indexMenu].step;
    }
    else if (_menu[_indexMenu].type == FLOAT)
    {
      (*(float *)_menu[_indexMenu].value) += _menu[_indexMenu].step;
    }
    else if (_menu[_indexMenu].type == BOOL)
    {
      (*(bool *)_menu[_indexMenu].value) = !(*(bool *)_menu[_indexMenu].value);
    }
    else if (_menu[_indexMenu].type == TIME)
    {
      (*(int *)_menu[_indexMenu].value) += (int)_menu[_indexMenu].step;
    }
    // ✅ เรียก callback ถ้ามี
    if (_onChange)
      _onChange();
  }
  else
  {
    _indexMenu--;
    if (_indexMenu < 0)
      _indexMenu = _numMenu - 1;
  }
  action();
}

void LCDMenu::downClick()
{
  if (_displayMode)
  {

    if (_numDisplay > 4)
    {
      _indexDisplay -= 4;
      if (_indexDisplay < 0)
        _indexDisplay = 0;
      //===========================
      // แสดง scroll indicator ถ้ามีมากกว่า 4 รายการ
      if (_numDisplay > 4)
      {
        _lcd.clear();
        // แสดงตำแหน่งปัจจุบัน เช่น "1/3" (หน้า 1 จาก 3)
        // int currentPage = (_indexDisplay / 4) + 1;
        // int totalPages = (_numDisplay + 3) / 4;  // round up
        _lcd.setCursor(16, 0);
        _lcd.print("PREV");
        _lcd.setCursor(16, 1);
        _lcd.print("<--");
        // _lcd.print(String(currentPage) + "/" + String(totalPages));
      }
      delay(500);
      //===================
      action();
    }
    return;
  }

  if (_editMode)
  {
    if (_menu[_indexMenu].type == INT)
    {
      int newValue = (*(int *)_menu[_indexMenu].value) - (int)_menu[_indexMenu].step;
      (*(int *)_menu[_indexMenu].value) = max(0, newValue);
    }
    else if (_menu[_indexMenu].type == FLOAT)
    {
      float newValue = (*(float *)_menu[_indexMenu].value) - _menu[_indexMenu].step;
      (*(float *)_menu[_indexMenu].value) = max(0.0f, newValue);
    }
    else if (_menu[_indexMenu].type == BOOL)
    {
      (*(bool *)_menu[_indexMenu].value) = !(*(bool *)_menu[_indexMenu].value);
    }
    else if (_menu[_indexMenu].type == TIME)
    {
      int newValue = (*(int *)_menu[_indexMenu].value) - (int)_menu[_indexMenu].step;
      (*(int *)_menu[_indexMenu].value) = max(0, newValue);
    }
    // ✅ เรียก callback ถ้ามี
    if (_onChange)
      _onChange();
  }
  else
  {
    _indexMenu++;
    if (_indexMenu >= _numMenu)
      _indexMenu = 0;
  }
  action();
}

void LCDMenu::action()
{
  if (_displayMode)
  {
    drawDisplay();
  }
  else
  {
    drawMenu();
  }
}

void LCDMenu::drawMenu()
{
  _lcd.clear();
  int row = _indexMenu % 4;
  if (_editMode)
  {
    _lcd.setCursor(11, row);
    _lcd.write(0);
  }
  else
  {
    _lcd.setCursor(0, row);
    _lcd.write(1);
  }

  int _index = _indexMenu - row;
  for (int i = 0; i < 4; i++)
  {
    if (_index >= _numMenu)
      break;

    if (_editMode)
      _lcd.setCursor(0, i);
    else
      _lcd.setCursor(1, i);

    _lcd.print(_menu[_index].name);
    _lcd.setCursor(12, i);

    printValue(_menu[_index]); // ใช้ฟังก์ชันใหม่
    _index++;
  }
}

void LCDMenu::drawDisplay()
{
  _lcd.clear();

  // แสดงรายการตาม index ปัจจุบัน
  for (int i = 0; i < 4 && (_indexDisplay + i) < _numDisplay; i++)
  {
    int displayIndex = _indexDisplay + i;
    _lcd.setCursor(0, i);
    _lcd.print(_display[displayIndex].name);
    _lcd.setCursor(12, i);

    printValue(_display[displayIndex]);
  }
}

// ฟังก์ชันใหม่เพื่อลดการ duplicate code
void LCDMenu::printValue(const createMenu &item, int precision)
{
  if (item.type == INT)
  {
    _lcd.print(*(int *)item.value);
  }
  else if (item.type == FLOAT)
  {
    char buffer[10];
    dtostrf(*(float *)item.value, 0, precision, buffer);
    _lcd.print(buffer);
  }
  else if (item.type == BOOL)
  {
    printStatus(*(bool *)item.value);
  }
  else if (item.type == TIME)
  {
    _lcd.print(printTimeFormat(*(int *)item.value));
  }
}

String LCDMenu::printTimeFormat(long totalSeconds)
{
  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;
  char buffer[9];
  sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
  return String(buffer);
}

void LCDMenu::printStatus(int state)
{
  if (state)
    _lcd.print("ON");
  else
    _lcd.print("OFF");
}