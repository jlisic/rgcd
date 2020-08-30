/* Copyright (c) 2018  Jonathan Lisic
 * Last edit 02AUG2018
 * License: BSD-2
 */


#include "gcd_r.h"



// inner kernel using GCD
void R_parallel_inner_kernel_gcd( double * x, double * y, int * n ) {

#ifdef _LIBDISPATCH
  // concurrent queue 
   dispatch_queue_t my_queue = dispatch_get_global_queue(0, 0);

  // for like loop
  dispatch_apply (*n, my_queue, ^(size_t idx){
     
      size_t j;
      double tmp = 0;

      for( j = 0; j < *n; j++) { 
        tmp += (x[idx] - y[j]) * (x[idx] - y[j]);
      }

      x[idx] = tmp;
      
  });

#else 
  // serial alternative implementation
  size_t idx,j;
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


// inner kernel using OpenMP
void R_parallel_inner_kernel_omp( double * x, double * y, int * n ) {

  size_t idx,j;
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
 

// inner kernel 
void R_inner_kernel( double * x, double * y, int * n ) {

  size_t idx,j;
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
