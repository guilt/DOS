/*
 * Microsoft Windows Installer database query declarations
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef _MSIQUERY_H_
#define _MSIQUERY_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <msi.h>

#define MSI_NULL_INTEGER 0x80000000

#define MSIDBOPEN_READONLY      (LPCTSTR)0
#define MSIDBOPEN_TRANSACT      (LPCTSTR)1
#define MSIDBOPEN_DIRECT        (LPCTSTR)2
#define MSIDBOPEN_CREATE        (LPCTSTR)3
#define MSIDBOPEN_CREATEDIRECT  (LPCTSTR)4
#define MSIDBOPEN_PATCHFILE     (32/sizeof(*MSIDBOPEN_READONLY))

typedef enum tagMSIDBSTATE {
    MSIDBSTATE_ERROR    = -1,
    MSIDBSTATE_READ     = 0,
    MSIDBSTATE_WRITE    = 1
} MSIDBSTATE;

typedef enum tagMSIMODIFY {
    MSIMODIFY_SEEK              = -1,
    MSIMODIFY_REFRESH           = 0,
    MSIMODIFY_INSERT            = 1,
    MSIMODIFY_UPDATE            = 2,
    MSIMODIFY_ASSIGN            = 3,
    MSIMODIFY_REPLACE           = 4,
    MSIMODIFY_MERGE             = 5,
    MSIMODIFY_DELETE            = 6,
    MSIMODIFY_INSERT_TEMPORARY  = 7,
    MSIMODIFY_VALIDATE          = 8,
    MSIMODIFY_VALIDATE_NEW      = 9,
    MSIMODIFY_VALIDATE_FIELD    = 10,
    MSIMODIFY_VALIDATE_DELETE   = 11
} MSIMODIFY;

typedef enum tagMSICOLINFO {
    MSICOLINFO_NAMES    = 0,
    MSICOLINFO_TYPES    = 1
} MSICOLINFO;

typedef enum tagMSICONDITION {
    MSICONDITION_FALSE  = 0,
    MSICONDITION_TRUE   = 1,
    MSICONDITION_NONE   = 2,
    MSICONDITION_ERROR  = 3
} MSICONDITION;

typedef enum tagMSICOSTTREE {
    MSICOSTTREE_SELFONLY    = 0,
    MSICOSTTREE_CHILDREN    = 1,
    MSICOSTTREE_PARENTS     = 2,
    MSICOSTTREE_RESERVED    = 3
} MSICOSTTREE;

typedef enum tagMSIDBERROR {
    MSIDBERROR_INVALIDARG       = -3,
    MSIDBERROR_MOREDATA         = -2,
    MSIDBERROR_FUNCTIONERROR    = -1,
    MSIDBERROR_NOERROR          = 0,
    MSIDBERROR_DUPLICATEKEY     = 1,
    MSIDBERROR_REQUIRED         = 2,
    MSIDBERROR_BADLINK          = 3,
    MSIDBERROR_OVERFLOW         = 4,
    MSIDBERROR_UNDERFLOW        = 5,
    MSIDBERROR_NOTINSET         = 6,
    MSIDBERROR_BADVERSION       = 7,
    MSIDBERROR_BADCASE          = 8,
    MSIDBERROR_BADGUID          = 9,
    MSIDBERROR_BADWILDCARD      = 10,
    MSIDBERROR_BADIDENTIFIER    = 11,
    MSIDBERROR_BADLANGUAGE      = 12,
    MSIDBERROR_BADFILENAME      = 13,
    MSIDBERROR_BADPATH          = 14,
    MSIDBERROR_BADCONDITION     = 15,
    MSIDBERROR_BADFORMATTED     = 16,
    MSIDBERROR_BADTEMPLATE      = 17,
    MSIDBERROR_BADDEFAULTDIR    = 18,
    MSIDBERROR_BADREGPATH       = 19,
    MSIDBERROR_BADCUSTOMSOURCE  = 20,
    MSIDBERROR_BADPROPERTY      = 21,
    MSIDBERROR_MISSINGDATA      = 22,
    MSIDBERROR_BADCATEGORY      = 23,
    MSIDBERROR_BADKEYTABLE      = 24,
    MSIDBERROR_BADMAXMINVALUES  = 25,
    MSIDBERROR_BADCABINET       = 26,
    MSIDBERROR_BADSHORTCUT      = 27,
    MSIDBERROR_STRINGOVERFLOW   = 28,
    MSIDBERROR_BADLOCALIZEATTRIB = 29
} MSIDBERROR;

typedef enum tagMSIRUNMODE {
    MSIRUNMODE_ADMIN            = 0,
    MSIRUNMODE_ADVERTISE        = 1,
    MSIRUNMODE_MAINTENANCE      = 2,
    MSIRUNMODE_ROLLBACKENABLED  = 3,
    MSIRUNMODE_LOGENABLED       = 4,
    MSIRUNMODE_OPERATIONS       = 5,
    MSIRUNMODE_REBOOTATEND      = 6,
    MSIRUNMODE_REBOOTNOW        = 7,
    MSIRUNMODE_CABINET          = 8,
    MSIRUNMODE_SOURCESHORTNAMES = 9,
    MSIRUNMODE_TARGETSHORTNAMES = 10,
    MSIRUNMODE_WINDOWS9X        = 12,
    MSIRUNMODE_ZAWENABLED       = 13,
    MSIRUNMODE_SCHEDULED        = 16,
    MSIRUNMODE_ROLLBACK         = 17,
    MSIRUNMODE_COMMIT           = 18
} MSIRUNMODE;

#define INSTALLMESSAGE_TYPEMASK 0xFF000000L

typedef enum tagMSITRANSFORM_ERROR {
    MSITRANSFORM_ERROR_ADDEXISTINGROW   = 0x00000001,
    MSITRANSFORM_ERROR_DELMISSINGROW    = 0x00000002,
    MSITRANSFORM_ERROR_ADDEXISTINGTABLE = 0x00000004,
    MSITRANSFORM_ERROR_DELMISSINGTABLE  = 0x00000008,
    MSITRANSFORM_ERROR_UPDATEMISSINGROW = 0x00000010,
    MSITRANSFORM_ERROR_CHANGECODEPAGE   = 0x00000020,
    MSITRANSFORM_ERROR_VIEWTRANSFORM    = 0x00000100
} MSITRANSFORM_ERROR;

typedef enum tagMSITRANSFORM_VALIDATE {
    MSITRANSFORM_VALIDATE_LANGUAGE                  = 0x00000001,
    MSITRANSFORM_VALIDATE_PRODUCT                   = 0x00000002,
    MSITRANSFORM_VALIDATE_PLATFORM                  = 0x00000004,
    MSITRANSFORM_VALIDATE_MAJORVERSION              = 0x00000008,
    MSITRANSFORM_VALIDATE_MINORVERSION              = 0x00000010,
    MSITRANSFORM_VALIDATE_UPDATEVERSION             = 0x00000020,
    MSITRANSFORM_VALIDATE_NEWLESSBASEVERSION        = 0x00000040,
    MSITRANSFORM_VALIDATE_NEWLESSEQUALBASEVERSION   = 0x00000080,
    MSITRANSFORM_VALIDATE_NEWEQUALBASEVERSION       = 0x00000100,
    MSITRANSFORM_VALIDATE_NEWGREATEREQUALBASEVERSION = 0x00000200,
    MSITRANSFORM_VALIDATE_NEWGREATERBASEVERSION     = 0x00000400,
    MSITRANSFORM_VALIDATE_UPGRADECODE               = 0x00000800
} MSITRANSFORM_VALIDATE;

#ifdef __cplusplus
extern "C" {
#endif

UINT WINAPI             MsiDatabaseOpenViewA(MSIHANDLE, LPCSTR, MSIHANDLE *);
UINT WINAPI             MsiDatabaseOpenViewW(MSIHANDLE, LPCWSTR, MSIHANDLE *);
MSIDBERROR WINAPI       MsiViewGetErrorA(MSIHANDLE, LPSTR, DWORD *);
MSIDBERROR WINAPI       MsiViewGetErrorW(MSIHANDLE, LPWSTR, DWORD *);
UINT WINAPI             MsiViewExecute(MSIHANDLE, MSIHANDLE);
UINT WINAPI             MsiViewFetch(MSIHANDLE, MSIHANDLE *);
UINT WINAPI             MsiViewModify(MSIHANDLE, MSIMODIFY, MSIHANDLE);
UINT WINAPI             MsiViewGetColumnInfo(MSIHANDLE, MSICOLINFO, MSIHANDLE *);
UINT WINAPI             MsiViewClose(MSIHANDLE);
UINT WINAPI             MsiDatabaseGetPrimaryKeysA(MSIHANDLE, LPCSTR, MSIHANDLE *);
UINT WINAPI             MsiDatabaseGetPrimaryKeysW(MSIHANDLE, LPCWSTR, MSIHANDLE *);
MSICONDITION WINAPI     MsiDatabaseIsTablePersistentA(MSIHANDLE, LPCSTR);
MSICONDITION WINAPI     MsiDatabaseIsTablePersistentW(MSIHANDLE, LPCWSTR);
UINT WINAPI             MsiGetSummaryInformationA(MSIHANDLE, LPCSTR, UINT, MSIHANDLE *);
UINT WINAPI             MsiGetSummaryInformationW(MSIHANDLE, LPCWSTR, UINT, MSIHANDLE *);
UINT WINAPI             MsiSummaryInfoGetPropertyCount(MSIHANDLE, UINT *);
UINT WINAPI             MsiSummaryInfoSetPropertyA(MSIHANDLE, UINT, UINT, INT, FILETIME *, LPCSTR);
UINT WINAPI             MsiSummaryInfoSetPropertyW(MSIHANDLE, UINT, UINT, INT, FILETIME *, LPCWSTR);
UINT WINAPI             MsiSummaryInfoGetPropertyA(MSIHANDLE, UINT, UINT *, INT *, FILETIME *, LPSTR, DWORD *);
UINT WINAPI             MsiSummaryInfoGetPropertyW(MSIHANDLE, UINT, UINT *, INT *, FILETIME *, LPWSTR, DWORD *);
UINT WINAPI             MsiSummaryInfoPersist(MSIHANDLE);
UINT WINAPI             MsiOpenDatabaseA(LPCSTR, LPCSTR, MSIHANDLE *);
UINT WINAPI             MsiOpenDatabaseW(LPCWSTR, LPCWSTR, MSIHANDLE *);
UINT WINAPI             MsiDatabaseImportA(MSIHANDLE, LPCSTR, LPCSTR);
UINT WINAPI             MsiDatabaseImportW(MSIHANDLE, LPCWSTR, LPCWSTR);
UINT WINAPI             MsiDatabaseExportA(MSIHANDLE, LPCSTR, LPCSTR, LPCSTR);
UINT WINAPI             MsiDatabaseExportW(MSIHANDLE, LPCWSTR, LPCWSTR, LPCWSTR);
UINT WINAPI             MsiDatabaseMergeA(MSIHANDLE, MSIHANDLE, LPCSTR);
UINT WINAPI             MsiDatabaseMergeW(MSIHANDLE, MSIHANDLE, LPCWSTR);
UINT WINAPI             MsiDatabaseGenerateTransformA(MSIHANDLE, MSIHANDLE, LPCSTR, int, int);
UINT WINAPI             MsiDatabaseGenerateTransformW(MSIHANDLE, MSIHANDLE, LPCWSTR, int, int);
UINT WINAPI             MsiDatabaseApplyTransformA(MSIHANDLE, LPCSTR, int);
UINT WINAPI             MsiDatabaseApplyTransformW(MSIHANDLE, LPCWSTR, int);
UINT WINAPI             MsiCreateTransformSummaryInfoA(MSIHANDLE, MSIHANDLE, LPCSTR, int, int);
UINT WINAPI             MsiCreateTransformSummaryInfoW(MSIHANDLE, MSIHANDLE, LPCWSTR, int, int);
UINT WINAPI             MsiDatabaseCommit(MSIHANDLE);
MSIDBSTATE WINAPI       MsiGetDatabaseState(MSIHANDLE);
MSIHANDLE WINAPI        MsiCreateRecord(UINT);
BOOL WINAPI             MsiRecordIsNull(MSIHANDLE, UINT);
UINT WINAPI             MsiRecordDataSize(MSIHANDLE, UINT);
UINT WINAPI             MsiRecordSetInteger(MSIHANDLE, UINT, int);
int WINAPI              MsiRecordGetInteger(MSIHANDLE, UINT);
UINT WINAPI             MsiRecordGetFieldCount(MSIHANDLE);
UINT WINAPI             MsiRecordReadStream(MSIHANDLE, UINT, char *, DWORD *);
UINT WINAPI             MsiRecordClearData(MSIHANDLE);
MSIHANDLE WINAPI        MsiGetActiveDatabase(MSIHANDLE);
LANGID WINAPI           MsiGetLanguage(MSIHANDLE);
BOOL WINAPI             MsiGetMode(MSIHANDLE, MSIRUNMODE);
UINT WINAPI             MsiSetMode(MSIHANDLE, MSIRUNMODE, BOOL);
int WINAPI              MsiProcessMessage(MSIHANDLE, INSTALLMESSAGE, MSIHANDLE);
UINT WINAPI             MsiRecordSetStringA(MSIHANDLE, UINT, LPCSTR);
UINT WINAPI             MsiRecordSetStringW(MSIHANDLE, UINT, LPCWSTR);
UINT WINAPI             MsiRecordGetStringA(MSIHANDLE, UINT, LPSTR, DWORD *);
UINT WINAPI             MsiRecordGetStringW(MSIHANDLE, UINT, LPWSTR, DWORD *);
UINT WINAPI             MsiRecordSetStreamA(MSIHANDLE, UINT, LPCSTR);
UINT WINAPI             MsiRecordSetStreamW(MSIHANDLE, UINT, LPCWSTR);
UINT WINAPI             MsiSetPropertyA(MSIHANDLE, LPCSTR, LPCSTR);
UINT WINAPI             MsiSetPropertyW(MSIHANDLE, LPCWSTR, LPCWSTR);
UINT WINAPI             MsiGetPropertyA(MSIHANDLE, LPCSTR, LPSTR, DWORD *);
UINT WINAPI             MsiGetPropertyW(MSIHANDLE, LPCWSTR, LPWSTR, DWORD *);
UINT WINAPI             MsiFormatRecordA(MSIHANDLE, MSIHANDLE, LPSTR, DWORD *);
UINT WINAPI             MsiFormatRecordW(MSIHANDLE, MSIHANDLE, LPWSTR, DWORD *);
UINT WINAPI             MsiDoActionA(MSIHANDLE, LPCSTR);
UINT WINAPI             MsiDoActionW(MSIHANDLE, LPCWSTR);
UINT WINAPI             MsiSequenceA(MSIHANDLE, LPCSTR, INT);
UINT WINAPI             MsiSequenceW(MSIHANDLE, LPCWSTR, INT);
MSICONDITION WINAPI     MsiEvaluateConditionA(MSIHANDLE, LPCSTR);
MSICONDITION WINAPI     MsiEvaluateConditionW(MSIHANDLE, LPCWSTR);
UINT WINAPI             MsiGetFeatureStateA(MSIHANDLE, LPCSTR, INSTALLSTATE *, INSTALLSTATE *);
UINT WINAPI             MsiGetFeatureStateW(MSIHANDLE, LPCWSTR, INSTALLSTATE *, INSTALLSTATE *);
UINT WINAPI             MsiSetFeatureStateA(MSIHANDLE, LPCSTR, INSTALLSTATE);
UINT WINAPI             MsiSetFeatureStateW(MSIHANDLE, LPCWSTR, INSTALLSTATE);
UINT WINAPI             MsiGetComponentStateA(MSIHANDLE, LPCSTR, INSTALLSTATE *, INSTALLSTATE *);
UINT WINAPI             MsiGetComponentStateW(MSIHANDLE, LPCWSTR, INSTALLSTATE *, INSTALLSTATE *);
UINT WINAPI             MsiSetComponentStateA(MSIHANDLE, LPCSTR, INSTALLSTATE);
UINT WINAPI             MsiSetComponentStateW(MSIHANDLE, LPCWSTR, INSTALLSTATE);
UINT WINAPI             MsiGetFeatureCostA(MSIHANDLE, LPCSTR, MSICOSTTREE, INSTALLSTATE, INT *);
UINT WINAPI             MsiGetFeatureCostW(MSIHANDLE, LPCWSTR, MSICOSTTREE, INSTALLSTATE, INT *);
UINT WINAPI             MsiSetInstallLevel(MSIHANDLE, int);
UINT WINAPI             MsiVerifyDiskSpace(MSIHANDLE);
UINT WINAPI             MsiEnableUIPreview(MSIHANDLE, MSIHANDLE *);
MSIHANDLE WINAPI        MsiGetLastErrorRecord();
UINT WINAPI             MsiGetFeatureValidStatesA(MSIHANDLE, LPCSTR, DWORD *);
UINT WINAPI             MsiGetFeatureValidStatesW(MSIHANDLE, LPCWSTR, DWORD *);
UINT WINAPI             MsiGetSourcePathA(MSIHANDLE, LPCSTR, LPSTR, DWORD *);
UINT WINAPI             MsiGetSourcePathW(MSIHANDLE, LPCWSTR, LPWSTR, DWORD *);
UINT WINAPI             MsiGetTargetPathA(MSIHANDLE, LPCSTR, LPSTR, DWORD *);
UINT WINAPI             MsiGetTargetPathW(MSIHANDLE, LPCWSTR, LPWSTR, DWORD *);
UINT WINAPI             MsiSetTargetPathA(MSIHANDLE, LPCSTR, LPCSTR);
UINT WINAPI             MsiSetTargetPathW(MSIHANDLE, LPCWSTR, LPCWSTR);
UINT WINAPI             MsiPreviewDialogA(MSIHANDLE, LPCSTR);
UINT WINAPI             MsiPreviewDialogW(MSIHANDLE, LPCWSTR);
UINT WINAPI             MsiPreviewBillboardA(MSIHANDLE, LPCSTR, LPCSTR);
UINT WINAPI             MsiPreviewBillboardW(MSIHANDLE, LPCWSTR, LPCWSTR);

#if (_WIN32_MSI >= 110)
UINT WINAPI             MsiSetFeatureAttributesA(MSIHANDLE, LPCSTR, DWORD);
UINT WINAPI             MsiSetFeatureAttributesW(MSIHANDLE, LPCWSTR, DWORD);
#endif

#if (_WIN32_MSI >= 150)
UINT WINAPI             MsiEnumComponentCostsA(MSIHANDLE, LPCSTR, DWORD, INSTALLSTATE, LPSTR, DWORD *, INT *, INT *);
UINT WINAPI             MsiEnumComponentCostsW(MSIHANDLE, LPCWSTR, DWORD, INSTALLSTATE, LPWSTR, DWORD *, INT *, INT *);
#endif

#ifdef UNICODE
    #define MsiDatabaseOpenView             MsiDatabaseOpenViewW
    #define MsiViewGetError                 MsiViewGetErrorW
    #define MsiDatabaseGetPrimaryKeys       MsiDatabaseGetPrimaryKeysW
    #define MsiDatabaseIsTablePersistent    MsiDatabaseIsTablePersistentW
    #define MsiGetSummaryInformation        MsiGetSummaryInformationW
    #define MsiSummaryInfoSetProperty       MsiSummaryInfoSetPropertyW
    #define MsiSummaryInfoGetProperty       MsiSummaryInfoGetPropertyW
    #define MsiOpenDatabase                 MsiOpenDatabaseW
    #define MsiDatabaseImport               MsiDatabaseImportW
    #define MsiDatabaseExport               MsiDatabaseExportW
    #define MsiDatabaseMerge                MsiDatabaseMergeW
    #define MsiDatabaseGenerateTransform    MsiDatabaseGenerateTransformW
    #define MsiDatabaseApplyTransform       MsiDatabaseApplyTransformW
    #define MsiCreateTransformSummaryInfo   MsiCreateTransformSummaryInfoW
    #define MsiRecordSetString              MsiRecordSetStringW
    #define MsiRecordGetString              MsiRecordGetStringW
    #define MsiRecordSetStream              MsiRecordSetStreamW
    #define MsiSetProperty                  MsiSetPropertyW
    #define MsiGetProperty                  MsiGetPropertyW
    #define MsiFormatRecord                 MsiFormatRecordW
    #define MsiDoAction                     MsiDoActionW
    #define MsiSequence                     MsiSequenceW
    #define MsiEvaluateCondition            MsiEvaluateConditionW
    #define MsiGetFeatureState              MsiGetFeatureStateW
    #define MsiSetFeatureState              MsiSetFeatureStateW
    #define MsiGetComponentState            MsiGetComponentStateW
    #define MsiSetComponentState            MsiSetComponentStateW
    #define MsiGetFeatureCost               MsiGetFeatureCostW
    #define MsiGetFeatureValidStates        MsiGetFeatureValidStatesW
    #define MsiGetSourcePath                MsiGetSourcePathW
    #define MsiGetTargetPath                MsiGetTargetPathW
    #define MsiSetTargetPath                MsiSetTargetPathW
    #define MsiPreviewDialog                MsiPreviewDialogW
    #define MsiPreviewBillboard             MsiPreviewBillboardW
#if (_WIN32_MSI >= 110)    
    #define MsiSetFeatureAttributes         MsiSetFeatureAttributesW
#endif
#if (_WIN32_MSI >= 150)
    #define MsiEnumComponentCosts           MsiEnumComponentCostsW
#endif
#else
    #define MsiDatabaseOpenView             MsiDatabaseOpenViewA
    #define MsiViewGetError                 MsiViewGetErrorA
    #define MsiDatabaseGetPrimaryKeys       MsiDatabaseGetPrimaryKeysA
    #define MsiDatabaseIsTablePersistent    MsiDatabaseIsTablePersistentA
    #define MsiGetSummaryInformation        MsiGetSummaryInformationA
    #define MsiSummaryInfoSetProperty       MsiSummaryInfoSetPropertyA
    #define MsiSummaryInfoGetProperty       MsiSummaryInfoGetPropertyA
    #define MsiOpenDatabase                 MsiOpenDatabaseA
    #define MsiDatabaseImport               MsiDatabaseImportA
    #define MsiDatabaseExport               MsiDatabaseExportA
    #define MsiDatabaseMerge                MsiDatabaseMergeA
    #define MsiDatabaseGenerateTransform    MsiDatabaseGenerateTransformA
    #define MsiDatabaseApplyTransform       MsiDatabaseApplyTransformA
    #define MsiCreateTransformSummaryInfo   MsiCreateTransformSummaryInfoA
    #define MsiRecordSetString              MsiRecordSetStringA
    #define MsiRecordGetString              MsiRecordGetStringA
    #define MsiRecordSetStream              MsiRecordSetStreamA
    #define MsiSetProperty                  MsiSetPropertyA
    #define MsiGetProperty                  MsiGetPropertyA
    #define MsiFormatRecord                 MsiFormatRecordA
    #define MsiDoAction                     MsiDoActionA
    #define MsiSequence                     MsiSequenceA
    #define MsiEvaluateCondition            MsiEvaluateConditionA
    #define MsiGetFeatureState              MsiGetFeatureStateA
    #define MsiSetFeatureState              MsiSetFeatureStateA
    #define MsiGetComponentState            MsiGetComponentStateA
    #define MsiSetComponentState            MsiSetComponentStateA
    #define MsiGetFeatureCost               MsiGetFeatureCostA
    #define MsiGetFeatureValidStates        MsiGetFeatureValidStatesA
    #define MsiGetSourcePath                MsiGetSourcePathA
    #define MsiGetTargetPath                MsiGetTargetPathA
    #define MsiSetTargetPath                MsiSetTargetPathA
    #define MsiPreviewDialog                MsiPreviewDialogA
    #define MsiPreviewBillboard             MsiPreviewBillboardA
#if (_WIN32_MSI >= 110)    
    #define MsiSetFeatureAttributes         MsiSetFeatureAttributesA
#endif
#if (_WIN32_MSI >= 150)
    #define MsiEnumComponentCosts           MsiEnumComponentCostsA
#endif
#endif /* UNICODE */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MSIQUERY_H_ */
