# dnl process for grand central dispatch and OpenMP
# based on rgdal configure.ac, Roger Bivand 
define([pkgversion], esyscmd([sh -c "grep Version: DESCRIPTION | cut -d' ' -f2 | tr -d '\n'"]))dnl

AC_INIT(rgcd, [pkgversion], jlisic@gmail.com)

# find R home and set correct compiler + flags
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
   AC_MSG_ERROR([cannot determine R_HOME. Make sure you use R CMD INSTALL!])
fi
RBIN="${R_HOME}/bin/R"

# pick all flags for testing from R
: ${CC=`"${RBIN}" CMD config CC`}
: ${CPP=`"${RBIN}" CMD config CPP`}
: ${CFLAGS=`"${RBIN}" CMD config CFLAGS`}
: ${CPPFLAGS=`"${RBIN}" CMD config CPPFLAGS`}
: ${LDFLAGS=`"${RBIN}" CMD config LDFLAGS`}
AC_MSG_NOTICE([CC: ${CC}])

AC_MSG_NOTICE([${PACKAGE_NAME}: ${PACKAGE_VERSION}])

### Checking if we can use frameworks

## Grand Central Dispatch on OSX
AC_MSG_CHECKING(can I compile GCD with Apple System frameworks) 

# can compile?
[cat > test_gcd.c <<_EOCONF
 #include <stdio.h>
 #include <stdlib.h>
 #include <dispatch/dispatch.h>
 int main() {
   dispatch_queue_t my_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
   dispatch_apply (100, my_queue, ^(size_t idx){
     int j;
     j = idx*idx; 
   });

   exit(0);
 }
_EOCONF]


if test `${CC} ${CFLAGS} ${PKG_CFLAGS} ${CPPFLAGS} ${PKG_CPPFLAGS} -o test_gcd test_gcd.c -framework system ${LDFLAGS} ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
  AC_MSG_RESULT(yes)

  ## can run?
  AC_MSG_CHECKING(can I run GCD with Apple System frameworks)

  if test `./test_gcd; echo $?` = 0; then
    AC_SUBST([PKG_CFLAGS], ["${PKG_CFLAGS} -D_LIBDISPATCH"])
    AC_SUBST([PKG_LIBS], ["${PKG_LIBS} -framework system"])
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
  fi

else
  AC_MSG_RESULT(no)
fi


## Grand Central Dispatch on FreeBSD
AC_MSG_CHECKING(can I compile GCD with libdispatch) 

# can compile?
[cat > test_gcd.c <<_EOCONF
 #include <stdio.h>
 #include <stdlib.h>
 #include <dispatch/dispatch.h>
 int main() {
   dispatch_queue_t my_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

   dispatch_apply (100, my_queue, ^(size_t idx){
     int j;
     j = idx*idx; 
   });

   exit(0);
 }
_EOCONF]



if test `${CC} ${CFLAGS} ${PKG_CFLAGS} ${CPPFLAGS} ${PKG_CPPFLAGS} -o test_gcd test_gcd.c -fblocks -lBlocksRuntime -ldispatch ${LDFLAGS} ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
  AC_MSG_RESULT(yes)

  ## can run?
  AC_MSG_CHECKING(can I run GCD with libdispatch)

  if test `./test_gcd; echo $?` = 0; then
    AC_SUBST([PKG_CFLAGS], ["${PKG_CFLAGS} -fblocks -D_LIBDISPATCH"])
    AC_SUBST([PKG_LIBS], ["${PKG_LIBS} -lBlocksRuntime -ldispatch"])
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
  fi

else
  AC_MSG_RESULT(no)
fi


## OpenMP 
AC_MSG_CHECKING(can I compile with OpenMP) 

# can compile?
[cat > test_omp.c <<_EOCONF
 #include <stdio.h>
 #include <stdlib.h>
 #include <omp.h>
 int main() {
   omp_set_num_threads(2);
   int i,j;
   #pragma omp parallel private(i,j)
   {
   for(i=0;i<100;i++) j=i*i;
   }
   exit(0);
 }
_EOCONF]

if test `${CC} ${CFLAGS} ${PKG_CFLAGS} ${CPPFLAGS} ${PKG_CPPFLAGS} -o test_omp test_omp.c -fopenmp ${LDFLAGS} ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
  AC_MSG_RESULT(yes)

  ## Can run
  AC_MSG_CHECKING(can I run with OpenMP)

  if test `./test_omp; echo $?` = 0; then
    AC_SUBST([PKG_CFLAGS], ["${PKG_CFLAGS} -fopenmp"])
    AC_SUBST([PKG_LIBS], ["${PKG_LIBS} -fopenmp"])
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
  fi
  
else
  AC_MSG_RESULT(no)
fi


AC_MSG_NOTICE([Package CFLAGS = ${PKG_CFLAGS}])
AC_MSG_NOTICE([Package LIBS =   ${PKG_LIBS}])

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT

rm -rf test_* 
