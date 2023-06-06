#include "utils.h"

#include <stdio.h>

struct BMPFileHeader
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t offset;

} __attribute__((__packed__));

struct BMPInfoHeader
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;

} __attribute__((__packed__));

int utils_bmp_write(const char* filename, uint32_t width, uint32_t height, uint8_t* data)
{
    struct BMPFileHeader bmpHeader;
    struct BMPInfoHeader bmpInfoHeader;

    bmpHeader.type = 0x4D42;
    bmpHeader.size = sizeof(struct BMPFileHeader) + sizeof(struct BMPInfoHeader) + width * height * 4;
    bmpHeader.reserved_1 = 0;
    bmpHeader.reserved_2 = 0;
    bmpHeader.offset = sizeof(struct BMPFileHeader) + sizeof(struct BMPInfoHeader);

    bmpInfoHeader.size = sizeof(struct BMPInfoHeader);
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.planes = 1;
    bmpInfoHeader.bits_per_pixel = 32;
    bmpInfoHeader.compression = 0;
    bmpInfoHeader.image_size = width * height * 4;
    bmpInfoHeader.x_pixels_per_meter = 0;
    bmpInfoHeader.y_pixels_per_meter = 0;
    bmpInfoHeader.colors_used = 0;
    bmpInfoHeader.colors_important = 0;

    FILE* file = fopen(filename, "wb");
    if (!file) 
    {
        fprintf(stderr, "Failed to open file %s\n", filename);
        return 1;
    }

    fwrite(&bmpHeader, sizeof(struct BMPFileHeader), 1, file);
    fwrite(&bmpInfoHeader, sizeof(struct BMPInfoHeader), 1, file);
    fwrite(data, width * height * 4, 1, file);

    fclose(file);

    return 0;
}