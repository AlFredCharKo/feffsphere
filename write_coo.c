//
//  write_coo.c
//  feffsphere2
//
//  Created by Alexander Kompch on 16.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "write_coo.h"

int write_coo(char *filename, coords *coo) {
    FILE *FP;
    int i=0;
    
    printf("\nwrite_coo: filename = %s",filename);
    
    if (coo == NULL) return EXIT_FAILURE;
    
    FP=fopen(filename, "wt");
    if (FP == NULL) {
        printf("\n***   write_coo:Could not open <%s>.", filename);
        return EXIT_FAILURE;
    }
    
    printf("\n***write_coo: coo->nat=%d",coo->nat);
    fprintf(FP, "%7s %6d %+10.4f %+10.4f %+10.4f\n", "new-coo", coo->nat, coo->boxL.x, coo->boxL.y, coo->boxL.z);
    
    for(i=0;i<coo->nat;i++) {
        fprintf(FP, "%5d %2s %2d %+-8.6f %+-8.6f %+-8.6f\n", coo->at[i]->n, coo->at[i]->esymb, coo->at[i]->atn, coo->at[i]->pnt.x, coo->at[i]->pnt.y, coo->at[i]->pnt.z);
    }
    
    printf("\n***write_coo: here!!!");
    fclose(FP);
    
    return EXIT_SUCCESS;
}