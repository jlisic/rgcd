## runtimes

# nothing 
#Without GCD or OpenMP: 11.616 sec elapsed
#Without GCD or OpenMP: 11.565 sec elapsed
#Without GCD or OpenMP: 11.562 sec elapsed
#Without GCD or OpenMP: 11.541 sec elapsed
#Without GCD or OpenMP: 11.54 sec elapsed
#Without GCD or OpenMP: 11.553 sec elapsed
#Without GCD or OpenMP: 11.575 sec elapsed
#Without GCD or OpenMP: 11.548 sec elapsed
#Without GCD or OpenMP: 11.576 sec elapsed
#Without GCD or OpenMP: 11.558 sec elapsed


# gcd 
#  1 
#  2  
#  3 
#  4 
#  5 
#  6 
#  7 
#  8  
#  9 
# 10  

# openmp
#  1 2.989
#  2 3.040 
#  3 3.245
#  4 2.995
#  5 2.992
#  6 2.969
#  7 2.985
#  8 3.071 
#  9 3.047
# 10 3.024 

set.seed(100)

library(rgcd)
library(tictoc)

n <- 100000

x <- 1:n
y <- 1:n


tic("With GCD") 
check1 <- inner_kernel(x,y,gcd=TRUE)
toc()

tic("With OpenMP") 
check2 <- inner_kernel(x,y,omp=TRUE)
toc()

#
# x1   y1      (x1-y1)^2 + (x1-y2)^2 + (x1-y3)^2 + (x1-y4)^2 = 4*x1^2 - 2*x1*sum(y) + sum(y^2) 
# x2   y2
# x3   y3
# x4   y4


tic("Without GCD or OpenMP") 
check3 <- inner_kernel(x,y)
toc()


tic("Correct and optimized results") 
check4 <- n*x^2 - 2*x*sum(y) + sum(y^2) 
toc()


print("Difference Between GCD and OpenMP Result:")
print( sum( check1 != check4))

print("Difference Between GCD and no threading Result:")
print( sum( check1 != check4))
