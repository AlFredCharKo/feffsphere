//
//  convert_new2old.c
//  newcoo2old
//
//  Created by Alexander Kompch on 04.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "convert_new2old.h"

coords* convert_new2old(coords *given, conv_tbl *cvt) {
    coords *oldcoo = coords_init(given->nat, given->boxL);
    for (int i = 0; i < given->nat; i++) {
        oldcoo->at[i]->n = given->at[i]->n;
        strncpy(given->at[i]->esymb, oldcoo->at[i]->esymb, 2);
        int att = cvt_attlookup(cvt, given->at[i]->atn);
        if (att == -1) {
            printf("\n***   convert_new2old: atn=%3d not found in conversion table. Will exit.",given->at[i]->atn);
            exit(EXIT_FAILURE);
        }
        oldcoo->at[i]->atn = att;
        oldcoo->at[i]->pnt.x = given->at[i]->pnt.x;
        oldcoo->at[i]->pnt.y = given->at[i]->pnt.y;
        oldcoo->at[i]->pnt.z = given->at[i]->pnt.z;
    }
    return oldcoo;
}
