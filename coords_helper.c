//
//  coords_helper.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "coords_helper.h"

coords *coords_init(int nat, vec boxL) {
    int i = 0;
    
    coords *given = (coords*)calloc(1, sizeof(coords));
    if (given == NULL) {
        printf("\n***   init_coords: malloc failed");
        return NULL;
    }
    given->at = (atom**)calloc(nat, sizeof(atom*));
    if (given->at == NULL) {
        printf("\n***   init_coords: malloc failed");
        return NULL;
    }
    for (i=0; i<nat; i++) {
        given->at[i] = (atom*)calloc(1, sizeof(atom));
        if (given->at[i] == NULL) {
            printf("\n***   init_coords: malloc failed");
            return NULL;
        }
        given->at[i]->n = i+1;
        strncpy(given->at[i]->esymb, "XX", 2);
        given->at[i]->atn = -1;
        given->at[i]->pnt.x = 0.0;
        given->at[i]->pnt.y = 0.0;
        given->at[i]->pnt.z = 0.0;
        given->at[i]->dist = 0.0;
    }
    given->nat = nat;
    given->boxL.x = boxL.x;
    given->boxL.y = boxL.y;
    given->boxL.z = boxL.z;
        

    return given;
}

int cp_coords(const coords *source, coords *dest) {
    int i = 0;
    
        // check that source is allocated, else exit function with error
    if (source == NULL) {
        return EXIT_FAILURE;
    }
        // check that destination is allocated, else exit function with error
    if (dest == NULL) {
        return EXIT_FAILURE;
    }
        // check that destination has been allocated for at least as many atoms as in source, else exit with error
    if (dest->nat < source->nat) {
        return EXIT_FAILURE;
    }
    
    for (i=0; i<source->nat; i++) {
        cp_atom(source->at[i], dest->at[i], i);
    }
    
    dest->boxL.x = source->boxL.x;
    dest->boxL.y = source->boxL.y;
    dest->boxL.z = source->boxL.z;
    
    
    return EXIT_SUCCESS;
}

int cp_ncoords(const coords *source, coords *dest, int n) {
    int i = 0;
    
        // check that source is allocated, else exit function with error
    if (source == NULL) {
        return EXIT_FAILURE;
    }
        // check that destination is allocated, else exit function with error
    if (dest == NULL) {
        return EXIT_FAILURE;
    }
        // check that destination has been allocated for at least n atoms
    if (dest->nat < n) {
        return EXIT_FAILURE;
    }
    
    for (i=0; i<n; i++) {
        cp_atom(source->at[i], dest->at[i], i);
    }
    
    dest->boxL.x = source->boxL.x;
    dest->boxL.y = source->boxL.y;
    dest->boxL.z = source->boxL.z;
    
    
    return EXIT_SUCCESS;
}

int move2center(coords *given, vec new_origin) {
    int i = 0;
    
    if (given == NULL) {
        printf("\n***   move2center: given == NULL");
        return EXIT_FAILURE;
    } else if (given->nat <= 0) {
        printf("\n*** move2center: given->nat <= 0. Nothing to do");
        return EXIT_SUCCESS;
    }
    
    for (i=0; i<given->nat; i++) {
        given->at[i]->pnt.x = given->at[i]->pnt.x - new_origin.x;
        given->at[i]->pnt.y = given->at[i]->pnt.y - new_origin.y;
        given->at[i]->pnt.z = given->at[i]->pnt.z - new_origin.z;
        given->at[i]->dist = len3D(given->at[i]->pnt);
    }
    
    return EXIT_SUCCESS;
}

int cp_atom(const atom *source, atom *dest, int v) {
    
    if (source == NULL || dest == NULL) {
        printf("\n***   cp_atom: source OR dest == NULL");
        return EXIT_FAILURE;
    }
    
    dest->n = v;
    strncpy(dest->esymb, source->esymb, 2);
    dest->atn = source->atn;
    dest->pnt.x = source->pnt.x;
    dest->pnt.y = source->pnt.y;
    dest->pnt.z = source->pnt.z;
    dest->dist = source->dist;
        
    return EXIT_SUCCESS;
}

void print_at(atom *given) {
    printf("\nn=%d \t esymb=%2s \t atn=%d \t x=%7.4f \t y=%7.4f \t z=%7.4f \t dist=%7.4f", given->n, given->esymb, given->atn,given->pnt.x, given->pnt.y, given->pnt.z, given->dist);
    
}

int coords_free(coords *given) {
    int i = 0;
    
    for (i=0;i<given->nat;i++) {
        free(given->at[i]);
    }
    free(given->at);
    free(given);
    return EXIT_SUCCESS;
}

double len3D_sq(vec given) {
    return given.x * given.x + given.y * given.y + given.z * given.z;
}

double len3D(vec given) {
    return sqrt(given.x * given.x + given.y * given.y + given.z * given.z);
}

double len2D_sq(vec given) {
    return given.x * given.x + given.y * given.y;
}

double len2D(vec given) {
    return sqrt(given.x * given.x + given.y * given.y);
}

