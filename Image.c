/**
 * Description:
 * Completion time: 6:15pm, 6:28pm
 *
 * @author Shota Bennett
 * @version 3/25/2023
 *
 */
#include "Image.h"
#include <math.h>

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
            int grey = (int) round((img->pArr[row][col].b * 0.114) + (img->pArr[row][col].g * 0.587)
                    + (img->pArr[row][col].r * 0.299));

            img->pArr[row][col].b = grey;
            img->pArr[row][col].g = grey;
            img->pArr[row][col].r = grey;
        }
    }
}

void image_apply_colorshift(Image* img, int rShift, int gShift, int bShift) {
    int row, col;
    for(row = image_get_height(img) - 1; row >= 0; row--) {
        for(col = 0; col < image_get_width(img); col++) {
            int newB = (img->pArr[row][col].b + bShift < 255) ? img->pArr[row][col].b + bShift : 255;
            int newG = (img->pArr[row][col].g + gShift < 255) ? img->pArr[row][col].g + gShift : 255;
            int newR = (img->pArr[row][col].r + rShift < 255) ? img->pArr[row][col].r + rShift : 255;

            img->pArr[row][col].b = newB;
            img->pArr[row][col].g = newG;
            img->pArr[row][col].r = newR;
        }
    }
}

void image_apply_resize(Image* img, float factor) {
    //create new pixel array
    struct Pixel** new_pixel;
    int width = (int) (image_get_width(img) * factor);
    int height = (int) (image_get_height(img) * factor);
    new_pixel = (struct Pixel **) malloc(sizeof(struct Pixel*) * width);
    int i;
    for(i = 0; i < width; i++) {
        new_pixel[i] = malloc(sizeof(struct Pixel) * height);
    }

    //Populate new array
    int row, col;
    for(row = height - 1; row >= 0; row--) {
        for(col = 0; col < width; col++) {
            new_pixel[row][col].b = img->pArr[(int)(row/factor)][(int)(col/factor)].b;
            new_pixel[row][col].g = img->pArr[(int)(row/factor)][(int)(col/factor)].g;
            new_pixel[row][col].r = img->pArr[(int)(row/factor)][(int)(col/factor)].r;
//            printf("r: %d, g: %d, b: %d\n", pArr[col][row].r, pArr[col][row].g, pArr[col][row].b);
        }
    }
    // Change img pointer to new image
    img->pArr = new_pixel;
    img->width = width;
    img->height = height;

}