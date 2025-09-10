#ifndef EEPROM_Arduino_hatyai_H
#define EEPROM_Arduino_hatyai_H

#include <Arduino.h>
#include <Preferences.h>

class ProcessManager {
  public:
    ProcessManager(const char* ns = "process");
    void begin(void* data, size_t size);
    void save();
    void load();
    void setChanged(bool changed = true);

  private:
    void* userData;
    size_t dataSize;
    Preferences prefs;
    const char* namespaceName;
    bool changedFlag;
};

#endif
