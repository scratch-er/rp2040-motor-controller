#include "motor.h"

void motor_init(struct motor *m) {
    gpio_set_function(m->pin_a, GPIO_FUNC_PWM);
    gpio_set_function(m->pin_b, GPIO_FUNC_PWM);
    uint slice_num_a = pwm_gpio_to_slice_num(m->pin_a);
    uint slice_num_b = pwm_gpio_to_slice_num(m->pin_b);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0);
    pwm_init(slice_num_a, &config, true);
    pwm_init(slice_num_b, &config, true);
    pwm_set_gpio_level(m->pin_a, 0);
    pwm_set_gpio_level(m->pin_b, 0);
}

inline void motor_set_pwm_duty(struct motor *m, int speed) {
    if (speed == 0) {
        pwm_set_gpio_level(m->pin_a, 0);
        pwm_set_gpio_level(m->pin_b, 0);
    } else if (speed > 0) {
        speed &= 0xFFFF;
        pwm_set_gpio_level(m->pin_b, 0);
        pwm_set_gpio_level(m->pin_a, speed);
    } else if (speed < 0) {
        speed = -speed;
        speed &= 0xFFFF;
        pwm_set_gpio_level(m->pin_a, 0);
        pwm_set_gpio_level(m->pin_b, speed);
    }
}