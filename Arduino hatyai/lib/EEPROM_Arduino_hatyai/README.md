# EEPROM_Arduino_hatyai

ไลบรารีสำหรับจัดการข้อมูลใน EEPROM ด้วย Preferences Library (เหมาะกับ ESP32) สามารถบันทึกและโหลดข้อมูลที่เป็น struct หรือ array ได้อย่างง่ายดาย พร้อมรองรับ namespace เพื่อแยกข้อมูลแต่ละชุด

---

## ส่วนที่ต้อง include

```cpp
#include <EEPROM_Arduino_hatyai.h>
```

---

## การประกาศและเริ่มต้นใช้งาน

```cpp
// กำหนด struct ข้อมูลที่ต้องการเก็บ
struct MyData {
  int counter;
  float value;
};

// สร้างตัวแปร struct และ ProcessManager
MyData data = {0, 0.0};
ProcessManager manager("myNamespace"); // ระบุ namespace สำหรับจัดการข้อมูล
```

---

## วิธีใช้งาน

### 1. เริ่มต้นการจัดการข้อมูล

```cpp
manager.begin(&data, sizeof(data)); // ให้ manager รู้ว่าจะจัดการข้อมูลอะไร ขนาดเท่าไร
```

### 2. โหลดข้อมูลจาก EEPROM

```cpp
manager.load(); // จะโหลดข้อมูลเข้า struct หากเคยบันทึกไว้แล้ว
```

### 3. บันทึกข้อมูลลง EEPROM

```cpp
manager.save(); // อัปเดตข้อมูลที่อยู่ใน EEPROM
```

### 4. เซ็ต flag ว่าข้อมูลเปลี่ยนแปลง (แล้วจะบันทึกอัตโนมัติ)

```cpp
data.counter++;
manager.setChanged(); // เมื่อข้อมูลถูกเปลี่ยนให้เรียกฟังก์ชันนี้เพื่อบันทึกลง EEPROM ทันที
```

---

## ตัวอย่างการใช้งานจริง

```cpp
#include <EEPROM_Arduino_hatyai.h>

struct MyData {
  int counter;
  float value;
};

MyData data;
ProcessManager manager("myNamespace");

void setup() {
  Serial.begin(115200);
  manager.begin(&data, sizeof(data));
  Serial.print("Counter: ");
  Serial.println(data.counter);
}

void loop() {
  // จำลองการเปลี่ยนแปลงข้อมูล
  data.counter++;
  data.value = analogRead(A0);

  manager.setChanged(); // บันทึกข้อมูลใหม่ทุกครั้งที่เปลี่ยน
  delay(1000);
}
```

---

## รายละเอียดฟังก์ชัน

| ฟังก์ชัน               | คำอธิบาย                                                         |
|------------------------|-------------------------------------------------------------------|
| `begin(void* data, size_t size)` | กำหนดข้อมูลและขนาดที่ต้องการจัดการ                        |
| `save()`               | บันทึกข้อมูลลง EEPROM                                            |
| `load()`               | โหลดข้อมูลจาก EEPROM                                             |
| `setChanged(bool changed = true)` | เซ็ต flag และบันทึกข้อมูลทันทีเมื่อข้อมูลเปลี่ยนแปลง      |

---

## หมายเหตุเพิ่มเติม

- ไลบรารีนี้ใช้ Preferences ของ ESP32 ในการจัดการ EEPROM
- สามารถใช้กับข้อมูลประเภท struct, array หรือ primitive ได้
- ควรระบุ namespace ให้ไม่ชนกับชุดข้อมูลอื่น

---

## License

MIT License © 2025 Voraches
