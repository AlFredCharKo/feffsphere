//
//  main.c
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "main.h"

int main(int argc, const char * argv[]) {
    
    char *parfile = handle_cmdlargs(argc, argv);
    parameters *pars = read_parfile(parfile);
    if (pars == NULL) {
        printf("\n***   main: read_parfile failed! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    print_pars(pars);
    
    coords *coo = read_newcoo(pars->infile);
    if (coo == NULL) {
        printf("\n***   main: read_oldcoo failed! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    char *filename = append_filename(pars->outfile, ".sub", ".gnu");
    write_gnuplot(filename, coo);
    free(filename);
    
    filename = append_filename(pars->outfile, ".sub", ".pdb");
    write_pdb(filename, coo);
    free(filename);
    
    
    
    printf("\n");
    return EXIT_SUCCESS;
}
    
    
        //example of using bstring library to replace fgets()
    FILE fp;
    fp = fopen ( ... );
    fp = NULL;
    if (fp) b = bgets ((bNgetc) fgetc, fp, '\n');
}
