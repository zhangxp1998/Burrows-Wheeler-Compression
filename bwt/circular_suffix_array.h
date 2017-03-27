//
//  circular_suffix_array.h
//  Burrows Wheeler Compression
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#ifndef circular_suffix_array_h
#define circular_suffix_array_h

#include <stdio.h>

typedef struct{
    size_t N;
    const char *data;
    int j;
}CircularSuffix;

CircularSuffix *new_circular_suffix_array(char *str, size_t len);
void free_circular_suffix_array(CircularSuffix *csa);

#endif /* circular_suffix_array_h */
