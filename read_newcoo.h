//
//  read_newcoo.h
//  feffsphere2
//
//  Created by Alexander Kompch on 15.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef __feffsphere2__read_newcoo__
#define __feffsphere2__read_newcoo__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "structs.h"
#include "coords_helper.h"
#include "trim.h"

coords* read_newcoo(char *filename);

#endif /* defined(__feffsphere2__read_newcoo__) */
