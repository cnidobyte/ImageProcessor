#include <stdio.h>
#include <unistd.h>
#include "Image.h"
#include "BMPHandler.h"

// Forward Declarations
void testPrintBMP(struct BMP_Header header);
void testPrintDIB(struct DIB_Header header);

int main(int argc, char **argv) {
    int bwflag = 0;
    int shiftFlag = 0;
    int rShift = 0;
    int gShift = 0;
    int bShift = 0;
    int thing;

    FILE* infile;
    FILE* outfile;
    struct BMP_Header bmpHeader;
    struct DIB_Header dibHeader;

    if(argc < 2) {
        printf("Please include an image to be processed. Usage: ImageProcessor <file.bmp> <args>");
    }

    infile = fopen(argv[1], "rb");
    while ((thing = getopt(argc, argv, "r:g:b:wo:s:")) != -1) {
        switch (thing) {
            // Stores shift values for later use, marks flag that shift operation should be performed.
            case 'r':
                rShift = atoi(optarg);
                shiftFlag = 1;
                printf("r reaches here");
                break;
            case 'g':
                gShift = atoi(optarg);
                shiftFlag = 1;
                printf("g reaches here");
                break;
            case 'b':
                bShift = atoi(optarg);
                shiftFlag = 1;
                printf("b reaches here");
                break;
            //Marks bwflag
            case 'w':
                printf("w reaches here.");
                bwflag = 1;
                break;
            //Stores name of outfile for later use.
            case 'o' :
                printf("o reaches here");
                outfile = fopen(optarg, "wb");
                break;
            //Stores resize factor.
            case 's' :
                printf("s reaches here");
                break;
            default :
                break;
        }
    }
    if(outfile == NULL) {
        //TODO: Play around with string so that file.bmp becomes file_copy.bmp
    }

    //TODO: Read file. Read BMP Header, DIB Header, Pixel array.
    readBMPHeader(infile, &bmpHeader);
//    testPrintBMP(bmpHeader);

    readDIBHeader(infile, &dibHeader);
//    testPrintDIB(dibHeader);


    printf("Hello, World!\n");
    fclose(infile);
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