#include "ModeManager.h"
#include "ServoControl.h"
#include "EEPROMHelper.h"

// 引用Servo对象
extern Servo servo1;

// 模式实现函数
void Basic_Mode()
{
  if(Serial.available()) 
  {
    serialCommand = Serial.readStringUntil('\0');
    serialCommand.trim(); // 去除首尾空白字符

    // 验证命令格式 - 必须包含CMD_前缀
    if(!serialCommand.startsWith("CMD_")) 
    {
      Serial.println(F("错误: 命令格式不正确，必须以CMD_开头"));
      return;
    }

    // 提取命令主体（去掉CMD_前缀）
    String command = serialCommand.substring(4);
    
    // 模式切换命令优先处理
    if(command == "D")  // 修正：使用双引号
    {
      currentMode = MODE_CENTER_SET;
      Serial.println(F("切换到: 中心设置模式"));
      Serial.println(F("输入角度值以设置中心, CMD_X返回基础模式"));  // 修正提示信息
      while(Serial.available()) Serial.read();
      return;
    }
    if(command == "E")  // 修正：使用双引号
    {
      currentMode = MODE_CUSTOM;
      Serial.println(F("切换到: 自定义模式"));
      Serial.println(F("输入格式1 (连续摆动): 角度1,角度2,延时"));
      Serial.println(F("输入格式2 (间断摆动): 角度1,角度2,延时,周期数,暂停时间"));
      Serial.println(F("示例1: CMD_70,110,20"));  // 修正示例
      Serial.println(F("示例2: CMD_70,110,20,2,1000"));  // 修正示例
      Serial.println(F("CMD_X返回基础模式"));  // 修正提示信息
      while(Serial.available()) Serial.read();
      return;
    }

    // 基础模式动作命令
    if(command == "S") 
    { // 回归中心
        servoMoveToCenter();
        Serial.println("动作: 回归中心");
    }
    else if(command == "R") 
    { // 右转动作
        Serial.println("动作: 右转");
        while (!Serial.available()) 
        {
          servoRightSwing();
        }
    }
    else if(command == "L") 
    { // 左转动作
        Serial.println("动作: 左转");
        while (!Serial.available())
        {
          servoLeftSwing();
        }
    }
    else if(command == "a") 
    { // 小幅度摆动
        Serial.println("慢动作: 15°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing15_L();  
        }
    }
    else if(command == "b") 
    { // 中幅度摆动
        Serial.println("慢动作: 30°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing30_L();  
        }
    }
    else if(command == "c") 
    { // 大幅度摆动
        Serial.println("慢动作: 45°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing45_L();  
        }
    }
    else if(command == "A") 
    { // 小幅度摆动
        Serial.println("快动作: 15°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing15_H();  
        }
    }
    else if(command == "B") 
    { // 中幅度摆动
        Serial.println("快动作: 30°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing30_H();  
        }
    }
    else if(command == "C") 
    { // 大幅度摆动
        Serial.println("快动作: 45°摆动");
        while (!Serial.available()) 
        {
          smoothServo_Swing45_H();  
        }
    }
    else 
    {
        Serial.print(F("未知命令: CMD_"));
        Serial.println(command);
        Serial.println(F("可用命令: S,R,L,a,b,c,A,B,C,D,E,X"));
    }
  }
}

void Set_Center_Mode()
{
  if(Serial.available()) 
  {
    serialCommand = Serial.readStringUntil('\n');
    serialCommand.trim();
    
    // 验证命令格式
    if(!serialCommand.startsWith("CMD_")) 
    {
      Serial.println(F("错误: 命令格式不正确，必须以CMD_开头"));
      return;
    }
    
    // 提取命令主体
    String command = serialCommand.substring(4);
    
    // 处理模式退出
    if(command == "X") 
    {
      currentMode = MODE_BASIC;
      Serial.println("返回基础模式");
      while(Serial.available()) Serial.read();
      return;
    }
    
    // 处理数字输入
    if(command.length() > 0 && command.charAt(0) >= '0' && command.charAt(0) <= '9') 
    {
      int angle = command.toInt();
      
      // 验证并执行
      if(angle >= 0 && angle <= 180) 
      {
        CENTER = angle;
        saveCenterToEEPROM(angle);
        servo1.write(angle);
        Serial.print("✓ 设置角度: ");
        Serial.print(angle);
        Serial.println("度");
        delay(800);
      } 
      else 
      {
        Serial.print("✗✗ 角度超出范围: ");
        Serial.println(angle);
        Serial.println("请输入0-180之间的数字");
      }
    }
    else 
    {
      Serial.println("✗✗ 无效输入: 请输入数字或'CMD_X'返回");
    }
  }
}

void Custom_Mode()
{
  if(Serial.available()) 
  {
    serialCommand = Serial.readStringUntil('\n');
    serialCommand.trim();
    
    // 验证命令格式
    if(!serialCommand.startsWith("CMD_")) 
    {
      Serial.println(F("错误: 命令格式不正确，必须以CMD_开头"));
      return;
    }
    
    // 提取命令主体
    String command = serialCommand.substring(4);
    
    // 返回基础模式
    if(command == "X") 
    {
      currentMode = MODE_BASIC;
      Serial.println(F("返回基础模式"));
      while(Serial.available()) Serial.read();
      return;
    }
    
    // 处理参数输入 - 直接处理数字参数部分（去掉CMD_前缀后的内容）
    if(command.length() > 0 && command.charAt(0) >= '0' && command.charAt(0) <= '9') 
    {
      char inputBuffer[50];
      command.toCharArray(inputBuffer, 50);
      
      Serial.print(F("接收: CMD_"));
      Serial.println(inputBuffer);
      
      // 统计逗号数量来确定参数个数
      int commaCount = 0;
      for(int i = 0; i < command.length(); i++) 
      {
        if(command.charAt(i) == ',') commaCount++;
      }
      
      // 根据逗号数量判断模式
      if(commaCount == 2) 
      {
        // 连续摆动模式: a,b,c
        int params[3];
        int paramIndex = 0;
        char* token = strtok(inputBuffer, ",");
        
        while(token != NULL && paramIndex < 3) 
        {
          params[paramIndex++] = atoi(token);
          token = strtok(NULL, ",");
        }
        
        if(paramIndex == 3) 
        {
          int angle1 = params[0];
          int angle2 = params[1];
          int stepDelay = params[2];
          
          // 验证参数
          if(angle1 >= 0 && angle1 <= 360 && 
             angle2 >= 0 && angle2 <= 360 && 
             stepDelay > 0 && stepDelay <= 1000) 
          {
            Serial.print(F("连续摆动: "));
            Serial.print(angle1);
            Serial.print(F("°↔↔"));
            Serial.print(angle2);
            Serial.print(F("° 延时"));
            Serial.print(stepDelay);
            Serial.println(F("ms"));
            
            // 执行连续摆动
            while (!Serial.available()) 
            {
                smoothMoveTo(angle1, stepDelay);
                delay(200);
                smoothMoveTo(angle2, stepDelay);
                delay(200);
            }
            
            Serial.println(F("摆动结束"));
          } 
          else 
          {
            Serial.println(F("参数错误! 角度:0-360 延时:1-1000ms"));
          }
        }
        else 
        {
          Serial.println(F("参数不足! 需要:角度1,角度2,延时"));
        }
      }
      else if(commaCount == 4) 
      {
        // 间断摆动模式: a,b,c,e,f
        int params[5];
        int paramIndex = 0;
        char* token = strtok(inputBuffer, ",");
        
        while(token != NULL && paramIndex < 5) 
        {
          params[paramIndex++] = atoi(token);
          token = strtok(NULL, ",");
        }
        
        if(paramIndex == 5) 
        {
          int angle1 = params[0];
          int angle2 = params[1];
          int stepDelay = params[2];
          int cycles = params[3];
          int pauseTime = params[4];
          
          // 验证参数
          if(angle1 >= 0 && angle1 <= 360 && 
             angle2 >= 0 && angle2 <= 360 && 
             stepDelay > 0 && stepDelay <= 1000 &&
             cycles > 0 && cycles <= 100 &&
             pauseTime >= 0 && pauseTime <= 60000) 
          {
            Serial.print(F("间断摆动: "));
            Serial.print(angle1);
            Serial.print(F("°↔↔"));
            Serial.print(angle2);
            Serial.print(F("° 延时"));
            Serial.print(stepDelay);
            Serial.print(F("ms 周期:"));
            Serial.print(cycles);
            Serial.print(F(" 暂停:"));
            Serial.print(pauseTime);
            Serial.println(F("ms"));
            
            // 执行间断摆动
            while (!Serial.available()) 
            {
                smoothMoveTo(angle1, stepDelay);
                
                for(int i = 0; i < cycles && !Serial.available(); i++) 
                {
                    smoothMoveTo(angle2, stepDelay);
                    delay(200);
                    smoothMoveTo(angle1, stepDelay);
                    delay(200);
                }
                
                if(Serial.available()) break;
                
                servoMoveToCenter();
                delay(pauseTime);
            }
            
            Serial.println(F("摆动结束"));
          }
          else 
          {
            Serial.println(F("参数错误!"));
            Serial.println(F("角度:0-360 延时:1-1000ms"));
            Serial.println(F("周期:1-100 暂停:0-10000ms"));
          }
        }
        else 
        {
          Serial.println(F("参数不足! 需要:角度1,角度2,延时,周期数,暂停时间"));
        }
      }
      else 
      {
        Serial.println(F("参数格式错误!"));
        Serial.println(F("连续摆动: CMD_角度1,角度2,延时"));
        Serial.println(F("间断摆动: CMD_角度1,角度2,延时,周期数,暂停时间"));
        Serial.println(F("示例1: CMD_70,110,20"));
        Serial.println(F("示例2: CMD_70,110,20,2,1000"));
      }
    }
    else
    {
      Serial.println(F("请输入数字参数或'CMD_X'返回"));
    }
  }
}