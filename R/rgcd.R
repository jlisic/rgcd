#'Parallel vector multiplication.
#'
#'\code{inner_kernel} calculates the total squared distance between all points in y against 
#' each point in x using either OpenMP or Grand Central Dispatch, provided one is available.
#'
#' @param x A numeric vector of length n.
#' @param y A numeric vector of length n.
#' @param gcd A boolean to use gcd or not.
#' @param omp A boolean to use OpenMP or not, if gcd is TRUE OpenMP will not be used.
#' @return The output is the product of x and y.
#' @examples
#' x <- 1:3
#' y <- 10:12
#' vector_multipy(x,y)
#' @author Jonthan Lisic, \email{jlisic@@gmail.com}
#' @useDynLib rgcd, .registration = TRUE
#' @export
inner_kernel <- function(
  x,
  y,
  gcd=FALSE,
  omp=FALSE  
  ) {

  n <- NROW(x)

  if( n != NROW(y) ) stop("x and y are not the same length")

  if( gcd ) {
  # send our data to the C program
  result <- .C("R_parallel_inner_kernel_gcd",
    as.double( x ),          
    as.double( y ),
    as.integer( n )    
  )
  } else if(omp) { 
  result <- .C("R_parallel_inner_kernel_omp",
    as.double( x ),          
    as.double( y ),
    as.integer( n )    
  )
  } else {
  result <- .C("R_inner_kernel",
    as.double( x ),          
    as.double( y ),
    as.integer( n )    
  )

  }

 #return our result stored in x
 return( result[[1]] ) 
  
}



