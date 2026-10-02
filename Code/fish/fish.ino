/*
 * 舵机控制程序 - 主程序
 * 功能：通过串口命令控制舵机执行各种动作
 * 使用Arduino Nano和Servo库
 */

#include <Servo.h>
#include "ServoControl.h"
#include "EEPROMHelper.h"
#include "ModeManager.h"

// 常量定义
#define SITE 9 //定义舵机引脚

// 全局变量定义
OperationMode currentMode = MODE_BASIC;
String serialCommand; //指令缓存区
int CENTER = 90;  //默认中心角度，会根据Flash值修改

/**
 * 初始化函数
 */
void setup() 
{  
  Serial.begin(9600);
  Serial.setTimeout(30); // 100毫秒超时，原来默认是1000ms
  loadCenterFromEEPROM();
  servoInit(SITE);
  servoMoveToCenter();
  
  Serial.println(F("舵机已初始化为中心位置"));
  Serial.println(F("=== 舵机多模式控制系统 ==="));
  Serial.println(F("默认模式: 基础模式"));
  Serial.println(F("命令格式: CMD_指令"));
  Serial.println(F("S-回中 R-右转 L-左转 A-小摆 B-中摆 C-大摆"));
  Serial.println(F("D-进入中心设置模式 E-进入自定义模式"));
  Serial.println(F("X-在任何模式下返回基础模式"));

  // 清空串口缓冲区
  while(Serial.available()) Serial.read();
}

/**
 * 主循环函数
 */
void loop() 
{
  switch(currentMode) 
  {
    case MODE_BASIC:
      Basic_Mode();
      break;
    case MODE_CENTER_SET:
      Set_Center_Mode();
      break;
    case MODE_CUSTOM:
      Custom_Mode();
      break;
  }
}