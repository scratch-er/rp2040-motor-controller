#include <stdio.h>
#include <limits.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "speedmeter.pio.h"

static inline void speedmeter_program_init(PIO pio, uint sm, uint offset, uint dma_chan, int32_t *dest, uint pin_a, uint pin_b) {
    pio_sm_config config_sm = speedmeter_program_get_default_config(offset);
    sm_config_set_in_pins(&config_sm, pin_a);
    sm_config_set_jmp_pin(&config_sm, pin_b);
    pio_gpio_init(pio, pin_a);
    pio_gpio_init(pio, pin_b);
    pio_sm_set_consecutive_pindirs(pio, sm, pin_a, 1, false);
    pio_sm_set_consecutive_pindirs(pio, sm, pin_b, 1, false);

    dma_channel_config config_dma = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&config_dma, DMA_SIZE_32);
    channel_config_set_read_increment(&config_dma, false);
    channel_config_set_write_increment(&config_dma, false);
    channel_config_set_dreq(&config_dma, pio_get_dreq(pio, sm, false));

    dma_channel_configure(dma_chan, &config_dma, dest, &pio->rxf[sm], UINT_MAX, true);

    pio_sm_init(pio, sm, offset, &config_sm);
    pio_sm_set_enabled(pio, sm, true);
}

int main() {
    stdio_init_all();
    puts("Hello, world!");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    bool value;

    int32_t count;

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &speedmeter_program);
    uint sm = pio_claim_unused_sm(pio, true);

    speedmeter_program_init(pio, sm, offset, 0, &count, 2, 3);

    while (true) {
        printf("%d\n", count);
        gpio_put(PICO_DEFAULT_LED_PIN, value);
        value = !value;
        sleep_ms(500);
    }

    return 0;
}
