
#include <stdio.h>
#include "libml.h"

void helper(int num_rows, int num_cols);

int main(void)
{
  helper(0, 0);
  helper(3, 2);
  return 0;
}

void helper(int num_rows, int num_cols)
{
  matrix* mat = NULL;
  mat = create_matrix(num_rows, num_cols);
  if (mat == NULL) (void) printf("Matrix is NULL\n");
  else (void) printf("Matrix is not NULL\n");
  (void) printf("%f\n", matrix_get(mat, 0, 0));
  (void) printf("%f\n", matrix_get(mat, 0, 1));
  (void) printf("%f\n", matrix_get(mat, 3, 2));
  matrix_set(mat, 0, 1, 3.28);
  matrix_set(mat, 1, 0, 8.53);
  matrix_set(mat, 1, 1, -2.18);
  matrix_set(mat, 4, 6, 2.23);
  (void) printf("%f\n", matrix_get(mat, 0, 1));
  print_matrix(mat);
  mat = delete_matrix(mat);
}


