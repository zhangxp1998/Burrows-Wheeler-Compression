//
//  circular_suffix_array.c
//  Burrows Wheeler Compression
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#include "circular_suffix_array.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define R 256

char charAt(CircularSuffix *s, int d)
{
    assert(d >= 0 && d <= s->N);
    
    if (d == s->N)
        return -1;
    return s->data[(d + s->j) % s->N];
}

void msd_sort(CircularSuffix *a, size_t lo, size_t hi, int d, CircularSuffix *aux)
{
    // cutoff to insertion sort for small subarrays
    if (hi <= lo)
    {
        return;
    }
    
    // compute frequency counts
    int count[R+2] = {0};
//    memset(count, 0, sizeof(count) * sizeof(int));
    for (size_t i = lo; i <= hi; i++)
    {
        int c = charAt(&a[i], d);
        count[c + 2]++;
    }
    
    // transform counts to indicies
    for (int r = 0; r < R + 1; r++)
        count[r + 1] += count[r];
    
    // distribute
    for (size_t i = lo; i <= hi; i++)
    {
        int c = charAt(&a[i], d);
        aux[count[c + 1]++] = a[i];
    }
    
    // copy back
    for (size_t i = lo; i <= hi; i++)
        a[i] = aux[i - lo];
    
    // recursively sort for each character (excludes sentinel -1)
    for (int r = 0; r < R; r++)
        if(count[r+1] > count[r])
            msd_sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    
    
}

static void sort_csa(CircularSuffix *csa, size_t len)
{
    CircularSuffix *aux = malloc(len * sizeof(CircularSuffix));
    msd_sort(csa, 0, len - 1, 0, aux);
//    for (int i = 0; i < len; i++)
//        csa[i] = aux[i];
    
//    memcpy(csa, aux, len * sizeof(CircularSuffix));
    free(aux);
}

CircularSuffix *new_circular_suffix_array(char *str, size_t len)
{
    CircularSuffix *csa = malloc(len * sizeof(CircularSuffix));
    for(int i = 0; i < len; i ++)
    {
        csa[i].data = str;
        csa[i].j = i;
        csa[i].N = (unsigned int)len;
    }
    
    sort_csa(csa, len);
    return csa;
}

void free_circular_suffix_array(CircularSuffix *csa)
{
    free(csa);
}
