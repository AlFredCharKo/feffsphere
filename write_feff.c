//
//  write_feff.c
//  feffsphere2
//
//  Created by Alexander Kompch on 16.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "write_feff.h"

int write_feff(char *filename, coords *coo) {
    FILE *FP;
    int i=0;
    
    if (coo == NULL) return EXIT_FAILURE;
    
    FP=fopen(filename, "wt");
    
    if (FP == NULL) {
        printf("\n***   write_feff:Could not open <%s>.", filename);
        return EXIT_FAILURE;
    }
    fprintf(FP,"%7s %6d %lf %lf %lf\n", "new-coo", coo->nat, coo->boxL.x, coo->boxL.y, coo->boxL.z);
    fprintf(FP,"n \t atyp \t esymb \t X \t \t Y \t \t att \t \t dist\n");
    for(i=0;i<coo->nat;i++) {
        fprintf(FP," %9.5f   %9.5f   %9.5f   %2d   %-13s   %8.5f\n", coo->at[i]->pnt.x, coo->at[i]->pnt.y, coo->at[i]->pnt.z, coo->at[i]->atn, "XX", coo->at[i]->dist);
        
            //        fprintf(FP, "%03d %02d \t \t %2s \t %+8.3f %+8.3f %+8.3f %+8.3f\n", coo->at[i]->n, coo->at[i]->atn, coo->at[i]->esymb, coo->at[i]->pnt.x, coo->at[i]->pnt.y, coo->at[i]->pnt.z, coo->at[i]->dist);
    }
    
    fclose(FP);
    
    return EXIT_SUCCESS;
}