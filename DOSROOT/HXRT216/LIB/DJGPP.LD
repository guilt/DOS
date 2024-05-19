OUTPUT_FORMAT("coff-go32")
ENTRY(start)
SEARCH_DIR("/djgpp/lib/gcc/djgpp/4.10"); SEARCH_DIR("/djgpp/lib")
SECTIONS
{
  .text 0x0 : {
    *(.text)
    *(.gnu.linkonce.t*)
    *(.gnu.linkonce.r*)
    etext  =  . ; _etext = .;
   } 
    . = ALIGN(0x200);
  .data 0x0 : {
    djgpp_first_ctor = . ;
    *(.ctor)
    djgpp_last_ctor = . ;
    djgpp_first_dtor = . ;
    *(.dtor)
    djgpp_last_dtor = . ;
    *(.data)
    *(.gnu.linkonce.d*)
    *(.gcc_exc*)
    ___EH_FRAME_BEGIN__ = . ;
    *(.eh_fram*)
    ___EH_FRAME_END__ = . ;
    LONG(0)
     edata  =  . ; _edata = .;
    } 
    . = ALIGN(0x200);
  .bss 0x0 : {
    _object.2 = . ;
    . += 24 ;
  	*(.bss)
  	*(.bss.*)
    *(.gnu.linkonce.b*)
    end = .;
    _end = .;
  }
  .comment 0x0:
  { 					
  }
}
