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
    
    
    
    coords *input = read_newcoo(pars->infile);
    if (input == NULL) {
        printf("\n***   main: read_newcoo failed! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    coords *sphere = cut_sphere(input, pars);
    if (sphere == NULL) {
        printf("\n***   main: cut_sphere failed! Will exit!");
        exit(EXIT_FAILURE);
    }
    
    qsort(sphere->at[0], sphere->nat, sizeof(atom), cmpdist);

    conv_tbl *cvt = get_noe(sphere);
    pars->cvt = cvt;
    cvt_askuser(cvt);
    print_pars(pars);
    
    coords *feffcoo = convert_new2old(sphere, cvt);
    if (feffcoo == NULL) {
        printf("\n***   main: convert_new2old failed! Will exit!");
        exit(EXIT_FAILURE);
    }

    char *filename = append_filename(pars->outfile, ".feff", ".pdb");
    write_pdb(filename, sphere);
    free(filename);
    
    filename = append_filename(pars->outfile, ".feff", ".coo");
    write_coo(filename, sphere);
    free(filename);
 
    write_feff(FEFFINP, feffcoo);

    
    
    printf("\n");
    coords_free(input);
    coords_free(sphere);
    pars_free(pars);
    free(parfile);
    
    return EXIT_SUCCESS;
}
    
/*
        //example of using bstring library to replace fgets()
    FILE fp;
    fp = fopen ( ... );
    fp = NULL;
    if (fp) b = bgets ((bNgetc) fgetc, fp, '\n');
*/