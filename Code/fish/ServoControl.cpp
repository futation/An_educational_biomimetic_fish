#include "ServoControl.h"
#include <Servo.h>  // 包含Servo库

// 创建舵机对象
Servo servo1;

// 舵机初始化函数
void servoInit(int pin) 
{
  servo1.attach(pin);  // 关联舵机到指定引脚
}

/**
 * 缓慢移动舵机到中心位置
 * 功能：逐步移动舵机，每步延迟10ms，直到到达中心位置
 * 注意：移动过程中会检查串口输入，如有数据则中断移动
 */
void servoMoveToCenter() 
{
  int angle = servo1.read(); // 读取当前角度
  int way = angle > CENTER  ? 0 : 1; // 确定移动方向：0=减小角度，1=增加角度
  
  // 逐步移动至中心位置
  while (angle != CENTER ) 
  {
    angle = servo1.read();
    servo1.write(way ? angle + 1 : angle - 1); // 逐步移动
    delay(10); // 控制移动速度
  }
}


/**
 * 平滑移动函数
 * @param fromAngle 起始角度
 * @param toAngle 目标角度
 * @param stepDelay 每步延迟(ms)，控制速度
 */
void smoothMove(int fromAngle, int toAngle, int stepDelay) 
{
    servo1.write(fromAngle); // 先快速定位到起始角度
    delay(50); // 短暂延迟确保舵机就位
    smoothMoveTo(toAngle, stepDelay); // 然后平滑移动到目标角度
}

/**
 * 平滑移动函数（从当前位置移动到目标角度）
 * 这是主要的移动函数，推荐使用
 */
void smoothMoveTo(int toAngle, int stepDelay) 
{
    int currentAngle = servo1.read();
    int steps = abs(toAngle - currentAngle);
    int direction = (toAngle > currentAngle) ? 1 : -1;
    
    for(int i = 1; i <= steps; i++) 
    {
        int newAngle = currentAngle + (i * direction);
        servo1.write(newAngle);
        delay(stepDelay);
    }
}

void smoothServo_Swing15_L() 
{
  int startAngle = servo1.read();  // 获取当前位置
  int targetAngle1 = CENTER - 15; // 目标位置1：85度
  int targetAngle2 = CENTER + 15; // 目标位置2：115度
  
  // 第一步：平滑移动到85度
  smoothMove(startAngle, targetAngle1, 15); // 15ms步进间隔
  
  // 短暂停留
  delay(200);
  
  // 第二步：平滑移动到115度
  smoothMove(targetAngle1, targetAngle2, 15);
  
  // 短暂停留
  delay(200);
}


/**
 * 平滑30度摆动函数
 * 功能：实现舵机从当前位置平滑摆动到中心±30度的位置
 * 摆动范围：从中心-30度到中心+30度（例如中心为100度时：70度↔130度）
 * 特点：使用分段步进平滑移动，运动轨迹自然流畅
 */
void smoothServo_Swing30_L() 
{
  // 获取舵机当前角度位置
  int startAngle = servo1.read();
  
  // 计算摆动目标角度
  int targetAngle1 = CENTER - 30; // 左摆动目标位置（中心-30度）
  int targetAngle2 = CENTER + 30; // 右摆动目标位置（中心+30度）
  
  // 第一步：平滑移动到左端位置
  smoothMove(startAngle, targetAngle1, 10); // 10ms步进间隔，控制移动速度
  
  // 在左端位置短暂停留200ms
  delay(200);
  
  // 第二步：平滑移动到右端位置
  smoothMove(targetAngle1, targetAngle2, 10); // 相同的步进间隔保持运动一致性
  
  // 在右端位置短暂停留200ms
  delay(200);
  
}

/**
 * 平滑45度摆动函数
 * 功能：实现舵机从当前位置平滑摆动到中心±45度的位置
 * 摆动范围：从中心-45度到中心+45度（例如中心为100度时：55度↔145度）
 * 特点：更大范围的平滑摆动，适合需要广泛扫描的应用场景
 */
void smoothServo_Swing45_L() 
{
  // 获取舵机当前角度位置
  int startAngle = servo1.read();
  
  // 计算摆动目标角度
  int targetAngle1 = CENTER - 45; // 左摆动目标位置（中心-45度）
  int targetAngle2 = CENTER + 45; // 右摆动目标位置（中心+45度）
  
  // 第一步：平滑移动到左端位置
  smoothMove(startAngle, targetAngle1, 8); // 稍长的步进间隔（25ms），因移动距离更大
  
  // 在左端位置短暂停留250ms（稍长停留时间）
  delay(250);
  
  // 第二步：平滑移动到右端位置
  smoothMove(targetAngle1, targetAngle2, 8); // 保持一致的移动速度
  
  // 在右端位置短暂停留250ms
  delay(250);
}

void smoothServo_Swing15_H() 
{
  int startAngle = servo1.read();  // 获取当前位置
  int targetAngle1 = CENTER - 15; // 目标位置1：85度
  int targetAngle2 = CENTER + 15; // 目标位置2：115度
  
  // 第一步：平滑移动到85度
  smoothMove(startAngle, targetAngle1, 1); // 20ms步进间隔
  
  // 短暂停留
  delay(200);
  
  // 第二步：平滑移动到115度
  smoothMove(targetAngle1, targetAngle2, 1);
  
  // 短暂停留
  delay(200);
}


/**
 * 平滑30度摆动函数
 * 功能：实现舵机从当前位置平滑摆动到中心±30度的位置
 * 摆动范围：从中心-30度到中心+30度（例如中心为100度时：70度↔130度）
 * 特点：使用分段步进平滑移动，运动轨迹自然流畅
 */
void smoothServo_Swing30_H() 
{
  // 获取舵机当前角度位置
  int startAngle = servo1.read();
  
  // 计算摆动目标角度
  int targetAngle1 = CENTER - 30; // 左摆动目标位置（中心-30度）
  int targetAngle2 = CENTER + 30; // 右摆动目标位置（中心+30度）
  
  // 第一步：平滑移动到左端位置
  smoothMove(startAngle, targetAngle1, 1); // 20ms步进间隔，控制移动速度
  
  // 在左端位置短暂停留200ms
  delay(200);
  
  // 第二步：平滑移动到右端位置
  smoothMove(targetAngle1, targetAngle2, 1); // 相同的步进间隔保持运动一致性
  
  // 在右端位置短暂停留200ms
  delay(200);
  
}

/**
 * 平滑45度摆动函数
 * 功能：实现舵机从当前位置平滑摆动到中心±45度的位置
 * 摆动范围：从中心-45度到中心+45度（例如中心为100度时：55度↔145度）
 * 特点：更大范围的平滑摆动，适合需要广泛扫描的应用场景
 */
void smoothServo_Swing45_H() 
{
  // 获取舵机当前角度位置
  int startAngle = servo1.read();
  
  // 计算摆动目标角度
  int targetAngle1 = CENTER - 45; // 左摆动目标位置（中心-45度）
  int targetAngle2 = CENTER + 45; // 右摆动目标位置（中心+45度）
  
  // 第一步：平滑移动到左端位置
  smoothMove(startAngle, targetAngle1, 1); // 稍长的步进间隔（25ms），因移动距离更大
  
  // 在左端位置短暂停留250ms（稍长停留时间）
  delay(250);
  
  // 第二步：平滑移动到右端位置
  smoothMove(targetAngle1, targetAngle2, 1); // 保持一致的移动速度
  
  // 在右端位置短暂停留250ms
  delay(250);
}

/**
 * 右转动作循环
 * 功能：舵机先向右转动到170度，保持500ms，然后返回中心位置100度，保持280ms
 * 动作流程：100 → 170 → 100 → ...
 * 循环执行直到串口有新命令输入
 */
void servoRightSwing() 
{
  servo1.write(CENTER + 75);  // 计算得到170度位置（90+80=170）
  delay(320);                  // 在右端位置保持500ms
  servo1.write(CENTER + 20);   //90+15=115
  delay(320);                  // 在中心位置保持200ms
}

/**
 * 左转动作循环
 * 功能：舵机先向左转动到10度，保持500ms，然后返回中心位置100度，保持280ms
 * 动作流程：100 → 10 → 100 → ...
 * 循环执行直到串口有新命令输入
 */
void servoLeftSwing() 
{
  servo1.write(CENTER - 75);   // 计算得到10度位置（100-90=10）
  delay(350);                  // 在左端位置保持500ms
  servo1.write(CENTER - 20);        // 返回中心位置
  delay(350);                  // 在中心位置保持200ms
}
