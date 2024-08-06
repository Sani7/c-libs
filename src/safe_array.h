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

/**
 * @brief This function generates a safe array
 * 
 * @param size The element size (sizeof(type))
 * @param rows The number of rows in the array
 * @return array_t* The pointer to the safe array struct
 */
array_t *array_init(size_t size, size_t rows);

/**
 * @brief This function creates a new array that uses the original array
 * 
 * @param initial The pointer to the original safe array struct
 * @param move The amount of rows to move
 * @return array_t The new safe array struct that uses the original array
 */
array_t array_move(array_t* initial, size_t move);

/**
 * @brief This function gets the number of rows in the safe array
 * 
 * @param arr The pointer to the safe array struct
 * @return size_t The number of rows
 */
size_t array_get_rows(array_t *arr);

/**
 * @brief This function gets an element from the safe array
 * 
 * @param arr The pointer to the safe array struct
 * @param index The row index of the element to get
 * @return void* The ptr to the element
 */
void *array_get(array_t *arr, size_t index);

/**
 * @brief This function sets an element in the safe array
 * 
 * @param arr The pointer to the safe array struct
 * @param index The row index of the element to set
 * @param element The ptr to the value to set
 * @return int 0 on success, -1 on failure
 */
int array_set(array_t *arr, size_t index, void *element);

/**
 * @brief This function frees the safe array, sets the pointer to NULL and the number of rows to 0
 * 
 * @param arr The pointer to the safe array struct
 */
void array_free(array_t *arr);

/**
 * @brief This function generates a 2D safe array
 * 
 * @param size The element size (sizeof(type))
 * @param rows The number of rows in the array
 * @param cols The number of columns in the array
 * @return Array_2D_t* The pointer to the 2D array struct
 */
array_2d_t *array_2d_init(size_t size, size_t rows, size_t cols);

/**
 * @brief This function gets the number of rows in the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @return size_t The number of rows
 */
size_t array_2d_get_rows(array_2d_t *x);

/**
 * @brief This function gets the number of columns in the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @return size_t The number of columns
 */
size_t array_2d_get_cols(array_2d_t *x);

/**
 * @brief This function gets an element from the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @param row The row index of the element to get
 * @param col The column index of the element to get
 * @return void* The ptr to the element
 */
void *array_2d_get(array_2d_t *x, size_t row, size_t col);

/**
 * @brief This function sets an element in the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @param row The row index of the element to set
 * @param col The column index of the element to set
 * @param val The ptr to the value to set
 */
int array_2d_set(array_2d_t *x, size_t row, size_t col, void *val);

/**
 * @brief This function frees the 2D safe array, sets the pointer to NULL and the number of rows and columns to 0
 *
 * @param x The pointer to the 2D array struct
 */
void array_2d_free(array_2d_t *x);