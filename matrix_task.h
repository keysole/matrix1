#include "matrix.h"
#ifndef MATRIX_TASK_H_INCLUDED
#define MATRIX_TASK_H_INCLUDED

matrix * matrix_task_exponent(matrix * matrix, const double eps);
matrix *matrix_task_gauss(matrix * matrix1, matrix * vals, matrix * sols, size_t n);

#endif // MATRIX_TASK_H_INCLUDED
