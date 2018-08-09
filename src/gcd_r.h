/* Copyright (c) 2018  Jonathan Lisic
 * Last edit 02AUG2018
 * License: BSD-2
 */

#include "R.h"
#include "Rinternals.h"
#include "Rmath.h"
#include <R_ext/Rdynload.h>

// if defined dispatch
#ifdef _LIBDISPATCH
  #include <dispatch/dispatch.h>
#endif


// if defined openmp
#ifdef _OPENMP
  #include <omp.h>
#endif


// vector multiply using GCD
void R_parallel_vector_multiply_gcd( double * x, double * y, int * n );

// vector multiply using OPENMP 
void R_parallel_vector_multiply_omp( double * x, double * y, int * n );
  
// vector multiply 
void R_vector_multiply( double * x, double * y, int * n );



// C function registration 

static R_NativePrimitiveArgType R_parallel_vector_multiply_gcd_t[] = {
  REALSXP, REALSXP, INTSXP
};

static R_NativePrimitiveArgType R_parallel_vector_multiply_omp_t[] = {
  REALSXP, REALSXP, INTSXP
};

static R_NativePrimitiveArgType R_vector_multiply_t[] = {
  REALSXP, REALSXP, INTSXP
};

static const R_CMethodDef cMethods[] = {
     {"R_parallel_vector_multiply_gcd", (DL_FUNC) &R_parallel_vector_multiply_gcd, 3, R_parallel_vector_multiply_gcd_t},
     {"R_parallel_vector_multiply_omp", (DL_FUNC) &R_parallel_vector_multiply_omp, 3, R_parallel_vector_multiply_omp_t},
     {"R_vector_multiply", (DL_FUNC) &R_vector_multiply, 3, R_vector_multiply_t},
     {NULL, NULL, 0, NULL}
};

void R_init_myLib(DllInfo *info)
{
     R_registerRoutines(info, cMethods, NULL, NULL, NULL);
     R_useDynamicSymbols(info, TRUE); 
}




