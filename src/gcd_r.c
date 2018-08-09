/* Copyright (c) 2018  Jonathan Lisic
 * Last edit 02AUG2018
 * License: BSD-2
 */


#include "gcd_r.h"



// vector multiply using GCD
void R_parallel_vector_multiply_gcd( double * x, double * y, int * n ) {

#ifdef _LIBDISPATCH
  // concurrent queue 
  dispatch_queue_t my_queue = dispatch_queue_create("r.dispatch",DISPATCH_QUEUE_CONCURRENT);

  // for like loop
  dispatch_apply (*n, my_queue, ^(size_t idx){
     
      int j;
      double tmp = 0;

      for( j = 0; j < *n; j++) { 
        tmp += (x[idx] - y[j]) * (x[idx] - y[j]);
      }

      x[idx] = tmp;
      
  });

#else 
  // serial alternative implementation
  int idx,j;
  double tmp;

  for( idx=0; idx < *n; idx++) { 
    tmp = 0;
    for( j = 0; j < *n; j++) { 
      tmp += (x[idx] - y[j]) * (x[idx] - y[j]);
    }
    x[idx] = tmp;
  }
#endif

  return;
} 


// vector multiply using OpenMP
void R_parallel_vector_multiply_omp( double * x, double * y, int * n ) {

  int idx,j;
  double tmp;
    
  #pragma omp parallel private(j,tmp) 
  { 

    #pragma omp for
    for( idx = 0; idx < *n; idx++) { 
      
      tmp = 0;

      for( j = 0; j < *n; j++) { 
        tmp += (x[idx] - y[j]) * (x[idx] - y[j]);
      }

      x[idx] = tmp;
    }

  }

  return;
} 
 

// vector multiply 
void R_vector_multiply( double * x, double * y, int * n ) {

  int idx,j;
  double tmp;

  for( idx=0; idx < *n; idx++) { 
    tmp = 0;
    for( j = 0; j < *n; j++) { 
      tmp += (x[idx] - y[j]) * (x[idx] - y[j]);
    }
    x[idx] = tmp;
  }

  return;
}
