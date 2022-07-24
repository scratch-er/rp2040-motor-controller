#include "pid.h"

float motor_kp=DEFAULT_KP, motor_ki=DEFAULT_KI, motor_kd=DEFAULT_KD;
struct repeating_timer pid_timer;
volatile int32_t speedmeter_counts[NUM_OF_MOTORS] = {0,};
int32_t speedmeter_counts_old[NUM_OF_MOTORS] = {0,};
float target_speeds[NUM_OF_MOTORS] = {0,};
float speeds[NUM_OF_MOTORS] = {0,};
float speeds_old[NUM_OF_MOTORS] = {0,};
float errs[NUM_OF_MOTORS] = {0,};
float errs_old[NUM_OF_MOTORS] = {0,};

bool do_pid(struct repeating_timer *t) {

}

void start_pid() {
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