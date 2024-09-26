# BMP Module

This module provides functionality for working with BMP (Bitmap) graphic files, including loading, saving, and managing BMP images. It defines structured data types and functions that represent and manipulate the BMP format.

## Structures

### `struct bmp_header`
This structure represents the header of a BMP file. The BMP header contains metadata about the image, such as its size, width, height, and format. The header occupies 54 bytes in memory. For more detailed information on the fields and their allowed values, refer to the `bmp.h` header file.

### `struct pixel`
This structure represents a single pixel in the BMP image. It contains the following fields:
- **`red`**: 8 bits representing the red color component.
- **`green`**: 8 bits representing the green color component.
- **`blue`**: 8 bits representing the blue color component.

Each pixel is stored using 24 bits, with 8 bits for each color channel (red, green, and blue).

### `struct bmp_image`
This structure represents an entire BMP image, which consists of:
- **`header`**: The BMP header (defined by `struct bmp_header`).
- **`data`**: A sequence of pixels representing the image. The pixels are stored in a one-dimensional array, where the number of pixels is determined by the product of the image's width and height.

## Functions

### `struct bmp_header* read_bmp_header(FILE* file)`
- **Parameters**:
  - `FILE* file`: A pointer to the BMP file stream to read from.
- **Returns**:
  - A pointer to the `bmp_header` structure containing the loaded header, or `NULL` if an error occurs.

This function reads the BMP header from the beginning of the file. It expects the BMP magic number `BM` in the header to verify that the file is a valid BMP file.

---

### `struct pixel* read_data(FILE* file, int width, int height)`
- **Parameters**:
  - `FILE* file`: A pointer to the BMP file stream to read from.
  - `int width`: The width of the image in pixels.
  - `int height`: The height of the image in pixels.
- **Returns**:
  - A pointer to the array of `pixel` structures representing the image data, or `NULL` if an error occurs.

This function reads the sequence of pixels (image data) from the BMP file. The data is stored as a one-dimensional array of pixels, with the number of elements determined by the image's width and height.

---

### `struct bmp_image* read_bmp(FILE* file)`
- **Parameters**:
  - `FILE* file`: A pointer to the BMP file stream to read from.
- **Returns**:
  - A pointer to a `bmp_image` structure containing both the header and image data, or `NULL` if an error occurs.

This function reads the entire BMP file, including both the header and the image data, and returns a pointer to the `bmp_image` structure representing the complete image.

---

### `bool write_bmp(FILE* file, const struct bmp_image* image)`
- **Parameters**:
  - `FILE* file`: A pointer to the BMP file stream to write to.
  - `const struct bmp_image* image`: A pointer to the `bmp_image` structure containing the image to write.
- **Returns**:
  - `true` if the image is successfully written to the file.
  - `false` if an error occurs during the write operation.

This function writes a BMP image (header and data) to a file. It returns `true` if the image is successfully saved, otherwise it returns `false`.

---

### `void free_bmp_image(struct bmp_image* image)`
- **Parameters**:
  - `struct bmp_image* image`: A pointer to the `bmp_image` structure whose memory needs to be freed.

This function releases the memory that was allocated to store the BMP image (both the header and the pixel data). It should be called after the image is no longer needed to avoid memory leaks.
# Transformations Module

This module provides basic image editing functionalities, enabling the creation of new images based on transformations applied to an input BMP image.

## Functions

### `struct bmp_image* flip_horizontally(const struct bmp_image* image)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to be flipped.
- **Returns**:
  - A new image flipped horizontally (mirror image along the vertical axis).
  - `NULL` if the input image reference is `NULL`.

This function creates a new image by flipping the original image horizontally, producing a mirror image. The dimensions of the image remain unchanged.

---

### `struct bmp_image* flip_vertically(const struct bmp_image* image)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to be flipped.
- **Returns**:
  - A new image flipped vertically (mirror image along the horizontal axis).
  - `NULL` if the input image reference is `NULL`.

This function creates a new image by flipping the original image vertically. The image dimensions remain unchanged.

---

### `struct bmp_image* rotate_right(const struct bmp_image* image)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to be rotated.
- **Returns**:
  - A new image rotated 90 degrees to the right.
  - `NULL` if the input image reference is `NULL`.

This function rotates the original image 90° to the right, which swaps the image's width and height in the resulting image.

---

### `struct bmp_image* rotate_left(const struct bmp_image* image)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to be rotated.
- **Returns**:
  - A new image rotated 90 degrees to the left.
  - `NULL` if the input image reference is `NULL`.

This function rotates the image 90° to the left, similarly swapping the image's width and height.

---

### `struct bmp_image* crop(const struct bmp_image* image, int start_y, int start_x, int height, int width)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to crop.
  - `int start_y`: The starting y-coordinate (row) of the crop area.
  - `int start_x`: The starting x-coordinate (column) of the crop area.
  - `int height`: The height of the crop area.
  - `int width`: The width of the crop area.
- **Returns**:
  - A new image created by cropping a portion of the original image.
  - `NULL` if the input image reference is `NULL` or if the cropping parameters are out of range.

This function extracts a rectangular section from the original image based on the specified starting coordinates, width, and height. The cropped region must be within the bounds of the original image, and the dimensions must be at least 1x1 pixels.

---

### `struct bmp_image* scale(const struct bmp_image* image, float factor)`
- **Parameters**:
  - `const struct bmp_image* image`: A reference to the original image to scale.
  - `float factor`: The scale factor, which determines the resizing:
    - `factor < 1`: The image will be scaled down (reduced in size).
    - `factor = 1`: The image will remain unchanged.
    - `factor > 1`: The image will be scaled up (enlarged).
- **Returns**:
  - A new image scaled by the specified factor.
  - `NULL` if the input image reference is `NULL`.

This function scales the image proportionally according to the provided scale factor. A factor less than 1 reduces the image size, while a factor greater than 1 enlarges the image.
# BMP Transformation Tool

The BMP module also provides a command-line tool for performing various transformations on BMP images. This section outlines how to use the tool and demonstrates an example of chaining commands via pipes.

## Usage
```
Usage: bmp [OPTION]... [FILE]...
Simple BMP transformation tool.

With no FILE, read from standard input or write to standard output.

  -r            rotate image right
  -l            rotate image left
  -h            flip image horizontally
  -v            flip image vertically
  -c y,x,h,w    crop image from position [y,x] of giwen height and widht
  -s factor     scale image by factor
  -e string     extract colors
  -o file       write output to file
  -i file       read input from the file
```
The following example demonstrates how to rotate the image saboteur.bmp to the right and save the result in output.bmp:

```$ bmp -i saboteur.bmp | bmp -r | bmp -l | bmp -o output.bmp```
