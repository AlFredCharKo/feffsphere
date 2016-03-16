//
//  mystr.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "mystr.h"

char *mystralloc(size_t i) {
    int j;
    j = snapUpSize((int) (i + (2 - (i != 0))));
    if (j <= (int) i) return NULL;
        
    char *c = (char*)calloc(j, sizeof(char));
        if (NULL == c) return NULL;
    printf("\n***   mystralloc: received request for string size %03zu (value from strlen) bytes but allocated %03d bytes of memory", i, j);
    return c;
}

/* Compute the snapped size for a given requested size.  By snapping to powers
 of 2 like this, repeated reallocations are avoided. */
int snapUpSize (int i) {
    if (i < 8) {
        i = 8;
    } else {
        unsigned int j;
        j = (unsigned int) i;
        
        j |= (j >>  1);     //Bitwise OR
        j |= (j >>  2);
        j |= (j >>  4);
        j |= (j >>  8);		/* Ok, since int >= 16 bits */
#if (UINT_MAX != 0xffff)
        j |= (j >> 16);		/* For 32 bit int systems */
#if (UINT_MAX > 0xffffffffUL)
        j |= (j >> 32);		/* For 64 bit int systems */
#endif
#endif
        /* Least power of two greater than i */
        j++;
        if ((int) j >= i) i = (int) j;
    }
    return i;
}