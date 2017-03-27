//
//  main.c
//  bwt
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "circular_suffix_array.h"

static const int R = 256;

static int get_first(CircularSuffix *csa, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        if (csa[i].j == 0)
            return i;
    }
    
    return -1;
}

size_t available(FILE *fp)
{
    size_t cur = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size_t end = ftell(fp);
    fseek(fp, cur, SEEK_SET);
    return end - cur;
}

// apply Burrows-Wheeler transform, reading from standard input and writing
// to standard output
static void encode(FILE *in, FILE *out)
{
    const int len = (int)available(in);
    char *buf = malloc(len);
    fread(buf, 1, len, in);
    CircularSuffix *csa = new_circular_suffix_array(buf, len);
    int first = get_first(csa, len);
    
    // Write first to stdout, using big endian
    for (int i = 24; i >= 0; i -= 8)
        fputc((first >> i) & 0xFF, out);
    
    //Write the end of each element in sorted suffix
    for (int i = 0; i < len; i++)
        fputc(buf[(len - 1 + csa[i].j) % len], out);
    
    free(buf);
    free_circular_suffix_array(csa);
}

// apply Burrows-Wheeler inverse transform, reading from standard input and
// writing to standard output
static void decode(FILE *in, FILE *out)
{
    //The first 4 bytes of input stream should be the
    //first index
    int first = 0;
    for(int i = 0; i < 4; i ++)
        first = (first << 8) | (fgetc(in));
    
    const int N = (int)available(in);
    
    //Buffer that holds all transformed data
    char *a = malloc(N);
    fread(a, 1, N, in);
    
    //the next table
    int *next = malloc(N * sizeof(int));
    
    //Apply "LSD Sort", takes O(N) time and O(R) space,
    char *aux = malloc(N);
    int *count = malloc(N+1);
    
    for(int i = 0; i < N; i ++)
        count[a[i]+1]++;
    
    //calculate cumulative
    for(int i = 0; i < R; i ++)
        count[i+1] += count[i];
    
    //move data, but do the same operations to index of elements in the unsorted array.
    //the resulting next stores the next table we want
    for(int i = 0; i < N; i ++)
    {
        char b = a[i];
        aux[count[b]] = b;
        next[count[b]] = i;
        count[b]++;
    }
    
    for(int i = 0; i < N; i++)
    {
        fputc(aux[first], out);
        first = next[first];
    }
    free(count);
    free(aux);
    free(a);
}

int main(int argc, const char * argv[])
{
    if(argv[1][0] == '-')
        encode(stdin, stdout);
    else if(argv[1][0] == '+')
        decode(stdin, stdout);
    return 0;
}
