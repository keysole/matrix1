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
    exp = matrix_assign(exp, term_prev);
    term_next = matrix_alloc(rows, cols);
    term_next = matrix_assign(term_next, matrix);

    double norm = matrix_op_norm(term_next);
   matrix_print(term_next);
 //  printf("norm %lf\n", norm);

   //exp A = E + A + A^2/2 +...+ A^n/n! +... = a0 + a1 + ... + an +...
//a0 = E
//an = a_{n-1} * A / n


  while (norm >= eps){
       // printf("norm %lf\n", norm);
        n++;
        exp = matrix_op_add(exp, term_next);
     //   if (n > 5)
     //       break;
        struct matrix * temp = matrix_op_mult_alloc(term_next, matrix);
        //temp = matrix_op_mult_alloc(term_next, matrix);
        double mult = 1.0 / (double) n;
        temp = matrix_op_scalar_multiply(temp, mult);
        term_prev = matrix_assign(term_prev, term_next);
        term_next = matrix_assign(term_next, temp);
        matrix_print(term_next);
        norm = matrix_op_norm(term_next);
        //matrix_free(term_next);
        //matrix_free(term_prev);
        matrix_free(temp);

    }
    matrix_free(term_next);
    matrix_free(term_prev);
    //matrix_free(temp);
    return exp;

}


matrix *matrix_task_gauss(matrix * matrix1, matrix * vals, matrix * sols, size_t n){
    for (size_t j = 0; j < n; ++j) {
        //int pivot_row = j;
        for (size_t i = 0; i < n; ++i) {
            if (i > j){
                double val = matrix_get(matrix1, j, j);
                size_t k = j + 1;
                while (fabs(val) <= 0.0001 && k < n){
                    matrix_op_swap_rows(matrix1, j, k);
                    matrix_op_swap_rows(vals, j, k);
                    k++;
                    val = matrix_get(matrix1, j, j);
                }
                if (fabs(val) <= 0.0001){
                    printf("Error, matrix is not invertible\n");
                    return NULL;
                    }
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
