#include <LiquidCrystal_I2C.h>
#include <button_Arduino_hatyai.h>
#include "LcdManu_Arduino_hatyai.h"
#include "EEPROM_Arduino_hatyai.h"
#include "Control_Arduino_hatyai.h"
ProcessManager pm("process");
// LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Buttons
#define okPin 18
#define upPin 16
#define downPin 17

ButtonControl okButton(okPin);
ButtonControl upButton(upPin);
ButtonControl downButton(downPin);

// ตัวแปรจริง
// int processTime = 300;
// float setTemp = 25.0;
// bool loadState = false;
float sensorValue = 7.1;
int motorSpeed = 5;
float pressure =  7.6;
bool heater = 1;
int cycleCount = 8;
// สร้างเมนู (3 menu + 4 display)
LCDMenu menu(lcd, okButton, upButton, downButton, 3, 10);
unsigned long xt =0;


struct MyConfig {
  int processTime;
  float setTemp;
  bool loadState;
};
MyConfig config;

void setup() {
  Serial.begin(115200);

  // โหมดแก้ไขค่า
  menu.setMenu(0, "Process", TIME, &config.processTime, 60);
  menu.setMenu(1, "SP_Temp", FLOAT, &config.setTemp, 0.1);
  menu.setMenu(2, "Load1", BOOL, &config.loadState, 1);

    // บอก library ให้จัดการ struct นี้
  pm.begin(&config, sizeof(config));

  // เปลี่ยนค่าแล้วบันทึก
  // config.processTime = 120;
  // pm.setChanged();

  // โหมดแสดงผล - เพิ่มรายการเพื่อทดสอบการเลื่อน
  menu.setDisplay(0, "1", TIME, &config.processTime);
  menu.setDisplay(1, "2", FLOAT, &config.setTemp);
  menu.setDisplay(2, "3", BOOL, &config.loadState);
  menu.setDisplay(3, "4", FLOAT, &sensorValue);

  menu.setDisplay(4, "5", INT, &motorSpeed);
  menu.setDisplay(5, "6", FLOAT, &pressure);
  menu.setDisplay(6, "7", BOOL, &heater);
  menu.setDisplay(7, "8", INT, &cycleCount);
  
  menu.setDisplay(8, "9", BOOL, &heater);
  menu.setDisplay(9, "10", TIME, &xt);

  menu.begin();

  // ✅ ทุกครั้งที่ค่ามีการเปลี่ยน → เซฟ
  menu.onValueChanged([](){
    pm.setChanged();  
  });
}

CreateCondition sensor0;
double sensorValue0 = 0;
bool result0;
bool result1;

void loop() {
  menu.update();
  xt = millis()/1000;
  // อัปเดตค่า sensor (ตัวอย่าง)
    sensorValue0 = random(0, 1000);
    Serial.print("sensorValue0: ");
    Serial.print(sensorValue0);
    Serial.print("-->");
    
    sensor0.inBetween(&sensorValue0, 200, 600, HIGH, &result0);
    sensor0.onChangeState(&sensorValue0, 200, 600, HIGH, &result1);
    Serial.print(result0);
    Serial.println(result1);
    delay(1000);
}