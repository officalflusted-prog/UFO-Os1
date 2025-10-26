// gui/xicon.c - simple icon loader
#include "../drivers/framebuffer.h"
#include <stdint.h>

// example 16x16 icon pixels (ARGB hex)
static const uint32_t sample_icon_16x16[16*16] = {
    0x00000000, /* ... fill with actual icon pixels ... */ 
    // keep 0 for transparency
};

void draw_sample_icon(int x, int y) {
    fb_draw_icon(x, y, sample_icon_16x16, 16, 16);
}
