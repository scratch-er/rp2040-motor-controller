#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "speedmeter.pio.h"
#include "pid.h"
#include "config.h"

int32_t count=0;

bool print_count(struct repeating_timer *t) {
    static bool value = true;
    gpio_put(PICO_DEFAULT_LED_PIN, value);
    value = !value;
    return true;
}


int main() {
    stdio_init_all();
    puts("Hello, world!");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    pid_init();

    struct repeating_timer timer;
    // add_repeating_timer_ms(500, print_count, NULL, &timer);

    target_speeds[0] = 15000;
    target_speeds[1] = 8000;
    
    while (1) {
        // do_pid(NULL);
        sleep_ms(PID_INTERVAL_MS);
    }

    return 0;
}