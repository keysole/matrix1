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
    matrix * test_matrix2 = matrix_alloc(n, n);
    matrix * test_exp_matrix = matrix_alloc(n, n);
    matrix * term_matrix = matrix_alloc(n, 1);
   // matrix * sols_matrix = matrix_alloc(n, 1);
    double test_matrix_3_x_3[3][3] = {{3.0, 2.0, -4.0}, {2.0, 3.0, 3.0}, {5.0, -3.0, 1.0}};
    double test_exp_matrix_3_x_3[3][3] = {{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, -1.0}};
    double test_term_matrix_3_x_1[3] = {3.0, 15.0, 14.0};
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
        matrix_set(test_matrix, i, j, test_matrix_3_x_3[i][j]);
        matrix_set(test_matrix2, i, j, test_matrix_3_x_3[i][j]);
        matrix_set(test_exp_matrix, i, j, test_exp_matrix_3_x_3[i][j]);
    }
}

    printf("-------------------\n");
    printf("Matrix test \n");
    matrix_print(test_matrix);
    printf("-------------------\n");
    printf("-------------------\n");
    printf("Matrix norm %lf\n", matrix_op_norm(test_matrix));
    printf("-------------------\n");

    size_t k = 0;
    printf("Введите размер квадратной матрицы (Гаусс)\n");
    scanf("%zu", &k);
    matrix * matrix_inp = matrix_alloc(k, k);
    for (size_t i = 0; i < k; ++i){
        for (size_t j = 0; j < k; ++j){
            double val;
            printf("A[%zu][%zu] = ", i, j);
            scanf("%lf", &val);
            printf("\n");
            matrix_set(matrix_inp, i, j, val);
    }
}

    printf("Введите матрицу свободных членов \n");

    matrix * term_matrix_inp = matrix_alloc(k, 1);
    matrix * sols_matrix = matrix_alloc(k, 1);
    for (size_t i = 0; i < k; ++i){
        double val;
        printf("A[%zu][%d] = ", i, 0);
        scanf("%lf", &val);
        matrix_set(term_matrix_inp, i, 0, val);
        matrix_set(sols_matrix, i, 0, 0);

    }

        //printf("Term matrix\n");
   // matrix_print(term_matrix);
   // printf("-------------------\n");
   // sols_matrix = matrix_task_gauss(test_matrix, term_matrix, sols_matrix, n);
    sols_matrix = matrix_task_gauss(matrix_inp, term_matrix_inp, sols_matrix, k);
    printf("-------------------\n");
    if (sols_matrix != NULL){
    printf("Solution matrix\n");
    matrix_print(sols_matrix);
    }
    printf("-------------------\n");

    printf("Введите размер квадратной матрицы (экспонента) \n");
    scanf("%zu", &k);
    matrix * matrix_exp_inp = matrix_alloc(k, k);
    for (size_t i = 0; i < k; ++i){
        for (size_t j = 0; j < k; ++j){
            double val;
            printf("A[%zu][%zu] = ", i, j);
            scanf("%lf", &val);
            printf("\n");
            matrix_set(matrix_exp_inp, i, j, val);
    }
}
    //test_exp_matrix = matrix_task_exponent(test_exp_matrix, eps);
    matrix_exp_inp = matrix_task_exponent(matrix_exp_inp, eps);
    printf("-------------------\n");
    printf("Exp matrix\n");
    //matrix_print(test_exp_matrix);
    matrix_print(matrix_exp_inp);
    printf("-------------------\n");

//printf("-------------------\n");
  //  printf("Matrix test exp \n");
   // matrix_print(test_exp_matrix);
  // printf("-------------------\n");



    matrix * product = matrix_op_mult_alloc(test_matrix, test_exp_matrix);
    printf("-------------------\n");
    printf("Product matrix (test exp * test) \n");
    matrix_print(product);
    printf("-------------------\n");



    for (size_t i = 0; i < n; ++i){
        matrix_set(term_matrix, i, 0, test_term_matrix_3_x_1[i]);
        matrix_set(sols_matrix, i, 0, 0);

    }



    printf("-------------------\n");



    printf("-------------------\n");
    printf("Matrix det\n %lf", matrix_op_det(test_matrix));
    printf("-------------------\n");


    printf("-------------------\n");
    printf("Matrix inv\n");
    matrix_print(matrix_op_inverse(test_matrix2));
    printf("\n-------------------\n");

    matrix_free(test_matrix);
    matrix_free(test_matrix2);
    matrix_free(test_exp_matrix);
    matrix_free(term_matrix);
    matrix_free(matrix_inp);
    matrix_free(term_matrix_inp);
    matrix_free(sols_matrix);
    matrix_free(matrix_exp_inp);
    matrix_free(product);
    return 0;
}
