#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>

struct Renderer
{
    uint16_t width;
    uint16_t height;

    uint8_t* color_buffer;
};

struct Renderer *renderer_create(uint16_t width, uint16_t height);
void renderer_destroy(struct Renderer *renderer);

void renderer_clear(struct Renderer *renderer, float r, float g, float b, float a);

void renderer_draw_pixel(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a);
void renderer_draw_line(struct Renderer *renderer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, float r, float g, float b, float a);

void renderer_draw_char(struct Renderer *renderer, uint16_t x, uint16_t y, char character, float r, float g, float b, float a);
void renderer_draw_string(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a, const char* string);
void renderer_draw_stringf(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a, const char* format, ...);

#endif // RENDERER_H