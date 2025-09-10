# Control_Arduino_hatyai

ไลบรารีสำหรับตรวจสอบและจัดการเงื่อนไขข้อมูลเซนเซอร์ใน Arduino สามารถใช้งานกับข้อมูลต่าง ๆ เช่น อุณหภูมิ, ความชื้น, หรือค่าจากอุปกรณ์วัดอื่น ๆ เหมาะสำหรับงาน IoT ที่ต้องการตรวสอบเงื่อนไขหรือการเปลี่ยนแปลงสถานะ

---

## ส่วนที่ต้อง include

```cpp
#include <Control_Arduino_hatyai.h>
```

---

## การประกาศและเริ่มต้นใช้งาน

```cpp
CreateCondition condition;  // ประกาศอ็อบเจกต์สำหรับตรวจสอบเงื่อนไข
```

---

## วิธีใช้งาน

### 1. ตรวจสอบค่าระหว่างช่วง (`inBetween`)

```cpp
double sensorValue = 15.2; // สมมติเป็นค่าที่อ่านมาจากเซนเซอร์
bool result;
condition.inBetween(&sensorValue, 10, 20, true, &result);
// result จะเป็น true เมื่อ sensorValue อยู่ในช่วง 10 ถึง 20
```

### 2. ตรวจจับการเปลี่ยนสถานะเมื่อค่าหลุดขอบเขต (`onChangeState`)

```cpp
double sensorValue = 25.0;
bool stateResult;
condition.setOnChangeInitial(false); // กำหนดสถานะเริ่มต้น
condition.onChangeState(&sensorValue, 10, 20, true, &stateResult);
// stateResult จะเปลี่ยนค่าเมื่อ sensorValue หลุดขอบเขตที่กำหนด
```

### 3. อ่านสถานะล่าสุด

```cpp
bool lastState = condition.getOnChangeState();
```

---

## ตัวอย่างการใช้งานจริง

```cpp
#include <Control_Arduino_hatyai.h>

CreateCondition condition;
double tempSensor;
bool state;

void setup() {
  Serial.begin(115200);
  condition.setOnChangeInitial(false);
}

void loop() {
  tempSensor = analogRead(A0) * (5.0 / 1023.0) * 100; // สมมติเป็นการอ่านอุณหภูมิ
  if (condition.inBetween(&tempSensor, 20, 30, true, &state)) {
    Serial.println("Temperature is in range!");
  }
  if (condition.onChangeState(&tempSensor, 20, 30, true, &state)) {
    Serial.println("State changed: Now in range");
  }
  delay(1000);
}
```

---

## รายละเอียดฟังก์ชัน

| ฟังก์ชัน                                                      | คำอธิบาย                                                      |
|---------------------------------------------------------------|----------------------------------------------------------------|
| `inBetween(double *sensor, double low, double high, bool resultTarget, bool *result)` | ตรวจสอบว่าค่าอยู่ในช่วงที่กำหนดหรือไม่                        |
| `onChangeState(double *sensor, double low, double high, bool resultTarget, bool *result)` | ตรวจจับการเปลี่ยนสถานะเมื่อค่าหลุดขอบเขต                      |
| `setOnChangeInitial(bool s)`                                  | เซ็ตสถานะเริ่มต้นสำหรับการตรวจจับการเปลี่ยนแปลง               |
| `getOnChangeState()`                                          | ดึงค่าสถานะล่าสุด                                              |

---

## หมายเหตุเพิ่มเติม

- รองรับการตรวจสอบเงื่อนไขได้หลากหลาย เช่น ช่วงค่าปกติ, ค่าที่เปลี่ยนแปลง, การแจ้งเตือนเมื่อมีการเปลี่ยนสถานะ
- สามารถนำไปใช้กับเซนเซอร์ต่าง ๆ ได้ตามต้องการ

---

## License

MIT License © 2025 Voraches
