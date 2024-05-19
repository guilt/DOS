
/* sample to test various aspects of DJGPP PE */

#include <stdio.h>
#include <stdlib.h>

#define PRINTFTEST 1 /* test printf() */
#define MALLOCTEST 0 /* test malloc() and free() */
#define ARGVTEST   0 /* test argv[] */

int main(int argc, char * argv[])
{
#if PRINTFTEST
    printf("hello, world\n");
#endif

#if ARGVTEST
    {
    int i;
    for (i = 0; i < argc; i++)
        printf("argv[%u]=%s\n", i, argv[i]);
    }
#endif

#if MALLOCTEST
    {
    void * pV[4];
    pV[0] = malloc(0x100000);printf("malloc(0x100000)=%X\n", pV[0]);
    pV[1] = malloc(0x10000) ;printf("malloc(0x10000)=%X\n" , pV[1]);
    pV[2] = malloc(0x100000);printf("malloc(0x100000)=%X\n", pV[2]);
    pV[3] = malloc(0x10000) ;printf("malloc(0x10000)=%X\n" , pV[3]);
    if (pV[0]) free(pV[0]);
    if (pV[1]) free(pV[1]);
    if (pV[2]) free(pV[2]);
    if (pV[3]) free(pV[3]);
    }
#endif

    return 0;

}
