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
    fwrite(&header->signature, sizeof(char) * 2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offset_pixel_array, sizeof(int), 1, file);
}

void readDIBHeader(FILE* file, struct DIB_Header* header) {
    fread(&header->DIB_Header_Size, sizeof(int), 1, file);
    fread(&header->image_width, sizeof(int), 1, file);
    fread(&header->image_height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->bits_per_pixel, sizeof(short), 1, file);
    fread(&header->compression, sizeof(int), 1, file);
    fread(&header->image_size, sizeof(int), 1, file);
    fread(&header->x_ppm, sizeof(int), 1, file);
    fread(&header->y_ppm, sizeof(int), 1, file);
    fread(&header->colors_in_table, sizeof(int), 1, file);
    fread(&header->important_color_count, sizeof(int), 1, file);
}

void writeDIBHeader(FILE* file, struct DIB_Header* header) {
    fwrite(&header->DIB_Header_Size, sizeof(int), 1, file);
    fwrite(&header->image_width, sizeof(int), 1, file);
    fwrite(&header->image_height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->bits_per_pixel, sizeof(short), 1, file);
    fwrite(&header->compression, sizeof(int), 1, file);
    fwrite(&header->image_size, sizeof(int), 1, file);
    fwrite(&header->x_ppm, sizeof(int), 1, file);
    fwrite(&header->y_ppm, sizeof(int), 1, file);
    fwrite(&header->colors_in_table, sizeof(int), 1, file);
    fwrite(&header->important_color_count, sizeof(int), 1, file);
}

void makeDIBHeader(struct DIB_Header* header, int width, int height) {
    int paddingRequired = 4- ((width * 3) % 4);
    header->DIB_Header_Size = 40;
    header->image_width = width;
    header->image_height = height;
    header->planes = 1;
    header->bits_per_pixel = 24;
    header->compression = 0;
    header->image_size = ((width * 3) + paddingRequired * 4);
    header->x_ppm = 0;
    header->y_ppm = 0;
    header->colors_in_table = 0;
    header->important_color_count = 0;
}

void makeBMPHeader(struct BMP_Header* header, int width, int height) {
    int paddingRequired = 4 - ((width * 3) % 4);
    header->signature[0] = 'B';
    header->signature[1] = 'M';
    header->size = 54 + ((width * 3) + paddingRequired) * height;
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offset_pixel_array = 54;
}

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {
    int row, col;
    int paddingRequired = 4 - ((width * 3) % 4);
    for(row = height - 1; row >= 0; row--) {
        for(col = 0; col < width; col++) {
            fread(&pArr[col][row].b, sizeof(char), 1, file);
            fread(&pArr[col][row].g, sizeof(char), 1, file);
            fread(&pArr[col][row].r, sizeof(char), 1, file);
//            printf("r: %d, g: %d, b: %d\n", pArr[col][row].r, pArr[col][row].g, pArr[col][row].b);
        }
        if(paddingRequired != 0) {
            fseek(file, sizeof(unsigned char) * paddingRequired, SEEK_CUR);
        }
    }
}

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {
    int row, col;
    int paddingRequired = 4 - ((width * 3) % 4);
    for(row = height - 1; row >= 0; row--) {
        for(col = 0; col < width; col++) {
            fwrite(&pArr[col][row].b, sizeof(char), 1, file);
            fwrite(&pArr[col][row].g, sizeof(char), 1, file);
            fwrite(&pArr[col][row].r, sizeof(char), 1, file);
//            printf("r: %d, g: %d, b: %d\n", pArr[col][row].r, pArr[col][row].g, pArr[col][row].b);
        }
        if(paddingRequired != 0) {
            fseek(file, sizeof(unsigned char) * paddingRequired, SEEK_CUR);
        }
    }
}