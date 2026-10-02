#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <Arduino.h>

// 模式枚举
enum OperationMode 
{
  MODE_BASIC,      // 基础模式：预设动作
  MODE_CENTER_SET, // 中心设置模式
  MODE_CUSTOM      // 自定义摆动模式
};

// 声明外部变量
extern OperationMode currentMode;
extern String  serialCommand;
extern int CENTER;

// 模式函数声明
void Basic_Mode();
void Set_Center_Mode();
void Custom_Mode();

#endif