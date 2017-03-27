//
//  main.c
//  Burrows Wheeler Compression
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/tty.h>
#include "encoder.h"
#include "decoder.h"

void encode(const char *infile, const char *outfile)
{
//    char *infile  = argv[1];
//    char *outfile = argv[2];
    
    int result;
    
    Encoder *encoder = encoder_new(infile, outfile);
    if (encoder == NULL)
    {
        printf("Encoder failed to initialize.");
        exit(1);
    }
    
    result = encoder_encode(encoder);
    if (result == -1)
    {
        printf("Problem occurred during encoding.");
        exit(1);
    }
    
    result = encoder_free(encoder);
    if (result == -1)
    {
        printf("Encoder failed to free properly.");
    }
}

void decode(const char *infile, const char *outfile)
{
    // Get a reference to the input and output files:
//    char *infile  = argv[1];
//    char *outfile = argv[2];
    
    // Create a new decoder:
    Decoder *decoder = decoder_new(infile, outfile);
    if (decoder == NULL)
    {
        printf("decoder was null\n");
        exit(1);
    }
    
    // Decode the file:
    decoder_decode(decoder);
    
    // Free up resources:
    decoder_free(decoder);
}

int main(int argc, const char *argv[])
{
    if(argv[1][0] == '-')
        encode(argv[2], argv[3]);
    else if(argv[1][0] == '+')
        decode(argv[2], argv[3]);
    return 0;
}
