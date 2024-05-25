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

matrix * matrix_task_exponent(matrix * matrix, const double eps){
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;
    struct matrix * exp;
    struct matrix * term_prev;
    struct matrix * term_next;
    int n = 1;
    term_prev = matrix_alloc_identity(rows);
    exp = matrix_alloc(rows, cols);
    exp = matrix_clone(term_prev);
    term_next = matrix_clone(matrix);

    double norm = matrix_op_norm(term_next);

  while (norm >= eps){
        n++;
        exp = matrix_op_add(exp, term_next);
        struct matrix * temp = matrix_op_mult_alloc(term_next, matrix);
        double mult = 1.0 / (double) n;
        temp = matrix_op_scalar_multiply(temp, mult);
        term_prev = matrix_clone(term_next);
        term_next = matrix_clone(temp);
        matrix_free(temp);
        norm = matrix_op_norm(term_next);

    }
    matrix_free(term_next);
    matrix_free(term_prev);
    return exp;

}


matrix *matrix_task_gauss(matrix * matrix1, matrix * vals, matrix * sols, size_t n){
    for (size_t j = 0; j < n; ++j) {
        //int pivot_row = j;


        for (size_t i = 0; i < n; ++i) {
            if (i > j){
                double factor = matrix_get(matrix1, i, j) / matrix_get(matrix1, j, j);
                matrix_set(vals, i, 0, matrix_get(vals, i, 0) - factor * matrix_get(vals, j, 0));
                matrix_op_add_rows(matrix1, i, j, -factor);

            }
            }

        }


    int n_i = (int) n;
    for (int k = n_i-1; k >= 0; k--) {
        double sum = 0;
        for (int l = k+1; l < n_i; l++) {
            sum += matrix_get(matrix1, k, l) * matrix_get(sols, l, 0);
        }
        double sol_val = (matrix_get(vals, k, 0) - sum) / matrix_get(matrix1, k, k);

        matrix_set(sols, k, 0, sol_val);
    }



    return sols;
}
