/**
 * Description:
 * Time to Complete: 6:28pm-6:36pm, 10am-
 *
 * @author Shota Bennett
 * @version 3/25/2023
 */
#include "BMPHandler.h"

/**
 * Read BMP header of a BMP file.
 *
 * @param  file: A pointer to the file being read
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header) {
    fread(&header->signature, sizeof(char) * 2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserved1, sizeof(short), 1, file);
    fread(&header->reserved2, sizeof(short), 1, file);
    fread(&header->offset_pixel_array, sizeof(int), 1, file);
}

void writeBMPHeader(FILE* file, struct BMP_Header* header) {

}

void readDIBHeader(FILE* file, struct DIB_Header* header) {
    fread(&header->DIB_Header_Size, sizeof(int), 1, file);
    fread(&header->image_width, sizeof(int), 1, file);
    fread(&header->image_height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->bits_per_pixel, sizeof(short), 1, file);
    fread(&header->compression, sizeof(int), 1, file);
    fread(&header->x_ppm, sizeof(int), 1, file);
    fread(&header->y_ppm, sizeof(int), 1, file);
    fread(&header->colors_in_table, sizeof(int), 1, file);
    fread(&header->important_color_count, sizeof(int), 1, file);
}

void writeDIBHeader(FILE* file, struct DIB_Header* header) {

}

void makeDIBHeader(struct DIB_Header* header, int width, int height) {

}

void makeBMPHeader(struct BMP_Header* header, int width, int height) {

}

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {

}

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {

}