
// HX's API for dynamic linking (Win32 compatible)
// intended to be used by DOS-PEs

#ifndef LoadLibrary

typedef int (__stdcall *FARPROC)();

void * __stdcall LoadLibrary(const char *);
int __stdcall FreeLibrary(void *);
FARPROC __stdcall GetProcAddress(void *, char *);

#endif
