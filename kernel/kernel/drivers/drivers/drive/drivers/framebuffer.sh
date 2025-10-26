#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uintptr_t addr;   // physical framebuffer address (or emulated)
    uint32_t width;
    uint32_t height;
    uint32_t pitch;   // bytes per scanline
    uint8_t bpp;      // bits per pixel (e.g., 32)
} framebuffer_t;

extern framebuffer_t fb;

void fb_init(uintptr_t addr, uint32_t w, uint32_t h, uint32_t pitch, uint8_t bpp);
void fb_putpixel(uint32_t x, uint32_t y, uint32_t color);
void fb_clear(uint32_t color);
void fb_draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void fb_draw_icon(uint32_t x, uint32_t y, const uint32_t *pixels, uint32_t w, uint32_t h);

#endif
