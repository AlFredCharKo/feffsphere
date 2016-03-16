//
//  cut_sphere.h
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef __feffsphere2__cut_sphere__
#define __feffsphere2__cut_sphere__

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "coords_helper.h"

coords *cut_sphere(coords *given, parameters *pars);
int natinsphere(coords *given, double dia);
int cpatinsphere(const coords *source, coords *dest, double dia);



#endif /* defined(__feffsphere2__cut_sphere__) */
