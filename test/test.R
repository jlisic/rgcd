# runtimes
# gcd    nothing  openmp
# 2.976  11.561   :
# 2.986  11.554
# 2.994  11.599

library(rgcd)
library(tictoc)

n <- 100000

x <- 1:n
y <- 1:n


tic("With GCD") 
check1 <- vector_multiply(x,y,gcd=TRUE)
toc()

tic("With OpenMP") 
check2 <- vector_multiply(x,y,omp=TRUE)
toc()

tic("Without GCD or OpenMP") 
check3 <- vector_multiply(x,y)
toc()

print("Difference Between GCD and OpenMP Result:")
print( sum( check1 != check2))

print("Difference Between GCD and no threading Result:")
print( sum( check1 != check3))
