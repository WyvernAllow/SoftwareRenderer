#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

int utils_bmp_write(const char* filename, uint32_t width, uint32_t height, uint8_t* data);

#endif