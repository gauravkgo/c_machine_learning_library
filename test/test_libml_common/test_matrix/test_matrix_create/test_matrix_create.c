
#include <stdio.h>
#include "libml.h"

int main(void)
{
  matrix* mat = NULL;

  mat = create_matrix(0, 0);
  if (mat == NULL) (void) printf("Matrix is NULL\n");
  else
  {
    (void) printf("Matrix is not NULL\n");
    mat = delete_matrix(mat);
  }

  mat = create_matrix(-1, -4);
  if (mat == NULL) (void) printf("Matrix is NULL\n");
  else
  {
    (void) printf("Matrix is not NULL\n");
    mat = delete_matrix(mat);
  }

  mat = create_matrix(1, 2);
  if (mat == NULL) (void) printf("Matrix is NULL\n");
  else
  {
    (void) printf("Matrix is not NULL\n");
    mat = delete_matrix(mat);
  }

  return 0;
}

