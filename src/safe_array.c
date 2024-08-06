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

array_t *array_init(size_t size, size_t rows)
{
    array_t *arr = calloc(sizeof(array_t) + (size * rows - 1), 1);
    if (!arr)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }

    arr->rows = rows;
    arr->size = size;
    arr->ptr = arr->data;
    return arr;
}

array_t array_move(array_t* initial, size_t move)
{
    if (initial->size <= move)
    {
        fprintf(stderr, "%s: initial->size <= move", __func__);
        return (array_t){.rows = 0, .ptr = 0, .size = 0};
    }

    return (array_t) {
        .size = initial->size,
        .rows = initial->rows - move,
        .ptr = initial->ptr + (move * initial->size)
    };
}

size_t array_get_rows(array_t *arr)
{
    if (!arr)
    {
        fprintf(stderr, "%s: Invalid argument\n", __func__);
        return 0;
    }

    return arr->rows;
}

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

    return (char *)arr->ptr + (index * arr->size);
}

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

    void *dest = (char *)arr->ptr + (index * arr->size);
    memcpy(dest, element, arr->size);

    return 0;
}

void array_free(array_t *arr)
{
    if (!arr)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
    }
    free(arr);
}


array_2d_t *array_2d_init(size_t size, size_t rows, size_t cols)
{
    array_2d_t *arr = calloc(sizeof(array_2d_t) + (size * rows * cols  - 1), 1);
    if (!arr)
    {
        fprintf(stderr, "%s: Failed to allocate memory for array", __func__);
        return NULL;
    }

    arr->rows = rows;
    arr->cols = cols;
    arr->size = size;
    arr->ptr = arr->data;
    return arr;
}

size_t array_2d_get_rows(array_2d_t *x)
{
    if (!x)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
        return 0;
    }

    return x->rows;
}

size_t array_2d_get_cols(array_2d_t *x)
{
    if (!x)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
        return 0;
    }

    return x->cols;
}

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

    return (char *)x->ptr + (row * x->size) + (col * x->cols * x->size);
}

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

    void *dest = (char *)x->ptr + (row * x->size) + (col * x->cols * x->size);
    memcpy(dest, val, x->size);

    return 0;
}

void array_2d_free(array_2d_t *x)
{
    if (!x)
    {
        fprintf(stderr, "%s: ptr dereferences to NULL\n", __func__);
    }
    free(x);
}
