/*  VUIstd.h

  vector management functions for data type "ui"
  ("unsigned index", the data type for indexing).

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/


#if defined( V_HUGE )
   #if !defined( __VULSTD_H )
      #include <VULstd.h>
   #endif
   #define VUI_vector            VUL_vector
   #define VUI_vector0           VUL_vector0
   #define VUI_Pelement          VUL_Pelement
   #define VUI_element           VUL_element
   #define VUI_equ0              VUL_equ0
   #define VUI_ramp              VUL_ramp
   #define VUI_equV              VUL_equV
   #define V_UItoU               V_ULtoU
   #define V_UtoUI               V_UtoUL
   #define V_UItoUB              V_ULtoUB
   #define V_UBtoUI              V_UBtoUL
   #define V_UItoUS              V_ULtoUS
   #define V_UStoUI              V_UStoUL
   #define V_ULtoUI              VUL_equV
   #define V_UItoUL              VUL_equV
   #define V_UItoF               V_ULtoF
   #define V_UItoD               V_ULtoD
   #define V_UItoE               V_ULtoE
   #define VUI_delete            VUL_delete
   #define VUI_insert            VUL_insert
   #define VUI_random            VUL_random
   #define VUI_sort              VUL_sort
   #define VUI_sortind           VUL_sortind
   #define VUI_subvector         VUL_subvector
   #define VUI_subvector_equC    VUL_subvector_equC
   #define VUI_subvector_equV    VUL_subvector_equV
   #define VUI_indpick           VUL_indpick
   #define VUI_indput            VUL_indput
   #define VUI_reflect           VUL_reflect
   #define VUI_rev               VUL_rev
   #define VUI_rotate            VUL_rotate
   #define VUI_iselementC        VUL_iselementC
   #define VUI_iselementV        VUL_iselementV
   #define VUI_sum               VUL_sum
   #define VUI_mean              VUL_mean
   #define VUI_max               VUL_max
   #define VUI_maxind            VUL_maxind
   #define VUI_min               VUL_min
   #define VUI_minind            VUL_minind
   #define VUI_runsum            VUL_runsum
   #define VUI_runmax            VUL_runmax
   #define VUI_runmin            VUL_runmin
   #define VUI_cprint            VUL_cprint
   #define VUI_fprint            VUL_fprint
   #define VUI_print             VUL_print
   #define VUI_write             VUL_write
   #define VUI_read              VUL_read
   #define VUI_nwrite            VUL_nwrite
   #define VUI_nread             VUL_nread
   #define VUI_setWriteFormat    VUL_setWriteFormat
   #define VUI_setWriteSeparate  VUL_setWriteSeparate
   #define VUI_setNWriteSeparate VUL_setNWriteSeparate
   #define VUI_store             VUL_store
   #define VUI_recall            VUL_recall
#else   /* not HUGE  */
   #if !defined( __VUSTD_H )
      #include <VUstd.h>
   #endif
   #define VUI_vector            VU_vector
   #define VUI_vector0           VU_vector0
   #define VUI_Pelement          VU_Pelement
   #define VUI_element           VU_element
   #define VUI_equ0              VU_equ0
   #define VUI_ramp              VU_ramp
   #define VUI_equV              VU_equV
   #define V_UItoU               VU_equV
   #define V_UtoUI               VU_equV
   #define V_UItoUB              V_UtoUB
   #define V_UBtoUI              V_UBtoU
   #define V_UItoUS              V_UtoUS
   #define V_UStoUI              V_UStoU
   #define V_ULtoUI              V_ULtoU
   #define V_UItoUL              V_UtoUL
   #define V_UItoF               V_UtoF
   #define V_UItoD               V_UtoD
   #define V_UItoE               V_UtoE
   #define VUI_delete            VU_delete
   #define VUI_insert            VU_insert
   #define VUI_random            VU_random
   #define VUI_sort              VU_sort
   #define VUI_sortind           VU_sortind
   #define VUI_subvector         VU_subvector
   #define VUI_subvector_equC    VU_subvector_equC
   #define VUI_subvector_equV    VU_subvector_equV
   #define VUI_indpick           VU_indpick
   #define VUI_indput            VU_indput
   #define VUI_reflect           VU_reflect
   #define VUI_rev               VU_rev
   #define VUI_rotate            VU_rotate
   #define VUI_iselementC        VU_iselementC
   #define VUI_iselementV        VU_iselementV
   #define VUI_sum               VU_sum
   #define VUI_mean              VU_mean
   #define VUI_max               VU_max
   #define VUI_maxind            VU_maxind
   #define VUI_min               VU_min
   #define VUI_minind            VU_minind
   #define VUI_runsum            VU_runsum
   #define VUI_runmax            VU_runmax
   #define VUI_runmin            VU_runmin
   #define VUI_cprint            VU_cprint
   #define VUI_fprint            VU_fprint
   #define VUI_print             VU_print
   #define VUI_write             VU_write
   #define VUI_read              VU_read
   #define VUI_nwrite            VU_nwrite
   #define VUI_nread             VU_nread
   #define VUI_setWriteFormat    VU_setWriteFormat
   #define VUI_setWriteSeparate  VU_setWriteSeparate
   #define VUI_setNWriteSeparate VU_setNWriteSeparate
   #define VUI_store             VU_store
   #define VUI_recall            VU_recall
#endif


