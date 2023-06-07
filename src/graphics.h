#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

struct gfx_context
{
    SDL_Surface *surface;
};

struct gfx_context *gfx_create(SDL_Surface* surface);
void gfx_destroy(struct gfx_context *context);

void gfx_clear(struct gfx_context *context, float r, float g, float b);

void gfx_draw_pixel(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b);

void gfx_draw_line(struct gfx_context *context, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, float r, float g, float b);
void gfx_draw_rect(struct gfx_context *context, uint16_t x, uint16_t y, uint16_t w, uint16_t h, float r, float g, float b);

void gfx_draw_char(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, char character);
void gfx_draw_string(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, const char* string);
void gfx_draw_stringf(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, const char* format, ...);

#endif // GRAPHICS_H