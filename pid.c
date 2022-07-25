#include "pid.h"
#include <stdio.h>

float motor_kp=DEFAULT_KP, motor_ki=DEFAULT_KI, motor_kd=DEFAULT_KD;
struct repeating_timer pid_timer;
volatile int32_t speedmeter_counts[NUM_OF_MOTORS] = {0,};
int32_t speedmeter_counts_old[NUM_OF_MOTORS] = {0,};
volatile float target_speeds[NUM_OF_MOTORS] = {0,};
volatile float speeds[NUM_OF_MOTORS] = {0,};
float speeds_old[NUM_OF_MOTORS] = {0,};
float errs[NUM_OF_MOTORS] = {0,};
float errs_old[NUM_OF_MOTORS] = {0,};
int pwm_dutys[NUM_OF_MOTORS] = {0,};
float int_errs[NUM_OF_MOTORS] = {0,};
float diff_errs[NUM_OF_MOTORS] = {0,};

bool do_pid(struct repeating_timer *t) {
    int cnt;
    for (int i=0; i<NUM_OF_MOTORS; ++i) {
        cnt = speedmeter_counts[i];
        speeds[i] = (float)(cnt-speedmeter_counts_old[i])/(float)(PID_INTERVAL_MS/1000.0);
        errs[i] = speeds[i] - target_speeds[i];
        int_errs[i] += errs[i];
        diff_errs[i] = errs[i] - errs_old[i];
        
        pwm_dutys[i] += motor_kp*errs[i] + motor_ki*int_errs[i] + motor_kd*diff_errs[i];
        motor_set_pwm_duty(motors+i, pwm_dutys[i]);

        speedmeter_counts_old[i] = cnt;
        speeds_old[i] = speeds[i];
        errs_old[i] = errs[i];
    }
    printf("speed=%f, %f; err=%f, %f; dutys=%d, %d\n", speeds[0], speeds[1], errs[0], errs[1], pwm_dutys[0], pwm_dutys[1]);
}

void pid_init() {
    // 初始化所有编码器和电机
    uint offset = pio_add_program(SPEEDMETER_PIO, &speedmeter_program);
    for (int i=0; i<NUM_OF_MOTORS; ++i) {
        uint sm = pio_claim_unused_sm(SPEEDMETER_PIO, true);
        speedmeter_program_init(SPEEDMETER_PIO, sm, offset, i, speedmeter_counts+i, speedmeters+i);
        motor_init(motors+i);
    }
    // 增加周期定时器
    add_repeating_timer_ms(PID_INTERVAL_MS, do_pid, NULL, &pid_timer);
}