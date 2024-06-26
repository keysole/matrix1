#include <stdlib.h>
#include <stdio.h>
#include "matrix_op.h"
#include "matrix.h"
#include "matrix_init.h"
#include <math.h>

struct matrix {
    size_t rows;
    size_t cols;
    double *data;
};



matrix *matrix_op_add(matrix * matrix_1, matrix * matrix_2)
{
    if (!same_size(matrix_1, matrix_2))
        return NULL;
    size_t rows = matrix_1->rows;
    size_t cols = matrix_2->cols;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            double a = matrix_get(matrix_1, i, j);
            double b = matrix_get(matrix_2, i, j);
            matrix_set(matrix_1, i, j, a + b);
        }
    }
    return matrix_1;
}


matrix *matrix_op_sum(matrix * matrix_1, matrix * matrix_2)
{
    if (!same_size(matrix_1, matrix_2))
        return NULL;
    size_t rows = matrix_1->rows;
    size_t cols = matrix_2->cols;
    matrix * sum = matrix_alloc(rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            double a = matrix_get(matrix_1, i, j);
            double b = matrix_get(matrix_2, i, j);
            matrix_set(sum, i, j, a + b);
        }
    }
    return sum;
}

matrix *matrix_op_mult_alloc(matrix *matrix_1, matrix *matrix_2)
{
    if (matrix_1->cols != matrix_2->rows)
    {
        return NULL;
    }
    size_t m = matrix_1->rows;
    size_t n = matrix_1->cols;
    size_t p = matrix_2->cols;
    matrix *product = matrix_alloc(m, p);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < p; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < n; k++)
            {
                sum += matrix_get(matrix_1, i, k) * matrix_get(matrix_2, k, j);
            }
            matrix_set(product, i, j, sum);
        }
    }
    return product;
}

matrix *matrix_op_mult(matrix *matrix_1, matrix *matrix_2)
{
    if (matrix_1->cols != matrix_2->rows)
    {
        return NULL;
    }
    size_t m = matrix_1->rows;
    size_t n = matrix_1->cols;
    size_t p = matrix_2->cols;
    struct matrix *temp = matrix_alloc(m, p);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < p; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < n; k++)
            {
                sum += matrix_get(matrix_1, i, k) * matrix_get(matrix_2, k, j);
            }
            matrix_set(temp, i, j, sum);
        }

    }
    matrix_1 = matrix_resize(matrix_1, m, p);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < p; j++)
        {
            matrix_set(matrix_1, i, j, matrix_get(temp, i, j));

        }
    }

    return matrix_1;
}



matrix * matrix_op_scalar_multiply(matrix *matrix, double x)
{
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix_set(matrix, i, j, matrix_get(matrix, i, j) * x);
        }
    }
    return matrix;
}

matrix * matrix_op_mult_row(matrix *matrix, const size_t i, double mult)
{
    for (size_t j = 0; j < matrix->cols; ++j)
    {
        matrix_set(matrix, i, j, matrix_get(matrix, i, j) * mult);
    }
    return matrix;
}

matrix * matrix_op_add_rows(matrix *matrix, size_t i_1, size_t i_2, double factor)
{
    for (size_t j = 0; j < matrix->cols; ++j)
    {
        matrix_set(matrix, i_1, j, matrix_get(matrix, i_1, j) + matrix_get(matrix, i_2, j) * factor);
    }
    return matrix;
}


matrix * matrix_op_swap_rows(matrix *matrix, size_t i_1, const size_t i_2)
{
    for (size_t j = 0; j < matrix->cols; ++j)
    {
        double row_2_el = matrix_get(matrix, i_2, j);
        matrix_set(matrix, i_2, j, matrix_get(matrix, i_1, j));
        matrix_set(matrix, i_1, j, row_2_el);

    }
    return matrix;
}

matrix *matrix_op_upper_triang(matrix * matrix){
    for (size_t j = 0; j < matrix->rows; ++j) {
        for (size_t i = 0; i < matrix->rows; ++i) {
            if (i > j){
                double factor = matrix_get(matrix, i, j) / matrix_get(matrix, j, j);
                matrix_op_add_rows(matrix, i, j, -factor);

            }
            }


        }

    return matrix;
}


matrix *matrix_op_inverse(matrix * matrix){
    if (matrix->rows != matrix->cols)
        return NULL;
    struct matrix * inv = matrix_alloc_identity(matrix->cols);

      for (size_t j = 0; j < matrix->rows; ++j) {
        for (size_t i = 0; i < matrix->rows; ++i) {
            if (i > j){
                double factor = matrix_get(matrix, i, j) / matrix_get(matrix, j, j);
                matrix_op_add_rows(inv, i, j, -factor);
                matrix_op_add_rows(matrix, i, j, -factor);

            }
            }


        }


    for (size_t j = 0; j < matrix->rows; ++j) {
        for (size_t i = 0; i < matrix->cols; ++i) {
            if (j > i){
                double factor = matrix_get(matrix, i, j) / matrix_get(matrix, j, j);
                matrix_op_add_rows(inv, i, j, -factor);
                matrix_op_add_rows(matrix, i, j, -factor);

            }
            }

        }

    for (size_t n = 0; n < matrix->rows; ++n) {
        if (fabs(matrix_get(matrix, n, n) - 0.0001) == 0.0){
            printf("Error, matrix is not invertible\n");
            return NULL;
            }
        double factor = 1.0 / matrix_get(matrix, n, n);
        matrix_op_mult_row(inv, n, factor);
        matrix_op_mult_row(matrix, n, factor);
    }

    matrix = matrix_assign(matrix, inv);
    matrix_free(inv);
    return matrix;
}


double matrix_op_det(matrix * matrix){
    if (matrix->cols != matrix->rows)
        return 0;
    matrix = matrix_op_upper_triang(matrix);
    double det = 1.0;
    for (size_t i = 0; i < matrix->cols; ++i){
        det *= matrix_get(matrix, i, i);
    }
    return det;
}

double matrix_op_norm(matrix * matrix){
    double sum = 0;
    double max = 0;
    for(size_t j = 0; j < matrix->cols; ++j){
        max += matrix_get(matrix, 0, j);
    }
    max = fabs(max);

    for (size_t i = 1; i < matrix->rows; ++i){
        for(size_t j = 0; j < matrix->cols; ++j){
            sum += matrix_get(matrix, i, j);
        }
        sum = fabs(sum);
        if (sum > max)
            max = sum;
        sum = 0;
    }
    return max;
}



