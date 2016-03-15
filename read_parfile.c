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
    char *buffer = (char*)calloc(MAX_LEN, sizeof(char));
    parameters* pars = (parameters *)calloc(1,sizeof(parameters));
    FILE *FP;
    
    FP=fopen(parfile, "rt");
    if (FP == NULL) {
        printf("\n***   read_parfile:Could not open <%s>.", parfile);
        return NULL;
    }
    
    pars->parfile = (char *)calloc(strlen(parfile)+1, sizeof(char));
    strcpy(pars->parfile, parfile);
    
    while (fgets(buffer, MAX_LEN, FP) != NULL) {
        line ++;
        if (line == 1) {
            trim(buffer);
            pars->infile = (char *)calloc(strlen(buffer)+1, sizeof(char));
            strcpy(pars->infile, buffer);
        } else if (line == 2) {
            trim(buffer);
            pars->outfile = (char *)calloc(strlen(buffer)+1, sizeof(char));
            strcpy(pars->outfile, buffer);
        } else if (line == 3) sscanf(buffer, "%2s %d %lf %d", pars->dopesymb, &(pars->atnofdop), &(pars->dopc), &(pars->atn2sub));
        
    }
//      Line == 3 worked with atom types from old-coo format(each element in a cluster gets a number from 1
//      up to total number of different elemets, eg. Zn=1, Mn=2,O=3). In new-coo format each atom is identified by
//      its atomic number. So in Mn:ZnO for example (Zn=30, Mn=25, O=8) and a new element brought into the cluster by
//      substitution is also indentified by its atomic number. To go back to atom types newcoo2old can be used to convert
//      a new-coo file to old-coo format and each element can be assigned an individual atom type.
//      else if (line == 3) sscanf(buffer, "%2s %d %d", pars->ch2atnesymb, &(pars->ch2atn), &(pars->chatn));
    fclose(FP);
    free(buffer);
    return pars;
}