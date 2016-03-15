//
//  append_filename.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "append_filename.h"

char* append_filename(const char *given, const char *suffix1, const char *suffix2) {
    size_t a = 0, b = 0, c = 0;
    
    a = strlen(given);
    b = strlen(suffix1);
    c = strlen(suffix2);
    
    char *filename = calloc((a+b+c+1), sizeof(char));
    if (filename == NULL) {
        printf("\n***   append_filename: malloc for filename failed.");
        return NULL;
    }
    
    strcpy(filename, given);
    strcat(filename, suffix1);
    strcat(filename, suffix2);
    
    return filename;
}