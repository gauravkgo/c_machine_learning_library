
#include <stdio.h>
#include "libml.h"

int main(void)
{
  matrix* samples_data = NULL;
  intvec* labels = NULL;
  read_numcsv("iris_test.csv", &samples_data, &labels);
  print_matrix(samples_data);
  print_intvec(labels);
  samples_data = delete_matrix(samples_data);
  labels = delete_intvec(labels);
  return 0;
}

