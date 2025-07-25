/*
 *  basemid.h   OS/2 Base Message IDs.
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

#ifndef __BASEMID__
#define __BASEMID__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MSG_RESPONSE_DATA               0
#define MSG_INVALID_FUNCTION            1
#define MSG_FILE_NOT_FOUND              2
#define MSG_PATH_NOT_FOUND              3
#define MSG_OUT_OF_HANDLES              4
#define MSG_ACCESS_DENIED               5
#define MSG_INVALID_HANDLE              6
#define MSG_MEMORY_BLOCKS_BAD           7
#define MSG_NO_MEMORY                   8
#define MSG_INVALID_MEM_ADDR            9
#define MSG_INVALID_ENVIRON             10
#define MSG_INVALID_FORMAT              11
#define MSG_INVALID_ACC_CODE            12
#define MSG_INVALID_DATA                13
#define MSG_INVALID_DRIVE               15
#define MSG_ATT_RD_CURDIR               16
#define MSG_NOT_SAME_DEVICE             17
#define MSG_NO_MORE_FILES               18
#define MSG_ATT_WRITE_PROT              19
#define MSG_UNKNOWN_UNIT                20
#define MSG_DRIVE_NOT_READY             21
#define MSG_UNKNOWN_COMMAND             22
#define MSG_DATA_ERROR                  23
#define MSG_BAD_REQ_STRUCTURE           24
#define MSG_SEEK_ERROR                  25
#define MSG_UNKNOWN_MEDIA               26
#define MSG_SECTOR_NOT_FOUND            27
#define MSG_OUT_OF_PAPER                28
#define MSG_WRITE_FAULT                 29
#define MSG_READ_FAULT                  30
#define MSG_GENERAL_FAILURE             31
#define MSG_SHARING_VIOLATION           32
#define MSG_SHAR_VIOLAT_FIND            32
#define MSG_LOCK_VIOLATION              33
#define MSG_INVALID_DISK_CHANGE         34
#define MSG_35                          35
#define MSG_SHARING_BUFF_OFLOW          36
#define MSG_ERROR_WRITE_PROTECT         37
#define MSG_ERROR_BAD_UNIT              38
#define MSG_ERROR_NOT_READY             39
#define MSG_ERROR_BAD_COMMAND           40
#define MSG_ERROR_CRC                   41
#define MSG_ERROR_BAD_LENGTH            42
#define MSG_ERROR_SEEK                  43
#define MSG_ERROR_NOT_DOS_DISK          44
#define MSG_ERROR_SECTOR_NOT_FOUND      45
#define MSG_ERROR_OUT_OF_PAPER          46
#define MSG_ERROR_WRITE_FAULT           47
#define MSG_ERROR_READ_FAULT            48
#define MSG_ERROR_GEN_FAILURE           49
#define MSG_NET_REQ_NOT_SUPPORT         50
#define MSG_NET_REMOTE_NOT_ONLINE       51
#define MSG_NET_DUP_FILENAME            52
#define MSG_NET_PATH_NOT_FOUND          53
#define MSG_NET_BUSY                    54
#define MSG_NET_DEV_NOT_INSTALLED       55
#define MSG_NET_BIOS_LIMIT_REACHED      56
#define MSG_NET_ADAPT_HRDW_ERROR        57
#define MSG_NET_INCORRECT_RESPONSE      58
#define MSG_NET_UNEXPECT_ERROR          59
#define MSG_NET_REMOT_ADPT_INCOMP       60
#define MSG_NET_PRINT_Q_FULL            61
#define MSG_NET_NO_SPACE_TO_PRINT_FL    62
#define MSG_NET_PRINT_FILE_DELETED      63
#define MSG_NET_NAME_DELETED            64
#define MSG_NET_ACCESS_DENIED           65
#define MSG_NET_DEV_TYPE_INVALID        66
#define MSG_NET_NAME_NOT_FOUND          67
#define MSG_NET_NAME_LIMIT_EXCEED       68
#define MSG_NET_BIOS_LIMIT_EXCEED       69
#define MSG_NET_TEMP_PAUSED             70
#define MSG_NET_REQUEST_DENIED          71
#define MSG_NET_PRT_DSK_REDIR_PAUSE     72
#define MSG_XGA_OUT_MEMORY              75
#define MSG_FILE_EXISTS                 80
#define MSG_CANNOT_MAKE                 82
#define MSG_NET_FAIL_INT_TWO_FOUR       83
#define MSG_NET_TOO_MANY_REDIRECT       84
#define MSG_NET_DUP_REDIRECTION         85
#define MSG_NET_INVALID_PASSWORD        86
#define MSG_NET_INCORR_PARAMETER        87
#define MSG_NET_DATA_FAULT              88
#define MSG_NO_PROC_SLOTS               89
#define MSG_DEVICE_IN_USE               99
#define MSG_TOO_MANY_SEMAPHORES         100
#define MSG_EXCL_SEM_ALREADY_OWNED      101
#define MSG_SEM_IS_SET                  102
#define MSG_TOO_MANY_SEM_REQUESTS       103
#define MSG_INVALID_AT_INTERRUPT_TIME   104
#define MSG_SEM_OWNER_DIED              105
#define MSG_ERROR_DISK_CHANGE           106
#define MSG_DISK_CHANGE                 107
#define MSG_DRIVE_LOCKED                108
#define MSG_BROKEN_PIPE                 109
#define MSG_ERROR_OPEN_FAILED           110
#define MSG_ERROR_FILENAME_LONG         111
#define MSG_DISK_FULL                   112
#define MSG_NO_SEARCH_HANDLES           113
#define MSG_ERR_INV_TAR_HANDLE          114
#define MSG_INVALID_CATEGORY            117
#define MSG_INVALID_VERIFY_SWITCH       118
#define MSG_BAD_DRIVER_LEVEL            119
#define MSG_BAD_DYNALINK                120
#define MSG_SEM_TIMEOUT                 121
#define MSG_INSUFFICIENT_BUFFER         122
#define MSG_INVALID_NAME                123
#define MSG_HPFS_INVALID_VOLUME_CHAR    123
#define MSG_INVALID_LEVEL               124
#define MSG_NO_VOLUME_LABEL             125
#define MSG_MOD_NOT_FOUND               126
#define MSG_PROC_NOT_FOUND              127
#define MSG_PROT_MODE_ONLY              129
#define MSG_APPL_SINGLEFRAMECHAR        130
#define MSG_APPL_DOUBLEFRAMECHAR        131
#define MSG_APPL_ARROWCHAR              132
#define MSG_JOIN_ON_DRIV_IS_TAR         133
#define MSG_JOIN_DRIVE_IS               134
#define MSG_SUB_DRIVE_IS                135
#define MSG_DRIVE_IS_NOT_JOINED         136
#define MSG_DRIVE_NOT_SUBSTED           137
#define MSG_JOIN_CANNOT_JOIN_DRIVE      138
#define MSG_SUB_CANNOT_SUBST_DRIVE      139
#define MSG_JOIN_CANNOT_SUB_DRIVE       140
#define MSG_SUB_CANNOT_JOIN_DRIVE       141
#define MSG_DRIVE_IS_BUSY               142
#define MSG_JOIN_SUB_SAME_DRIVE         143
#define MSG_DIRECT_IS_NOT_SUBDIR        144
#define MSG_DIRECT_IS_NOT_EMPTY         145
#define MSG_PATH_USED_SUBST_JOIN        146
#define MSG_NO_NEEDED_RESOURCES         147
#define MSG_PATH_BUSY                   148
#define MSG_SUB_ON_DRIVE_IS_JOIN        149
#define MSG_SYSTEM_TRACE                150
#define MSG_INVALID_EVENT_COUNT         151
#define MSG_TOO_MANY_MUXWAITERS         152
#define MSG_INVALID_LIST_FORMAT         153
#define MSG_VOLUME_TOO_LONG             154
#define MSG_HPFS_VOL_LABEL_LONG         154
#define MSG_TOO_MANY_TCBS               155
#define MSG_SIGNAL_REFUSED              156
#define MSG_DISCARDED                   157
#define MSG_NOT_LOCKED                  158
#define MSG_BAD_THREADID_ADDR           159
#define MSG_BAD_ARGUMENTS               160
#define MSG_SIGNAL_PENDING              162
#define MSG_MAX_THRDS_REACHED           164
#define MSG_UNC_DRIVER_NOT_INSTALLED    166
#define MSG_LOCK_FAILED                 167
#define MSG_SWAPIO_FAILED               168
#define MSG_SWAPIN_ATTEMPT_FAILED       169
#define MSG_SEGMENT_BUSY                170
#define MSG_INT_TOO_LONG                171
#define MSG_UNLOCK_VIOLATION            173
#define MSG_INVALID_SEGMENT_NUM         180
#define MSG_INVALID_ORDINAL             182
#define MSG_INVALID_FLAG_NUMBER         186
#define MSG_SEM_NOT_FOUND               187
#define MSG_INVALID_STARTING_CODESEG    188
#define MSG_INVALID_STACKSEG            189
#define MSG_INVALID_MODULETYPE          190
#define MSG_INVALID_EXE_SIGNATURE       191
#define MSG_EXE_MARKED_INVALID          192
#define MSG_BAD_EXE_FORMAT              193
#define MSG_ITERATED_DATA_EXCEEDS_64K   194
#define MSG_INVALID_MINALLOCSIZE        195
#define MSG_DYNLINK_FROM_INVALID_RING   196
#define MSG_IOPL_NOT_ENABLED            197
#define MSG_INVALID_SEGDPL              198
#define MSG_AUTODATASEG_EXCEEDS_64K     199
#define MSG_CODESEG_CANNOT_BE_64K       200
#define MSG_RELOC_CHAIN_XEEDS_SEGMENT   201
#define MSG_INFLOOP_IN_RELOC_CHAIN      202
#define MSG_ENVVAR_NOT_FOUND            203
#define MSG_SIGNAL_NOT_SENT             205
#define MSG_NAME_TOO_LONG               206
#define MSG_RING2_STACK_IN_USE          207
#define MSG_WILD_CARD_NAME              208
#define MSG_INVALID_SIGNAL_NUMBER       209
#define MSG_THREAD_1_INACTIVE           210
#define MSG_LOCKED                      212
#define MSG_TOO_MANY_MODULES            214
#define MSG_CANNOT_SHRINK               216
#define MSG_INVALID_EXITROUTINE_RING    219
#define MSG_NO_CHILDREN                 228
#define MSG_ERROR_BAD_PIPE              230
#define MSG_ERROR_PIPE_BUSY             231
#define MSG_ERROR_NO_DATA               232
#define MSG_ERROR_PIPE_NOT_CONNECTED    233
#define MSG_ERROR_MORE_DATA             234
#define MSG_ERROR_VC_DISCONNECTED       240
#define MSG_CIRCULARITY_REQUESTED       250
#define MSG_DIRECTORY_IN_CDS            251
#define MSG_INVALID_FSD_NAME            252
#define MSG_INVALID_PATH                253
#define MSG_INVALID_EA_NAME             254
#define MSG_EA_LIST_INCONSISTENT        255
#define MSG_EA_LIST_TOO_LONG            256
#define MSG_NO_META_MATCH               257
#define MSG_FINDNOTIFY_TIMEOUT          258
#define MSG_NO_MORE_ITEMS               259
#define MSG_SEARCH_STRUC_REUSED         260
#define MSG_CHAR_NOT_FOUND              261
#define MSG_TOO_MUCH_STACK              262
#define MSG_INVALID_ATTR                263
#define MSG_INVALID_STARTING_RING       264
#define MSG_INVALID_DLL_INIT_RING       265
#define MSG_CANNOT_COPY                 266
#define MSG_DIRECTORY                   267
#define MSG_OPLOCKED_FILE               268
#define MSG_OPLOCK_THREAD_EXISTS        269
#define MSG_ERROR_EAS_CORRUPT           276
#define MSG_EA_TABLE_FULL               277
#define MSG_INVALID_EA_HANDLE           278
#define MSG_NO_CLUSTER                  279
#define MSG_ERROR_CREATE_EA_FILE        280
#define MSG_CANNOT_OPEN_FILE            281
#define MSG_EAS_NOT_SUPPORTED           282
#define MSG_NEED_EAS_FOUND              283
#define MSG_EAS_DISCARDED               284
#define MSG_DUPLICATE_SEM_NAME          285
#define MSG_EMPTY_MUXWAIT_SEM           286
#define MSG_MUTEX_SEM_OWNED             287
#define MSG_NOT_MUTEX_SEM_OWNER         288
#define MSG_QUERY_MUX_PARAM_TOO_SMALL   289
#define MSG_TOO_MANY_SEM_HANDLES        290
#define MSG_TOO_MANY_SEM_OPENS          291
#define MSG_SEM_WRONG_TYPE              292
#define MSG_TOO_MANY_EVENT_SEM_POSTS    298
#define MSG_EVENT_SEM_ALREADY_POSTED    299
#define MSG_EVENT_SEM_ALREADY_RESET     300
#define MSG_SEM_BUSY                    301
#define MSG_MR_MSG_TOO_LONG             316
#define MSG_MR_CANT_FORMAT              317
#define MSG_MR_NOT_FOUND                318
#define MSG_MR_READ_ERROR               319
#define MSG_MR_IVCOUNT_ERROR            320
#define MSG_MR_UN_PERFORM               321
#define MSG_QUE_PROC_NOT_OWNED          330
#define MSG_QUE_DUPLICATE               332
#define MSG_QUE_ELEMENT_NOT_EXIST       333
#define MSG_QUE_NO_MEMORY               334
#define MSG_VIO_INVALID_MASK            349
#define MSG_VIO_PTR                     350
#define MSG_DIS_ERROR                   355
#define MSG_VIO_WIDTH                   356
#define MSG_VIO_ROW                     358
#define MSG_VIO_COL                     359
#define MSG_VIO_WAIT_FLAG               366
#define MSG_VIO_UNLOCK                  367
#define MSG_SMG_INVALID_SESSION_ID      369
#define MSG_SMG_GRP_NOT_FOUND           371
#define MSG_SMG_SESSION_NOT_FOUND       371
#define MSG_SMG_SET_TITLE               372
#define MSG_KBD_PARAMETER               373
#define MSG_KBD_INVALID_IOWAIT          375
#define MSG_KBD_INVALID_LENGTH          376
#define MSG_KBD_INVALID_ECHO_MASK       377
#define MSG_KBD_INVALID_INPUT_MASK      377
#define MSG_MON_INVALID_PARMS           379
#define MSG_MON_INVALID_DEVNAME         380
#define MSG_MON_INVALID_HANDLE          381
#define MSG_MON_BUFFER_TOO_SMALL        382
#define MSG_MON_BUFFER_EMPTY            383
#define MSG_MON_DATA_TOO_LARGE          384
#define MSG_MOUSE_NO_DEVICE             385
#define MSG_MOUSE_INV_HANDLE            386
#define MSG_MOUSE_CALLER_NOT_SYBSYS     387
#define MSG_NLS_NO_COUNTRY_FILE         396
#define MSG_NO_COUNTRY_SYS              396
#define MSG_NLS_OPEN_FAILED             397
#define MSG_OPEN_COUNTRY_SYS            397
#define MSG_NLS_NO_CTRY_CODE            398
#define MSG_NO_COUNTRY_OR_CODEPAGE      398
#define MSG_NLS_TABLE_TRUNCATED         399
#define MSG_NLS_BAD_TYPE                400
#define MSG_NLS_TYPE_NOT_FOUND          401
#define MSG_COUNTRY_NO_TYPE             401
#define MSG_SWAPIN_FAILED               402
#define MSG_SEGVALIDATE_FAILURE         403
#define MSG_VIO_DEREGISTER              404
#define MSG_VIO_NO_POPUP                405
#define MSG_VIO_EXISTING_POPUP          406
#define MSG_KBD_SMG_ONLY                407
#define MSG_KBD_INVALID_ASCIIZ          408
#define MSG_KBD_INVALID_MASK            409
#define MSG_KBD_REGISTER                410
#define MSG_KBD_DEREGISTER              411
#define MSG_MOUSE_SMG_ONLY              412
#define MSG_MOUSE_INVALID_ASCIIZ        413
#define MSG_MOUSE_INVALID_MASK          414
#define MSG_MOUSE_REGISTER              415
#define MSG_MOUSE_DEREGISTER            416
#define MSG_SMG_BAD_ACTION              417
#define MSG_SMG_INVALID_CALL            418
#define MSG_VIO_INVALID_PARMS           421
#define MSG_VIO_FUNCTION_OWNED          422
#define MSG_VIO_REGISTER                426
#define MSG_VIO_NO_SAVE_RESTORE_THD     428
#define MSG_VIO_IN_BG                   429
#define MSG_VIO_ILLEGAL_DURING_POPUP    430
#define MSG_SMG_NOT_BASESHELL           431
#define MSG_SMG_BAD_STATUSREQ           432
#define MSG_VIO_LOCK                    434
#define MSG_MOUSE_INVALID_IOWAIT        435
#define MSG_VIO_INVALID_HANDLE          436
#define MSG_VIO_INVALID_LENGTH          438
#define MSG_KBD_INVALID_HANDLE          439
#define MSG_KBD_NO_MORE_HANDLE          440
#define MSG_KBD_CANNOT_CREATE_KCB       441
#define MSG_KBD_CODEPAGE_LOAD_INCOMPL   442
#define MSG_KBD_INVALID_CODEPAGE_ID     443
#define MSG_KBD_NO_CODEPAGE_SUPPORT     444
#define MSG_KBD_FOCUS_REQUIRED          445
#define MSG_KBD_FOCUS_ALREADY_ACTIVE    446
#define MSG_KBD_KEYBOARD_BUSY           447
#define MSG_KBD_INVALID_CODEPAGE        448
#define MSG_KBD_UNABLE_TO_FOCUS         449
#define MSG_SMG_SESSION_NON_SELECT      450
#define MSG_SMG_SESSION_NOT_FOREGRND    451
#define MSG_SMG_SESSION_NOT_PARENT      452
#define MSG_SMG_INVALID_START_MODE      453
#define MSG_SMG_INVALID_RELATED_OPT     454
#define MSG_SMG_INVALID_BOND_OPTION     455
#define MSG_SMG_INVALID_SELECT_OPT      456
#define MSG_SMG_START_IN_BACKGROUND     457
#define MSG_SMG_INVALID_STOP_OPTION     458
#define MSG_SMG_BAD_RESERVE             459
#define MSG_SMG_PROCESS_NOT_PARENT      460
#define MSG_SMG_INVALID_DATA_LENGTH     461
#define MSG_SMG_NOT_BOUND               462
#define MSG_SMG_RETRY_SUB_ALLOC         463
#define MSG_KBD_DETACHED                464
#define MSG_VIO_DETACHED                465
#define MSG_MOU_DETACHED                466
#define MSG_VIO_FONT                    467
#define MSG_VIO_USER_FONT               468
#define MSG_VIO_BAD_CP                  469
#define MSG_VIO_NA_CP                   471
#define MSG_SMG_INVALID_TRACE_OPTION    478
#define MSG_VIO_SHELL_INIT              480
#define MSG_SMG_NO_HARD_ERRORS          481
#define MSG_VIO_TRANSPARENT_POPUP       483
#define MSG_VIO_BAD_RESERVE             486
#define MSG_INVALID_ADDRESS             487
#define MSG_ZERO_SELECTORS_REQUESTED    488
#define MSG_NOT_ENOUGH_SELECTORS_AVA    489
#define MSG_INVALID_SELECTOR            490
#define MSG_SMG_INVALID_PROGRAM_TYPE    491
#define MSG_SMG_INVALID_PGM_CONTROL     492
#define MSG_SMG_INVALID_INHERIT_OPT     493
#define MSG_VIO_EXTENDED_SG             494
#define MSG_VIO_NOT_PRES_MGR_SG         495
#define MSG_VIO_SHIELD_OWNED            496
#define MSG_VIO_NO_MORE_HANDLES         497
#define MSG_KBD_NO_CONSOLE              500
#define MSG_DOS_STOPPED                 501
#define MSG_MOUSE_INVALID_HANDLE        502
#define MSG_SMG_INVALID_DEBUG_PARMS     503
#define MSG_KBD_EXTENDED_SG             504
#define MSG_MOU_EXTENDED_SG             505
#define MSG_TRC_PID_NON_EXISTENT        507
#define MSG_TRC_COUNT_ACTIVE            508
#define MSG_TRC_SUSPENDED_BY_COUNT      509
#define MSG_TRC_COUNT_INACTIVE          510
#define MSG_TRC_COUNT_REACHED           511
#define MSG_NO_MC_TRACE                 512
#define MSG_MC_TRACE                    513
#define MSG_TRC_COUNT_ZERO              514
#define MSG_SMG_TOO_MANY_DDS            515
#define MSG_SMG_INVALID_NOTIFICATION    516
#define MSG_LF_INVALID_FUNCTION         517
#define MSG_LF_NOT_AVAIL                518
#define MSG_LF_SUSPENDED                519
#define MSG_LF_BUF_TOO_SMALL            520
#define MSG_LF_BUF_FULL                 521
#define MSG_LF_INVAL_RECORD             522
#define MSG_LF_INVAL_SERVICE            523
#define MSG_LF_GENERAL_FAILURE          524
#define MSG_HPFS_DISK_ALREADY_INUSE     525
#define MSG_HPFS_CANNOT_FORMAT_DISK     526
#define MSG_HPFS_CANNOT_COPY_SYS_DATA   527
#define MSG_HPFS_FORMAT_NOT_DONE        528
#define MSG_HPFS_FMT_NOT_ENOUGH_MEM     529
#define MSG_HPFS_SPECIFY_FIXDSK         530
#define MSG_HPFS_SPECIFY_ONE_DRIVE      531
#define MSG_HPFS_UNKNOWN_ERR_NO_FORMAT  532
#define MSG_HPFS_SYNTAX_HELP            533
#define MSG_HPFS_DISK_FORMATING         534
#define MSG_HPFS_AVAIL_DISK_SPACE       535
#define MSG_HPFS_BAD_BLOCKS             536
#define MSG_HPFS_DISK_SPACE_AVAIL       537
#define MSG_HPFS_SPACE_FORMATTED        538
#define MSG_HPFS_TYPE_CUR_VOLUME_LABEL  539
#define MSG_HPFS_DRIVER_NOT_LOADED      540
#define MSG_HPFS_DRIVER_LOADER          541
#define MSG_HPFS_CACHE_BUF_SPECIFIED    542
#define MSG_HPFS_CHKDSK_PARM_ERROR      543
#define MSG_HPFS_CHKDSK_NOACCESS_DRIVE  544
#define MSG_HPFS_UNKNOWN_ERR_NO_CHKDSK  545
#define MSG_HPFS_CHKDSK_NOT_ENOUGH_MEM  546
#define MSG_HPFS_CHKDSK_NOWRITEODATA    547
#define MSG_HPFS_CHKDSK_NORECOVER_DATA  548
#define MSG_HPFS_CHKDSK_NO_PARM_SPACE   549
#define MSG_HPFS_CHKDSK_NORECOGNIZE     550
#define MSG_HPFS_CHKDSK_NOROOT_FIND     551
#define MSG_HPFS_CHKDSK_NOFIX_FS_ERROR  552
#define MSG_HPFS_CHKDSK_CORRECT_FS_ERR  553
#define MSG_HPFS_CHKDSK_ORGAN_FIX       554
#define MSG_HPFS_CHKDSK_RELOC_BBPDATA   555
#define MSG_HPFS_CHKDSK_REM_CORRU_BLOC  556
#define MSG_HPFS_CHKDSK_REM_CORRUP_FIL  557
#define MSG_HPFS_CHKDSK_FIX_SPACE_ALLO  558
#define MSG_HPFS_NOT_FORMATTED_DISK     559
#define MSG_HPFS_CHKDSK_COR_ALLOC       560
#define MSG_HPFS_CHKDSK_SEARC_UNALLOC   561
#define MSG_HPFS_CHKDSK_DET_LOST_DATA   562
#define MSG_HPFS_CHKDSK_PERCENT_SEARC   563
#define MSG_HPFS_CHKDSK_LOST_DATASEARC  564
#define MSG_HPFS_CHKDSK_CRIT_NOREAD     565
#define MSG_HPFS_CHKDSK_DISK_INUSE      566
#define MSG_HPFS_CHKDSK_RECOVTEMP_RELOC 567
#define MSG_HPFS_TOTAL_DISK_SPACE       568
#define MSG_HPFS_DIR_KBYTES             569
#define MSG_HPFS_FILE_KBYTES            570
#define MSG_HPFS_KBYTES_AVAILABLE       571
#define MSG_HPFS_CHKDSK_PLACE_REC_FILE  572
#define MSG_HPFS_CHKDSK_RECO_DIR_AS     573
#define MSG_HPFS_CHKDSK_PLACEED_DATA    574
#define MSG_HPFS_CHKDSK_RECOV_EA        575
#define MSG_HPFS_CHKDSK_FIND_EA_INTEM   576
#define MSG_HPFS_CHKDSK_RELOC_TEMP_EA   577
#define MSG_HPFS_CHKDSK_RELOC_AC_LIST   578
#define MSG_HPFS_CHKDSK_LIST_NORELOC    579
#define MSG_HPFS_CHKDSK_TRUN_EA_LIST    580
#define MSG_HPFS_CHKDSK_TRUN_EA_NAME    581
#define MSG_HPFS_CHKDSK_TRUN_EA_BBLOCK  582
#define MSG_HPFS_CHKDSK_REM_INVALID_EA  583
#define MSG_HPFS_CHKDSK_FIX_EA_ALLOC    584
#define MSG_HPFS_CHKDSK_FIX_ALACCCTRL   585
#define MSG_HPFS_CHKDSK_ACCTR_LIST_BBL  586
#define MSG_HPFS_CHKDSK_REM_ACLIST      587
#define MSG_HPFS_CHKDSK_FOUND_DATANORL  588
#define MSG_HPFS_WRONG_VERSION          589
#define MSG_HPFS_CHKDSK_FOUND_DATATEMP  590
#define MSG_HPFS_CHKDSK_FIX_TEMPSTATUS  591
#define MSG_HPFS_CHKDSK_FIX_NEEDEADATA  592
#define MSG_HPFS_RECOVER_PARM_ERROR     593
#define MSG_HPFS_RECOV_FILE_NOT_FOUND   594
#define MSG_HPFS_RECOV_UNKNOWN_ERROR    595
#define MSG_HPFS_RECOV_NOT_ENOUGH_MEM   596
#define MSG_HPFS_RECOV_NOWRITE_DATA     597
#define MSG_HPFS_RECOV_NOTEMP_CREATE    598
#define MSG_HPFS_RECOV_EA_NOREAD        599
#define MSG_HPFS_RECOV_FILE_BYTES       600
#define MSG_HPFS_RECOV_BAD_BYTES_RECOV  601
#define MSG_HPFS_RECOV_FILEBYTES_NOREC  602
#define MSG_HPFS_RECOV_DISK_INUSE       603
#define MSG_HPFS_RECOV_FILE_NODELETE    604
#define MSG_HPFS_RECOV_NOCREATE_NEWFILE 605
#define MSG_HPFS_RECOV_SYSTEM_ERROR     606
#define MSG_HPFS_SYS_PARM_ERROR         607
#define MSG_HPFS_SYS_CANNOT_INSTALL     608
#define MSG_HPFS_SYS_DRIVE_NOTFORMATED  609
#define MSG_HPFS_SYS_FILE_NOCREATE      610
#define MSG_HPFS_SIZE_EXCEED            611
#define MSG_HPFS_SYNTAX_ERR             612
#define MSG_HPFS_NOTENOUGH_MEM          613
#define MSG_HPFS_WANT_MEM               614
#define MSG_HPFS_GET_RETURNED           615
#define MSG_HPFS_SET_RETURNED           616
#define MSG_HPFS_BOTH_RETURNED          617
#define MSG_HPFS_STOP_RETURNED          618
#define MSG_HPFS_SETPRTYRETURNED        619
#define MSG_HPFS_ALCSG_RETURNED         620
#define MSG_HPFS_MSEC_SET               621
#define MSG_HPFS_OPTIONS                622
#define MSG_HPFS_POS_NUM_VALUE          623
#define MSG_HPFS_VALUE_TOO_LARGE        624
#define MSG_HPFS_LAZY_NOT_VALID         625
#define MSG_HPFS_VOLUME_ERROR           626
#define MSG_HPFS_VOLUME_DIRTY           627
#define MSG_HPFS_NEW_SECTOR             628
#define MSG_HPFS_FORMAT_PARM_ERROR      629
#define MSG_HPFS_CANNOT_ACCESS_CONFIG   630
#define MSG_HPFS_RECOV_FILE             631
#define MSG_HPFS_CHKDSK_KBYTES_RESERVE  632
#define MSG_HPFS_CHKDSK_KBYTES_IN_EA    633
#define MSG_HPFS_BYTEBUF_SET            634
#define MSG_HPFS_FORMATTING_COMPLETE    635
#define MSG_HPFS_WRONG_VOLUME_LABEL     636
#define MSG_HPFS_FMAT_TOO_MANY_DRS      637
#define MSG_VDD_UNSUPPORTED_ACCESS      638
#define MSG_REC_WARNING                 640
#define MSG_VDD_MISSING                 651
#define MSG_HPFS_LAZY_ON                689
#define MSG_HPFS_LAZY_OFF               690
#define MSG_HPFS_DISK_ERROR_WARN        693
#define MSG_BAD_MON_BUFFER              730
#define MSG_MODULE_CORRUPTED            731
#define MSG_BOOT_DRIVE_NOT_ACCESSIBLE   732
#define MSG_LF_TIMEOUT                  2055
#define MSG_LF_SUSP_SUCCESS             2057
#define MSG_LF_RESUM_SUCCESS            2058
#define MSG_LF_REDIR_SUCCESS            2059
#define MSG_LF_REDIR_FAILURE            2060
#define MSG_BAD_PARM1                   1001
#define MSG_BAD_PARM2                   1002
#define MSG_BAD_SYNTAX                  1003
#define MSG_STAND_BY                    1004
#define MSG_INVALID_DATE                1036
#define MSG_DEV_INSTALL_FAIL            1111
#define MSG_DEV_AT_ONLY                 1112
#define MSG_DEV_PS2_ONLY                1113
#define MSG_DEV_HW_UNSUPPORTED          1114
#define MSG_DEV_HW_UNAVAILABLE          1115
#define MSG_DEV_IRQ                     1116
#define MSG_DEV_ABIOS                   1117
#define MSG_NO_HELP_MSG                 1118
#define MSG_NEXT_DISKETTE               1120
#define MSG_SYSINIT_PROCS_INITED        1188
#define MSG_SYSINIT_PSD_NOT_FND         1190
#define MSG_SYSINIT_NO_IFS_STMT         1191
#define MSG_SYSINIT_287_DISABLED        1193
#define MSG_SYSINIT_387_WITH_386B1      1194
#define MSG_SYSINIT_INVAL_CMD           1195
#define MSG_SYSINIT_INVAL_PARM          1196
#define MSG_SYSINIT_MISSING_PARM        1197
#define MSG_SYSINIT_BAD_DOS_DD          1198
#define MSG_SYSINIT_BOOT_FAILURE        1199
#define MSG_SYSINIT_DOS_FAIL            1200
#define MSG_SYSINIT_UDRVR_FAIL          1201
#define MSG_SYSINIT_SDRVR_FAIL          1202
#define MSG_SYSINIT_UFILE_IOPL          1203
#define MSG_SYSINIT_SFILE_IOPL          1204
#define MSG_SYSINIT_DOS_MODIFIED        1205
#define MSG_SYSINIT_UFILE_NO_MEM        1206
#define MSG_INCORRECT_DOSVERSION        1210
#define MSG_ABORT_RTRY_IGNORE           1211
#define MSG_HPFS_FORMAT_YES_NO          1271
#define MSG_HPFS_SYS_FILES_COPIED       1272
#define MSG_HPFS_BAD_BLOCKS_CRIT_AREA   1279
#define MSG_HPFS_TYPE_VOLUME_LABEL      1288
#define MSG_HPFS_SPECIFY_DRIVE_LETTER   1310
#define MSG_HPFS_DIRECTORY              1338
#define MSG_HPFS_CHKDSK_NOREAD_DATA     1341
#define MSG_SAD_REMOTE_DUMP             1394
#define MSG_SAD_INSERT_DUMP             1395
#define MSG_SAD_NOT_AVAILABLE           1398
#define MSG_DLL_CANT_LOAD_RESOURCE      1417
#define MSG_SWAP_INVALID_DRIVE          1470
#define MSG_SWAP_INVALID_PATH           1471
#define MSG_SWAP_CANNOT_CREATE          1472
#define MSG_SWAP_DISABLED               1473
#define MSG_SWAP_CANT_INIT              1474
#define MSG_SYSINIT_BOOT_NOT_FD         1475
#define MSG_SWAP_INVALID_PATH_ROOT      1476
#define MSG_STRI_FILE_NOT_FOUND         1490
#define MSG_SWAP_NOT_READY              1500
#define MSG_SWAP_WRITE_PROTECT          1501
#define MSG_SWAP_IN_ERROR               1502
#define MSG_SWAP_IO_ERROR               1502
#define MSG_SWAP_FILE_FULL              1503
#define MSG_SWAP_TABLE_FULL             1504
#define MSG_SYSINIT_SFILE_NOT_FND       1518
#define MSG_SYSINIT_SFILE_NO_MEM        1519
#define MSG_SYSINIT_DSKT_NOT_INSTALLED  1520
#define MSG_SYSINIT_TOO_MANY_PARMS      1521
#define MSG_SYSINIT_DSKT_INSTALLED_AS   1522
#define MSG_SYSINIT_MISSING_SYMB        1523
#define MSG_SYSINIT_START_NO_LOAD       1709
#define MSG_SYSINIT_START_NO_INIT       1710
#define MSG_SYSINIT_UFILE_NOT_FND       1718
#define MSG_SYSINIT_UDRVR_INVAL         1719
#define MSG_SYSINIT_FSD_NOT_VAL         1720
#define MSG_SYSINIT_BANNER              1721
#define MSG_SYSINIT_CANT_LOAD_MOD       1722
#define MSG_SYSINIT_EPT_MISSING         1723
#define MSG_SYSINIT_CANT_OPEN_CON       1724
#define MSG_SYSINIT_WRONG_HANDLE        1725
#define MSG_SYSINIT_PRESS_ENTER         1726
#define MSG_SYSINIT_CANT_GET_CACHE      1727
#define MSG_SYSINIT_CANT_INIT_CACHE     1728
#define MSG_SYSINIT_VIO_CP              1729
#define MSG_SYSINIT_KBD_CP              1730
#define MSG_SYSINIT_SCFILE_INVAL        1733
#define MSG_SYSINIT_CP_ASSUME           1735
#define MSG_SYSINIT_CP_FATAL            1737
#define MSG_SYSINIT_NOT_INIT_NMI        1738
#define MSG_VLPT_NO_SPOOL               1797
#define MSG_VCOM_DEVICE_IN_USE          1798
#define MSG_VLPT_DEVICE_BUSY            1799
#define MSG_ASYNC_BAD_ARBT              1903
#define MSG_SYSINIT_DRV_RESERVE         1914
#define MSG_INTERNAL_ERROR              1915
#define MSG_USER_ERROR                  1916
#define MSG_SYSINIT_UEXEC_FAIL          1919
#define MSG_PAGE_FAULT                  1923
#define MSG_INTERRUPTS_DISABLED         1924
#define MSG_SYSINIT_SEXEC_FAIL          1925
#define MSG_GEN_PROT_FAULT              1926
#define MSG_CHANGE_INT_VECTOR           1927
#define MSG_NOMEM_FOR_RELOAD            1928
#define MSG_STACK_OVERFLOW              1929
#define MSG_TRAP0                       1930
#define MSG_TRAP1                       1931
#define MSG_TRAP2                       1932
#define MSG_TRAP3                       1933
#define MSG_TRAP4                       1934
#define MSG_TRAP5                       1935
#define MSG_TRAP6                       1936
#define MSG_TRAP7                       1937
#define MSG_TRAP8                       1938
#define MSG_TRAP9                       1939
#define MSG_TRAPA                       1940
#define MSG_TRAPB                       1941
#define MSG_TRAPC                       1942
#define MSG_TRAPD                       1943
#define MSG_NMI                         1944
#define MSG_NMI_EXC1                    1945
#define MSG_NM12_EXC2                   1946
#define MSG_NMI2_EXC3                   1947
#define MSG_NMI2_EXC4                   1948
#define MSG_TRAPE                       1949
#define MSG_NPXIEMSG                    1950
#define MSG_NPXDEMSG                    1951
#define MSG_NPXZEMSG                    1952
#define MSG_NPXOEMSG                    1953
#define MSG_NPXUEMSG                    1954
#define MSG_NPXPEMSG                    1955
#define MSG_NPXINSTEMSG                 1956
#define MSG_NPXBADSW                    1957
#define MSG_PAGEMGR_TRAP02_MEM_REC      1958
#define MSG_PAGEMGR_TRAP02_APP_TERM     1959
#define MSG_SYSINIT_BOOT_ERROR          2025
#define MSG_SYSINIT_BIO_NOT_FD          2026
#define MSG_SYSINIT_INSER_DK            2027
#define MSG_SYSINIT_DOS_NOT_FD          2028
#define MSG_SYSINIT_DOS_NOT_VAL         2029
#define MSG_SYSINIT_MORE_MEM            2030
#define MSG_SYSINIT_DOS_TOO_BIG         2063
#define MSG_SYSINIT_DOS_NO_MEM          2064
#define MSG_SYSINIT_SYS_STOPPED         2065
#define MSG_SYSINIT_DOS_STOPPED         2066
#define MSG_SYSINIT_SDRVR_INVAL         2067
#define MSG_SYSINIT_MSG_LOST            2068
#define MSG_SYSINIT_UCFILE_INVAL        2069
#define MSG_DEMAND_LOAD_FAILED          2070
#define MSG_CDFS_BAD_OS_VERSION         3100
#define MSG_CDFS_DEB_STAT_SIGNON        3101
#define MSG_CDFS_DEB_SIGNON             3102
#define MSG_CDFS_STAT_SIGNON            3103
#define MSG_CDFS_SIGNON                 3104
#define MSG_CDFS_UNKNOWN_ERR_CODE       3105
#define MSG_CDFS_BAD_PARM               3106
#define MSG_CDFS_MIN_SECTORS            3107
#define MSG_CDFS_DEBUG                  3108
#define MSG_CDFS_MAX_SECTORS            3109
#define MSG_CDFS_MIN_FILE_SECT          3110
#define MSG_CDFS_MAX_FILE_SECT          3111
#define MSG_CDFS_PRIMARY_VD             3112
#define MSG_CDFS_SECONDARY_VD           3113
#define MSG_CDFS_SECTOR_CACHE           3114
#define MSG_CDFS_SECTORS_READ           3115
#define MSG_CDFS_INIT_FAIL              3116
#define MSG_CDFS_MEM_INIT_FAIL          3117
#define MSG_CDFS_PARTIAL_MEM_FAIL       3118
#define MSG_CDFS_NO_INFOSEG             3119
#define MSG_SYSINIT_DISPLAY_MISMATCH    3135
#define MSG_EISA_NMI_SOFTWARE           3140
#define MSG_EISA_NMI_BUS                3141
#define MSG_EISA_NMI_FAILSAFE           3142
#define MSG_EISA_NMI_IOCHK              3143
#define MSG_EISA_NMI_PARITY             3144
#define MSG_BAD_COMMAND_COM             3145
#define MSG_SYSINIT_LDR_MSG_NOT_FD      3146
#define MSG_SYSINIT_LDR_MSG_NOT_VAL     3147
#define MSG_NOT_80386_CPU               3161
#define MSG_80_STEPPING                 3162
#define MSG_32BIT_MULTIPLY              3163
#define MSG_XCPT_USER                   3170
#define MSG_XCPT_STACK_OVERRUN          3171
#define MSG_XCPT_CANNOT_DISPATCH        3172
#define MSG_XCPT_BREAKPOINT             3173
#define MSG_XCPT_SINGLE_STEP            3174
#define MSG_XCPT_ACCESS_VIOLATION       3175
#define MSG_XCPT_ILLEGAL_INSTRUCTION    3176
#define MSG_XCPT_FLOAT_DENORMAL_OPERAND 3177
#define MSG_XCPT_FLOAT_DIVIDE_BY_ZERO   3178
#define MSG_XCPT_FLOAT_INEXACT_RESULT   3179
#define MSG_XCPT_FLOAT_INVALID_OPERATIO 3180
#define MSG_XCPT_FLOAT_OVERFLOW         3181
#define MSG_XCPT_FLOAT_STACK_CHECK      3182
#define MSG_XCPT_FLOAT_UNDERFLOW        3183
#define MSG_XCPT_INTEGER_DIVIDE_BY_ZERO 3184
#define MSG_XCPT_INTEGER_OVERFLOW       3185
#define MSG_XCPT_PRIVILEGED_INSTRUCTION 3186
#define MSG_XCPT_IN_PAGE_ERROR          3187
#define MSG_XCPT_NONCONTINUABLE_EXCEPTI 3188
#define MSG_XCPT_INVALID_DISPOSITION    3189
#define MSG_XCPT_INVALID_LOCK_SEQUENCE  3190
#define MSG_XCPT_ARRAY_BOUNDS_EXCEEDED  3191
#define MSG_XCPT_B1NPX_ERRATA_02        3192
#define MSG_HARDWARE_CONFIGURATION      3332
#define MSG_SYSINIT_CMOS_ERR            3357
#define MSG_SYSINIT_BAD_TRAPDUMP_DRV    3358

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
