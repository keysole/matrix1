#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "matrix_op.h"
#include <math.h>

struct matrix {
    size_t rows;
    size_t cols;
    double *data;
};

matrix * matrix_set_zero (matrix *matrix){
    size_t rows, cols;
    rows = matrix->rows;
    cols = matrix->cols;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix_set(matrix, i, j, 0);
        }
    }
    return matrix;
}

matrix * matrix_alloc_zero (size_t rows, size_t cols){
    matrix * matrix = matrix_alloc(rows, cols);
    matrix_set_zero(matrix);
    return matrix;

}

matrix * matrix_set_identity(matrix * matrix)
{

    if (matrix->rows != matrix->cols)
        return NULL;
    const size_t size = matrix->rows;
    //matrix *matrix = matrix_alloc(size, size);
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix_set(matrix, i, j, (i == j ? 1 : 0));
        }
    }
    return matrix;
}


matrix * matrix_alloc_identity(size_t size)
{
    matrix * matrix = matrix_alloc(size, size);
    matrix = matrix_set_identity(matrix);
    return matrix;
}


matrix * matrix_assign(matrix *matrix_1, matrix *matrix_2){
    if (!same_size(matrix_1, matrix_2))
        return NULL;
    size_t rows, cols;
    rows = matrix_1->rows;
    cols = matrix_1->cols;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix_set(matrix_1, i, j, matrix_get(matrix_2, i, j));
        }
    }
    return matrix_1;
}

matrix * matrix_clone (matrix * matrix1, matrix * matrix2){
    size_t rows, cols;
    rows = matrix1->rows;
    cols = matrix1->cols;
   // struct matrix * clone = matrix_alloc(rows, cols);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix_set(matrix1, i, j, matrix_get(matrix2, i, j));
        }
    }
    return matrix1;

}
