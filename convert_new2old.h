//
//  convert_new2old.h
//  newcoo2old
//
//  Created by Alexander Kompch on 04.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#ifndef __newcoo2old__convert_new2old__
#define __newcoo2old__convert_new2old__

#include <stdio.h>
#include <strings.h>

#include "defs.h"
#include "structs.h"
#include "coords_helper.h"
#include "conversiontable_helper.h"


coords* convert_new2old(coords *given, conv_tbl *cvt);

#endif /* defined(__newcoo2old__convert_new2old__) */
