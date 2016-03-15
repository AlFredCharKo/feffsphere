//
//  main.h
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//


#ifndef feffsphere2_main_h
#define feffsphere2_main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


    //global definitions and structs
#include "structs.h"
#include "defs.h"

    //functions called directly from main
#include "handle_cmdlargs.h"
#include "read_parfile.h"
#include "print_pars.h"
#include "read_newcoo.h"
#include "write_gnuplot.h"
#include "write_pdb.h"

    //helper functions
#include "append_filename.h"


#endif