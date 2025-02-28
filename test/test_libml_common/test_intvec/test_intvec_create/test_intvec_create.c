
#include <stdio.h>
#include "libml.h"

int main(void)
{
  intvec* vec = NULL;

  vec = create_intvec(0);
  if (vec == NULL) (void) printf("Intvec is NULL\n");
  else
  {
    (void) printf("Intvec is not NULL\n");
    vec = delete_intvec(vec);
  }

  vec = create_intvec(-1);
  if (vec == NULL) (void) printf("Intvec is NULL\n");
  else
  {
    (void) printf("Intvec is not NULL\n");
    vec = delete_intvec(vec);
  }

  vec = create_intvec(1);
  if (vec == NULL) (void) printf("Intvec is NULL\n");
  else
  {
    (void) printf("Intvec is not NULL\n");
    vec = delete_intvec(vec);
  }

  return 0;
}

