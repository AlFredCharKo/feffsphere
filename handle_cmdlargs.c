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
        char *parfile=(char*)calloc(strlen(DEFPARFILE)+1, sizeof(char));
        if (parfile == NULL) {
            printf("\n***   handle_cmdlargs: malloc parfile failed");
            return NULL;
        }
        printf("\n***   handle_cmdlargs: strlen('DEFPARFILE')*sizeof(char)=%zu",strlen(DEFPARFILE)*sizeof(char));
        strcpy(parfile,DEFPARFILE);
        return parfile;
    } else {
        char *parfile=(char*)calloc(strlen(argv[1])+1, sizeof(char));
        if (parfile == NULL) {
            printf("\n***   handle_cmdlargs: malloc parfile failed");
            return NULL;
        }
        printf("\n***   handle_cmdlargs: strlen(argv[1])*sizeof(char)=%zu",strlen(argv[1])*sizeof(char));
        strcpy(parfile,argv[1]);
        return parfile;
    }
}
