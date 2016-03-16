//
//  read_newcoo.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "read_newcoo.h"

coords* read_newcoo(char *filename) {
    FILE *FP;
    vec boxL = {.x=-1.0, .y=-1.0, .z=-1.0};
    char *buffer = (char*)calloc(MAX_LEN, sizeof(char));
    char *fileformat = (char*)calloc(7, sizeof(char));
    int i=0, nat=0;
    
    printf("\nread_newcoo: filename = %s",filename);
    
    FP=fopen(filename, "rt");
    if (FP == NULL) {
        printf("\n***   read_newcoo:Could not open <%s>.", filename);
        return NULL;
    }
        // read first line of file to get nat, boxL and confirm newcoo-format
    if (fgets(buffer, MAX_LEN, FP) == NULL) {
        printf("\n***   read_newcoo: read from input file failed");
        return NULL;
    }
    sscanf(buffer,"%7s %6d %lf %lf %lf",fileformat, &nat, &boxL.x, &boxL.y, &boxL.z);
    trim(fileformat);
    if (strncmp(fileformat, "new-coo", 7) != 0) {
        printf("\n***   read_newcoo: file format to read is incompatible (not new-coo)");
        return NULL;
    }
    coords *coo = coords_init(nat, boxL);
    printf("\n*** read_newcoo: header = %7s %6d %10.6f %10.4f %10.4f",fileformat, nat, boxL.x, boxL.y, boxL.z);

    for(i=0;i<coo->nat;i++) {
        fgets(buffer, MAX_LEN, FP);
        sscanf(buffer, "%5d %2s %2d %lf %lf %lf\n", &(coo->at[i]->n), coo->at[i]->esymb, &(coo->at[i]->atn), &(coo->at[i]->pnt.x), &(coo->at[i]->pnt.y), &(coo->at[i]->pnt.z));
        coo->at[i]->dist = len3D(coo->at[i]->pnt);
    }
    fclose(FP);
    return coo;
}