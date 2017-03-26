//
//  circular_suffix_array.c
//  Burrows Wheeler Compression
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#include "circular_suffix_array.h"
#include <stdlib.h>

static void sort_csa(CircularSuffix *csa, size_t len)
{
    
}

CircularSuffix *new_circular_suffix_array(char *str, size_t len)
{
    CircularSuffix *csa = malloc(len * sizeof(CircularSuffix));
    for(int i = 0; i < len; i ++)
    {
        csa[i].data = str;
        csa[i].j = i;
    }
    
    sort_csa(csa, len);
    return csa;
}
