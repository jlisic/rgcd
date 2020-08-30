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


// inner kernel using GCD
void R_parallel_inner_kernel_gcd( double * x, double * y, int * n );

// inner kernel using OPENMP 
void R_parallel_inner_kernel_omp( double * x, double * y, int * n );
  
// inner kernel 
void R_inner_kernel( double * x, double * y, int * n );



// C function registration 

static R_NativePrimitiveArgType R_parallel_inner_kernel_gcd_t[] = {
  REALSXP, REALSXP, INTSXP
};

static R_NativePrimitiveArgType R_parallel_inner_kernel_omp_t[] = {
  REALSXP, REALSXP, INTSXP
};

static R_NativePrimitiveArgType R_inner_kernel_t[] = {
  REALSXP, REALSXP, INTSXP
};

static const R_CMethodDef cMethods[] = {
     {"R_parallel_inner_kernel_gcd", (DL_FUNC) &R_parallel_inner_kernel_gcd, 3, R_parallel_inner_kernel_gcd_t},
     {"R_parallel_inner_kernel_omp", (DL_FUNC) &R_parallel_inner_kernel_omp, 3, R_parallel_inner_kernel_omp_t},
     {"R_inner_kernel", (DL_FUNC) &R_inner_kernel, 3, R_inner_kernel_t},
     {NULL, NULL, 0, NULL}
};

void R_init_myLib(DllInfo *info)
{
     R_registerRoutines(info, cMethods, NULL, NULL, NULL);
     R_useDynamicSymbols(info, TRUE); 
}




