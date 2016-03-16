//
//  sortybydistance.c
//  feffsphere2
//
//  Created by Alexander Kompch on 16.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.
//

#include "sortybydistance.h"

int cmpdist(const void *a, const void *b) {
    atom *one = (atom *)a;
    atom *two = (atom *)b;
    
      if (one->dist < two->dist) {
        return -1;
    } else if (one->dist > two->dist) {
        return +1;
    } else {
        return 0;
    }
}
