//
//  handle_cmdlargs.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "handle_cmdlargs.h"


char* handle_cmdlargs(int argc, const char *argv[]) {

    if (argc < 2) {
        char *parfile = mystralloc(strlen(DEFPARFILE));
        if (parfile == NULL) {
            printf("\n***   handle_cmdlargs: malloc parfile failed");
            free(parfile);
            return NULL;
        }
        strcpy(parfile,DEFPARFILE);
        return parfile;
    } else {
        char *parfile = mystralloc(strlen(argv[1]));
        if (parfile == NULL) {
            printf("\n***   handle_cmdlargs: malloc parfile failed");
            free(parfile);
            return NULL;
        }
        strcpy(parfile,argv[1]);
        return parfile;
    }
}
