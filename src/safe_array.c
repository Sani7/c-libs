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
#include "safe_array.h"

/**
 * @brief This function generates a safe array
 * 
 * @param size The element size (sizeof(type))
 * @param rows The number of rows in the array
 * @return array_t* The pointer to the safe array struct
 */
array_t *array_init(size_t size, size_t rows)
{
    array_t *arr = calloc(sizeof(array_t) + (size * rows), 1);
    if (!arr)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }

    arr->rows = rows;
    arr->size = size;
    return arr;
}

/**
 * @brief This function gets an element from the safe array
 * 
 * @param arr The pointer to the safe array struct
 * @param index The row index of the element to get
 * @return void* The ptr to the element
 */
void *array_get(array_t *arr, size_t index)
{
    if (!arr)
    {
        fprintf(stderr, "%s: Invalid argument\n", __func__);
        return NULL;
    }

    if (index >= arr->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, index, arr->rows);
        return NULL;
    }

    return (char *)arr->data + (index * arr->size);
}

/**
 * @brief This function sets an element in the safe array
 * 
 * @param arr The pointer to the safe array struct
 * @param index The row index of the element to set
 * @param element The ptr to the value to set
 * @return int 0 on success, -1 on failure
 */
int array_set(array_t *arr, size_t index, void *element)
{
    if (!arr || !element)
    {
        fprintf(stderr, "%s: Invalid argument\n", __func__);
        return -1;
    }

    if (index >= arr->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, index, arr->rows);
        return -1;
    }

    void *dest = (char *)arr->data + (index * arr->size);
    memcpy(dest, element, arr->size);

    return 0;
}

/**
 * @brief This function frees the safe array, sets the pointer to NULL and the number of rows to 0
 * 
 * @param arr The pointer to the safe array struct
 */
void array_free(array_t *arr)
{
    if (!arr)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
    }
    free(arr);
}

/**
 * @brief This function generates a 2D safe array
 * 
 * @param size The element size (sizeof(type))
 * @param rows The number of rows in the array
 * @param cols The number of columns in the array
 * @return Array_2D_t* The pointer to the 2D array struct
 */
array_2d_t *array_2d_init(size_t size, size_t rows, size_t cols)
{
    array_2d_t *arr = calloc(sizeof(array_2d_t) + (size * rows * cols), 1);
    if (!arr)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }

    arr->rows = rows;
    arr->cols = cols;
    arr->size = size;
    return arr;
}

/**
 * @brief This function gets an element from the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @param row The row index of the element to get
 * @param col The column index of the element to get
 * @return void* The ptr to the element
 */
void *array_2d_get(array_2d_t *x, size_t row, size_t col)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: row index out of bounds: %d > %d\n", __func__, row, x->rows);
        return 0;
    }
    if (col >= x->cols)
    {
        fprintf(stderr, "%s: col index out of bounds: %d > %d\n", __func__, col, x->cols);
        return 0;
    }

    return (char *)x->data + (row * x->size) + (col * x->cols * x->size);
}

/**
 * @brief This function sets an element in the 2D safe array
 *
 * @param x The pointer to the 2D array struct
 * @param row The row index of the element to set
 * @param col The column index of the element to set
 * @param val The ptr to the value to set
 */
int array_2d_set(array_2d_t *x, size_t row, size_t col, void *val)
{
    if (!x || !val)
    {
        fprintf(stderr, "%s: Invalid argument\n", __func__);
        return -1;
    }

    if (row >= x->rows)
    {
        fprintf(stderr, "%s: row index out of bounds: %d > %d\n", __func__, row, x->rows);
        return -1;
    }
    if (col >= x->cols)
    {
        fprintf(stderr, "%s: col index out of bounds: %d > %d\n", __func__, col, x->cols);
        return -1;
    }

    void *dest = (char *)x->data + (row * x->size) + (col * x->cols * x->size);
    memcpy(dest, val, x->size);

    return 0;
}

/**
 * @brief This function frees the 2D safe array, sets the pointer to NULL and the number of rows and columns to 0
 *
 * @param x The pointer to the 2D array struct
 */
void array_2d_free(array_2d_t *x)
{
    if (!x)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
    }
    free(x);
}

/**
 * @brief This function generates a complex safe array
 * 
 * @param rows The number of rows in the array
 * @param size The element size (sizeof(type))
 * @return array_c_s_t* The pointer to the complex array struct
 */
array_c_s_t *array_c_s_init(size_t rows, size_t size)
{
    array_c_s_t *x = calloc(sizeof(array_c_s_t), 1);
    if (!x)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }
    x->real = calloc(size, rows);
    if (!x->real)
    {
        fprintf(stderr, "%s: Failed to allocate memory for data", __func__);
        free(x);
        return NULL;
    }
    x->imaginary = calloc(size, rows);
    if (!x->imaginary)
    {
        fprintf(stderr, "%s: Failed to allocate memory for data", __func__);
        free(x->real);
        free(x);
        return NULL;
    }

    x->rows = rows;
    x->size = size;
    return x;
}

/**
 * @brief This function gets an imaginary element from the complex safe array
 * 
 * @param x The pointer to the complex array struct
 * @param row The row index of the element to get
 * @return void* The ptr to the imaginary element
 */
void* array_c_get_imag(array_c_s_t *x, size_t row)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return NULL;
    }

    return (char *)x->imaginary + (row * x->size);
}

/**
 * @brief This function gets a real element from the complex safe array
 * 
 * @param x The pointer to the complex array struct
 * @param row The row index of the element to get
 * @return void* The ptr to the real element
 */
void* array_c_get_real(array_c_s_t *x, size_t row)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return NULL;
    }

    return (char *)x->real + (row * x->size);
}

/**
 * @brief This function sets an element in the complex safe array
 *
 * @param x The pointer to the complex array struct
 * @param row The row index of the element to set
 * @param real The ptr to the real value of the element
 * @param imaginary The ptr to the imaginary value of the element
 */
int array_c_s_set(array_c_s_t *x, size_t row, void *real, void *imaginary)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return -1;
    }

    memcpy((char *)x->real + (row * x->size), real, x->size);
    memcpy((char *)x->imaginary + (row * x->size), imaginary, x->size);
    return 0;
}

/**
 * @brief This function frees the complex safe array, sets the pointer to NULL and the number of rows to 0
 *
 * @param x The pointer to the complex array struct
 */
void array_c_s_free(array_c_s_t *x)
{
    if (!x)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
    }
    free(x->real);
    free(x->imaginary);
    free(x);
}

/**
 * @brief This function generates a complex safe array in polar form
 *
 * @param x The pointer to the complex array struct
 * @param rows The number of complex elements in the array
 * @param init_val The initial value of the array
 * @return int The number of elements in the array
 */
array_c_p_t *array_c_p_init(size_t rows, size_t size)
{
    array_c_p_t* x = calloc(sizeof(array_c_p_t), 1);
    if (!x)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }
    x->magnitude = (double *)calloc(rows, sizeof(double));
    if (!x->magnitude)
    {
        fprintf(stderr, "%s: Failed to allocate memory for data", __func__);
        free(x);
        return NULL;
    }
    x->phase = (double *)calloc(rows, sizeof(double));
    if (!x->phase)
    {
        fprintf(stderr, "%s: Failed to allocate memory for data", __func__);
        free(x->magnitude);
        free(x);
        return NULL;
    }
    x->size = size;
    x->rows = rows;

    return x;
}

void* array_c_get_mag(array_c_p_t *x, size_t row)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return 0;
    }

    return (char *)x->magnitude + (row * x->size);
}

void* array_c_get_phase(array_c_p_t *x, size_t row)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return 0;
    }

    return (char *)x->phase + (row * x->size);
}

/**
 * @brief This function sets an element in the complex safe array
 *
 * @param x The pointer to the complex array struct
 * @param row The row index of the element to set
 * @param magnitude The magnitude value of the element
 * @param phase The phase value of the element
 */
int array_c_p_set(array_c_p_t *x, size_t row, void* magnitude, void* phase)
{
    if (row >= x->rows)
    {
        fprintf(stderr, "%s: index out of bounds: %d > %d\n", __func__, row, x->rows);
        return -1;
    }

    memcpy((char *)x->magnitude + (row * x->size), magnitude, x->size);
    memcpy((char *)x->phase + (row * x->size), phase, x->size);
    return 0;
}

/**
 * @brief This function frees the complex safe array, sets the pointer to NULL and the number of rows to 0
 *
 * @param x The pointer to the complex array struct
 */
void array_c_p_free(array_c_p_t *x)
{
    free(x->magnitude);
    free(x->phase);
    x->magnitude = NULL;
    x->phase = NULL;
    x->rows = 0;
}