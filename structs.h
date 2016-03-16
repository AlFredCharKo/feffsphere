//
//  structs.h
//  mklatc
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef mklatc_structs_h
#define mklatc_structs_h

//typedefstructs
typedef struct {
    double x;
    double y;
    double z;
} vec;

typedef struct {
    int n;
    char esymb[2];
    int atn;
    vec pnt;
    double dist;
} atom;

typedef struct {
    int nat;
    vec boxL;
    atom **at;
} coords;

typedef struct {
    int atnoat0;
    double dia;
    int noe;
    void *cvt;
    char *parfile;
    char *infile;
    char *outfile;
} parameters;

#endif


