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
    const char *data;
    int j;
}CircularSuffix;

CircularSuffix *new_circular_suffix_array(char *str, size_t len);

#endif /* circular_suffix_array_h */
