
// calling HX's DOS API for dlls (without using the KERNEL32 emulation)
// this is intended to be used by DOS-PE binaries. The API is installed
// by DPMILD32.EXE.

unsigned int _stdcall LoadLibrary(char * pszModule)
{
    unsigned int hModule = 0;
    _asm {
            push es
            xor ebx,ebx
            mov es, ebx
            mov edx, pszModule
            mov ax,0x4b00
            int 0x21
            pop es
            mov hModule, eax
    };
    return hModule;
}
void * _stdcall GetProcAddress(unsigned int hModule, char * pszProcName)
{
    void * rc = 0;
    _asm {
            mov ebx, hModule
            mov edx, pszProcName
            mov ax,0x4b81
            int 0x21
            mov rc, eax
    };
    return rc;
}
unsigned int _stdcall FreeLibrary(unsigned int hModule)
{
    unsigned int rc = 0;
    _asm {
            mov ebx, hModule
            mov ax,0x4b80
            int 0x21
            mov rc,1
    };
    return rc;
}
