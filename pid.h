#ifndef __PID_H
#define __PID_H

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/pio.h"
#include "motor.h"
#include "config.h"

extern float motor_kp, motor_ki, motor_kd;
extern struct repeating_timer pid_timer;

void start_pid();

bool do_pid(struct repeating_timer *t);

#endif // __PID_H