#include <stdio.h>
#include "bmp.h"
#include "transformations.h"
#include "bmp.c"
#include "transformations.c"

int main(){
    FILE *filePtr;  //our file pointer

    //open file in read binary mode
    filePtr = fopen("lenna.bmp","rb");
    struct bmp_image *Image = read_bmp(filePtr);
    struct bmp_image *Imageo = flip_vertically(Image);
    struct bmp_image *Imageg = flip_horizontally(Image);
    struct bmp_image *Imagex = rotate_left(Image);
    struct bmp_image *Imagec = rotate_right(Image);
    struct bmp_image *ImageCrop = crop(Image,0,0,32,48);
    float factor = 2;
    struct bmp_image *ImageScale = scale(Image,factor);
    char *c = "rgbe";
    struct bmp_image *ImageE = extract(Image, c);
    fclose(filePtr);
    FILE *filePtr2;
    filePtr2 = fopen("new.bmp", "w");
    write_bmp(filePtr2, ImageE);
    fclose(filePtr2);
    free_bmp_image(Image);
    free_bmp_image(Imageo);
    free_bmp_image(Imageg);
    free_bmp_image(Imagex);
    free_bmp_image(Imagec);
    free_bmp_image(ImageCrop);
    free_bmp_image(ImageScale);
    free_bmp_image(ImageE);
}

