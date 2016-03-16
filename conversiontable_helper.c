//
//  conversiontable_helper.c
//  taken from newcoo2old
//
//  Created by Alexander Kompch on 03.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "conversiontable_helper.h"

conv_tbl *cvt_init(int nset) {
    int i = 0, j = 0;
    int m = 2;
    conv_tbl *cvt = (conv_tbl*)calloc(1, sizeof(conv_tbl));
    if (cvt == NULL) {
        printf("\n***   init_cvt: calloc failed. Will exit!");
        exit(EXIT_FAILURE);
    }
    cvt->size1 = nset;
    cvt->size2 = m;
    cvt->tda = m;
    cvt->data = calloc(nset * m, sizeof(int));

    for (i = 0; i < cvt->size1; i++) {
        for (j = 0; j < cvt->size2; j++) {
            *(cvt->data + (i * cvt->tda + j)) = 0;
        }
    }
    return cvt;
}

int cvt_free(conv_tbl *given) {
    free(given->data);
    free(given);
    return EXIT_SUCCESS;
}

void cvt_set(conv_tbl *given, int n, cvt_pair set) {
    if (given == NULL) {
        printf("\n***   cvt_init: calloc failed. Will exit!");
        exit(EXIT_FAILURE);
    } else if (n >= given->size1) {
        printf("\n***   cvt_set: row > allocated. Will exit!");
        exit(EXIT_FAILURE);
    } else if (given->size2 < 2) {
        printf("\n***   cvt_set: less than 2 columns allocated. Will exit!");
        exit(EXIT_FAILURE);
    }
    *(given->data + n * given->tda + 0) = set.atn;
    *(given->data + n * given->tda + 1) = set.att;
}

cvt_pair cvt_get(conv_tbl *given, int n) {
    cvt_pair pair = {.atn=0, .att=0};
    if (given == NULL) {
        printf("\n***   cvt_get: calloc failed. Will exit!");
        exit(EXIT_FAILURE);
    } else if (n >= given->size1) {
        printf("\n***   cvt_get: row > allocated. Will exit!");
        exit(EXIT_FAILURE);
    } else if (given->size2 < 2) {
        printf("\n***   cvt_get: less than 2 columns allocated. Will exit!");
        exit(EXIT_FAILURE);
    }
    pair.atn = *(given->data + n * given->tda + 0);
    pair.att = *(given->data + n * given->tda + 1);
    
    return pair;
}

int cvt_size(conv_tbl *given) {
    if (given == NULL) {
        printf("\n***   cvt_size: conv_tbl not allocated. Will exit!");
        exit(EXIT_FAILURE);
    }
    return (int)given->size1;
}


void cvt_askuser(conv_tbl *given) {
    if (given == NULL) {
        printf("\n***   cvt_askuser: newcoo not allocated. Will exit!");
        exit(EXIT_FAILURE);
    }
    cvt_pair pair = {.atn = 0, .att = 0};
    int noe = cvt_size(given);
    for (int i = 0; i < noe; i++) {
        pair = cvt_get(given, i);
        printf("\nenter atom type for atomic number: %3d ", pair.atn);
        scanf("%2d", &pair.att);
        cvt_set(given, i, pair);
    }
}

int cvt_add(conv_tbl *given, cvt_pair pair) {
    for (int i = 0; i < cvt_size(given); i++) {
        cvt_pair current = cvt_get(given, i);
        if (current.atn == 0 && current.att == 0) {
            cvt_set(given, i, pair);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

void cvt_limitsize(conv_tbl *given) {
        //limits the accessable size of given to the non-zero pairs of given
    for (int i = 0; i < cvt_size(given); i++) {
        cvt_pair current = cvt_get(given, i);
        if (current.atn == 0 && current.att == 0) {
            given->size1 = i;
        }
    }
}

int cvt_attlookup(conv_tbl *cvt, int atn) {
    cvt_pair pair = {.atn = 0, .att = 0};
    for (int i = 0; i < cvt_size(cvt); i++) {
        pair = cvt_get(cvt, i);
        if (atn == pair.atn) {
            return pair.att;
        }
    }
    return -1;
}





