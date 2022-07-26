#ifndef __PID_H
#define __PID_H

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/pio.h"
#include "motor.h"
#include "config.h"

extern float motor_kp, motor_ki, motor_kd;
// 编码器计数器数值
extern volatile int32_t speedmeter_counts[NUM_OF_MOTORS];
// 各个电机的目标速度
extern volatile float target_speeds[NUM_OF_MOTORS];
// 各个电机的实际速度
extern volatile float speeds[NUM_OF_MOTORS];

void pid_init();

bool do_pid(struct repeating_timer *t);

#endif // __PID_H