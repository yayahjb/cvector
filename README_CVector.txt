   Get CVector at SourceForge.net. Fast, secure and Free Open Source software
   downloads

     ----------------------------------------------------------------------

                    CVector -- ANSI C API for Dynamic Arrays

                                 Release 1.0.5
                                  21 Jan 2022
                 © 2008, 2009, 2014, 2022 Herbert J. Bernstein
                      yaya at bernstein-plus-sons dot com
               You may distribute the CVector API under the LGPL

   CVector is an ANSI C implementation of dynamic arrays to provide a crude
   approximation to the C++ vector class.

   Release 1.0.5 is a clean-up of the Makefile Release 1.0.4.1 is a move from
   Sourceforge to Github. Release 1.0.4 adds a CMakeLists.txt file to the kit
   and changes the test program to allow normal output to be written to a
   specified file. Release 1.0.3 was is a minor revision of release 1.0.0 of
   8 January 2009 to update the Makefile for builds under MINGW, on 26
   February 2009 to add the macro CVectorElementAt, and on 7 July 2009 to
   change the macro to CVECTOR_FAR and similarly change the macros that
   handle memmove and memset. There are no changes to the code. The internal
   copy of libtool has been removed.

    Installation

   The CVector package is available on Github at
   https://github.com/yayahjb/cvector.

   To see the current settings for a build execute

   make

   which should give the following information:

 PLEASE READ README_CVector.txt and lgpl.txt
 
  Before making the CVector library and example programs, check
  that the chosen settings are correct
 
  The current compile command is:
 
    libtool --mode=compile gcc -g -O2  -Wall -ansi -pedantic -I.  -c
 
  The current library link command is:
 
    libtool --mode=link  gcc -version-info 2:0:0 -release 1.0.4 -rpath /usr/local/lib
 
  The current library local, dynamic and static build commands are:
 
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -I.
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -shared -I /usr/local/include
    libtool --mode=link gcc -g -O2  -Wall -ansi -pedantic -static -I /usr/local/include
 
  Before installing the CVector library and example programs, check
  that the install directory and install commands are correct:
 
  The current values are :
 
    /usr/local
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
   libtool versions 1.3.5, 1.5.4 and 2.2.6. If the system libtool is not to
   be used, define the variable LIBTOOL to be the path to the libtool
   executable, e.g. in bash. On MINGW, use of gcc 4 and libtool 2.2.6 are
   highly recommended.

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

   void *
   CVectorElementAt(const CVectorHandle vectorhandle, const size_t index);

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
   dynamic array using CVectorGetElementptr(). The function
   CVectorElementAt() performs the same function as CVectorGetElementptr()
   for use in complex expressions, but does no error checking. Caution must
   be used in using pointers because expansion of the dynamic array can force
   relocation of all data in the dynamic array. Therefore, any use of
   CVectorGetElementptr() sets a flag, CVECTOR_FLAGS_NO_RELOCATION, that
   disables any further array relocation, which will prevent the extension of
   the size array beyond the capacity in effect at the time of the first
   CVectorGetElementptr() call. Calls to CVectorElementAt() do not set
   CVECTOR_FLAGS_NO_RELOCATION and returning resulting values to calling
   routines is dangerous. The functions CVectorGetFlags() and
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
   work in future versions of CVector. The function CVectorElementAt() is
   implemented as a macro and returns a void * pointer into the data array
   with no bounds checking. All other functions return 0 for normal
   completion, or the sum of one or more of the following non-zero error
   codes:

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

   Updated 1 May 2018
   yaya at bernstein-plus-sons dot com
