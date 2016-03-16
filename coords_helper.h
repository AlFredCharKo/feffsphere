//
//  coords_helper.h
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef __feffsphere2__coords_helper__
#define __feffsphere2__coords_helper__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "defs.h"
#include "structs.h"


coords *coords_init(int nat, vec boxL);
int cp_coords(const coords *source, coords *dest);
int cp_ncoords(const coords *source, coords *dest, int n);
int move2center(coords *given, vec new_origin);
int cp_atom(const atom *source, atom *dest, int v);
int coords_free(coords *given);

double len3D_sq(vec given);
double len3D(vec given);
double len2D_sq(vec given);
double len2D(vec given);

#endif /* defined(__feffsphere2__coords_helper__) */
