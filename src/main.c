#include "utils.h"
#include "renderer.h"

#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    struct Renderer* renderer = renderer_create(800, 450);

    // Clear the screen to black.
    renderer_clear(renderer, 0.0, 0.0, 0.0, 1.0);

    // Draw a gradient based on the x and y coordinates of the screen.
    for(int y = 0; y < renderer->height; y++)
    {
        for(int x = 0; x < renderer->width; x++)
        {
            float r = ((float)x / renderer->width) * 0.5f;
            float g = ((float)y / renderer->height) * 0.5f;
            float b = 0.0f;

            renderer_draw_pixel(renderer, x, y, r, g, b, 1.0);
        }
    }

    // Draw a line from the bottom left corner to the top right corner of the screen.
    renderer_draw_line(renderer, 0, 0, renderer->width, renderer->height, 1.0, 1.0, 1.0, 1.0);

    // Draw different colored pieces of text onto the screen.
    renderer_draw_string(renderer, 0, renderer->height - 13, 1.0, 0.0, 0.0, 1.0, "This is the color red!");
    renderer_draw_string(renderer, 0, renderer->height - 26, 0.0, 1.0, 0.0, 1.0, "This is the color green!");
    renderer_draw_string(renderer, 0, renderer->height - 39, 0.0, 0.0, 1.0, 1.0, "This is the color blue!");

    // Test the formatted text rendering by printing the date onto the screen. 
    time_t t;
    time(&t);
    renderer_draw_stringf(renderer, 0, 0, 1.0, 1.0, 1.0, 1.0, "This image was rendered on %s", ctime(&t));
    
    utils_bmp_write("out.bmp", renderer->width, renderer->height, renderer->color_buffer);
}