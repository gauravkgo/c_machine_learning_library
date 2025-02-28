
#include <stdio.h>
#include "libml.h"

int main(void)
{
  matrix* train_mat = NULL;
  intvec* train_labs = NULL;
  matrix* test_mat = NULL;
  intvec* test_labs = NULL;
  intvec* results = NULL;
  knn_classifier* knnc = NULL;

  knnc = create_knn(3);
  read_numcsv("iris_train.csv", &train_mat, &train_labs);
  read_numcsv("iris_test.csv", &test_mat, &test_labs); 
  (void) train_knn(knnc, train_mat, train_labs);
  print_knn(knnc);
  results = classify_knn(knnc, test_mat);
  print_intvec(results);
  print_intvec(test_labs);

  train_mat = delete_matrix(train_mat);
  train_labs = delete_intvec(train_labs);
  test_mat = delete_matrix(test_mat);
  test_labs = delete_intvec(test_labs);
  results = delete_intvec(results);
  knnc = delete_knn(knnc);

  return 0;
}

