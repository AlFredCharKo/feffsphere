//
//  read_parfile.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "read_parfile.h"

parameters* read_parfile(char* parfile)
{
    int line = 0;
    char *buffer = mystralloc(MAX_LEN);
    parameters* pars = (parameters *)calloc(1, sizeof(parameters));
    FILE *FP;
    
    FP=fopen(parfile, "rt");
    if (FP == NULL) {
        printf("\n***   read_parfile:Could not open <%s>.", parfile);
        return NULL;
    }
    
    pars->parfile = (char *)mystralloc(strlen(parfile));
    strcpy(pars->parfile, parfile);
    
    while (fgets(buffer, MAX_LEN, FP) != NULL) {
        line ++;
        if (line == 1) {
            trim(buffer);
            pars->infile = mystralloc(strlen(buffer));
            strcpy(pars->infile, buffer);
        } else if (line == 2) {
            trim(buffer);
            pars->outfile = mystralloc(strlen(buffer));
            strcpy(pars->outfile, buffer);
        } else if (line == 3) sscanf(buffer, "%d %lf", &(pars->atnoat0), &(pars->dia));
        
    }
    fclose(FP);
    free(buffer);
    return pars;
}