#ifndef __CONFIG_H
#define __CONFIG_H

#include "motor.h"
#include "speedmeter.h"
#include "hardware/pio.h"

// 两次执行PID控制的间隔
#define PID_INTERVAL_MS 20

// PID参数的默认值
#define DEFAULT_KP 0.0
#define DEFAULT_KI 0.0
#define DEFAULT_KD 0.0

// 电机的数量
#define NUM_OF_MOTORS 2

// 电机占用引脚的列表
extern struct motor motors[NUM_OF_MOTORS];

// 编码器占用的PIO
#define SPEEDMETER_PIO pio0

// 编码器占用引脚的列表
extern struct speedmeter speedmeters[NUM_OF_MOTORS];

// I2C使用的引脚
#define I2C_SDA 31
#define I2C_SCL 32

#endif // __CONFIG_H