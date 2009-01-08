                    CVector -- ANSI C API for Dynamic Arrays

                                  Release 1.0
                                 8 January 2009
                      (c) 2008, 2009 Herbert J. Bernstein
                      yaya at bernstein-plus-sons dot com
               You may distribute the CVector API under the LGPL

   CVector is an ANSI C implementation of dynamic arrays to provide a crude
   approximation to the C++ vector class.

    Installation

   The CVector package is available at www.sourceforge.net/projects/cvector.
   A source tarball is available at
   downloads.sourceforge.net/cvector/CVector-1.0.0.tar.gz. Later tarballs may
   be available.

   When the source tarball is dowloaded and unpacked, you should have a
   directory CVector-1.0.0. To see the current settings for a build execute

   make

   which should give the following information:

  PLEASE READ README_CVector.txt and lgpl.txt
 
  Before making the CVector library and example programs, check
  that the chosen settings are corr
 
  The current compile command is:
 
    libtool --mode=compile gcc -g -O2  -Wall -ansi -pedantic -I.  -c
 
  The current library link command is:
 
    libtool --mode=link  gcc -version-info 1:0:1 -release 1.0 \
      -rpath /home/faculty/bernsteh/lib
 
  The current library local, dynamic and static build commands are:
 
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -I.
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -dynamic \
      -I /home/faculty/bernsteh/include -L/home/faculty/bernsteh/lib
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -static \
      -I /home/faculty/bernsteh/include -L/home/faculty/bernsteh/lib
 
  Before installing the CVector library and example programs, check
  that the install directory and install commands are correct:
 
  The current values are :
 
    your home directory
    libtool --mode=install cp
    
 
  To compile the CVector library and example programs type:
 
    make clean
    make all
 
  To run a set of tests type:
 
    make tests
 
  To clean up the directories type:
 
    make clean
 
  To install the library and binaries type:
   
    make install


   If these settings need to be changed, edit Makefile. On some systems, e.g.
   Mac OS X, the default libtool is not appropriate. In that case you should
   install a recent version of libtool. The CVector kit has been tested with
   libtool versions 1.3.5 and 1.5.4. If the system libtool is not to be used,
   define the variable LIBTOOL to be the path to the libtaol executable, e.g.
   in bash

   export LIBTOOL=$HOME/bin/libtool

   of in the Makefie

   LIBTOOL = $(HOME)/bin/libtool

   If you need to include local header files using #include "..." instead of
   #include <...>, define the variable USE_LOCAL_HEADERS

    Synopsis

   #include <CVector.h>

   int
   CVectorCreate(CVectorHandle * vectorhandle, const size_t elementsize,
   const size_t capacity);

   int
   CVectorAddElement(const CVectorHandle vectorhandle, const void * element);

   int
   CVectorGetElement(const CVectorHandle vectorhandle, void * element, const
   size_t index);

   int
   CVectorGetElementptr(const CVectorHandle vectorhandle, void ** elementptr,
   const size_t index);

   int
   CVectorSetElement(const CVectorHandle vectorhandle, void * element, const
   size_t index);

   int
   CVectorRemoveElement(const CVectorHandle vectorhandle, const size_t
   index);

   int
   CVectorClear(const CVectorHandle vectorhandle);

   int
   CVectorFree(CVectorHandle * vectorhandle);

   size_t
   CVectorCapacity(const CVectorHandle vectorhandle);

   int
   CVectorGetCapacity(const CVectorHandle vectorhandle, size_t * capacity);

   size_t
   CVectorSize(const CVectorHandle vectorhandle);

   int
   CVectorGetSize(const CVectorHandle vectorhandle, size_t * size);

   int
   CVectorGetFlags(const CVectorHandle vectorhandle, int * flags);

   int
   CVectorSetCapacity(const CVectorHandle vectorhandle, const size_t
   capacity);

   int
   CVectorSetSize(const CVectorHandle vectorhandle, const size_t size);

   int
   CVectorSetFlags(const CVectorHandle vectorhandle, const unsigned int
   flags);

    Description

   The CVector.h header file defines the CVectorHandle type as a dynamic
   array for elements in which each element uses elementsize characters in a
   block of memory elementsize*capacity characters long. There are size
   elements used in the array each with an index between 0 and size-1.
   CVectorCreate() is used to create the dynamic array. Elements may either
   be added at the end of the dynamic array using CVectorAddElement(), or in
   arbitrary order with CVectorSetElement(). Elements may be examined with
   copy semantics using CVectorGetElement() or as pointers directly into the
   dynamic array using CVectorGetElementptr(). Caution must be used in using
   pointers because expansion of the dynamic array can force relocation of
   all data in the dynamic array. Therefore, any use of
   CVectorGetElementptr() sets a flag, CVECTOR_FLAGS_NO_RELOCATION, that
   disables any further array relocation, which will prevent the extension of
   the size array beyond the capacity in effect at the time of the first
   CVectorGetElementptr() call. The functions CVectorGetFlags() and
   CVectorSetFlags() can be used to reset this flag (see Examples below). The
   function CVectorRemoveElement() will remove the element of the indicated
   index, shifting all elements of higher indices down, unless the flag
   CVECTOR_FLAGS_NO_RELOCATION is set. The capacity, size and flags may be
   examined or set with CVectorCapacity(), CVectorGetCapacity(),
   CVectorSize(), CVectorGetSize(), CVectorGetFlags, CVectorSetCapacity(),
   CVectorSetSize() and CVectorSetFlags().

   External declarations as well as the CVector structure definition, and the
   CVectorHandle definition are included in the <CVector.h> include file. The
   CVector structure includes at least the following fields:

     size_t size;                /* size of the vector */     
     size_t capacity;            /* capacity of the vector */ 
     size_t elementsize;         /* size of an element */     
     void * array;               /* the array of elements */  
     int flags;                  /* flags */                  

   The valid flags are CVECTOR_FLAGS_NO_RELOCATION and
   CVECTOR_FLAGS_NO_RESIZE which may be ORed.

    Returns

   The functions CVectorCapacity() and CVectorSize() are implemented as
   macros and return the CVector capacity and size directly. While they could
   be used as lvalues, such use is not recommended and is not guaranteed to
   work in future versions of CVector. All other functions return 0 for
   normal completion, or the sum of one or more of the following non-zero
   error codes:

     Error Return          Numeric Value    Meaning                           
     CVECTOR_MALLOC_FAILED    -1            /* A call to allocate memory      
                                         failed */                            
     CVECTOR_BAD_ARGUMENT     -2            /* An argument is not valid */    
     CVECTOR_NOT_FOUND        -4            /* An element could not be found  
                                         */                                   
     CVECTOR_NO_RELOCATION    -8            /* Relocation is not permitted */ 
     CVECTOR_NO_RESIZE        -16           /* A change is size is not        
                                         permitted */                         

    Examples

   To create a vector of doubles, starting with minimal capacity, reporting
   failure to stderr:

         #include <CVector.h>
         ...
         CvectorHandle vectorhandle;
         ...
         if (CVectorCreate(&vectorhandle,sizeof(double),1)) fprintf(stderr," CVectorCreate failed!!\n");

   To create a vector of arrays of or pointers to doubles:

         #include <CVector.h>
         ...
         CvectorHandle vectorhandle;
         ...
         if (CVectorCreate(&vectorhandle,sizeof(double *),1)) fprintf(stderr," CVectorCreate failed!!\n");

   To pop the last element of a vector of doubles:

         #include <CVector.h>
         ...
         CvectorHandle vectorhandle;
         double element;
         ...
         if (CVectorGetElement(vectorhandle, &element, (CVectorSize(vectorhandle)-1))
             fprintf(stderr," Failed CVectorGetElement);
         if (CVectorRemoveElement(vectorhandle,  (CVectorSize(vectorhandle)-1))
             fprintf(stderr," Failed CVectorRemoveElement);

   See the test program CVectorBasicTest.c

     ----------------------------------------------------------------------

   Updated 8 January 2009
   yaya at bernstein-plus-sons dot com
