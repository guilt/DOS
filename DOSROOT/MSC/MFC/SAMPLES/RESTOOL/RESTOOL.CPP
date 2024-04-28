// restool.cpp : Parses RES files, making Foundation-ready header files for
//               all dialogs in it.  This can make it easier to port the
//               dialog code from existing applications, but it is not
//               intended to make writing new dialog code easier or better.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include <afx.h>
#include <afxcoll.h>

#include <windows.h>

#include <fcntl.h>
#include <io.h>
#include <ctype.h>

#include "dlgres.h"

/////////////////////////////////////////////////////////////////////////////

// forward declarations
BOOL GenDialog(const char*, const char*, int, long, BYTE*);

BOOL CheckResFile(int fh, long cbytes)
{
	long lFilesize, lCurloc;
	BYTE ch;
	int iType, inum, n;
	long l;
	BYTE* pBuffer;
	char szDlgName[128];
	char szResourceName[128];

	lFilesize = cbytes;
	lCurloc = 0;
	if (lCurloc == lFilesize)
		return FALSE;
	while (lCurloc < lFilesize)
	{
		n = _read(fh, &ch, 1);
		if (!CheckReadValue(n))
			return FALSE;
		if (ch == 0xFF)
		{
			n = _read(fh, &iType, 2);
			if (!CheckReadValue(n))
				return FALSE;
		}
		else
		{
			while (ch != 0)
			{
				n = _read(fh, &ch, 1);
				if (!CheckReadValue(n))
					return FALSE;
			}
		}
		// read name of resource
		n = _read(fh, &ch, 1);
		if (!CheckReadValue(n))
			return FALSE;

		if (ch == 0xFF)
		{
			// numbered dialog template resource
			n = _read(fh, &inum, 2);
			if (!CheckReadValue(n))
				return FALSE;
			sprintf(szDlgName, "DLG%d", inum);
			sprintf(szResourceName, "MAKEINTRESOURCE(%d)", inum);
		}
		else
		{
			char* psz;
			psz = szDlgName;
			while (ch != 0)
			{
				*psz++ = ch;
				n = _read(fh, &ch, 1);
				if (!CheckReadValue(n))
					return FALSE;
			}
			*psz = 0;
			sprintf(szResourceName, "\"%s\"", szDlgName);
		}
		n = _read(fh, &inum, 2);
		if (!CheckReadValue(n))
			return FALSE;
		n = _read(fh, &l, sizeof(long));
		if (!CheckReadValue(n))
			return FALSE;

		pBuffer = new BYTE[(size_t)l];
		if (!pBuffer)
			return FALSE;

		n = _read(fh, pBuffer, (int)l);

		if (iType == 5)
		{
			// Convert all but first letter of "class name" to lower case.
			//
			{
				char* pch = szDlgName;
				if (*pch)
				{
					*pch = toupper(*pch);
					for (pch++; *pch; pch++)
						*pch = tolower(*pch);
				}
			}

			if (!GenDialog(szDlgName, szResourceName, inum, l, pBuffer))
				return FALSE;
		}

		delete pBuffer;

		if (n != l)
			return FALSE;

		lCurloc = _lseek(fh, 0l, 1);
	}
	if (lCurloc != lFilesize)
		return FALSE;

	return TRUE;
}

int main(int argc, char* argv[])
{
	int fh;
	long lBytes;

	if (argc != 2)
	{
		fprintf(stderr, "restool : usage: restool file.res >file.h\n");
		fprintf(stderr, "           Parses RES files, making Foundation-ready H files for\n");
		fprintf(stderr, "           all dialogs in it.  This can make it easier to port the\n");
		fprintf(stderr, "           dialog code from existing applications.\n");
		fprintf(stderr, "           The output should be redirected into an H file for use.\n");
		exit(1);
	}

	fh = _open(argv[1], O_BINARY);
	if (fh == -1)
	{
		fprintf(stderr, "restool : Cannot open file %s for reading.\n", argv[1]);
		exit(1);
	}
	lBytes = _lseek(fh, 0l, 2);
	_lseek(fh, 0l, 0);

	printf("// restool has generated the following header code from %s\n\n", argv[1]);
	if (!CheckResFile(fh, lBytes))
	{
		fprintf(stderr, "restool : Cannot parse file %s; may be invalid.\n", argv[1]);
		exit(1);
	}
	printf("\n\n// END OF restool code\n");

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Information for control types

struct ControlType
{
	BYTE        code;       // if 0 => end, if 0xFF => match any
	BYTE        style;      // lower 4 bits of style
							//   0xFF => accept any style

	const char* pszClass;   // if NULL use previous
	const char* pszNoun;    // if NULL use previous
	int         nCount;     // significant only if pszNoun != NULL
};

ControlType types[] =
{
	{ BUTTONCODE,   BS_AUTOCHECKBOX,    "CButton",  "Check" },
	{ BUTTONCODE,   BS_CHECKBOX,        NULL,       NULL },
	{ BUTTONCODE,   BS_3STATE,          NULL,       NULL },
	{ BUTTONCODE,   BS_AUTO3STATE,      NULL,       NULL },
	{ BUTTONCODE,   BS_AUTORADIOBUTTON, NULL,       "Option" },
	{ BUTTONCODE,   BS_RADIOBUTTON,     NULL,       NULL },
	{ BUTTONCODE,   BS_GROUPBOX,        NULL,       "Group" },
	{ BUTTONCODE,   BS_PUSHBUTTON,      NULL,       "Button" },
	{ BUTTONCODE,   BS_DEFPUSHBUTTON,   NULL,       NULL },
	{ EDITCODE,     0xFF,               "CEdit",    "Edit" },
	{ STATICCODE,   SS_SIMPLE,          "CStatic",  "Text" },
	{ STATICCODE,   SS_LEFT,            NULL,       NULL },
	{ STATICCODE,   SS_CENTER,          NULL,       NULL },
	{ STATICCODE,   SS_RIGHT,           NULL,       NULL },
	{ STATICCODE,   SS_LEFTNOWORDWRAP,  NULL,       NULL },
	{ STATICCODE,   SS_ICON,            NULL,       "Icon" },
	{ STATICCODE,   SS_BLACKRECT,       NULL,       "Box" },
	{ STATICCODE,   SS_GRAYRECT,        NULL,       NULL },
	{ STATICCODE,   SS_WHITERECT,       NULL,       NULL },
	{ STATICCODE,   SS_BLACKFRAME,      NULL,       NULL },
	{ STATICCODE,   SS_GRAYFRAME,       NULL,       NULL },
	{ STATICCODE,   SS_WHITEFRAME,      NULL,       NULL },
	{ LISTBOXCODE,  0xFF,               "CListBox", "List" },
	{ COMBOBOXCODE, 0xFF,               "CComboBox", "Combo" },
	{ SCROLLBARCODE, 0,                 "CScrollBar", "HScroll" },
	{ SCROLLBARCODE, SBS_VERT,          NULL,       "VScroll" },
	{ 0xFF,         0xFF,               "CWnd",     "Control" },    // 2nd last
	{ 0 }
};

void InitCounts()
{
	for (register ControlType* pType = types; pType->code != 0; pType++)
		if (pType->pszNoun != NULL)
			pType->nCount = 0;
}

// IsLabel:
// Simple logic for determining if an item is really a label.
// Labels do not (usually) need any code, so none is generated.
//
BOOL IsLabel(BYTE code, DLGITEMTEMPLATE* pDit, BYTE nextCode)
{
	if (pDit->id == -1)
		return TRUE;            // may not be real label, but ignore anyway

	if (code == STATICCODE && nextCode != 0)
	{
		// static code with something after it
		if (pDit->style & SS_NOPREFIX)
			return FALSE;   // no accelerator => probably not a label

		switch (pDit->style & 0xf)
		{
		case SS_LEFT: case SS_CENTER: case SS_RIGHT:
		case SS_SIMPLE: case SS_LEFTNOWORDWRAP:
			break;      // keep going
		default:
			return FALSE;
		}

		// lastly, only keep labels if next item is edit or list/combo
		switch (nextCode)
		{
		case EDITCODE: case LISTBOXCODE: case COMBOBOXCODE:
			return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

// ControlInfo:
// Decode control information and place in easy-to-use structure.
//
struct ControlInfo
{
	BYTE code;
	BYTE style;     // lower 4 bits of style

	const char* pszClass;
	CString memberName;         // will be literal text for a label
	UINT id;

	// special values
	BOOL bLabel;                // label not an interactive control
	int nRadioGroup;            // or -1 for none

	ControlInfo()   // structure initialization
	{
		pszClass = NULL;
		id = 0;
		bLabel = FALSE;
		nRadioGroup = -1;
	}
};

struct ControlInfo* DecodeControls(BYTE* pBuffer, BYTE* pEnd, int nCount)
{
	// decode controls in dialog
	CMapStringToPtr usedNames;
	CString lastLabel, lastLabelLiteral;
	lastLabel.GetBuffer(128);       // set a reasonable size
	lastLabelLiteral.GetBuffer(128);    // set a reasonable size

	struct ControlInfo* pAllInfo = new ControlInfo[nCount];
	ASSERT(pAllInfo != NULL);

	for (int iCtl = 0; iCtl < nCount; iCtl++)
	{
		struct ControlInfo* pInfo = &pAllInfo[iCtl];
		DLGITEMTEMPLATE* pDit = (DLGITEMTEMPLATE*)pBuffer;
		pBuffer += sizeof(DLGITEMTEMPLATE);

		BYTE cTokenCode = *pBuffer++;
		char* pszString = (char*)pBuffer;
		pBuffer = SkipString(pBuffer) + 1;

		ASSERT(pBuffer <= pEnd);
		pInfo->code = cTokenCode;
		pInfo->id = pDit->id;
		pInfo->style = (BYTE)(pDit->style&0xf);     // lower 4 bits of style

		if (*pszString != '\0')
		{
			// save it away as a reasonable symbol
			lastLabelLiteral = pszString;       // literal string (for comments)
			lastLabel = "";

			while (*pszString != '\0' && !isalpha(*pszString))
				pszString++;        // skip non-alpha

			// include alpha+numbers for the rest of the name
			while (*pszString != '\0')
			{
				if (isalnum(*pszString))
					lastLabel += *pszString;
				*pszString++;
			}
		}

		BYTE nextCode = 0;
		if (pBuffer + sizeof(DLGITEMTEMPLATE) < pEnd)
			nextCode = *(pBuffer+sizeof(DLGITEMTEMPLATE));

		if (IsLabel(cTokenCode, pDit, nextCode))
		{
			pInfo->bLabel = TRUE;
			pInfo->pszClass = NULL;
			pInfo->memberName = lastLabelLiteral;
			continue;
		}

		const char* pszClass = NULL;
		const char* pszNoun = NULL;
		BOOL bExact = FALSE;
		int* pnIndex = NULL;
		for (register ControlType* pType = types; pType->code != 0; pType++)
		{
			if (pType->code == cTokenCode || pType->code == 0xFF)
			{
				// match raw category
				if (pType->pszClass != NULL)
					pszClass = pType->pszClass;
				ASSERT(pszClass != NULL);
				if (pType->pszNoun != NULL)
				{
					pszNoun = pType->pszNoun;
					pnIndex = &pType->nCount;
				}

				// check for sub-type match
				if (pType->style == 0xFF ||
					((BYTE)pType->style == (BYTE)(pDit->style&0xf)))
				{
					// exact match
					bExact = TRUE;
					break;
				}
			}
		}

		ASSERT(bExact);
		(*pnIndex)++;       // bump count of objects using that noun

		// save remaining info
		pInfo->pszClass = pszClass;
		CString memberName;
		if (!lastLabel.IsEmpty())
		{
			pInfo->memberName = lastLabel;
			pInfo->memberName += pszNoun;
		}
		else
		{
			pInfo->memberName = pszNoun;
			char szT[10];
			pInfo->memberName += _itoa(*pnIndex, szT, 10);
		}

		void* p;
		if (usedNames.Lookup(pInfo->memberName, p))
		{
			// name has already been used in this class
			char szT[10];
			pInfo->memberName += _itoa(*pnIndex, szT, 10);
		}
		usedNames[pInfo->memberName] = "USED";

		lastLabel = "";
		lastLabelLiteral = "";
	}
	ASSERT(pBuffer == pEnd);
	return pAllInfo;        // return array
}

/////////////////////////////////////////////////////////////////////////////
// Print out control info

void PrintControls(const struct ControlInfo * pInfo, int nCount,
		DWORD /* styleDlg */)
{
	for (int iCtl = 0; iCtl < nCount; iCtl++, pInfo++)
	{
		if (pInfo->bLabel)
		{
			printf("\t// label '%s'\n", (const char*)pInfo->memberName);
		}
		else
		{
			// Build normal member type.
			//
			CString typeName = pInfo->pszClass;
			typeName += '&';            // return reference
			if (typeName.GetLength() < 8)
				typeName += '\t';

			// Write out member function definition.
			printf("\t%s %s()\n"
				"\t\t\t{ return *((%s*) GetDlgItem(%d)); } \n",
					(const char*)typeName,
					(const char*)pInfo->memberName,
					pInfo->pszClass, pInfo->id);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

// DetectRadioGroups:
// Special detection for radio groups.
//
void DetectRadioGroups(struct ControlInfo* pInfo, int nCount)
{
	int nRadioGroup = -1;
	UINT idLast = 0;

	for (int iCtl = 0; iCtl < nCount; iCtl++, pInfo++)
	{
		if (pInfo->code == BUTTONCODE &&
			(pInfo->style == BS_AUTORADIOBUTTON ||
			 pInfo->style == BS_RADIOBUTTON))
		{
			if (pInfo->id != idLast+1)
			{
				// start new group
				nRadioGroup = -1;
			}
			pInfo->nRadioGroup = ++nRadioGroup;
				// next in sequence
		}
		else
		{
			nRadioGroup = -1;
		}
		idLast = pInfo->id;
	}
}


/////////////////////////////////////////////////////////////////////////////

// GenDialog:
// Do the actual code-generation work.
//
BOOL GenDialog(const char* pszName, const char* pszResourceName,
	int /* flags */, long l, BYTE* pBuffer)
{
	BYTE* pEnd = &pBuffer[l];

	InitCounts();

	DLGTEMPLATE* pdt = (DLGTEMPLATE*)pBuffer;
	pBuffer += sizeof(DLGTEMPLATE);
	DWORD styleDlg = pdt->style;
	BYTE cdit = pdt->cdit;

	fprintf(stderr, "restool : Generating header for dialog %s.\n", pszName);

	// Make sure there is no menu string...
	if (*pBuffer != '\0')
		fprintf(stderr, "\nrestool : WARNING: Menus in dialogs are not supported.\n");
	pBuffer = SkipString(pBuffer);

	// Make sure only generic window class used

	if (*pBuffer != '\0')
		fprintf(stderr, "\nrestool : WARNING: Only generic window classes are supported.\n");
	pBuffer = SkipString(pBuffer);

	// Deal with caption string...
	char* pszCaption = (char*) pBuffer;
	pBuffer = SkipString(pBuffer);

	// Skip over font data if present
	if (styleDlg & DS_SETFONT)
		pBuffer = SkipString(pBuffer + sizeof(short int));

	// preliminary stuff
	const char* pszBaseClass;

	BOOL bModal = ((styleDlg & (DS_SYSMODAL | DS_MODALFRAME)) != 0);
	pszBaseClass = bModal ? "CModalDialog" : "CDialog";

	printf("///////////////////////////////////////////////////////////\n");
	printf("// class C%s manages the %s dialog resource\n\n", pszName,
		pszResourceName);
	printf("class C%s : public %s\n", pszName, pszBaseClass);
	printf("{\n");
	printf("public:\n");

	// Write the constructor.
	//
	printf("\tC%s(CWnd* pParentWnd = NULL)\n", pszName);
	if (bModal)
	{
		// CModalDialog constructor
		printf("\t\t: %s(%s, pParentWnd)\n", pszBaseClass, pszResourceName);
		printf("\t\t\t{ }\n");
	}
	else
	{
		// CModal dialog constructor + create modeless
		printf("\t\t{\n");
		printf("\t\t\tVERIFY(Create(%s, pParentWnd));\n", pszResourceName);
		printf("\t\t}\n");
	}

	// Write the public member variable declarations.
	//
	printf("\n\t// Attributes\n");
	struct ControlInfo* pAllInfo;
	pAllInfo = DecodeControls(pBuffer, pEnd, cdit);
	DetectRadioGroups(pAllInfo, cdit);
	PrintControls(pAllInfo, cdit, styleDlg);

	// Write the member function declarations.
	printf("\n\t// Operations\n");

	// Write the overriding virtual member function declarations.
	//
	printf("\n\t// Overridables\n");

	// Write the message-map and message-handling member function declarations.
	//
	printf("\n\t// Implementation\n");
	printf("private:\n");
	printf("\tBOOL OnInitDialog();\n");
	printf("\tDECLARE_MESSAGE_MAP()\n");
	printf("};\n\n");
	return TRUE;
}
