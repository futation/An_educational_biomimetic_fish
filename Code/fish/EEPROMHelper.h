#ifndef EEPROMHELPER_H
#define EEPROMHELPER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_CENTER_ADDR 0

// 声明外部变量，在主程序中定义
extern int CENTER;

// 函数声明
void loadCenterFromEEPROM();
void saveCenterToEEPROM(int centerValue);

#endif