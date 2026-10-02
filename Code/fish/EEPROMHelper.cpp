#include "EEPROMHelper.h"

extern int CENTER;  // 引用主程序中定义的全局变量

void loadCenterFromEEPROM() 
{
  int savedCenter = EEPROM.read(EEPROM_CENTER_ADDR);
  if (savedCenter >= 0 && savedCenter <= 180) 
  {
    CENTER = savedCenter;
    Serial.print("从EEPROM读取中心角度: ");
    Serial.println(CENTER);
  } 
  else 
  {
    CENTER = 90;
    saveCenterToEEPROM(CENTER);
    Serial.println("使用默认中心角度: 90");
  }
}

void saveCenterToEEPROM(int centerValue) 
{
  if (centerValue >= 0 && centerValue <= 180) 
  {
    EEPROM.write(EEPROM_CENTER_ADDR, centerValue);
    Serial.print("中心角度已保存到EEPROM: ");
    Serial.println(centerValue);
  }
}