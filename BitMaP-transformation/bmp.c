#include "bmp.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct bmp_header* read_bmp_header(FILE* stream){
    if (stream == NULL){
        return NULL;
    }

    struct bmp_header *bitmapFileHeader = malloc(sizeof(struct bmp_header));  
    rewind(stream);
    fread(bitmapFileHeader, sizeof(struct bmp_header),1,stream);
    //verify that this is a .BMP file by checking bitmap id
    if (bitmapFileHeader->type !=0x4D42){
        free(bitmapFileHeader);
        return NULL;
    }

    return bitmapFileHeader;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){

    if (stream == NULL){
        return NULL;
    }
    if (header == NULL){
        return NULL;
    }

    fseek(stream,header->offset,SEEK_SET);

    struct pixel* pixel_array = malloc((header->width * header->height) * sizeof(struct pixel));
    int padding = header->width % 4;
    int count = 0;

    for (int x = 0; x < (header->width * header->height) ; x++){

        fread(&pixel_array[x].blue,sizeof(pixel_array->blue), 1, stream);
        fread(&pixel_array[x].green,sizeof(pixel_array->green), 1, stream);
        fread(&pixel_array[x].red,sizeof(pixel_array->red), 1, stream);
        count++;
        if (count == header->width && padding > 0){
            fseek(stream, padding,SEEK_CUR);
            count = 0;
        }

    }

    return pixel_array;
}

struct bmp_image* read_bmp(FILE* stream){
    if (stream == NULL){
        return NULL;
    }
    rewind(stream);

    struct bmp_image *BitMapImage = malloc(sizeof(struct bmp_image));
    BitMapImage->header = read_bmp_header(stream);

    if (BitMapImage->header == NULL){
        fprintf(stderr,"Error: This is not a BMP file.\n");
        free(BitMapImage);
        return NULL;
    }
    BitMapImage->data = read_data(stream,BitMapImage->header);
    if (BitMapImage->data == NULL){
        fprintf(stderr,"Error: Corrupted BMP file.\n");
        free(BitMapImage);
        return NULL;
    }
    return BitMapImage;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
    if (stream == NULL){
        return false;
    }
    if (image == NULL){
        return false;
    }

    rewind(stream);
    fwrite(image->header, sizeof(*image->header),1,stream);

    int padding = image->header->width % 4;
    int count = 0;

    for (int x = 0; x < (image->header->width * image->header->height) ; x++){

        fwrite(&image->data[x].blue,sizeof(image->data->blue), 1, stream);
        fwrite(&image->data[x].green,sizeof(image->data->green), 1, stream);
        fwrite(&image->data[x].red,sizeof(image->data->red), 1, stream);
        count++;
        if (count == image->header->width && padding > 0){
            fwrite(PADDING_CHAR,1,(size_t)padding,stream);
            count = 0;
        }

    }

    return true;
}

void free_bmp_image(struct bmp_image* image){
    if( image != NULL ){ free(image->header); free(image->data); free(image);}
}
