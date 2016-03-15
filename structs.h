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
} atom;

typedef struct {
    int nat;
    vec boxL;
    atom **at;
} coords;

typedef struct {
    char dopesymb[2];
    int atnofdop;
    double dopc;
    int atn2sub;
    char *parfile;
    char *infile;
    char *outfile;
} parameters;

#endif


