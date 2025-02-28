
#include <stdio.h>
#include "libml.h"

void helper(int len);

int main(void)
{
  helper(0);
  helper(3);
  return 0;
}

void helper(int len)
{
  intvec* vec = NULL;
  vec = create_intvec(len);
  if (vec == NULL) (void) printf("Intvec is NULL\n");
  else (void) printf("Intvec is not NULL\n");
  (void) printf("%d\n", intvec_get(vec, 0));
  (void) printf("%d\n", intvec_get(vec, -1));
  (void) printf("%d\n", intvec_get(vec, 3));
  intvec_set(vec, 0, 3);
  intvec_set(vec, -1, -8);
  intvec_set(vec, 2, 2);
  intvec_set(vec, 1, 3);
  (void) printf("%d\n", intvec_get(vec, 2));
  print_intvec(vec);
  vec = delete_intvec(vec);
}


