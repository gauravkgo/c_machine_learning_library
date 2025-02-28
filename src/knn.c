
/******************************************************************************/
/*                                 K N N _ C                                  */
/******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knn.h"



/******************************************************************************/
/*                   K Nearest Neighbors Classifier Methods                   */
/******************************************************************************/



knn_classifier* create_knn(int k)
{
  knn_classifier* classifier = NULL;

  if (k < 1) return NULL;
  classifier = calloc(1, sizeof(knn_classifier));
  if (classifier == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to allocate for knn classifier.\n");
    return NULL;
  }
  classifier->k = k;
  return classifier;
}

void print_knn(knn_classifier* classifier)
{
  if (classifier == NULL) return;
  if (classifier->k < 1) return;
  (void) printf("Type: KNN classifier\n");
  (void) printf("k: %d\n", classifier->k);
  if (classifier->num_training_samples < 1) return;
  if (classifier->training_data == NULL) return;
  (void) printf("Training data:\n");
  print_matrix(classifier->training_data);
  if (classifier->training_labels == NULL) return;
  (void) printf("Training labels:\n");
  print_intvec(classifier->training_labels);
}

int train_knn(knn_classifier* classifier, matrix* data, intvec* labels)
{
  matrix* training_data = NULL;
  intvec* training_labels = NULL;
  int r = 0, c = 0;

  /* Check args */

  if (classifier == NULL)
  {
    (void) fprintf(stderr, "Error: Cannot train NULL KNN classifier.\n");
    goto fail_train_knn;
  }

  if (data == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with NULL matrix.\n");
    goto fail_train_knn;
  }
  if (data->rows < 1 || data->cols < 1)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier ");
    (void) fprintf(stderr,
      "with matrix with 0 or negative row/column count.\n");
    goto fail_train_knn;
  }
  if (data->data == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with matrix with NULL data.\n");
    goto fail_train_knn;
  }

  if (labels == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with NULL intvec labels.\n");
    goto fail_train_knn;
  }
  if (labels->len < 1)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with intvec labels with a ");
    (void) fprintf(stderr,
      "0 or negative length.\n");
    goto fail_train_knn;
  }
  if (labels->data == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with intvec labels with NULL data.\n");
    goto fail_train_knn;
  }

  if (labels->len != data->rows)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier with training data and labels of ");
    (void) fprintf(stderr,
      "different sizes (training matrix row count != labels intvec length).\n");
    goto fail_train_knn;
  }
  if (labels->len < classifier->k)
  {
    (void) fprintf(stderr,
      "Error: Cannot train KNN classifier where number of training samples ");
    (void) fprintf(stderr,
      "is less than classifier's k value.\n");
    goto fail_train_knn;
  }

  /* Create and store copy of training data */

  training_data = create_matrix(data->rows, data->cols);
  if (training_data == NULL)
  {
    (void) fprintf(stderr,
      "Error: Failed to create training data matrix copy for knn classifier.\n");
    goto fail_train_knn;
  }
  training_labels = create_intvec(labels->len);
  if (training_labels == NULL)
  {
    (void) fprintf(stderr,
      "Error: Failed to create training labels copy for knn classifier.\n");
    goto fail_train_knn;
  }
  for (r = 0; r < training_data->rows; r ++)
    for (c = 0; c < training_data->cols; c ++)
      matrix_set(training_data, r, c, matrix_get(data, r, c));
  for (r = 0; r < training_labels->len; r ++)
    intvec_set(training_labels, r, intvec_get(labels, r));
  classifier->num_training_samples = labels->len;
  classifier->training_data = training_data;
  classifier->training_labels = training_labels;

  return 0;

  /* Function fail clean up */

fail_train_knn:

  training_data = delete_matrix(training_data);
  training_labels = delete_intvec(training_labels);
  return -1;
}


intvec* classify_knn(knn_classifier* classifier, matrix* input)
{
  intvec* results = NULL;
  int* k_indices = NULL;
  int k_indices_index = 0;
  int found = 0;
  int r = 0, c = 0;
  int r_train = 0;
  int i = 0, min_i = 0;
  double sqr_dist = 0, dist_1d = 0, min_sqr_dist = 0;
  int mode = -1, count = 0, max_count = 0, j = 0;

  /* Check args */

  if (classifier == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot classify with NULL KNN classifier.\n");
    goto fail_classify_knn;
  }
  if (classifier->num_training_samples < 1
      || classifier->training_data == NULL
      || classifier->training_labels == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot classify with untrained KNN classifier.\n");
    goto fail_classify_knn;
  }
  
  if (input == NULL)
  {
    (void) fprintf(stderr,
      "Error: Cannot classify NULL input with KNN classifier.\n");
    goto fail_classify_knn;
  }
  if (input->cols != classifier->training_data->cols)
  {
    (void) fprintf(stderr,
      "Error: Cannot classify input of wrong size with KNN classifier ");
    (void) fprintf(stderr,
      "(column counts differ between given matrix and training matrix).\n");
    goto fail_classify_knn;
  }

  /* Classify */

  results = create_intvec(input->rows);
  if (results == NULL)
  {
    (void) fprintf(stderr,
      "Error: Failed to allocate results intvec for KNN classifier.\n");
    goto fail_classify_knn;
  }
  k_indices = calloc(classifier->k, sizeof(int));
  if (k_indices == NULL)
  {
    (void) fprintf(stderr,
      "Error: Failed to allocate internal array for ");
    (void) fprintf(stderr,
      "classification calculation for KNN classifier.\n");
    goto fail_classify_knn;
  }

  
  for (r = 0; r < input->rows; r ++)
  {
    (void) memset(k_indices, 0, classifier->k * sizeof(int));
    for (k_indices_index = 0; k_indices_index < classifier->k; k_indices_index ++)
    {
      min_sqr_dist = 0;
      for (c = 0; c < classifier->training_data->cols; c ++)
      {
        dist_1d = matrix_get(classifier->training_data, 0, c)
            - matrix_get(input, r, c);
        min_sqr_dist += dist_1d * dist_1d;
      }
      for (r_train = 0; r_train < classifier->training_data->rows; r_train ++)
      {
        sqr_dist = 0;
        for (c = 0; c < classifier->training_data->cols; c ++)
        {
          dist_1d = matrix_get(classifier->training_data, r_train, c)
              - matrix_get(input, r, c);
          sqr_dist += dist_1d * dist_1d;
        }
        if (sqr_dist <= min_sqr_dist)
        {
          found = 0;
          for (i = 0; i < k_indices_index; i ++)
            if (k_indices[i] == r_train) found = 1;
          if (!found)
          {
            min_sqr_dist = sqr_dist;
            min_i = r_train;
          }
        }
      }
      k_indices[k_indices_index] = intvec_get(
          classifier->training_labels, min_i);
    }

    max_count = 0;
    for (i = 0; i < classifier->k; i ++)
    {
      count = 0;
      for (j = 0; j < classifier->k; j ++)
        count += (k_indices[i] == k_indices[j]);
      if (count > max_count)
      {
        max_count = count;
        mode = k_indices[i];
      }
    }

    intvec_set(results, r, mode);
  }

  /* Clean up */

  (void) memset(k_indices, 0, classifier->k * sizeof(int));
  free(k_indices);
  k_indices = NULL;
  return results;

  /* Function fail clean up */

fail_classify_knn:

  if (results != NULL) results = delete_intvec(results);
  return NULL;
}

knn_classifier* delete_knn(knn_classifier* classifer)
{
  if (classifer == NULL) return NULL;
  classifer->training_data = delete_matrix(classifer->training_data);
  classifer->training_labels = delete_intvec(classifer->training_labels);
  (void) memset(classifer, 0, sizeof(knn_classifier));
  free(classifer);
  return NULL;
}



/******************************************************************************/
