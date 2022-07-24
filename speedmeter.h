#ifndef __SPEEDMETER_H
#define __SPEEDMETER_H

#include <limits.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "speedmeter.pio.h"

// 使用的DMA通道
#define SPEEDMETER_DMA_CHAN 0

void speedmeter_program_init(PIO pio, uint sm, uint offset, uint dma_chan, int32_t *dest, uint pin_a, uint pin_b);

#endif // __SPEEDMETER_H