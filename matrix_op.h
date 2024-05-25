#ifndef MATRIX_OP_H_INCLUDED
#define MATRIX_OP_H_INCLUDED
#include "matrix.h"

// Allocates new matrix
matrix * matrix_op_sum(matrix * matrix_1, matrix * matrix_2);


matrix * matrix_op_add(matrix * matrix_1, matrix * matrix_2);

matrix * matrix_op_mult(matrix * matrix_1, matrix * matrix_2);

// Allocates new matrix
matrix * matrix_op_mult_alloc(matrix * matrix_1, matrix * matrix_2);


matrix * matrix_op_scalar_multiply(matrix * matrix, double x);

matrix * matrix_op_mult_row(matrix *matrix, const size_t i, double mult);

matrix * matrix_op_add_rows(matrix *matrix, size_t i_1, size_t i_2, double factor);

matrix * matrix_op_swap_rows(matrix *matrix, size_t i_1, const size_t i_2);

matrix *matrix_op_inverse(matrix * matrix);


double matrix_op_norm(matrix * matrix);
double matrix_op_det(matrix * matrix);


#endif // MATRIX_OP_H_INCLUDED
