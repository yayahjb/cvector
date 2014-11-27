/*
 *  CVectorBasicTest.c
 *  CVector
 *
 *  Created by Herbert J. Bernstein on 12/04/08.
 *  Copyright 2008 Herbert J. Bernstein. All rights reserved.
 *
 */


/**********************************************************************
 *                                                                    *
 * YOU MAY REDISTRIBUTE THE CVector API UNDER THE TERMS OF THE LGPL   *
 *                                                                    *
 **********************************************************************/

/************************* LGPL NOTICES *******************************
 *                                                                    *
 * This library is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU Lesser General Public         *
 * License as published by the Free Software Foundation; either       *
 * version 2.1 of the License, or (at your option) any later version. *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 * Lesser General Public License for more details.                    *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License along with this library; if not, write to the Free         *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    *
 * MA  02110-1301  USA                                                *
 *                                                                    *
 **********************************************************************/

#ifdef USE_LOCAL_HEADERS
#include "CVector.h"
#else
#include <CVector.h>
#endif
#include <stdio.h>

typedef long unsigned int LUI;

CVectorHandle vectorhandle;

int main(int argc, char **argv) {
    size_t index;
    double element;
    double * elementptr;
    void * velementptr;
    unsigned int flags;
    size_t size, capacity;
    
    FILE * out;
    
    out = stdout;
    
    if (argc > 1) {
        out = fopen(argv[1],"w+");
        if (!out) {
            fprintf(stderr," Failed to open output file %s\n", argv[1]);
            exit(1);
        }
    }
    
    fprintf(out," Test 0: Create vector and load it with 1000000 elements.\n");
    CVectorCreate(&vectorhandle,sizeof(double),1);
    for (index=0; index<1000000; index++) {
        element = (double)index;
        CVectorAddElement(vectorhandle, &element);
        if (!(index&0x1FFFF)) {
            if (CVectorGetCapacity(vectorhandle,&capacity) ){
                fprintf(stderr,"Call to CVectorGetCapacity failed.\n");
            }
            if (CVectorGetSize(vectorhandle,&size)) {
                fprintf(stderr,"Call to CVectorGetSize failed.\n");
            }
            if (size != index+1) {
                fprintf(stderr,"Size mismatch index+1 %lu, size %lu.\n",(LUI)index+1,(LUI)size);
            }
            fprintf(out,"Size %lu, capacity %lu.\n", (LUI)size, (LUI)capacity);
        }
    }
    fprintf(out," Test 1: Reference elements of CVector as an array.\n");
    for (index=0; index<1000000; index++) {
        if ((double)index != ((double *)(vectorhandle->array))[index]) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                    (LUI)index, ((double *)(vectorhandle->array))[index]);
        }
    }
    fprintf(out," Test 2: Reference elements of CVector via CVectorGetElement.\n");
    for (index=0; index<(size_t)1000000; index++) {
        if (CVectorGetElement(vectorhandle, &element, index)) 
            fprintf(stderr," Failed CVectorGetElement, index = %lu\n",(LUI)index);
        if ((double)index != element) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                    (LUI)index, element);
        }
    }
    /*  The next block will referenece the array via pointers
        This will also set the CVECTOR_FLAGS_NO_RELOCATION 
        Will then reset the flag.
     */
    fprintf(out," Test 3: Reference elements of CVector via CVectorGetElementptr.\n");
    for (index=0; index<(size_t)1000000; index++) {
        if (CVectorGetElementptr(vectorhandle, &velementptr, index)) 
            fprintf(stderr," Failed CVectorGetElement, index = %lu\n",(LUI)index);
        elementptr = (double *)velementptr;
        if (velementptr != CVectorElementAt(vectorhandle, index)) {
            fprintf(stderr," Failed CVectorGetElementAt, index = %lu\n",(LUI)index);
        }
        if ((double)index != *elementptr) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                    (LUI)index, *elementptr);
        }
    }
    if (CVectorGetFlags(vectorhandle,&flags))
        fprintf(stderr,"Call to CVectorGetFlags failed.\n");
    if ( !(flags&CVECTOR_FLAGS_NO_RELOCATION) )
        fprintf(stderr,"CVECTOR_FLAGS_NO_RELOCATION not set by CVectorGetElementptr.\n");
    flags = 0;
    if (CVectorSetFlags(vectorhandle,flags))
        fprintf(stderr,"Call to CVectorSetFlags failed.\n");
    
    fprintf(out," Test 4: Set elements of CVector as an array\n");
    for (index=0; index<(size_t)1000000; index++) {
        ((double *)(vectorhandle->array))[index] = (double)(1000000-index);
    }
    for (index=0; index<(size_t)1000000; index++) {
        if ((double)(1000000-index) != ((double *)(vectorhandle->array))[index]) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                    (LUI)index, ((double *)(vectorhandle->array))[index]);
        }
    }
    fprintf(out," Test 5: Set elements of CVector via CVectorSetElement.\n");
    for (index=0; index<(size_t)1000000; index++) {
        element = (double)(index-1000000);
        if (CVectorSetElement(vectorhandle,&element,1000000-index))
            fprintf(stderr," Failed CVectorSetElement, index = %lu\n",(LUI)(1000000-index));
     }
    for (index=0; index<(size_t)1000000; index++) {
        if ((double)(index-1000000) != ((double *)(vectorhandle->array))[1000000-index]) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                (LUI)index, ((double *)(vectorhandle->array))[1000000-index]);
        }
    }
    fprintf(out," Test 6: Remove elements of CVector via CVectorRemoveElement.\n");
    for (index=0; index<(size_t)2000; index++) {
        ((double *)(vectorhandle->array))[index] = (double)(index);
    }
    for (index=0; index<(size_t)1000; index++) {
        if (CVectorRemoveElement(vectorhandle,index))
            fprintf(stderr," Failed CVectorRemoveElement, index = %lu\n",(LUI)index);
    }
    for (index=0; index<(size_t)1000; index++) {
        if ((double)(index*2+1) != ((double *)(vectorhandle->array))[index]) {
            fprintf(stderr," data mismatch array[%lu] = %g\n",
                (LUI)index, ((double *)(vectorhandle->array))[index]);
        }
    }
    fprintf(out," Test 7: Remove all elements of CVector via CVectorClear.\n");
    if (CVectorClear(vectorhandle))
        fprintf(stderr," Failed CVectorClear\n");
    if (CVectorSize(vectorhandle) !=0) {
        fprintf(stderr," CVectorClear failed to set size to zero\n");
    }


    return 0;
}

