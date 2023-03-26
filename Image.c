/**
 * Description:
 * Completion time: 6:15pm, 6:28pm
 *
 * @author Shota Bennett
 * @version 3/25/2023
 *
 */
#include "Image.h"

Image* image_create(struct Pixel** pArr, int width, int height) {
    Image* img = (Image*) malloc(sizeof(Image));
    img->pArr = pArr;
    img->width = width;
    img->height = height;
    return img;
}

void image_destroy(Image** img) {
    free(*img);
    *img = NULL;
}

struct Pixel** image_get_pixels(Image* img) {
    return img->pArr;
}

int image_get_width(Image* img) {
    return img->width;
}

int image_get_height(Image* img) {
    return img->height;
}

void image_apply_bw(Image* img) {
    int row, col;
    for(row = image_get_height(img) - 1; row >= 0; row--) {
        for(col = 0; col < image_get_width(img); col++) {
           img->pArr[row][col].b *= 0.114;
           img->pArr[row][col].g *= 0.587;
           img->pArr[row][col].r *= 0.299;
        }
    }
}

void image_apply_colorshift(Image* img, int rShift, int gShift, int bShift) {

}

void image_apply_resize(Image* img, float factor) {

}