#include "i2c_interface.h"
#include "hardware/gpio.h"

void i2c_interface_init() {
    i2c_init(I2C_HW, 100 * 1000);
    i2c_set_slave_mode(I2C_HW, true, I2C_ADDRESS);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void i2c_daemon() {
    static bool value = false;
    while (true) {
        i2c_read_raw_blocking(I2C_HW, (void*)target_speeds, sizeof(target_speeds));
        value = !value;
        gpio_put(25, value);
    }
}