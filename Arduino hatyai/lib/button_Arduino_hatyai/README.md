# button_Arduino_hatyai

ไลบรารีสำหรับอ่านสถานะปุ่มกดบน Arduino พร้อมฟังก์ชัน Debounce ป้องกันการอ่านค่าเด้งซ้ำ เหมาะกับงานที่ต้องการตรวจจับการกดปุ่มแบบแม่นยำและลดการเกิด false trigger

---

## ส่วนที่ต้อง include

```cpp
#include <button_Arduino_hatyai.h>
```

---

## การประกาศและเริ่มต้นใช้งาน

```cpp
ButtonHatyai button(2); // ระบุขา (pin) ที่ต่อปุ่มกด
```

---

## วิธีใช้งาน

### 1. ตั้งค่าเริ่มต้น

```cpp
button.begin(); // ตั้งค่าขาเป็น INPUT_PULLUP และอ่านสถานะเริ่มต้น
```

### 2. อ่านสถานะปุ่มแบบ Debounce

```cpp
if (button.read()) {
  // ปุ่มถูกกด (LOW) 1 ครั้ง (edge detection)
}
```

### 3. ปรับระยะเวลา debounce

```cpp
button.setDebounceDelay(100); // ตั้งเวลา debounce เป็น 100 ms (ค่ามาตรฐานคือ 50 ms)
```

---

## ตัวอย่างการใช้งานจริง

```cpp
#include <button_Arduino_hatyai.h>

ButtonHatyai button(2); // ปุ่มต่อกับขา 2

void setup() {
  Serial.begin(115200);
  button.begin();
}

void loop() {
  if (button.read()) {
    Serial.println("Button pressed!");
  }
}
```

---

## รายละเอียดฟังก์ชัน

| ฟังก์ชัน                       | คำอธิบาย                                         |
|---------------------------------|--------------------------------------------------|
| `ButtonHatyai(uint8_t pin)`     | สร้างอ็อบเจกต์และระบุขาที่ต่อกับปุ่ม            |
| `begin()`                       | ตั้งค่าขาเป็น INPUT_PULLUP และอ่านสถานะเริ่มต้น  |
| `read()`                        | คืนค่า true เมื่อมีการกดปุ่ม (LOW) 1 ครั้ง       |
| `setDebounceDelay(unsigned long delay)` | ปรับระยะเวลา debounce ตามต้องการ          |

---

## หมายเหตุเพิ่มเติม

- ใช้กับปุ่มที่ต่อแบบ Active LOW ร่วมกับ INPUT_PULLUP
- Debounce ป้องกันการอ่านค่าซ้ำเมื่อปุ่มเด้ง
- หากต้องการรองรับ long press, double click สามารถขยาย logic ได้ตามต้องการ

---

## License

MIT License © 2025 Voraches
