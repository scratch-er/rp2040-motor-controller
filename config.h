#ifndef __CONFIG_H
#define __CONFIG_H

#include "motor.h"
#include "speedmeter.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"

// 两次执行PID控制的间隔
#define PID_INTERVAL_MS 20

// PID参数的默认值
#define DEFAULT_KP -0.02
#define DEFAULT_KI -0.0
#define DEFAULT_KD 0.0

// 电机的数量
#define NUM_OF_MOTORS 2

// 电机占用引脚的列表
extern struct motor motors[NUM_OF_MOTORS];

// 编码器占用的PIO
#define SPEEDMETER_PIO pio0

// 编码器占用引脚的列表
extern struct speedmeter speedmeters[NUM_OF_MOTORS];

// 使用的I2C端口
#define I2C_HW i2c1

// I2C地址
#define I2C_ADDRESS 42

// I2C使用的引脚
#define I2C_SDA 26
#define I2C_SCL 27

#endif // __CONFIG_H