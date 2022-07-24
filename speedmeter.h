#ifndef __SPEEDMETER_H
#define __SPEEDMETER_H

#include <limits.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "speedmeter.pio.h"

struct speedmeter {
    uint pin_a;
    uint pin_b;
};

// 开启编码器测量
// BUG: 在DMA结束后（约需要至少20小时）DMA不会自动重启，导致计数值卡住不动
void speedmeter_program_init(PIO pio, uint sm, uint offset, uint dma_chan, volatile int32_t *dest, struct speedmeter *s);

#endif // __SPEEDMETER_H