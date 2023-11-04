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
#define ARRAY_C_GET_IMAG(arr, row, type) (*(type *)array_c_get_imag(arr, row))
#define ARRAY_C_GET_REAL(arr, row, type) (*(type *)array_c_get_real(arr, row))
#define ARRAY_C_GET_MAG(arr, row, type) (*(type *)array_c_get_mag(arr, row))
#define ARRAY_C_GET_PHASE(arr, row, type) (*(type *)array_c_get_phase(arr, row))


typedef struct array_s
{
    size_t rows;
    size_t size;
    uint8_t data[1];
} array_t;

typedef struct array_2d_s
{
    size_t rows;
    size_t cols;
    size_t size;
    uint8_t data[1];
} array_2d_t;

typedef struct array_c_s
{
    size_t rows;
    size_t size;
    uint8_t data[1];
} array_c_s_t;

typedef struct array_c_p_s
{
    size_t rows;
    size_t size;
    uint8_t data[1];
} array_c_p_t;

// Array.c
array_t *array_init(size_t size, size_t rows);
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

array_c_s_t *array_c_s_init(size_t rows, size_t size);
size_t array_c_s_get_rows(array_c_s_t *x);
void* array_c_get_real(array_c_s_t *x, size_t row);
void* array_c_get_imag(array_c_s_t *x, size_t row);
int array_c_s_set(array_c_s_t *x, size_t row, void *real, void *imaginary);
void array_c_s_free(array_c_s_t *x);

array_c_p_t *array_c_p_init(size_t rows, size_t size);
size_t array_c_p_get_rows(array_c_p_t *x);
void *array_c_get_mag(array_c_p_t *x, size_t row);
void *array_c_get_phase(array_c_p_t *x, size_t row);
int array_c_p_set(array_c_p_t *x, size_t row, void* magnitude, void* phase);
void array_c_p_free(array_c_p_t *x);