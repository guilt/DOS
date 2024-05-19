
// alloc some memory

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define ALLOCTRIES 10

main(int argc, char * * argv)
{
    void * pTmp[ALLOCTRIES];
    char * * ppSz;
    int i;

    for (i = 0;i < argc;i++)
        printf("cmdline parameter: !%s!\n", argv[i]);

    for (i = 0; i < ALLOCTRIES; i++) {
        if (pTmp[i] = malloc(0x80000)) {
            printf("malloc of 512 kB returned %X\n",pTmp[i]);
            memset(pTmp[i], 0x80000,00);
        }
    }
    for (i = 0; i < ALLOCTRIES; i++)
        if (pTmp[i])
            free(pTmp[i]);

    return 0;
}
