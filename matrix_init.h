#ifndef MATRIX_INIT_H_INCLUDED
#define MATRIX_INIT_H_INCLUDED


matrix * matrix_set_zero (matrix *matrix);
matrix * matrix_alloc_zero (size_t rows, size_t cols);
matrix * matrix_set_identity(matrix * matrix);
matrix * matrix_alloc_identity(size_t size);
matrix * matrix_assign(matrix *matrix_1, matrix *matrix_2);
matrix * matrix_clone (matrix * matrix);


#endif // MATRIX_INIT_H_INCLUDED
