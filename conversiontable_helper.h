//
//  conversiontable_helper.h
//  newcoo2old
//
//  Created by Alexander Kompch on 03.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef __newcoo2old__conversiontable_helper__
#define __newcoo2old__conversiontable_helper__

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

typedef struct {
    size_t size1;
    size_t size2;
    size_t tda;
    int *data;
} conv_tbl;

typedef struct {
    int atn;
    int att;
} cvt_pair;

conv_tbl *cvt_init(int nset);
int cvt_free(conv_tbl *given);
void cvt_set(conv_tbl *given, int n, cvt_pair set);
cvt_pair cvt_get(conv_tbl *given, int n);
int cvt_size(conv_tbl *given);
int cvt_add(conv_tbl *given, cvt_pair pair);
void cvt_limitsize(conv_tbl *given);
void cvt_askuser(conv_tbl *given);
int cvt_attlookup(conv_tbl *cvt, int atn);


#endif /* defined(__newcoo2old__conversiontable_helper__) */
