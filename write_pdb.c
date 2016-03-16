//
//  write_pdb.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "write_pdb.h"

int write_pdb(char *filename, coords *coo) {
    FILE *FP;
    int i=0;
    
    if (coo == NULL) return EXIT_FAILURE;
    
    FP=fopen(filename, "wt");
    
    if (FP == NULL) {
        printf("\n***   write_pdb:Could not open <%s>.", filename);
        return EXIT_FAILURE;
    }
    
    for(i=0;i<coo->nat;i++) {
        fprintf(FP, "ATOM  %5d %2s   UNK  %4d      %+-8.3f%+-8.3f%+-8.3f%-6.2f%-6.2f         %2s  \n",coo->at[i]->n,coo->at[i]->esymb,0,coo->at[i]->pnt.x, coo->at[i]->pnt.y, coo->at[i]->pnt.z,1.0,0.0,coo->at[i]->esymb);
    }
    
    fclose(FP);
    
    return EXIT_SUCCESS;
}
