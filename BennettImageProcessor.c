/**
 * Description:
 * Time to Complete:
 *
 * @author Shota Bennett,
 */

#include <stdio.h>
#include <unistd.h>
#include "Image.h"
#include "BMPHandler.h"
#include <string.h>

// Forward Declarations
void testPrintBMP(struct BMP_Header header);
void testPrintDIB(struct DIB_Header header);

int main(int argc, char **argv) {
    int bwFlag = 0;
    int shiftFlag = 0;
    int sizeFlag = 0;
    int rShift = 0;
    int gShift = 0;
    int bShift = 0;
    float factor = 1;
    int option;

    FILE* infile;
    FILE* outfile;
    struct BMP_Header bmpHeader, bmpHeaderOut;
    struct DIB_Header dibHeader, dibHeaderOut;
    struct Pixel** pixel;


    if(argc < 2) {
        fprintf(stderr, "Please include an image to be processed. Usage: ImageProcessor <file.bmp> <args>");
        exit(1);
    }

    infile = fopen(argv[1], "rb");
    while ((option = getopt(argc, argv, "r:g:b:wo:s:")) != -1) {
        switch (option) {
            // Stores shift values for later use, marks flag that shift operation should be performed.
            case 'r':
                rShift = atoi(optarg);
                if(rShift == 0) {
                    fprintf(stderr, "Not a valid input for this argument. Enter any non-zero number.");
                    exit(2);
                }
                shiftFlag = 1;
                break;
            case 'g':
                gShift = atoi(optarg);
                if(gShift == 0) {
                    fprintf(stderr, "Not a valid input for this argument. Enter any non-zero number.");
                    exit(2);
                }
                shiftFlag = 1;
                break;
            case 'b':
                bShift = atoi(optarg);
                if(bShift == 0) {
                    fprintf(stderr, "Not a valid input for this argument. Enter any non-zero number.");
                    exit(2);
                }
                shiftFlag = 1;
                break;
            //Marks bwflag
            case 'w':
                bwFlag = 1;
                break;
            //Stores name of outfile for later use.
            case 'o' :
                outfile = fopen(optarg, "wb");
                break;
            //Stores resize factor.
            case 's' :
                factor = atof(optarg);
                if(factor == 0) {
                    fprintf(stderr, "Not a valid input for this argument. Enter any non-zero number.");
                    exit(3);
                }
                sizeFlag = 1;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                exit(4);
            default :
                break;
        }
    }
    if(outfile == NULL) {
        //TODO: Play around with string so that file.bmp becomes file_copy.bmp
        char* fileName = strtok(argv[1], " ");
        strcat(fileName, "_copy.bmp");
        outfile = fopen(fileName, "wb");
    }

    // Read BMP and DIB headers.
    readBMPHeader(infile, &bmpHeader);
    readDIBHeader(infile, &dibHeader);

    //testPrintBMP(bmpHeader);
    //testPrintDIB(dibHeader);

    //Make Pixel Array
    pixel = (struct Pixel **) malloc(sizeof(struct Pixel*) * dibHeader.image_width);
    int i;
    for(i = 0; i < dibHeader.image_width; i++) {
        pixel[i] = malloc(sizeof(struct Pixel) * dibHeader.image_height);
    }
    readPixelsBMP(infile, pixel, dibHeader.image_width, dibHeader.image_height);
    fclose(infile);

    //Create Image
    Image* img = image_create(pixel, dibHeader.image_width, dibHeader.image_height);

    //Apply image filters, grayscale conversion first, then colorshifts, then resize.
    if(bwFlag == 1) {
        image_apply_bw(img);
    }
    if(shiftFlag == 1) {
        image_apply_colorshift(img, rShift, gShift, bShift);
    }
    if(sizeFlag == 1) {
        image_apply_resize(img, factor);
    }
    //Make headers
    makeBMPHeader(&bmpHeaderOut, image_get_width(img), image_get_height(img));
    makeDIBHeader(&dibHeaderOut, image_get_width(img), image_get_height(img));
    //Write files for export
    writeBMPHeader(outfile, &bmpHeaderOut);
    writeDIBHeader(outfile, &dibHeaderOut);
    writePixelsBMP(outfile, image_get_pixels(img), image_get_width(img), image_get_height(img));

    printf("Hello, World!\n");
    image_destroy(&img);

    fclose(outfile);
    return 0;
}

void testPrintBMP(struct BMP_Header header) {
    printf("signature: %c%c\n", header.signature[0], header.signature[1]);
    printf("size: %d\n", header.size);
    printf("reserved1: %d\n", header.reserved1);
    printf("reserved2: %d\n", header.reserved2);
    printf("offset_pixel_array: %d\n", header.offset_pixel_array);
}

void testPrintDIB(struct DIB_Header header) {
    printf("DIB Header size: %d\n", header.DIB_Header_Size);
    printf("Image width: %d \n", header.image_width);
    printf("Image height: %d\n", header.image_width);
    printf("Planes: %d\n", header.planes);
    printf("Bits per pixel: %d\n", header.bits_per_pixel);
    printf("Compression: %d\n", header.compression);
    printf("X Pixels per meter: %d\n", header.x_ppm);
    printf("Y Pixels per meter: %d\n", header.y_ppm);
    printf("Colors in table: %d\n", header.colors_in_table);
    printf("Important color count: %d\n", header.important_color_count);
}