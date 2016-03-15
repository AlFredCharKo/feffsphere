//
//  print_pars.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "print_pars.h"

int print_pars(parameters *pars)
{    
    printf("\n***   IN print_pars   ***\n");
    
    printf("\nparameters read from <%s>", pars->parfile);
    printf("\ninput file <%s>", pars->infile);
    printf("\noutput file: <%s>", pars->outfile);
    printf("\nsubstitute %7.4f of atomic number %d by atomic number %d (%2s)", pars->dopc, pars->atn2sub, pars->atnofdop, pars->dopesymb);
    printf("\n");
    return EXIT_SUCCESS;
}