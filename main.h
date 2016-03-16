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
#include "cut_sphere.h"
#include "sortybydistance.h"
#include "conversiontable_helper.h"
#include "count_noe.h"
#include "convert_new2old.h"
#include "write_gnuplot.h"
#include "write_pdb.h"
#include "write_feff.h"

    //helper functions
#include "append_filename.h"


#endif
