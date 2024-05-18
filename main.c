#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrix_op.h"
#include "matrix_init.h"
#include "matrix_task.h"

int main()
{
    const double eps = 0.0001;
    size_t n = 3;
    matrix * test_matrix = matrix_alloc(n, n);
    matrix * test_exp_matrix = matrix_alloc(n, n);
    matrix * term_matrix = matrix_alloc(n, 1);
    matrix * sols_matrix = matrix_alloc(n, 1);
    double test_matrix_3_x_3[3][3] = {{3.0, 2.0, -4.0}, {2.0, 3.0, 3.0}, {5.0, -3.0, 1.0}};
    double test_exp_matrix_3_x_3[3][3] = {{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, -1.0}};
    double test_term_matrix_3_x_1[3] = {3.0, 15.0, 14.0};
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
        matrix_set(test_matrix, i, j, test_matrix_3_x_3[i][j]);
        matrix_set(test_exp_matrix, i, j, test_exp_matrix_3_x_3[i][j]);
    }
}
    printf("-------------------\n");
    printf("Matrix norm %lf\n", matrix_op_norm(test_matrix));
    printf("-------------------\n");

    matrix * product = matrix_op_multiply(test_matrix, test_exp_matrix);
    printf("-------------------\n");
    printf("Product matrix\n");
    matrix_print(product);
    printf("-------------------\n");



    for (size_t i = 0; i < n; ++i){
        matrix_set(term_matrix, i, 0, test_term_matrix_3_x_1[i]);
        matrix_set(sols_matrix, i, 0, 0);

    }


    sols_matrix = matrix_task_gauss(test_matrix, term_matrix, sols_matrix, n);
    printf("-------------------\n");
    printf("Solution matrix\n");
    matrix_print(sols_matrix);
    printf("-------------------\n");


    test_exp_matrix = matrix_task_exponent(test_exp_matrix, eps);
    printf("-------------------\n");
    printf("Exp matrix\n");
    matrix_print(test_exp_matrix);
    printf("-------------------\n");

    return 0;
}
