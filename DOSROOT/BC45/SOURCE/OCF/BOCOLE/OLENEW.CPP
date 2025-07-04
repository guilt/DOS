//
//**************************************************************************
//
// OleNew.cpp -- Remap global operator new to use the current Ole2 allocator
//
// Copyright (c) 1993,94 by Borland International, Inc. All rights reserved
//
//**************************************************************************

#include "BOle.h"
#include <Windows.h>

#include <string.h>
#include <compobj.h>


/*inline*/ void _FAR * OleAlloc (unsigned size) 
{
	void _FAR * p = NULL;
	IMalloc *pMalloc;

#ifndef WIN32
	if (SUCCEEDED(CoGetMalloc (MEMCTX_SHARED, &pMalloc))) {
		p = pMalloc->Alloc (size);
		pMalloc->Release();
	}
	return p;
#else
	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc))) {
		p = pMalloc->Alloc(size); 
		pMalloc->Release();
	}
	return p;
#endif
}

inline BOOL OleFree (void * p) 
{
	IMalloc *pMalloc;

#ifndef WIN32
	if (SUCCEEDED(CoGetMalloc(MEMCTX_SHARED, &pMalloc))) {
		pMalloc->Free(p);
		return TRUE;
	}
	return FALSE;
#else
	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc))) {
		pMalloc->Free(p);
		return TRUE;
	}
	return FALSE;
#endif
}

void _FAR * _cdecl _FARFUNC operator new (unsigned size)
{
	return OleAlloc(size);
}

#ifndef WIN32
void _FAR * _cdecl _FARFUNC operator new (unsigned long size)
{
	return OleAlloc(size);
}
#endif

void _FAR * _cdecl _FARFUNC operator new[] (unsigned size)
{
	return OleAlloc(size);
}

#ifndef WIN32
void _FAR * _cdecl _FARFUNC operator new[] (unsigned long size)
{
	return OleAlloc(size);
}
#endif

void _cdecl _FARFUNC operator delete (void *p)
{
	OleFree(p);
}

void _cdecl _FARFUNC operator delete[] (void *p)
{
	OleFree(p);
}


