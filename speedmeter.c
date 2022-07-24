#include "speedmeter.h"

void speedmeter_program_init(PIO pio, uint sm, uint offset, uint dma_chan, int32_t *dest, uint pin_a, uint pin_b) {
    // 设定PIO状态机
    pio_sm_config config_sm = speedmeter_program_get_default_config(offset);
    sm_config_set_in_pins(&config_sm, pin_a);
    sm_config_set_jmp_pin(&config_sm, pin_b);
    pio_gpio_init(pio, pin_a);
    pio_gpio_init(pio, pin_b);
    pio_sm_set_consecutive_pindirs(pio, sm, pin_a, 1, false);
    pio_sm_set_consecutive_pindirs(pio, sm, pin_b, 1, false);

    // 配置DMA通道，实现计数值自动传输
    dma_channel_config config_dma = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&config_dma, DMA_SIZE_32);
    channel_config_set_read_increment(&config_dma, false);
    channel_config_set_write_increment(&config_dma, false);
    channel_config_set_dreq(&config_dma, pio_get_dreq(pio, sm, false));

    // 开启DMA通道
    dma_channel_configure(dma_chan, &config_dma, dest, &pio->rxf[sm], UINT_MAX, true);

    // 开启PIO状态机
    pio_sm_init(pio, sm, offset, &config_sm);
    pio_sm_set_enabled(pio, sm, true);
}
