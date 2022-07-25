#ifndef __I2C_INTERFACE_H
#define __I2C_INTERFACE_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "config.h"
#include "pid.h"
#include <string.h>

void i2c_interface_init();

void i2c_daemon();

#endif // __I2C_INTERFACE_H