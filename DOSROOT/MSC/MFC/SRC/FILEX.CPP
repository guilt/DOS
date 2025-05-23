// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "afx.h"

#pragma hdrstop

#include <errno.h>

#ifdef AFX_AUX_SEG
#pragma code_seg(AFX_AUX_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG

// character strings to use for dumping CFileException
static char BASED_CODE szNone[] = "none";
static char BASED_CODE szGeneric[] = "generic";
static char BASED_CODE szFileNotFound[] = "fileNotFound";
static char BASED_CODE szBadPath[] = "badPath";
static char BASED_CODE szTooManyOpenFiles[] = "tooManyOpenFiles";
static char BASED_CODE szAccessDenied[] = "accessDenied";
static char BASED_CODE szInvalidFile[] = "invalidFile";
static char BASED_CODE szRemoveCurrentDir[] = "removeCurrentDir";
static char BASED_CODE szDirectoryFull[] = "directoryFull";
static char BASED_CODE szBadSeek[] = "badSeek";
static char BASED_CODE szHardIO[] = "hardIO";
static char BASED_CODE szSharingViolation[] = "sharingViolation";
static char BASED_CODE szLockViolation[] = "lockViolation";
static char BASED_CODE szDiskFull[] = "diskFull";
static char BASED_CODE szEndOfFile[] = "endOfFile";

static char FAR* BASED_CODE rgszCFileExceptionCause[] =
{
	szNone,
	szGeneric,
	szFileNotFound,
	szBadPath,
	szTooManyOpenFiles,
	szAccessDenied,
	szInvalidFile,
	szRemoveCurrentDir,
	szDirectoryFull,
	szBadSeek,
	szHardIO,
	szSharingViolation,
	szLockViolation,
	szDiskFull,
	szEndOfFile,
};

static char BASED_CODE szUnknown[] = "unknown";
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileException

IMPLEMENT_DYNAMIC(CFileException, CException)

void
CFileException::ThrowOsError(LONG lOsError)
{
	if (lOsError != 0)
		AfxThrowFileException(CFileException::OsErrorToException(lOsError),
			lOsError);
}

void
CFileException::ThrowErrno(int nErrno)
{
	if (nErrno != 0)
		AfxThrowFileException(CFileException::ErrnoToException(nErrno),
			_doserrno);
}


#ifdef _DEBUG
void
CFileException::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << " m_cause = ";

	if (m_cause >= 0 &&
		m_cause < sizeof(rgszCFileExceptionCause) / sizeof(char FAR*))
	{
		dc << rgszCFileExceptionCause[m_cause];
	}
	else
	{
		dc << szUnknown;
	}
	dc << ", lOsError = " << m_lOsError;
}
#endif

void
PASCAL AfxThrowFileException(int cause, LONG lOsError)
{
#ifdef _DEBUG
	TRACE("CFile exception: ");
	if (cause >= 0 &&
		cause < sizeof(rgszCFileExceptionCause) / sizeof(char FAR*))
	{
		afxDump << (char FAR*)rgszCFileExceptionCause[cause];
	}
	else
	{
		afxDump << (char FAR*)szUnknown;
	}
	afxDump << ", OS error information = " << (void FAR*)lOsError << "\n";
#endif
	THROW(new CFileException(cause, lOsError));
}


int
CFileException::ErrnoToException(int nErrno)
{
	switch(nErrno)
	{
		case EPERM:
		case EACCES:
						return CFileException::accessDenied;
		case EBADF:     return CFileException::invalidFile;
		case EDEADLOCK: return CFileException::sharingViolation;
		case EMFILE:    return CFileException::tooManyOpenFiles;
		case ENOENT:
		case ENFILE:
						return CFileException::fileNotFound;
		case ENOSPC:    return CFileException::diskFull;
		case EINVAL:
		case EIO:       return CFileException::hardIO;
		default:
						return CFileException::generic;
	}
}


#ifdef _DOSWIN
int
CFileException::OsErrorToException(LONG lOsErr)
{
	switch ((UINT)lOsErr)
	{
		// DOS Error codes
		case 0x1: return CFileException::generic;
		case 0x2: return CFileException::fileNotFound;
		case 0x3: return CFileException::badPath;
		case 0x4: return CFileException::tooManyOpenFiles;
		case 0x5: return CFileException::accessDenied;
		case 0x6: return CFileException::invalidFile;
		case 0xf: return CFileException::badPath;
		case 0x10: return CFileException::removeCurrentDir;
		case 0x12: return CFileException::directoryFull;
		case 0x19: return CFileException::badSeek;
		case 0x1d: return CFileException::hardIO;
		case 0x1e: return CFileException::hardIO;
		case 0x1f: return CFileException::hardIO;
		case 0x58: return CFileException::hardIO;
		case 0x20: return CFileException::sharingViolation;
		case 0x21: return CFileException::lockViolation;
		case 0x23: return CFileException::tooManyOpenFiles;
		case 0x24: return CFileException::sharingViolation;
		case 0x41: return CFileException::accessDenied;
		case 0x43: return CFileException::fileNotFound;
		case 0x52: return CFileException::accessDenied;
		default: return CFileException::generic;
	}
}
#endif // _WINDOWS



