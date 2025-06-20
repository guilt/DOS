/*
 *  arch/i386/sys/endian.h
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

#define BYTE_ORDER      LITTLE_ENDIAN

#define htobe16(x) _SWAPNC_16(x)
#define htole16(x) (x)
#define be16toh(x) _SWAPNC_16(x)
#define le16toh(x) (x)

#define htobe32(x) _SWAPNC_32(x)
#define htole32(x) (x)
#define be32toh(x) _SWAPNC_32(x)
#define le32toh(x) (x)

#define htobe64(x) _SWAPNC_64(x)
#define htole64(x) (x)
#define be64toh(x) _SWAPNC_64(x)
#define le64toh(x) (x)
