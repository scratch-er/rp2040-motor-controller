#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "speedmeter.pio.h"
#include "pid.h"

int32_t count=0;

bool print_count(struct repeating_timer *t) {
    static bool value = true;
    printf("%d\n", speedmeter_counts[0]);
    gpio_put(PICO_DEFAULT_LED_PIN, value);
    value = !value;
    return true;
}


int main() {
    stdio_init_all();
    puts("Hello, world!");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // PIO pio = pio0;
    // uint offset = pio_add_program(pio, &speedmeter_program);
    // uint sm = pio_claim_unused_sm(pio, true);

    // struct speedmeter s={2, 3};
    // speedmeter_program_init(pio, sm, offset, 0, &count, &s);

    start_pid();

    struct repeating_timer timer;
    add_repeating_timer_ms(500, print_count, NULL, &timer);

    while (true) {
        tight_loop_contents();
    }

    return 0;
}