#ifndef __MOTOR_H
#define __MOTOR_H

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include <limits.h>

struct motor {
    uint pin_a;
    uint pin_b;
};

// 初始化电机驱动，尽量让两个脚在同一PWM通道
void motor_init(struct motor *m);

// 设定转速，正值正转，负值反转
void motor_set_pwm_duty(struct motor *m, int speed);

#endif // __MOTOR_H