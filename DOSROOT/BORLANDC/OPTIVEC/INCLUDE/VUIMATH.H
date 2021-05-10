/*  VUImath.h

  vector management functions for data type "ui"
  ("unsigned index", the data type for indexing):
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/
#if defined (V_HUGE)
   #if !defined( __VULMATH_H )
       #include <VULmath.h>
   #endif
   #define VUI_addC    VUL_addC
   #define VUI_subC    VUL_subC
   #define VUI_subrC   VUL_subrC
   #define VUI_mulC    VUL_mulC
   #define VUIo_addC   VULo_addC
   #define VUIo_subC   VULo_subC
   #define VUIo_subrC  VULo_subrC
   #define VUIo_mulC   VULo_mulC
   #define VUI_divC    VUL_divC
   #define VUI_divrC   VUL_divrC
   #define VUI_modC    VUL_modC
   #define VUI_maxC    VUL_maxC
   #define VUI_minC    VUL_minC
   #define VUI_addV    VUL_addV
   #define VUI_subV    VUL_subV
   #define VUI_subrV   VUL_subrV
   #define VUI_mulV    VUL_mulV
   #define VUIo_addV   VULo_addV
   #define VUIo_subV   VULo_subV
   #define VUIo_subrV  VULo_subrV
   #define VUIo_mulV   VULo_mulV
   #define VUI_divV    VUL_divV
   #define VUI_divrV   VUL_divrV
   #define VUI_modV    VUL_modV
   #define VUI_maxV    VUL_maxV
   #define VUI_minV    VUL_minV
   #define VUI_accV    VUL_accV
   #define VUI_accVUB  VUL_accVUB
   #define VUI_accVUS  VUL_accVUS
   #define VUI_accVU   VUL_accVU
   #define VUI_shl     VUL_shl
   #define VUI_shr     VUL_shr
   #define VUI_and     VUL_and
   #define VUI_or      VUL_or
   #define VUI_xor     VUL_xor
   #define VUI_not     VUL_not
   #define VUI_ODtoF   VUL_ODtoF
   #define VUI_ODtoD   VUL_ODtoD
   #define VUI_ODtoE   VUL_ODtoE
   #define VUI_ODtoFwDark   VUL_ODtoFwDark
   #define VUI_ODtoDwDark   VUL_ODtoDwDark
   #define VUI_ODtoEwDark   VUL_ODtoEwDark
   #define VUI_setODThresh  VUL_setODThresh
#else
   #if !defined( __VUMATH_H )
       #include <VUmath.h>
   #endif
   #define VUI_addC    VU_addC
   #define VUI_subC    VU_subC
   #define VUI_subrC   VU_subrC
   #define VUI_mulC    VU_mulC
   #define VUIo_addC   VUo_addC
   #define VUIo_subC   VUo_subC
   #define VUIo_subrC  VUo_subrC
   #define VUIo_mulC   VUo_mulC
   #define VUI_divC    VU_divC
   #define VUI_divrC   VU_divrC
   #define VUI_modC    VU_modC
   #define VUI_maxC    VU_maxC
   #define VUI_minC    VU_minC
   #define VUI_addV    VU_addV
   #define VUI_subV    VU_subV
   #define VUI_subrV   VU_subrV
   #define VUI_mulV    VU_mulV
   #define VUIo_addV   VUo_addV
   #define VUIo_subV   VUo_subV
   #define VUIo_subrV  VUo_subrV
   #define VUIo_mulV   VUo_mulV
   #define VUI_divV    VU_divV
   #define VUI_divrV   VU_divrV
   #define VUI_modV    VU_modV
   #define VUI_maxV    VU_maxV
   #define VUI_minV    VU_minV
   #define VUI_accV    VU_accV
   #define VUI_accVUB  VU_accVUB
   #define VUI_accVUS  VU_accVUS
   #define VUI_accVU   VU_accV
   #define VUI_shl     VU_shl
   #define VUI_shr     VU_shr
   #define VUI_and     VU_and
   #define VUI_or      VU_or
   #define VUI_xor     VU_xor
   #define VUI_not     VU_not
   #define VUI_ODtoF   VU_ODtoF
   #define VUI_ODtoD   VU_ODtoD
   #define VUI_ODtoE   VU_ODtoE
   #define VUI_ODtoFwDark   VU_ODtoFwDark
   #define VUI_ODtoDwDark   VU_ODtoDwDark
   #define VUI_ODtoEwDark   VU_ODtoEwDark
   #define VUI_setODThresh  VU_setODThresh
#endif
