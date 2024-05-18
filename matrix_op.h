#ifndef MATRIX_OP_H_INCLUDED
#define MATRIX_OP_H_INCLUDED
#include "matrix.h"
matrix * matrix_op_add(matrix * matrix_1, matrix * matrix_2);

matrix * matrix_op_multiply(matrix * matrix_1, matrix * matrix_2);

matrix * matrix_op_scalar_multiply(matrix * matrix, double x);

matrix * matrix_op_mult_row(matrix *matrix, const size_t i, double mult);

matrix * matrix_op_add_rows(matrix *matrix, size_t i_1, size_t i_2, double factor);

matrix * matrix_op_swap_rows(matrix *matrix, size_t i_1, const size_t i_2);

double matrix_op_norm(matrix * matrix);


#endif // MATRIX_OP_H_INCLUDED
