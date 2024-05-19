
/* a simple spawn() test for DOS-32 */

#include <stdlib.h>
#include <stdio.h>
#include <process.h>

int main(int argc, char * * argv)
{
    int i;

    printf("launching test.com\n");
    fflush(stdout); /* ensure it IS displayed */
    if ((i = spawnl(P_WAIT, ".\\TEST.COM", NULL)) != -1)
        printf("spawn() ok, returncode=%X\n", i);
    else
        printf("spawn() failed, error=%d\n", errno);

    return 0;
}
