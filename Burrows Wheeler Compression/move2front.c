//
//  main.c
//  Burrows Wheeler Compression
//
//  Created by Kelvin Zhang on 3/26/17.
//  Copyright © 2017 Kelvin Zhang. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#define N_CHARS 256
#define BUF_SIZE (1024*128)


void encode(FILE *in, FILE *out)
{
    // Simulate a link list
    int next[N_CHARS];
    int head = 0;
    for (int i = 0; i < N_CHARS; i++)
        next[i] = i + 1;
    
    int c = 0;
    while ((c = fgetc(in)) != -1)
    {
        if (c == head)
        {
            fputc(0, out);
        } else
        {
            int index = 1;
            int cur = head;
            while (next[cur] < N_CHARS)
            {
                if (next[cur] == c)
                {
                    fputc(index, out);
                    int tmp = next[cur];
                    // unlink table[cur] from link list
                    next[cur] = next[next[cur]];
                    
                    // move that node to the front of the list
                    next[tmp] = head;
                    head = tmp;
                    break;
                }
                cur = next[cur];
                index++;
            }
        }
    }
}

void decode(FILE *in, FILE *out)
{
    // Simulate a link list, this is the table that stores the next pointers
    int next[N_CHARS];
    // head of the link list
    int head = 0;
    
    // initialize the next pointers
    for (int i = 0; i < N_CHARS; i++)
        next[i] = i + 1;
    
    int c = 0;
    while ((c = fgetc(in)) != -1)
    {
        int index = 0;
        int cur = head;
        int prev = -1;
        while (index != c)
        {
            prev = cur;
            cur = next[cur];
            index++;
        }
        fputc(cur, out);
        
        // Don't do anything if the char is already the head
        if (prev == -1)
            continue;
        
        int tmp = next[prev];
        // unlink table[prev] from link list
        next[prev] = next[tmp];
        
        // move that node to the front of the list
        next[tmp] = head;
        head = tmp;
    }
}

int main(int argc, const char * argv[])
{
    
    return 0;
}
