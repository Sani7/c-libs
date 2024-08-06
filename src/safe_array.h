/*
 * Copyright © 2023 Sander Speetjens
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_GET(arr, index, type) (*(type *)array_get(arr, index))
#define ARRAY_2D_GET(arr, row, col, type) (*(type *)array_2d_get(arr, row, col))

typedef struct array_s
{
    size_t rows;
    size_t size;
    void* ptr;
    uint8_t data[1];
} array_t;

typedef struct array_2d_s
{
    size_t rows;
    size_t cols;
    size_t size;
    void* ptr;
    uint8_t data[1];
} array_2d_t;

// Array.c
array_t *array_init(size_t size, size_t rows);
array_t array_move(array_t* initial, size_t move);
size_t array_get_rows(array_t *arr);
void *array_get(array_t *arr, size_t index);
int array_set(array_t *arr, size_t index, void *element);
void array_free(array_t *arr);

array_2d_t *array_2d_init(size_t size, size_t rows, size_t cols);
size_t array_2d_get_rows(array_2d_t *x);
size_t array_2d_get_cols(array_2d_t *x);
void *array_2d_get(array_2d_t *x, size_t row, size_t col);
int array_2d_set(array_2d_t *x, size_t row, size_t col, void *val);
void array_2d_free(array_2d_t *x);