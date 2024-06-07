#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "matrix_op.h"
#include "matrix_init.h"
#include <math.h>


struct matrix {
    size_t rows;
    size_t cols;
    double *data;
};

void matrix_print(matrix *matrix)
{
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            printf("A[%d][%d] = %5.2f \n", (int) i, (int) j, matrix_get(matrix, i, j));
        }
    }
}

matrix* matrix_alloc (size_t rows, size_t cols){
    matrix *matrix = malloc(sizeof(*matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = malloc(rows * cols * sizeof(double));
    if (!matrix->data) {
        return NULL;
    }
    return matrix;

}

void matrix_free (matrix * matrix){
    free(matrix->data);
    free(matrix);
}



double matrix_get (matrix *m, size_t i, size_t j){
   return m->data[m->cols * j + i];
}

void matrix_set(matrix *m, size_t i, size_t j, double x)
{
    //*(matrix->data + i * matrix->rows + j) = x;
    m->data[m->cols * j + i] = x;

}

matrix * matrix_resize (matrix *m, size_t rows, size_t cols){
    free(m->data);
    m = realloc(m, rows * cols * sizeof(double));
    return m;
}



int same_size(matrix * matrix_1, matrix * matrix_2){
    return (matrix_1->rows == matrix_2->rows && matrix_1->cols == matrix_2->cols);

}


matrix *matrix_transpose_sqr(matrix *matrix)
{
   size_t rows = matrix->cols;
   size_t cols = matrix->rows;
   struct matrix * matrix_t = matrix_alloc(rows, cols);
   if (rows != cols)
        return NULL;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            {
            double temp = matrix_get(matrix, i, j);

            matrix_set(matrix_t, i, j, matrix_get(matrix, j, i));
            matrix_set(matrix_t, j, i, temp);
            }
            }
    return matrix_t;
}




matrix *matrix_transpose_sqr_in_place(matrix *matrix)
{
   size_t rows = matrix->cols;
   size_t cols = matrix->rows;
   if (rows != cols)
        return NULL;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            {
            double temp = matrix_get(matrix, i, j);

            matrix_set(matrix, i, j, matrix_get(matrix, j, i));
            matrix_set(matrix, j, i, temp);
            }
            }
    return matrix;
}






