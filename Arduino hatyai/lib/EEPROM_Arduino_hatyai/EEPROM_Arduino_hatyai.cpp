#include "EEPROM_Arduino_hatyai.h"

ProcessManager::ProcessManager(const char* ns) {
  namespaceName = ns;
  userData = nullptr;
  dataSize = 0;
  changedFlag = false;
}

void ProcessManager::begin(void* data, size_t size) {
  userData = data;
  dataSize = size;
  load();
}

void ProcessManager::save() {
  if (!userData || dataSize == 0) return;
  prefs.begin(namespaceName, false);
  prefs.putBytes("data", userData, dataSize);
  prefs.end();
  Serial.println("Data saved to EEPROM");
}

void ProcessManager::load() {
  if (!userData || dataSize == 0) return;
  prefs.begin(namespaceName, true);
  if (prefs.isKey("data")) {
    prefs.getBytes("data", userData, dataSize);
    Serial.println("Data loaded from EEPROM");
  } else {
    Serial.println("No saved data, using defaults");
  }
  prefs.end();
}

void ProcessManager::setChanged(bool changed) {
  changedFlag = changed;
  if (changedFlag) {
    save();
    changedFlag = false;
  }
}
