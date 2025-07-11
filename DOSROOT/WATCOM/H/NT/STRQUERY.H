/*
 *  strquery.h / structuredquery.h  Structured query interfaces
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

#include <rpc.h>
#include <rpcndr.h>
#ifndef COM_NO_WINDOWS_H
    #include <windows.h>
    #include <ole2.h>
#endif

#ifndef __structuredquery_h__
#define __structuredquery_h__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#pragma include_alias( <structuredquerycondition.h>, <strqcond.h> )
#pragma include_alias( <objectarray.h>, <objarray.h> )
#pragma include_alias( <propkeydef.h>, <propkdef.h> )
#include <structuredquerycondition.h>
#include <objectarray.h>
#include <propkeydef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef interface IQuerySolution            IQuerySolution;
typedef interface ISchemaProvider           ISchemaProvider;
typedef interface IEntity                   IEntity;
typedef interface ITokenCollection          ITokenCollection;
typedef interface INamedEntityCollector     INamedEntityCollector;
typedef interface IRelationship             IRelationship;
typedef interface INamedEntity              INamedEntity;
typedef interface ISchemaLocalizerSupport   ISchemaLocalizerSupport;

/* Structured query syntax values */
typedef enum tagSTRUCTURED_QUERY_SYNTAX {
    SQS_NO_SYNTAX               = 0,
    SQS_ADVANCED_QUERY_SYNTAX   = 1,
    SQS_NATURAL_QUERY_SYNTAX    = 2
} STRUCTURED_QUERY_SYNTAX;

/* Structured query single options */
typedef enum tagSTRUCTURED_QUERY_SINGLE_OPTION {
    SQSO_SCHEMA                 = 0,
    SQSO_LOCALE_WORD_BREAKING   = 1,
    SQSO_WORD_BREAKER           = 2,
    SQSO_NATURAL_SYNTAX         = 3,
    SQSO_AUTOMATIC_WILDCARD     = 4,
    SQSO_TRACE_LEVEL            = 5,
    SQSO_LANGUAGE_KEYWORDS      = 6,
    SQSO_SYNTAX                 = 7,
    SQSO_TIME_ZONE              = 8,
    SQSO_IMPLICIT_CONNECTOR     = 9,
    SQSO_CONNECTOR_CASE         = 10
} STRUCTURED_QUERY_SINGLE_OPTION;

/* Structured query multioptions */
typedef enum tagSTRUCTURED_QUERY_MULTIOPTION {
    SQMO_VIRTUAL_PROPERTY   = 0,
    SQMO_DEFAULT_PROPERTY   = 1,
    SQMO_GENERATOR_FOR_TYPE = 2,
    SQMO_MAP_PROPERTY       = 3
} STRUCTURED_QUERY_MULTIOPTION;

/* Structured query parse error */
typedef enum tagSTRUCTURED_QUERY_PARSE_ERROR {
    SQPE_NONE                       = 0,
    SQPE_EXTRA_OPENING_PARENTHESIS  = 1,
    SQPE_EXTRA_CLOSING_PARENTHESIS  = 2,
    SQPE_IGNORED_MODIFIER           = 3,
    SQPE_IGNORED_CONNECTOR          = 4,
    SQPE_IGNORED_KEYWORD            = 5,
    SQPE_UNHANDLED                  = 6
} STRUCTURED_QUERY_PARSE_ERROR;

/* Structured query resolve options */
typedef enum STRUCTURED_QUERY_RESOLVE_OPTION {
    SQRO_DEFAULT                            = 0x00000000,
    SQRO_DONT_RESOLVE_DATETIME              = 0x00000001,
    SQRO_ALWAYS_ONE_INTERVAL                = 0x00000002,
    SQRO_DONT_SIMPLIFY_CONDITION_TREES      = 0x00000004,
    SQRO_DONT_MAP_RELATIONS                 = 0x00000008,
    SQRO_DONT_RESOLVE_RANGES                = 0x00000010,
    SQRO_DONT_REMOVE_UNRESTRICTED_KEYWORDS  = 0x00000020,
    SQRO_DONT_SPLIT_WORDS                   = 0x00000040,
    SQRO_IGNORE_PHRASE_ORDER                = 0x00000080,
    SQRO_ADD_VALUE_TYPE_FOR_PLAIN_VALUES    = 0x00000100,
    SQRO_ADD_ROBUST_ITEM_NAME               = 0x00000200
} STRUCTURED_QUERY_RESOLVE_OPTION;

/* Case requirements */
typedef enum CASE_REQUIREMENT {
    CASE_REQUIREMENT_ANY            = 0,
    CASE_REQUIREMENT_UPPER_IF_AQS   = 1
} CASE_REQUIREMENT;

/* Condition creation options */
typedef enum CONDITION_CREATION_OPTIONS {
    CONDITION_CREATION_DEFAULT              = 0x00000000,
    CONDITION_CREATION_NONE                 = 0x00000000,
    CONDITION_CREATION_SIMPLIFY             = 0x00000001,
    CONDITION_CREATION_VECTOR_AND           = 0x00000002,
    CONDITION_CREATION_VECTOR_OR            = 0x00000004,
    CONDITION_CREATION_VECTOR_LEAF          = 0x00000008,
    CONDITION_CREATION_USE_CONTENT_LOCALE   = 0x00000010
} CONDITION_CREATION_OPTIONS;

/* Interval limit kinds */
typedef enum tagINTERVAL_LIMIT_KIND {
    ILK_EXPLICIT_INCLUDED   = 0,
    ILK_EXPLICIT_EXCLUDED   = 1,
    ILK_NEGATIVE_INFINITY   = 2,
    ILK_POSITIVE_INFINITY   = 3
} INTERVAL_LIMIT_KIND;

/* Query parser manager options */
typedef enum tagQUERY_PARSER_MANAGER_OPTION {
    QPMO_SCHEMA_BINARY_NAME                 = 0,
    QPMO_PRELOCALIZED_SCHEMA_BINARY_PATH    = 1,
    QPMO_UNLOCALIZED_SCHEMA_BINARY_PATH     = 2,
    QPMO_LOCALIZED_SCHEMA_BINARY_PATH       = 3,
    QPMO_APPEND_LCID_TO_LOCALIZED_PATH      = 4,
    QPMO_LOCALIZER_SUPPORT                  = 5
} QUERY_PARSER_MANAGER_OPTION;

/* Named entity certainties */
typedef enum {
    NEC_LOW     = 0,
    NEC_MEDIUM  = 1,
    NEC_HIGH    = 2
} NAMED_ENTITY_CERTAINTY;

/* Hit range */
typedef struct tagHITRANGE {
    ULONG   iPosition;
    ULONG   cLength;
} HITRANGE;

/* IQueryParser interface */
#undef INTERFACE
#define INTERFACE   IQueryParser
DECLARE_INTERFACE_( IQueryParser, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;
    
    /* IQueryParser methods */
    STDMETHOD( Parse )( THIS_ LPCWSTR, IEnumUnknown *, IQuerySolution ** ) PURE;
    STDMETHOD( SetOption )( THIS_ STRUCTURED_QUERY_SINGLE_OPTION, const PROPVARIANT * ) PURE;
    STDMETHOD( GetOption )( THIS_ STRUCTURED_QUERY_SINGLE_OPTION, PROPVARIANT * ) PURE;
    STDMETHOD( SetMultiOption )( THIS_ STRUCTURED_QUERY_MULTIOPTION, LPCWSTR, const PROPVARIANT * ) PURE;
    STDMETHOD( GetSchemaProvider )( THIS_ ISchemaProvider ** ) PURE;
    STDMETHOD( RestateToString )( THIS_ ICondition *, BOOL, LPWSTR * ) PURE;
    STDMETHOD( ParsePropertyValue )( THIS_ LPCWSTR, LPCWSTR, IQuerySolution ** ) PURE;
    STDMETHOD( RestatePropertyValueToString )( THIS_ ICondition *, BOOL, LPWSTR *, LPWSTR * ) PURE;
};

/* IConditionFactory interface */
#undef INTERFACE
#define INTERFACE   IConditionFactory
DECLARE_INTERFACE_( IConditionFactory, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IConditionFactory methods */
    STDMETHOD( MakeNot )( THIS_ ICondition *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeAndOr )( THIS_ CONDITION_TYPE, IEnumUnknown *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeLeaf )( THIS_ LPCWSTR, CONDITION_OPERATION, LPCWSTR, const PROPVARIANT *, IRichChunk *, IRichChunk *, IRichChunk *, BOOL, ICondition ** ) PURE;
    STDMETHOD( Resolve )( THIS_ ICondition *, STRUCTURED_QUERY_RESOLVE_OPTION, const SYSTEMTIME *, ICondition ** ) PURE;
};

/* IConditionFactory2 interface */
#undef INTERFACE
#define INTERFACE   IConditionFactory2
DECLARE_INTERFACE_( IConditionFactory2, IConditionFactory ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IConditionFactory methods */
    STDMETHOD( MakeNot )( THIS_ ICondition *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeAndOr )( THIS_ CONDITION_TYPE, IEnumUnknown *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeLeaf )( THIS_ LPCWSTR, CONDITION_OPERATION, LPCWSTR, const PROPVARIANT *, IRichChunk *, IRichChunk *, IRichChunk *, BOOL, ICondition ** ) PURE;
    STDMETHOD( Resolve )( THIS_ ICondition *, STRUCTURED_QUERY_RESOLVE_OPTION, const SYSTEMTIME *, ICondition ** ) PURE;

    /* IConditionFactory2 methods */
    STDMETHOD( CreateTrueFalse )( THIS_ BOOL, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateNegation )( THIS_ ICondition *, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateCompoundFromObjectArray )( THIS_ CONDITION_TYPE, IObjectArray *, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateCompoundFromArray )( THIS_ CONDITION_TYPE, ICondition **, ULONG, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateStringLeaf )( THIS_ REFPROPERTYKEY, CONDITION_OPERATION, LPCWSTR, LPCWSTR, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateIntegerLeaf )( THIS_ REFPROPERTYKEY, CONDITION_OPERATION, INT32, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateBooleanLeaf )( THIS_ REFPROPERTYKEY, CONDITION_OPERATION, BOOL, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( CreateLeaf )( THIS_ REFPROPERTYKEY, CONDITION_OPERATION, REFPROPVARIANT, LPCWSTR, LPCWSTR, IRichChunk *, IRichChunk *, IRichChunk *, CONDITION_CREATION_OPTIONS, REFIID, void ** ) PURE;
    STDMETHOD( ResolveCondition )( THIS_ ICondition *, STRUCTURED_QUERY_RESOLVE_OPTION, SYSTEMTIME const *, REFIID, void ** ) PURE;
};

/* IQuerySolution interface */
#undef INTERFACE
#define INTERFACE   IQuerySolution
DECLARE_INTERFACE_( IQuerySolution, IConditionFactory ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IConditionFactory methods */
    STDMETHOD( MakeNot )( THIS_ ICondition *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeAndOr )( THIS_ CONDITION_TYPE, IEnumUnknown *, BOOL, ICondition ** ) PURE;
    STDMETHOD( MakeLeaf )( THIS_ LPCWSTR, CONDITION_OPERATION, LPCWSTR, const PROPVARIANT *, IRichChunk *, IRichChunk *, IRichChunk *, BOOL, ICondition ** ) PURE;
    STDMETHOD( Resolve )( THIS_ ICondition *, STRUCTURED_QUERY_RESOLVE_OPTION, const SYSTEMTIME *, ICondition ** ) PURE;

    /* IQuerySolution methods */
    STDMETHOD( GetQuery )( THIS_ ICondition **, IEntity ** ) PURE;
    STDMETHOD( GetErrors )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( GetLexicalData )( THIS_ LPWSTR *, ITokenCollection **, LCID *, IUnknown ** ) PURE;
};

/* IConditionGenerator interface */
#undef INTERFACE
#define INTERFACE   IConditionGenerator
DECLARE_INTERFACE_( IConditionGenerator, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IConditionGenerator methods */
    STDMETHOD( Initialize )( THIS_ ISchemaProvider * ) PURE;
    STDMETHOD( RecognizeNamedEntities )( THIS_ LPCWSTR, LCID, ITokenCollection *, INamedEntityCollector * ) PURE;
    STDMETHOD( GenerateForLeaf )( THIS_ IConditionFactory *, LPCWSTR, CONDITION_OPERATION, LPCWSTR, LPCWSTR, LPCWSTR, IRichChunk *, IRichChunk *, IRichChunk *, BOOL, BOOL *, ICondition ** ) PURE;
    STDMETHOD( DefaultPhrase )( THIS_ LPCWSTR, const PROPVARIANT *, BOOL, LPWSTR * ) PURE;
};

/* IInterval interface */
#undef INTERFACE
#define INTERFACE   IInterval
DECLARE_INTERFACE_( IInterval, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IInterval methods */
    STDMETHOD( GetLimits )( THIS_ INTERVAL_LIMIT_KIND *, PROPVARIANT *, INTERVAL_LIMIT_KIND *, PROPVARIANT * ) PURE;
};

/* IMetaData interface */
#undef INTERFACE
#define INTERFACE   IMetaData
DECLARE_INTERFACE_( IMetaData, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IMetaData methods */
    STDMETHOD( GetData )( THIS_ LPWSTR *, LPWSTR * ) PURE;
};

/* IEntity interface */
#undef INTERFACE
#define INTERFACE   IEntity
DECLARE_INTERFACE_( IEntity, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IEntity methods */
    STDMETHOD( Name )( THIS_ LPWSTR * ) PURE;
    STDMETHOD( Base )( THIS_ IEntity ** ) PURE;
    STDMETHOD( Relationships )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( GetRelationship )( THIS_ LPCWSTR, IRelationship ** ) PURE;
    STDMETHOD( MetaData )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( NamedEntities )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( GetNamedEntity )( THIS_ LPCWSTR, INamedEntity ** ) PURE;
    STDMETHOD( DefaultPhrase )( THIS_ LPWSTR * ) PURE;
};

/* IRelationship interface */
#undef INTERFACE
#define INTERFACE   IRelationship
DECLARE_INTERFACE_( IRelationship, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IRelationship methods */
    STDMETHOD( Name )( THIS_ LPWSTR * ) PURE;
    STDMETHOD( IsReal )( THIS_ BOOL * ) PURE;
    STDMETHOD( Destination )( THIS_ IEntity ** ) PURE;
    STDMETHOD( MetaData )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( DefaultPhrase )( THIS_ LPWSTR * ) PURE;
};

/* INamedEntity interface */
#undef INTERFACE
#define INTERFACE   INamedEntity
DECLARE_INTERFACE_( INamedEntity, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* INamedEntity methods */
    STDMETHOD( GetValue )( THIS_ LPWSTR * ) PURE;
    STDMETHOD( DefaultPhrase )( THIS_ LPWSTR * ) PURE;
};

/* ISchemaProvider interface */
#undef INTERFACE
#define INTERFACE   ISchemaProvider
DECLARE_INTERFACE_( ISchemaProvider, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* ISchemaProvider methods */
    STDMETHOD( Entities )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( RootEntity )( THIS_ IEntity ** ) PURE;
    STDMETHOD( GetEntity )( THIS_ LPCWSTR, IEntity ** ) PURE;
    STDMETHOD( MetaData )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD( Localize )( THIS_ LCID, ISchemaLocalizerSupport * ) PURE;
    STDMETHOD( SaveBinary )( THIS_ LPCWSTR ) PURE;
    STDMETHOD( LookupAuthoredNamedEntity )( THIS_ IEntity *, LPCWSTR, ITokenCollection *, ULONG, ULONG *, LPWSTR * ) PURE;
};

/* ITokenCollection interface */
#undef INTERFACE
#define INTERFACE   ITokenCollection
DECLARE_INTERFACE_( ITokenCollection, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* ITokenCollection methods */
    STDMETHOD( NumberOfTokens )( THIS_ ULONG * ) PURE;
    STDMETHOD( GetToken )( THIS_ ULONG, ULONG *, ULONG *, LPWSTR * ) PURE;
};

/* INamedEntityCollector interface */
#undef INTERFACE
#define INTERFACE   INamedEntityCollector
DECLARE_INTERFACE_( INamedEntityCollector, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* INamedEntityCollector methods */
    STDMETHOD( Add )( THIS_ ULONG, ULONG, ULONG, ULONG, IEntity *, LPCWSTR, NAMED_ENTITY_CERTAINTY ) PURE;
};

/* ISchemaLocalizerSupport interface */
#undef INTERFACE
#define INTERFACE   ISchemaLocalizerSupport
DECLARE_INTERFACE_( ISchemaLocalizerSupport, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* ISchemaLocalizerSupport methods */
    STDMETHOD( Localize )( THIS_ LPCWSTR, LPWSTR * ) PURE;
};

/* IQueryParserManager interface */
#undef INTERFACE
#define INTERFACE   IQueryParserManager
DECLARE_INTERFACE_( IQueryParserManager, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IQueryParserManager methods */
    STDMETHOD( CreateLoadedParser )( THIS_ LPCWSTR, LANGID, REFIID, void ** ) PURE;
    STDMETHOD( InitializeOptions )( THIS_ BOOL, BOOL, IQueryParser * ) PURE;
    STDMETHOD( SetOption )( THIS_ QUERY_PARSER_MANAGER_OPTION, const PROPVARIANT * ) PURE;
};

/* C object macros */
#if (!defined( __cplusplus ) || defined( CINTERFACE )) && defined( COBJMACROS )
    #define IQueryParser_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IQueryParser_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IQueryParser_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IQueryParser_Parse( x, p1, p2, p3 ) \
        (x)->lpVtbl->Parse( x, p1, p2, p3 )
    #define IQueryParser_SetOption( x, p1, p2 ) \
        (x)->lpVtbl->SetOption( x, p1, p2 )
    #define IQueryParser_GetOption( x, p1, p2 ) \
        (x)->lpVtbl->GetOption( x, p1, p2 )
    #define IQueryParser_SetMultiOption( x, p1, p2, p3 ) \
        (x)->lpVtbl->SetMultiOption( x, p1, p2, p3 )
    #define IQueryParser_GetSchemaProvider( x, p ) \
        (x)->lpVtbl->GetSchemaProvider( x, p )
    #define IQueryParser_RestateToString( x, p1, p2, p3 ) \
        (x)->lpVtbl->RestateToString( x, p1, p2, p3 )
    #define IQueryParser_ParsePropertyValue( x, p1, p2, p3 ) \
        (x)->lpVtbl->ParsePropertyValue( x, p1, p2, p3 )
    #define IQueryParser_RestatePropertyValueToString( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->RestatePropertyValueToString( x, p1, p2, p3, p4 )
    #define IConditionFactory_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IConditionFactory_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IConditionFactory_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IConditionFactory_MakeNot( x, p1, p2, p3 ) \
        (x)->lpVtbl->MakeNot( x, p1, p2, p3 )
    #define IConditionFactory_MakeAndOr( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->MakeAndOr( x, p1, p2, p3, p4 )
    #define IConditionFactory_MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) \
        (x)->lpVtbl->MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
    #define IConditionFactory_Resolve( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->Resolve( x, p1, p2, p3, p4 )
    #define IConditionFactory2_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IConditionFactory2_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IConditionFactory2_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IConditionFactory2_MakeNot( x, p1, p2, p3 ) \
        (x)->lpVtbl->MakeNot( x, p1, p2, p3 )
    #define IConditionFactory2_MakeAndOr( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->MakeAndOr( x, p1, p2, p3, p4 )
    #define IConditionFactory2_MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) \
        (x)->lpVtbl->MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
    #define IConditionFactory2_Resolve( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->Resolve( x, p1, p2, p3, p4 )
    #define IConditionFactory2_CreateTrueFalse( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->CreateTrueFalse( x, p1, p2, p3, p4 )
    #define IConditionFactory2_CreateNegation( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->CreateNegation( x, p1, p2, p3, p4 )
    #define IConditionFactory2_CreateCompoundFromObjectArray( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->CreateCompoundFromObjectArray( x, p1, p2, p3, p4, p5 )
    #define IConditionFactory2_CreateCompoundFromArray( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->CreateCompoundFromArray( x, p1, p2, p3, p4, p5, p6 )
    #define IConditionFactory2_CreateStringLeaf( x, p1, p2, p3, p4, p5, p6, p7 ) \
        (x)->lpVtbl->CreateStringLeaf( x, p1, p2, p3, p4, p5, p6, p7 )
    #define IConditionFactory2_CreateIntegerLeaf( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->CreateIntegerLeaf( x, p1, p2, p3, p4, p5, p6 )
    #define IConditionFactory2_CreateBooleanLeaf( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->CreateBooleanLeaf( x, p1, p2, p3, p4, p5, p6 )
    #define IConditionFactory2_CreateLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) \
        (x)->lpVtbl->CreateLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
    #define IQuerySolution_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IQuerySolution_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IQuerySolution_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IQuerySolution_MakeNot( x, p1, p2, p3 ) \
        (x)->lpVtbl->MakeNot( x, p1, p2, p3 )
    #define IQuerySolution_MakeAndOr( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->MakeAndOr( x, p1, p2, p3, p4 )
    #define IQuerySolution_MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) \
        (x)->lpVtbl->MakeLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
    #define IQuerySolution_Resolve( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->Resolve( x, p1, p2, p3, p4 )
    #define IQuerySolution_GetQuery( x, p1, p2 ) \
        (x)->lpVtbl->GetQuery( x, p1, p2 )
    #define IQuerySolution_GetErrors( x, p1, p2 ) \
        (x)->lpVtbl->GetErrors( x, p1, p2 )
    #define IQuerySolution_GetLexicalData( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->GetLexicalData( x, p1, p2, p3, p4 )
    #define IConditionGenerator_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IConditionGenerator_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IConditionGenerator_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IConditionGenerator_Initialize( x, p ) \
        (x)->lpVtbl->Initialize( x, p )
    #define IConditionGenerator_RecognizeNamedEntities( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->RecognizeNamedEntities( x, p1, p2, p3, p4 )
    #define IConditionGenerator_GenerateForLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) \
        (x)->lpVtbl->GenerateForLeaf( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
    #define IConditionGenerator_DefaultPhrase( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->DefaultPhrase( x, p1, p2, p3, p4 )
    #define IInterval_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IInterval_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IInterval_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IInterval_GetLimits( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->GetLimits( x, p1, p2, p3, p4 )
    #define IMetaData_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IMetaData_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IMetaData_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IMetaData_GetData( x, p1, p2 ) \
        (x)->lpVtbl->GetData( x, p1, p2 )
    #define IEntity_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IEntity_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IEntity_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IEntity_Name( x, p ) \
        (x)->lpVtbl->Name( x, p )
    #define IEntity_Base( x, p ) \
        (x)->lpVtbl->Base( x, p )
    #define IEntity_Relationships( x, p1, p2 ) \
        (x)->lpVtbl->Relationships( x, p1, p2 )
    #define IEntity_GetRelationship( x, p1, p2 ) \
        (x)->lpVtbl->GetRelationship( x, p1, p2 )
    #define IEntity_MetaData( x, p1, p2 ) \
        (x)->lpVtbl->MetaData( x, p1, p2 )
    #define IEntity_NamedEntities( x, p1, p2 ) \
        (x)->lpVtbl->NamedEntities( x, p1, p2 )
    #define IEntity_GetNamedEntity( x, p1, p2 ) \
        (x)->lpVtbl->GetNamedEntity( x, p1, p2 )
    #define IEntity_DefaultPhrase( x, p ) \
        (x)->lpVtbl->DefaultPhrase( x, p )
    #define IRelationship_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IRelationship_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IRelationship_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IRelationship_Name( x, p ) \
        (x)->lpVtbl->Name( x, p )
    #define IRelationship_IsReal( x, p ) \
        (x)->lpVtbl->IsReal( x, p )
    #define IRelationship_Destination( x, p ) \
        (x)->lpVtbl->Destination( x, p )
    #define IRelationship_MetaData( x, p1, p2 ) \
        (x)->lpVtbl->MetaData( x, p1, p2 )
    #define IRelationship_DefaultPhrase( x, p ) \
        (x)->lpVtbl->DefaultPhrase( x, p )
    #define INamedEntity_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define INamedEntity_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define INamedEntity_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define INamedEntity_GetValue( x, p ) \
        (x)->lpVtbl->GetValue( x, p )
    #define INamedEntity_DefaultPhrase( x, p ) \
        (x)->lpVtbl->DefaultPhrase( x, p )
    #define ISchemaProvider_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define ISchemaProvider_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define ISchemaProvider_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define ISchemaProvider_Entities( x, p1, p2 ) \
        (x)->lpVtbl->Entities( x, p1, p2 )
    #define ISchemaProvider_RootEntity( x, p ) \
        (x)->lpVtbl->RootEntity( x, p )
    #define ISchemaProvider_GetEntity( x, p1, p2 ) \
        (x)->lpVtbl->GetEntity( x, p1, p2 )
    #define ISchemaProvider_MetaData( x, p1, p2 ) \
        (x)->lpVtbl->MetaData( x, p1, p2 )
    #define ISchemaProvider_Localize( x, p1, p2 ) \
        (x)->lpVtbl->Localize( x, p1, p2 )
    #define ISchemaProvider_SaveBinary( x, p ) \
        (x)->lpVtbl->SaveBinary( x, p )
    #define ISchemaProvider_LookupAuthoredNamedEntity( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->LookupAuthoredNamedEntity( x, p1, p2, p3, p4, p5, p6 )
    #define ITokenCollection_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define ITokenCollection_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define ITokenCollection_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define ITokenCollection_NumberOfTokens( x, p ) \
        (x)->lpVtbl->NumberOfTokens( x, p )
    #define ITokenCollection_GetToken( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->GetToken( x, p1, p2, p3, p4 )
    #define INamedEntityCollector_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define INamedEntityCollector_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define INamedEntityCollector_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define INamedEntityCollector_Add( x, p1, p2, p3, p4, p5, p6, p7 ) \
        (x)->lpVtbl->Add( x, p1, p2, p3, p4, p5, p6, p7 )
    #define ISchemaLocalizerSupport_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define ISchemaLocalizerSupport_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define ISchemaLocalizerSupport_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define ISchemaLocalizerSupport_Localize( x, p1, p2 ) \
        (x)->lpVtbl->Localize( x, p1, p2 )
    #define IQueryParserManager_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IQueryParserManager_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IQueryParserManager_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IQueryParserManager_CreateLoadedParser( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->CreateLoadedParser( x, p1, p2, p3, p4 )
    #define IQueryParserManager_InitializeOptions( x, p1, p2, p3 ) \
        (x)->lpVtbl->InitializeOptions( x, p1, p2, p3 )
    #define IQueryParserManager_SetOption( x, p1, p2 ) \
        (x)->lpVtbl->SetOption( x, p1, p2 )
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* GUIDs */
EXTERN_C const IID      __cdecl IID_IQueryParser;
EXTERN_C const IID      __cdecl IID_IConditionFactory;
EXTERN_C const IID      __cdecl IID_IConditionFactory2;
EXTERN_C const IID      __cdecl IID_IQuerySolution;
EXTERN_C const IID      __cdecl IID_IConditionGenerator;
EXTERN_C const IID      __cdecl IID_IInterval;
EXTERN_C const IID      __cdecl IID_IMetaData;
EXTERN_C const IID      __cdecl IID_IEntity;
EXTERN_C const IID      __cdecl IID_IRelationship;
EXTERN_C const IID      __cdecl IID_INamedEntity;
EXTERN_C const IID      __cdecl IID_ISchemaProvider;
EXTERN_C const IID      __cdecl IID_ITokenCollection;
EXTERN_C const IID      __cdecl IID_INamedEntityCollector;
EXTERN_C const IID      __cdecl IID_ISchemaLocalizerSupport;
EXTERN_C const IID      __cdecl IID_IQueryParserManager;
EXTERN_C const IID      __cdecl LIBID_StructuredQuery1;
EXTERN_C const CLSID    __cdecl CLSID_QueryParser;
EXTERN_C const CLSID    __cdecl CLSID_NegationCondition;
EXTERN_C const CLSID    __cdecl CLSID_CompoundCondition;
EXTERN_C const CLSID    __cdecl CLSID_LeafCondition;
EXTERN_C const CLSID    __cdecl CLSID_ConditionFactory;
EXTERN_C const CLSID    __cdecl CLSID_Interval;
EXTERN_C const CLSID    __cdecl CLSID_QueryParserManager;

#endif /* __structuredquery_h__ */
