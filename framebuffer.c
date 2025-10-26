#include "framebuffer.h"
#include <stdint.h>

framebuffer_t fb;

void fb_init(uintptr_t addr, uint32_t w, uint32_t h, uint32_t pitch, uint8_t bpp) {
    fb.addr = addr;
    fb.width = w;
    fb.height = h;
    fb.pitch = pitch;
    fb.bpp = bpp;
}

static inline uint32_t* fb_ptr(uint32_t x, uint32_t y) {
    return (uint32_t*)(fb.addr + y * fb.pitch + x * (fb.bpp/8));
}

void fb_putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= fb.width || y >= fb.height) return;
    *fb_ptr(x,y) = color;
}

void fb_clear(uint32_t color) {
    for (uint32_t y=0;y<fb.height;y++) {
        for (uint32_t x=0;x<fb.width;x++) {
            *fb_ptr(x,y) = color;
        }
    }
}

void fb_draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
    for (uint32_t yy = y; yy < y+h; yy++)
        for (uint32_t xx = x; xx < x+w; xx++)
            fb_putpixel(xx,yy,color);
}

void fb_draw_icon(uint32_t x, uint32_t y, const uint32_t *pixels, uint32_t w, uint32_t h) {
    for (uint32_t yy = 0; yy < h; yy++) {
        for (uint32_t xx = 0; xx < w; xx++) {
            uint32_t px = pixels[yy*w + xx];
            if (px != 0x00000000) // treat 0 as transparent
                fb_putpixel(x+xx,y+yy,px);
        }
    }
}
