#include "transformations.h"
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if (image == NULL || image->header == NULL || image->data == NULL){
        return NULL;
    }
    //new struct with same header but empty data
    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    result->data = (struct pixel*)malloc((image->header->width * image->header->height) * sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    size_t w = (size_t)image->header->width;
    size_t h = (size_t)image->header->height;

    for (size_t y = 0; y < h; y++){
        for (size_t x = 0; x < w; x++){
            result->data[x + (w * y)] = image->data[(y * w) + (w - (x+1))];
        }
    }
    return result;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if (image == NULL || image->header == NULL || image->data == NULL){
        return NULL;
    }
    //new struct with same header but empty data
    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    result->data = (struct pixel*)malloc((image->header->width * image->header->height) * sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    size_t w = (size_t)image->header->width;
    size_t h = (size_t)image->header->height;

    for (size_t y = 0; y < h; y++){
        for (size_t x = 0; x < w; x++){
            result->data[x + (w * y)] = image->data[((h-1-y) * w) + x];
        }
    }
    return result;

}


struct bmp_image* rotate_left(const struct bmp_image* image){
    if (image == NULL || image->header == NULL || image->data == NULL){
        return NULL;
    }
    //new struct with same header but empty data
    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    result->data = (struct pixel*)malloc((image->header->width * image->header->height) * sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    uint32_t w = image->header->width;
    uint32_t h = image->header->height;
    uint32_t new_w = h;
    uint32_t new_h = w;

    result->header->width = new_w;
    result->header->height = new_h;

    uint32_t padding = new_w % 4;

    result->header->image_size = new_w * new_h * (uint32_t)sizeof(struct pixel) + (padding * new_h);
    result->header->size = result->header->image_size + 54;

    for (size_t y = 0; y < h; y++){
        for (size_t x = 0; x < w; x++){
            result->data[(h-y-1) + (new_w * x)] = image->data[(y * w) + x];
        }
    }
    return result;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
    if (image == NULL || image->header == NULL || image->data == NULL){
        return NULL;
    }
    //do the same that we did with Karel the Robot
    //create 2 temp struct
    struct bmp_image *Left1;
    struct bmp_image *Left2;
    struct bmp_image *Left3;
    //rotate 3 times
    Left1 = rotate_left(image);
    Left2 = rotate_left(Left1);
    Left3 = rotate_left(Left2);
    //free space that u dont need
    free_bmp_image(Left1);
    free_bmp_image(Left2);

    return Left3;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if (image == NULL || image->header == NULL || image->data == NULL){ return NULL; }
    if (image->header->width < 0 || image->header->height < 0){ return NULL; }
    if (start_y > image->header->height|| start_y < 0 || start_x > image->header->width || start_x < 0){ return NULL; }
    if (start_y + height > image->header->height || start_x + width > image->header->width ){ return NULL; }
    if( width > image->header->width || height > image->header->height){ return NULL;}
    uint32_t w = image->header->width;

    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    result->data = (struct pixel*)malloc((width * height) * sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->header->width = width;
    result->header->height = height;

    uint32_t padding = width % 4;

    result->header->image_size = width * height * (uint32_t)sizeof(struct pixel) + (padding * height);
    result->header->size = result->header->image_size + 54;

    struct bmp_image *new_image = flip_vertically(image);

    size_t pos = 0;
    size_t count_w = width;
    size_t count_h = height;

    for (size_t y = start_y; count_h > 0; y++){
        count_h--;
        count_w = width;
        for (size_t x = start_x; count_w > 0; x++){
            result->data[pos] = new_image->data[y * w + x];
            pos++;
            count_w--;
        }
    }
    struct bmp_image *ver_result = flip_vertically(result);

    free_bmp_image(result);
    free_bmp_image(new_image);

    return ver_result;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if (image == NULL || image->header == NULL || image->data == NULL){ return NULL; }
    if (factor < 0){ return NULL; }
    //new struct with same header but empty data
    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    uint32_t w = image->header->width;
    uint32_t h = image->header->height;

    if (factor == 1){
        result->data = (struct pixel*)malloc(( w * h) * sizeof(struct pixel));
        memcpy(result->data, image->data, (size_t)image->header->image_size);

        return result;
    }

    uint32_t new_w = (uint32_t)round((float)w * factor);
    uint32_t new_h = (uint32_t)round((float)h * factor); 

    result->header->width = new_w;
    result->header->height = new_h;

    result->data = (struct pixel*)malloc(( new_w * new_h) * sizeof(struct pixel));

    uint32_t padding = new_w % 4;

    result->header->image_size = new_w * new_h * (uint32_t)sizeof(struct pixel) + (padding * new_h);
    result->header->size = result->header->image_size + 54;

    size_t pos = 0;
    for (size_t y = 0; y < new_h; y++){
        for (size_t x = 0; x < new_w; x++){
            result->data[pos] = image->data[ (((x*w)/new_w) * w) + ((y*h)/new_h) ];
            pos++;
        }
    }
    return result;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if (image == NULL || image->header == NULL || image->data == NULL || colors_to_keep == NULL){
        return NULL;
    }
    bool r = 0, g = 0, b = 0;
    size_t z = 0;
    while (z < strlen(colors_to_keep)){
        
        if (colors_to_keep[z] != 'r' && colors_to_keep[z] != 'g' && colors_to_keep[z] != 'b'){
            printf("NO\n");
            return NULL;
        }

        if (colors_to_keep[z] == 'r'){
            r = 1;
        }
        if (colors_to_keep[z] == 'g'){
            g = 1;
        }
        if (colors_to_keep[z] == 'b'){
            b = 1;
        }

        z++;
    }

    if (r == 0 && g == 0 && b == 0){
        return NULL;
    }
    
    uint32_t w = image->header->width;
    uint32_t h = image->header->height;
    
    //new struct with same header but empty data
    struct bmp_image *result = malloc(sizeof(struct bmp_image));
    result->header = malloc(sizeof(struct bmp_header));
    result->data = (struct pixel*)malloc((w * h) * sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
   // memcpy(result->data, image->data, (size_t)image->header->image_size);
    
    for (size_t y = 0; y < h; y++){
        for (size_t x = 0; x < w; x++){
            
            if ( r == 1 ){
                result->data[ (y*w)+x ].red = image->data[ (y*w)+x ].red;
            }
            else{ result->data[ (y*w)+x ].red = 0; }

            if ( g == 1 ){
                result->data[ (y*w)+x ].green = image->data[ (y*w)+x ].green;
            }
            else{ result->data[ (y*w)+x ].green = 0; }

            if ( b == 1 ){
                result->data[ (y*w)+x ].blue = image->data[ (y*w)+x ].blue;
            }
            else{ result->data[ (y*w)+x ].blue = 0; }

        }
    }

    return result;
}
