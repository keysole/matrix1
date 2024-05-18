#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

typedef struct matrix matrix;

matrix * matrix_alloc (size_t h, size_t w);

void matrix_free (struct matrix *);

void matrix_print(matrix *matrix);

matrix * matrix_resize (struct matrix *m, size_t h, size_t w);

double matrix_get (matrix *m, size_t i, size_t j);

void matrix_set(matrix *m, size_t i, size_t j, double x);

int same_size(matrix * matrix_1, matrix * matrix_2);

matrix * matrix_transpose(matrix *matrix);

void matrix_add_rows(matrix *matrix, size_t i_1, size_t i_2, double factor);

void matrix_swap_rows(matrix *matrix, size_t i_1, size_t i_2);

matrix * matrix_gauss(matrix *matrix1, matrix * vals, matrix * sols, size_t n);

matrix * matrix_exponent(matrix * matrix, const double eps);
#endif // MATRIX_H_INCLUDED
