
/******************************************************************************/
/*                               L I B M L _ H                                */
/******************************************************************************/



#ifndef LIBML_H
#define LIBML_H



/******************************************************************************/
/*                                   Macros                                   */
/******************************************************************************/



#define MAX_CHAR_ARR_LEN 100



/******************************************************************************/
/*                                    Data                                    */
/******************************************************************************/



typedef struct matrix_struct matrix;
struct matrix_struct
{
  int rows;
  int cols;
  double* data;
};

typedef struct int_vector_struct intvec;
struct int_vector_struct
{
  int len;
  int* data;
};



/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/



matrix* create_matrix(int num_rows, int num_cols);
double matrix_get(matrix* mat, int r, int c);
void matrix_set(matrix* mat, int r, int c, double val);
void print_matrix(matrix* mat);
matrix* delete_matrix(matrix* mat);

intvec* create_intvec(int len);
int intvec_get(intvec* vec, int i);
void intvec_set(intvec* vec, int i, int val);
void print_intvec(intvec* vec);
intvec* delete_intvec(intvec* vec);

void read_numcsv(const char* filename, matrix** mat, intvec** labels);



/******************************************************************************/



#include "knn.h"

#endif



/******************************************************************************/
