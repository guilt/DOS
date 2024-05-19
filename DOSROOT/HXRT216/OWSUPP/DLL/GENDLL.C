
// a win32 dll for testing with OW

#include <windows.h>
#include <stdio.h>

int __declspec(dllexport) __stdcall DllFunction1(int i)
{
    printf("DllFunction1(%X) called\n", i);
    return 1;
}

int __declspec(dllexport) __stdcall DllFunction2(int i)
{
    printf("DllFunction2(%X) called\n", i);
    return 1;
}

int __stdcall LibMain(int hModule, int dwReason, LPVOID dwReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
        printf("process attached\n");
    else
        if (dwReason == DLL_PROCESS_DETACH)
            printf("process detached\n");

    return 1;
}
