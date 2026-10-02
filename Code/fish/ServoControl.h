#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Servo.h>  // 包含Servo库
#include <Arduino.h>

// 改为使用EEPROM存储的值
extern int CENTER;  // 声明为外部变量，将在主程序中定义

// 初始化函数
void servoInit(int pin); // 初始化舵机，指定信号引脚

// 动作函数（这些函数会循环执行动作，直到串口有数据输入）
void servoMoveToCenter(); // 缓慢移动舵机到中心位置（90度）
void servoRightSwing();    // 右转动作：移动到170度后返回中心（100→170→100循环）
void servoLeftSwing();     // 左转动作：移动到10度后返回中心（100→10→100循环）
void smoothServo_Swing15_L();      // 15度摆动：在85度和115度之间循环摆动（±15度）
void smoothServo_Swing30_L();      // 30度摆动：在70度和130度之间循环摆动（±30度）
void smoothServo_Swing45_L();      // 45度摆动：在55度和145度之间循环摆动（±45度）
void smoothServo_Swing15_H();      // 15度摆动：在85度和115度之间循环摆动（±15度）
void smoothServo_Swing30_H();      // 30度摆动：在70度和130度之间循环摆动（±30度）
void smoothServo_Swing45_H();      // 45度摆动：在55度和145度之间循环摆动（±45度）
void smoothMove(int fromAngle, int toAngle, int stepDelay); 
void smoothMoveTo(int toAngle, int stepDelay);

#endif