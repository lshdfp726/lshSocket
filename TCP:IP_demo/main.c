#include <stdio.h>
#include <stdlib.h>
#include "lshSocket.h"


int main(int argc, char const *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "useage: %s <hex number>\n",argv[0]);
        exit(0);
    }

    lsh_nslookup((char *)argv[1]);
    return 0;
}