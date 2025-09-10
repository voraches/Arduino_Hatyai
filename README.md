# Arduino Hatyai Library

ไลบรารีสำหรับ Arduino ที่รวบรวมฟังก์ชันสำคัญเพื่อใช้งานกับเซนเซอร์, การจัดการ EEPROM, จอ LCD เมนู และการอ่านปุ่มกด เหมาะสำหรับโปรเจค IoT และ Embedded Systems ที่ต้องการความสะดวกและประสิทธิภาพในการพัฒนา

## ไลบรารี่ที่มีในชุด

### 1. Control_Arduino_hatyai

**สำหรับตรวจสอบเงื่อนไขเซนเซอร์และการเปลี่ยนแปลงสถานะ**

- ฟังก์ชันหลัก
  - ตรวจสอบค่าว่าตรงตามช่วงที่กำหนดหรือไม่ (`inBetween`)
  - ตรวจจับการเปลี่ยนสถานะเมื่อค่าหลุดขอบเขต (`onChangeState`)
  - กำหนดค่าเริ่มต้นและอ่านสถานะล่าสุดได้

**ตัวอย่างการใช้งาน**
```cpp
CreateCondition condition;
double sensorValue = ...;
bool result;
condition.inBetween(&sensorValue, 10, 20, true, &result);
```

---

### 2. EEPROM_Arduino_hatyai

**สำหรับจัดการข้อมูลใน EEPROM ด้วย Preferences Library (ESP32)**

- ฟังก์ชันหลัก
  - บันทึกข้อมูลแบบ struct หรือ array ลง EEPROM (`save`)
  - โหลดข้อมูลจาก EEPROM (`load`)
  - เซ็ตสถานะเปลี่ยนแปลงข้อมูลและบันทึกอัตโนมัติ (`setChanged`)

**ตัวอย่างการใช้งาน**
```cpp
struct MyData { int a; float b; };
MyData data;
ProcessManager manager("myNamespace");
manager.begin(&data, sizeof(data));
manager.setChanged();
```

---

### 3. LcdManu_Arduino_hatyai

**สำหรับแสดงเมนูบนจอ LCD แบบ I2C**

- ฟังก์ชันหลัก
  - สร้างเมนูจาก array ชื่อเมนู (`begin`)
  - เลื่อนเมนูขึ้น/ลง (`next`, `prev`)
  - แสดงผลเมนูและสถานะปัจจุบัน (`display`)

**ตัวอย่างการใช้งาน**
```cpp
const char* menuItems[] = {"Menu1", "Menu2", "Menu3"};
LiquidCrystal_I2C lcd(0x27, 16, 2);
MenuLcd menu;
menu.begin(&lcd, menuItems, 3);
menu.next();
```

---

### 4. button_Arduino_hatyai

**สำหรับอ่านค่าปุ่มกดและลดปัญหา debounce**

- ฟังก์ชันหลัก
  - อ่านสถานะปุ่มกดแบบกรองการเด้งสัญญาณ (`read`)
  - ปรับระยะเวลา debounce (`setDebounceDelay`)

**ตัวอย่างการใช้งาน**
```cpp
ButtonHatyai button(2);
button.begin();
if (button.read()) {
  // กดปุ่ม
}
```

---

## การติดตั้ง

1. ดาวน์โหลดไฟล์ `.cpp` และ `.h` ของแต่ละไลบรารี่ไปไว้ในโฟลเดอร์โปรเจค Arduino ของคุณ
2. เพิ่มคำสั่ง `#include` ในไฟล์หลักของคุณตามไลบรารี่ที่ต้องการใช้งาน

## การใช้งาน

ดูตัวอย่างโค้ดในแต่ละหัวข้อด้านบน หรือศึกษาเพิ่มเติมได้จากไฟล์ตัวอย่างในโปรเจคนี้

---

## License

MIT License © 2025 Voraches
