
/******************************************************************************/
/*                               L I B M L _ C                                */
/******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libml.h"




/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/



matrix* create_matrix(int num_rows, int num_cols)
{
  matrix* mat = NULL;

  mat = calloc(1, sizeof(matrix));
  if (mat == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to allocate for matrix struct.\n");
    return mat;
  }

  if (num_rows < 1 || num_cols < 1)
  {
    (void) fprintf(stderr,
      "Error: Matrix row and column counts must be 1 or more.\n");
    return delete_matrix(mat);
  }
  mat->rows = num_rows;
  mat->cols = num_cols;

  mat->data = calloc(num_rows * num_cols, sizeof(double));
  if (mat->data == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to allocate for data in matrix.\n");
    return delete_matrix(mat);
  }

  return mat;
}

double matrix_get(matrix* mat, int r, int c)
{
  if (mat == NULL) return 0.0;
  if (mat->data == NULL) return 0.0;
  if (mat->rows < 1 || mat->cols < 1) return 0.0;
  if (r < 0 || r >= mat->rows) return 0.0;
  if (c < 0 || c >= mat->cols) return 0.0;
  return mat->data[r * mat->cols + c];
}

void matrix_set(matrix* mat, int r, int c, double val)
{
  if (mat == NULL) return;
  if (mat->data == NULL) return;
  if (mat->rows < 1 || mat->cols < 1) return;
  if (r < 0 || r >= mat->rows) return;
  if (c < 0 || c >= mat->cols) return;
  mat->data[r * mat->cols + c] = val;
}

void print_matrix(matrix* mat)
{
  int r = 0, c = 0, num_rows = 0, num_cols = 0;
  if (mat == NULL) return;
  if (mat->rows < 1 || mat->cols < 1) return;
  num_rows = mat->rows;
  num_cols = mat->cols;
  (void) printf("Type: matrix\n");
  (void) printf("Dimensions: %dx%d\n", num_rows, num_cols);
  if (mat->data == NULL) return;
  (void) printf("Content:\n");
  for (r = 0; r < num_rows; r ++)
  {
    for (c = 0; c < num_cols; c ++)
      (void) printf("%f\t", mat->data[r * num_cols + c]);
    (void) printf("\n");
  }
}

matrix* delete_matrix(matrix* mat)
{
  if (mat == NULL) return mat;

  if (mat->data != NULL)
  {
    (void) memset(mat->data, 0, mat->rows * mat->cols * sizeof(double));
    free(mat->data);
  }

  (void) memset(mat, 0, sizeof(matrix));
  free(mat);
  return NULL;
}



/******************************************************************************/



intvec* create_intvec(int len)
{
  intvec* vec = NULL;

  vec = calloc(1, sizeof(intvec));
  if (vec == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to allocate for intvec struct.\n");
    return vec;
  }

  if (len < 1)
  {
    (void) fprintf(stderr, "Error: Intvec length must be 1 or greater.\n");
    return delete_intvec(vec);
  }
  vec->len = len;

  vec->data = calloc(len, sizeof(int));
  if (vec->data == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to allocate for data in intvec.\n");
    return delete_intvec(vec);
  }

  return vec;
}

int intvec_get(intvec* vec, int i)
{
  if (vec == NULL) return 0;
  if (vec->data == NULL) return 0;
  if (vec->len < 1 || i < 0 || i >= vec->len) return 0;
  return vec->data[i];
}

void intvec_set(intvec* vec, int i, int val)
{
  if (vec == NULL) return;
  if (vec->data == NULL) return;
  if (vec->len < 1 || i < 0 || i >= vec->len) return;
  vec->data[i] = val;
}

void print_intvec(intvec* vec)
{
  int i = 0, len = 0;
  if (vec == NULL) return;
  if (vec->len < 1) return;
  len = vec->len;
  (void) printf("Type: intvec\n");
  (void) printf("Length: %d\n", len);
  if (vec->data == NULL) return;
  (void) printf("Content:\n");
  for (i = 0; i < len; i ++) (void) printf("%d\n", vec->data[i]);
}

intvec* delete_intvec(intvec* vec)
{
  if (vec == NULL) return vec;

  if (vec->data != NULL)
  {
    (void) memset(vec->data, 0, vec->len * sizeof(int));
    free(vec->data);
  }

  (void) memset(vec, 0, sizeof(intvec));
  free(vec);
  return NULL;
}



/******************************************************************************/



void read_numcsv(const char* filename, matrix** mat, intvec** labels)
{
  matrix* csv_mat = NULL;
  intvec* csv_labels = NULL;
  FILE* csv_pointer = NULL;
  int i = 0;
  char c = '\0';
  int num_rows = 0, num_cols = 0;
  char* s = NULL;
  int s_end = 0;
  int ri = 0, ci = 0;


  /* Check arguments */

  if (filename == NULL)
  {
    (void) fprintf(stderr, "Error: Provided NULL filename for numerical csv.\n");
    goto fail_read_numcsv;
  }
  for (i = 0; i < MAX_CHAR_ARR_LEN && filename[i] != '\0'; i ++) ;
  if (i >= MAX_CHAR_ARR_LEN)
  {
    (void) fprintf(stderr, "Error: Povided filename for numerical csv is too long.\n");
    goto fail_read_numcsv;
  }

  /* Begin reading file */

  csv_pointer = fopen(filename, "r");
  if (csv_pointer == NULL)
  {
    (void) fprintf(stderr, "Error: Failed to open numerical csv file.\n");
    goto fail_read_numcsv;
  }

  if (fseek(csv_pointer, 0, SEEK_SET) != 0)
  {
    (void) fprintf(stderr, "Error: Failed to seek in numerical csv file.\n");
    goto fail_read_numcsv;
  }

  /* Count number of rows */

  while (!feof(csv_pointer) && (c = fgetc(csv_pointer)) != '\n')
    num_cols += (c == ',');
  if (num_cols == 0)
  {
    (void) fprintf(stderr, "Error: No columns in numerical csv file.\n");
    goto fail_read_numcsv;
  }
  num_cols += (c == '\n');

  /* Count number of columns */

  num_rows += (c == '\n');
  while (!feof(csv_pointer))
    num_rows += (fgetc(csv_pointer) == '\n');
  if (num_rows == 0)
  {
    (void) fprintf(stderr, "Error: No rows in numerical csv file.\n");
    goto fail_read_numcsv;
  }

  /* Get ready to load data */

  csv_mat = create_matrix(num_rows, num_cols - 1);
  if (csv_mat == NULL)
  {
    (void) fprintf(stderr,
        "Error: Failed to allocate for matrix to read numerical csv file.\n");
    goto fail_read_numcsv;
  }
  csv_labels = create_intvec(num_rows);
  if (csv_labels == NULL)
  {
    (void) fprintf(stderr,
        "Error: Failed to allocate for intvec to read numerical csv file.\n");
    goto fail_read_numcsv;
  }
  s = calloc(MAX_CHAR_ARR_LEN, sizeof(char));
  if (s == NULL)
  {
    (void) fprintf(stderr,
      "Error: Failed to allocate for string to read numerical csv file.\n");
    goto fail_read_numcsv;
  }
  if (fseek(csv_pointer, 0, SEEK_SET) != 0)
  {
    (void) fprintf(stderr, "Error: Failed to seek in numerical csv file.\n");
    goto fail_read_numcsv;
  }

  /* Read data */

  while (!feof(csv_pointer))
  {
    c = fgetc(csv_pointer);

    if (c == ',' || c == '\n')
    {
      if (s_end == 0)
      {
        (void) fprintf(stderr,
          "Error: Found empty value in numerical csv file.\n");
        goto fail_read_numcsv;
      }
      s[s_end] = '\0';
      if (ci < 1) intvec_set(csv_labels, ri, atoi(s));
      else matrix_set(csv_mat, ri, ci - 1, atof(s));

      s_end = 0;
      if (c == '\n')
      {
        ci = 0;
        ri ++;
      }
      else ci ++;
    }
    else
    {
      if (s_end >= MAX_CHAR_ARR_LEN - 1)
      {
        (void) fprintf(stderr,
          "Error: Found too long value in numerical csv file.\n");
        goto fail_read_numcsv;
      }
      s[s_end] = c;
      s_end ++;
    }
  }

  /* Clean up */

  if (fclose(csv_pointer) != 0)
    fprintf(stderr, "Error: Failed to close numerical csv file\n");
  csv_pointer = NULL;
  (void) memset(s, '\0', MAX_CHAR_ARR_LEN * sizeof(char));
  free(s);
  s = NULL;

  *mat = csv_mat;
  *labels = csv_labels;
  return;

  /* Function fail clean up */

fail_read_numcsv:

  if (csv_pointer != NULL)
  {
    if (fclose(csv_pointer) != 0)
      fprintf(stderr, "Error: Failed to close numerical csv file\n");
    csv_pointer = NULL;
  }
  csv_mat = delete_matrix(csv_mat);
  csv_labels = delete_intvec(csv_labels);
  if (s != NULL) (void) memset(s, '\0', MAX_CHAR_ARR_LEN * sizeof(char));
  free(s);
  s = NULL;

  *mat = NULL;
  *labels = NULL;
}


