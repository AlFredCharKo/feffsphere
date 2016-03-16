//
//  pars_helper.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "pars_helper.h"

int pars_free(parameters *given) {
    free(given->infile);
    free(given->outfile);
    free(given->parfile);
    free(given->cvt);
    free(given);
    return EXIT_SUCCESS;
}