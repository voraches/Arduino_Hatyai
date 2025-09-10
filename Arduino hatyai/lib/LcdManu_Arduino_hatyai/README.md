# LcdManu_Arduino_hatyai

ไลบรารีสำหรับสร้างเมนูและแสดงผลบนจอ LCD I2C ใน Arduino เหมาะกับงานที่ต้องการ UI สำหรับเลือกเมนูหรือแสดงสถานะต่าง ๆ สามารถใช้งานร่วมกับ LiquidCrystal_I2C ได้ทันที

---

## ส่วนที่ต้อง include

```cpp
#include <LcdManu_Arduino_hatyai.h>
#include <LiquidCrystal_I2C.h>
```

---

## การประกาศและเริ่มต้นใช้งาน

```cpp
// กำหนดหัวข้อเมนู
const char* menuItems[] = {"Home", "Settings", "Info"};

// สร้างอ็อบเจกต์ LCD และเมนู
LiquidCrystal_I2C lcd(0x27, 16, 2); // address, columns, rows
MenuLcd menu;
```

---

## วิธีใช้งาน

### 1. เริ่มต้นเมนู

```cpp
menu.begin(&lcd, menuItems, 3); // lcd pointer, array เมนู, จำนวนรายการ
```

### 2. เลื่อนเมนูไปข้างหน้า

```cpp
menu.next(); // ไปยังเมนูถัดไป (ถ้ามี)
```

### 3. เลื่อนเมนูกลับ

```cpp
menu.prev(); // กลับไปเมนูก่อนหน้า (ถ้ามี)
```

### 4. แสดงผลเมนูปัจจุบันบนจอ LCD

```cpp
menu.display();
```

### 5. อ่านตำแหน่งเมนูปัจจุบัน

```cpp
uint8_t idx = menu.getIndex(); // คืนค่าดัชนีเมนูปัจจุบัน
```

---

## ตัวอย่างการใช้งานจริง

```cpp
#include <LcdManu_Arduino_hatyai.h>
#include <LiquidCrystal_I2C.h>

const char* menuItems[] = {"Home", "Settings", "Info"};
LiquidCrystal_I2C lcd(0x27, 16, 2);
MenuLcd menu;

void setup() {
  lcd.begin();
  lcd.backlight();
  menu.begin(&lcd, menuItems, 3);
}

void loop() {
  if (digitalRead(2) == LOW) { // สมมติปุ่มต่อกับขา 2
    menu.next(); // เลื่อนเมนู
    delay(200);
  }
  if (digitalRead(3) == LOW) { // สมมติปุ่มต่อกับขา 3
    menu.prev(); // ย้อนเมนู
    delay(200);
  }
}
```

---

## รายละเอียดฟังก์ชัน

| ฟังก์ชัน                                                | คำอธิบาย                      |
|---------------------------------------------------------|-------------------------------|
| `begin(LiquidCrystal_I2C* lcdPtr, const char** items, uint8_t size)` | เริ่มต้นเมนูและแสดงผลครั้งแรก |
| `next()`                                                | เลื่อนไปเมนูถัดไป              |
| `prev()`                                                | เลื่อนกลับเมนูก่อนหน้า          |
| `display()`                                             | แสดงชื่อเมนูและสถานะบนจอ LCD   |
| `getIndex()`                                            | คืนค่าดัชนีเมนูปัจจุบัน         |

---

## หมายเหตุเพิ่มเติม

- เมนูจะแสดงชื่อหัวข้อและสถานะว่าอยู่ใน item ที่เท่าไร
- เหมาะกับเมนูที่มีจำนวนหัวข้อไม่มาก (1-10 หัวข้อ)
- สามารถนำไปปรับแต่งแสดงผลเพิ่มเติมบน LCD ได้ตามต้องการ

---

## License

MIT License © 2025 Voraches
