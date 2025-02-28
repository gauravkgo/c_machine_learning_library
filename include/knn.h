
/******************************************************************************/
/*                                 K N N _ H                                  */
/******************************************************************************/



#ifndef KNN_H
#define KNN_H

#include "libml.h"



/******************************************************************************/
/*                    K Nearest Neighbors Classifier Data                     */
/******************************************************************************/



typedef struct knn_classifier_struct knn_classifier;
struct knn_classifier_struct
{
  int k;
  int num_training_samples;
  matrix* training_data;
  intvec* training_labels;
};



/******************************************************************************/
/*                  K Nearest Neighbors Classifier Functions                  */
/******************************************************************************/



knn_classifier* create_knn(int k);
void print_knn(knn_classifier* classifier);
int train_knn(knn_classifier* classifier, matrix* data, intvec* labels);
intvec* classify_knn(knn_classifier* classifier, matrix* input);
knn_classifier* delete_knn(knn_classifier* classifer);



/******************************************************************************/

#endif

/******************************************************************************/
