#include <LiquidCrystal_I2C.h>
#include <ButtonControl.h>
#include "LCDMenu.h"

// LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Buttons
#define okPin 18
#define upPin 17
#define downPin 16

ButtonControl okButton(okPin);
ButtonControl upButton(upPin);
ButtonControl downButton(downPin);

// ตัวแปรจริง
int processTime = 300;
float setTemp = 25.0;
bool loadState = false;
float sensorValue = 7.1;
int motorSpeed = 5;
float pressure =  7.6;
bool heater = 1;
int cycleCount = 8;
// สร้างเมนู (3 menu + 4 display)
LCDMenu menu(lcd, okButton, upButton, downButton, 3, 10);
unsigned long xt =0;

void setup() {
  Serial.begin(115200);

  // โหมดแก้ไขค่า
  menu.setMenu(0, "Process", TIME, &processTime, 60);
  menu.setMenu(1, "SP_Temp", FLOAT, &setTemp, 0.1);
  menu.setMenu(2, "Load1", BOOL, &loadState, 1);

  // โหมดแสดงผล - เพิ่มรายการเพื่อทดสอบการเลื่อน
  menu.setDisplay(0, "Process", TIME, &processTime);
  menu.setDisplay(1, "SP_Temp", FLOAT, &setTemp);
  menu.setDisplay(2, "Load1", BOOL, &loadState);
  menu.setDisplay(3, "Sensor", FLOAT, &sensorValue);

  menu.setDisplay(4, "Motor", INT, &motorSpeed);
  menu.setDisplay(5, "Pressure", FLOAT, &pressure);
  menu.setDisplay(6, "Heater", BOOL, &heater);
  menu.setDisplay(7, "Cycle", INT, &cycleCount);
  
  menu.setDisplay(8, "Heater", BOOL, &heater);
  menu.setDisplay(9, "TIME", TIME, &xt);

  menu.begin();
}


void loop() {
  menu.update();
  xt = millis()/1000;
  
  // อัปเดตค่า sensor (ตัวอย่าง)
  // sensorValue = readSensor(); // ใส่ฟังก์ชันอ่านค่า sensor จริงตรงนี้
}