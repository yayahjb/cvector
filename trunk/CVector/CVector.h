/*
 *  CVector.h
 *  CVector
 *
 *  Created by Herbert J. Bernstein on 11/28/08.
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

#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED

#ifdef __cplusplus

extern "C" {
    
#endif
    
    /* CVector flags */
    
#define CVECTOR_FLAGS_NO_RELOCATION  1
#define CVECTOR_FLAGS_NO_RESIZE      2
    
    
    /* CVector error return values */
    
#define CVECTOR_MALLOC_FAILED -1
#define CVECTOR_BAD_ARGUMENT  -2
#define CVECTOR_NOT_FOUND     -4
#define CVECTOR_NO_RELOCATION -8
#define CVECTOR_NO_RESIZE     -16
    
#ifdef CVECTOR_USE_FAR
#include <malloc.h>
#include <string.h>
#define FAR __far
#define MALLOC _fmalloc
#define FREE _ffree
#define MEMSET _fmemset
#define MEMMOVE _fmemmove
#else
#include <stdlib.h>
#include <string.h>
#define FAR
#define MALLOC malloc
#define FREE free
#define MEMSET memset
#define MEMMOVE memmove
#endif
    
    typedef struct {
        size_t size;             /* size of the vector      */
        size_t capacity;         /* capacity of the vector  */
        size_t elementsize;      /* size of an element      */
        void FAR * array;        /* the array of elements   */
        int flags;               /* flags                   */
    } CVector;
    
    typedef CVector FAR * CVectorHandle;
    
    
    /*  CVectorAddElement -- add an element to a CVector */
    
    int CVectorAddElement(CVectorHandle vectorhandle, void FAR * element);

    /* CVectorCapacity -- macro to return the CVector capacity */
    
#define CVectorCapacity(vectorhandle)  (vectorhandle)->capacity
    
    /* CVectorClear -- clear a generic vector */
    
    int CVectorClear(CVectorHandle vectorhandle);

    /* CVectorCreate -- create a CVector */
    
    int CVectorCreate(CVectorHandle FAR * vectorhandle, size_t elementsize, size_t capacity);
        
    /* CVectorFree -- remove a CVector */
    
    int CVectorFree(CVectorHandle FAR * vectorhandle);
    
    /* CVectorGetCapacity - function to return the CVector capacity */
    
    int CVectorGetCapacity(CVectorHandle vectorhandle, size_t FAR * capacity);
    
    /* CVectorGetElement -- get a copy of an element from a CVector */
    
    int CVectorGetElement(CVectorHandle vectorhandle, void FAR * element, size_t index);
    
    /* CVectorGetElementptr -- get a pointer to an element from a CVector */
    
    int CVectorGetElementptr(CVectorHandle vectorhandle, void FAR ** elementptr, size_t index);
    
    /* CVectorGetFlags - function to return the CVector flags */
    
    int CVectorGetFlags(CVectorHandle vectorhandle, int FAR * flags);
    
    /* CVectorGetSize - function to return the CVector size */
    
    int CVectorGetSize(CVectorHandle vectorhandle, size_t FAR * size);
        
    /* CVectorRemoveElement -- remove an element from a generic vector */
    
    int CVectorRemoveElement(CVectorHandle vectorhandle, size_t index);

    /* CVectorSetCapacity - function to set the CVector capacity */
    
    int CVectorSetCapacity(CVectorHandle vectorhandle, size_t capacity);       
        
    /* CVectorSetElement -- set a copy of an element into a CVector */
    
    int CVectorSetElement(CVectorHandle vectorhandle, void FAR * element, size_t index);

    /* CVectorSetFags - function to set the CVector flags */
    
    int CVectorSetFlags(CVectorHandle vectorhandle, int flags);
    
    /* CVectorSetSize - function to set the CVector size */
    
    int CVectorSetSize(CVectorHandle vectorhandle, size_t size);

    /* CVectorSize -- macro to return the CVector size */
    
#define CVectorSize(vectorhandle)  (vectorhandle)->size
    


#ifdef __cplusplus
    
}

#endif


#endif
