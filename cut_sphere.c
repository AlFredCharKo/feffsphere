//
//  cut_sphere.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "cut_sphere.h"

coords *cut_sphere(coords *given, parameters *pars) {
    if (given == NULL) {
        printf("\n***   cut_sphere: given coords == NULL! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    int r = move2center(given, given->at[pars->atnoat0]->pnt);
    if (r != EXIT_SUCCESS) {
        printf("\n***   cut_sphere: move2center failed! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    
    vec boxL = {.x = pars->dia, .y = pars->dia, .z = pars->dia};
    coords *sphere = coords_init(natinsphere(given, pars->dia), boxL);
    
        //copy all within dia (<) to sphere
    
    r = cpatinsphere(given, sphere, pars->dia);             //reusing r!
    if (r < 1) {
        printf("\n***   cut_sphere: no atoms copied to sphere!");
    }
    
    printf("\n***   cut_sphere: %d atoms copied to sphere!", r);

    
    return sphere;
}


int natinsphere(coords *given, int dia) {
        //counts number of atomes inside (<) diameter around origin
        //use move2center prior to this function for selecting a specific atom at origin
    int j = 0;
    double rad = 0.5 * dia;                            //r = 1/2 * dia
    for (int i = 0; i < given->nat; i++) {
        if (given->at[i]->dist < rad) {
            j++;
        }
    }
    return j;
}


int cpatinsphere(const coords *source, coords *dest, int dia) {
        //copy atomes inside (<) diameter around origin in source to dest
        //use move2center prior to this function for selecting a specific atom at origin
        //returns number of atoms copied
    int j = 0;
    double rad = 0.5 * dia;                            //r = 1/2 * dia
    for (int i = 0; i < source->nat; i++) {
        if (source->at[i]->dist < rad) {
            cp_atom(source->at[i], dest->at[j], j);
            j++;
        }
    }
    return j;
}




