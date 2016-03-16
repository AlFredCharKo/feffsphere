//
//  count_noe.c
//  taken from newcoo2old
//
//  Created by Alexander Kompch on 03.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "count_noe.h"

conv_tbl *get_noe(coords *given) {
        //returns a conv_tbl with size 'START_SIZE' (automatic resizing not yet implemented)
        //the pair.atn in the returned conv_tabl is set with all different atn(s) found in given
        //the corresponding att is left to zero
        //finally cvt_limitsize limits access to the non-zero {pair.atn != 0 && pair.att != 0} pairs of conv_tbl
    
    conv_tbl *cvt = cvt_init(START_SIZE);
    cvt_pair pair = {.atn = 0, .att = 0};
    FILE *FP;
    FP=fopen("count_noe.txt", "wt");
    
    for (int i = 0; i < given->nat; i++) {
        for (int j = 0; j < cvt_size(cvt); j++) {
            pair = cvt_get(cvt, j);
            fprintf(FP,"\ni=%03d\tj=%02d\tat[%03d]->atn=%02d\tpair.atn=%02d",i, j, i, given->at[i]->atn, pair.atn);
                //           printf("\ni=%03d \t j=%02d \t at[%03d]->atn=%02d \t pair.atn=%02d",i, j, i, given->at[i]->atn, pair.atn);
            if (given->at[i]->atn == pair.atn) {
                break;
            }
            if (j == cvt_size(cvt) - 1) {
                pair.atn = given->at[i]->atn;
                pair.att = 0;
                if (cvt_add(cvt, pair) == EXIT_FAILURE) {
                    printf("\n***   get_noe: conversion too small. Will exit!");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    cvt_limitsize(cvt);
    fclose(FP);
    return cvt;
}