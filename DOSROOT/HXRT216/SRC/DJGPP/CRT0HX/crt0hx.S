/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/*****************************************************************************\
 * Interface to 32-bit HX executable
 *
 *   cs        32-bit true flat code segment
 *   ds,es,ss  32-bit true flat data segment
 *   fs        0, not used
 *   gs        0, not used
 *   eip       entry from PE header
 *   esp       top of stack
 *   <others>	All unspecified registers have unspecified values in them.
\*****************************************************************************/

	.file "crt0.s"

#include "stubinfo.h"

#if    1		/* Define problems with old bnutils */

#define LJMP(there) \
	ljmp	there
#define LCALL(there) \
	lcall	there
#else
#define LJMP(there) \
	ljmp	*there
#define LCALL(there) \
	lcall	*there
#endif

	.comm	__stklen, 4
	.comm	__stubinfo, 4
	.comm	___djgpp_base_address, 4
	.comm	___djgpp_selector_limit, 4
	.comm	___djgpp_stack_limit, 4
	.lcomm	sel_buf, 8
	/* ___djgpp_ds_alias defined in go32/exceptn.S */

#define MULTIBLOCK 1

	.data

#ifdef MULTIBLOCK
	.globl	___djgpp_memory_handle_pointer
___djgpp_memory_handle_pointer:
	.long	___djgpp_memory_handle_list+8		/* Next free, first for stub */
	.comm	___djgpp_memory_handle_list, 2048	/* Enough for 256 handles */
	.comm	___djgpp_memory_handle_size, 1024	/* Enough for 256 handles */
#endif

sbrk16_first_byte:
#include "sbrk16.ah"
sbrk16_last_byte:

sbrk16_api_ofs:
	.long	0
sbrk16_api_seg:
	.word	0
zero:
	.long	0

/* normally this should be a
struct object {
  void *pc_begin;
  void *pc_end;
  void *fde_begin;
  void **fde_array;
  size_t count;
  struct object *next;
};
but a placeholder of the same size does it also */
/* W A R N I N G : If the size of this struct changes in future
   versions of gcc, remember this here !!! The struct is declared
   in the file frame.h from the gcc sources */
_frame_struct:
	.long	0,0,0,0,0,0
	.long	0,0,0,0,0,0 /* DJ - more zeros, just in case */
.section .eh_frame
_CRT0_EH_FRAME_BEGIN_:

	.data

exit16_first_byte:
#include "exit16.ah"
exit16_last_byte:

hook_387_emulator:
	.long	___emu387_load_hook

	/* this pulls in the ident string, generated in .. */
	.long	___libc_ident_string

	/* this is for when main comes from a library */
	.long	_main

	.text

	.globl	start
	.globl	_start
	.balign	16,,7

_start:    
start:

#if 1
	and		$0xf000, %si
	movl	%esi, ___djgpp_base_address
    movl	%ebx, __stubinfo /* use it as temporary storage */
#endif

/* Create an alias for DS to be used by real-mode callbacks (exception handler messes with DS itself) */

    
	movl	%cs, %ebx
	movw	$0x000a, %ax
	int	$0x31
	jnc	ds_alias_ok
	movb	$0x4c, %ah
	int	$0x21
ds_alias_ok:
	movw	%ax, ___djgpp_ds_alias
	movl	%eax, %ebx
	movw	$0x0009, %ax
	movl	%cs, %ecx	/* get CPL from %cs */
	andl	$3, %ecx
	shll	$5, %ecx		/* move it into place */
	orw	$0xc093, %cx
	int	$0x31		/* set access rights for alias */

#ifdef MULTIBLOCK
	testb	$0x8, __crt0_startup_flags+1		/* include/crt0.h */
	jz	8f
#endif
/* Allocate some DOS memory and copy our sbrk helper into it. */
	movl	$sbrk16_first_byte, %esi
	movzwl	8(%esi), %ebx
	shrl	$4, %ebx
	movw	$0x0100, %ax
	int	$0x31
	jnc	dos_alloc_ok
	movb	$0x4c, %ah
	int	$0x21
dos_alloc_ok:
	movw	%cs, 2(%esi)			/* store API information */
	movw	%ds, 4(%esi)
	movw	%dx, 6(%esi)			/* selector for allocated block */

	movzwl	(%esi), %eax			/* calculate API address */
	movl	%eax, sbrk16_api_ofs

	pushl	%es				/* move the data */
	movw	%dx, %es
	movl	$(sbrk16_last_byte - sbrk16_first_byte), %ecx
	shrl	$2,%ecx
	xorl	%edi, %edi
	cld
	rep
	movsl
	popl	%es

	movl	%edx, %ebx			/* dos memory selector */
	movw	$0x000b, %ax			/* get descriptor */
	movl	$sel_buf, %edi
	int	$0x31

	andb	$0xbf, sel_buf+6		/* make 16-bit */
	andb	$0xf0, sel_buf+5		/* remove old type */
	orb	$0x0a, sel_buf+5		/* set new type to code/read */

	xorl	%eax, %eax			/* allocate new selector */
	movw	$0x0001, %cx
	int	$0x31
	movw	%ax, sbrk16_api_seg

	movl	%eax, %ebx
	movw	$0x000c, %ax			/* set descriptor */
	movl	$sel_buf, %edi
	int	$0x31
#ifdef MULTIBLOCK
8:	movl	$___djgpp_memory_handle_list+8, %edi
	movl	%edi, ___djgpp_memory_handle_pointer
	xorl	%eax, %eax
9:	cmpl	%eax, (%edi)
	je	10f
	mov	%eax, (%edi)
	addl	$4, %edi
	jmp	9b
10:
#if 0
	movw	%cs, %bx
	movw	$0x0006,%ax
	int	$0x31
	movl	%edx,___djgpp_base_address
	movw	%cx,___djgpp_base_address+2
#else
/*    movw    $0x4B82, %ax */
/*    xorl    %edx,%edx */
/*    int $0x21 */
	movl	___djgpp_base_address, %eax
    pushl   %eax
    popw    %dx
    popw    %cx
#endif
#endif	/* MULTIBLOCK */

/* Initialize the brk/sbrk variables */

/*	movl	$end, __what_size_app_thinks_it_is */
#if 0
	.byte 0x64 /* fs: */
	movl	STUBINFO_INITIAL_SIZE, %eax
	movl	%eax, __what_size_dpmi_thinks_we_are
#else
    movl    ___djgpp_base_address, %eax
    addl	0x3C(%eax), %eax        /* MZHDR + 3Ch */
    movl	0x50(%eax), %eax 		/* 50h is offset SizeOfImage */
	movl	$-1, __what_size_dpmi_thinks_we_are
#endif
/*	movl	%eax, ___djgpp_memory_handle_size */

/* Maybe lock the initial block, expects BX:CX */
	movl	%ecx,%ebx
	movl	%edx,%ecx
	addw	$4096,%cx			/* Skip null page */
	adcl	$0,%ebx
	subl	$4096,%eax
	pushl	%eax
	call	lock_memory

#if 0
	.byte 0x64 /* fs: */
	movl	STUBINFO_MEMORY_HANDLE, %eax
#else
	xorl	%eax, %eax         /* the image is maintained by DPMILD32 */
#endif
	movl	%eax, ___djgpp_memory_handle_list
#if 0
	.byte 0x64 /* fs: */			/* copy stubinfo into local memory */
	movl	STUBINFO_SIZE, %eax
#else
	movl	$STUBINFO_END, %eax
#endif
	pushl	%eax
	call	___sbrk
	cmpl	$-1, %eax
	je	no_memory
#if 0    
	movl	%eax, __stubinfo
	movl	%eax, %edi
	.byte 0x64 /* fs: */
	movl	STUBINFO_SIZE, %ecx
	shrl	$2, %ecx
	xorl	%esi, %esi			/* Zero */
	pushl	%ds
	pushl	%fs
	popl	%ds
	cld
	rep
	movsl
	popl	%ds
#else
	movl	__stubinfo, %ebx		/* PSP linear address was saved here */
	movl	%eax, __stubinfo
	movl	%eax, %edi

    movw    0x2C(%ebx), %ax         /* get environment selector */
    lsl		%eax, %eax              /* lsl? (is usually FFFF) */
    incl	%eax
    movw	%ax, 42(%edi) 	    	/* env size */
    
    shrl	$4,%ebx
    movw	$2,%ax
    int		$0x31
    movw	%ax,38(%edi)
    
    movl	$0x0,(%edi)				/* magic */
    movl	$STUBINFO_SIZE,16(%edi)	/* set size */
    movl	$0x20000,20(%edi)      	/* minstack */
    movl	$0x0,24(%edi)		   	/* memory handle */
    
    movl    ___djgpp_base_address, %eax

    addl	0x3C(%eax), %eax
    movl	0x50(%eax), %eax		/* 50h is offset SizeOfImage */
    movl	%eax,28(%edi)	       	/* initial size */
    
    movw	$0x4000,32(%edi)       	/* min keep */
    
    movw	$0x100, %ax             /* alloc 16k DOS memory */
    movw	$0x400, %bx
    int		$0x31
    movw	%dx,34(%edi)	       	/* selector */
    movw	%ax,36(%edi)	       	/* segment */
/*    movb	$0x51, %ah */
/*    int		$0x21 */
/*    movw	%bx,38(%edi) */	       	/* psp selector */

	xorl	%eax, %eax				/* alloc a selector */
    movw	$0x1, %cx
    int		$0x31
    movl	%eax, %edx
    movw	%ax, 40(%edi)	       	/* cs selector */
	pushl	%edi
	movw	$0x000b, %ax			/* get descriptor */
    movw	34(%edi), %bx			/* of DOS memory block */
	movl	$sel_buf, %edi
	int	$0x31
    movl	%edx, %ebx
    orb		$0x8, 5(%edi)			/* create a code alias for DOS memory */
	movw	$0x000c, %ax			/* set descriptor */
	int	$0x31
    popl	%edi

    movb	$0, 44(%edi)	       	/* basename[8] */
    movb	$0, 52(%edi)	       	/* argv0[16] */
    movb	$0, 68(%edi)	       	/* argv0 */
#endif

#if 0
	movl	__stklen, %eax		/* get program-requested stack size */
	.byte 0x64 /* fs: */
	movl	STUBINFO_MINSTACK, %ecx	/* get stub-requested stack size */
	cmpl	%ecx, %eax
	jge	use_stubinfo_stack_size	/* use the larger of the two */
	movl	%ecx, %eax
	movl	%eax, __stklen		/* store the actual stack length */
use_stubinfo_stack_size:
	pushl	%eax
	call	___sbrk			/* allocate the memory */
	cmpl	$-1, %eax
	je	no_memory
	movl	%eax, ___djgpp_stack_limit	/* Bottom of stack */
	addl	__stklen, %eax
	movw	%ds, %dx		/* set stack */
	movw	%dx, %ss
	andb	$0xf8, %al		/* align to 8-byte boundary */
	movl	%eax, %esp
#else
    movl    ___djgpp_base_address, %eax
    addl	0x3C(%eax), %eax
    movl	0x60(%eax), %ecx /* 0x60 is offset SizeOfStackReserve */
    movl	%esp, %eax
    addl	$0x0FFF, %eax
    andb	$0x0F0, %ah
    movb	$0x00, %al
    subl	%ecx, %eax
	movl	%eax, ___djgpp_stack_limit	/* Bottom of stack */
#endif

	xorl	%ebp, %ebp
	pushl	$_frame_struct
	pushl	$_CRT0_EH_FRAME_BEGIN_
	call	___register_frame_info
	addl	$8, %esp
	call	___crt1_startup		/* run program */
	jmp	exit

no_memory:
	movb	$0xff, %al
	jmp	exit

/*-----------------------------------------------------------------------------*/

#define FREESEL(x) movw x, %bx; movw $0x0001, %ax; int $0x31

	.global	___exit
	.balign	16,,7
___exit:
	movb	4(%esp), %al
exit:
	movb	%al, %cl
	xorl	%eax,%eax
	movw	%ax,%fs
	movw	%ax,%gs
	cli				/* Just in case they didn't unhook ints */
	FREESEL(__go32_info_block+26)	/* selector for linear memory */
	FREESEL(___djgpp_ds_alias)	/* DS alias for rmcb exceptions */
#ifdef MULTIBLOCK
	testb	$0x8, __crt0_startup_flags+1		/* include/crt0.h */
	jz	9f
#endif
	FREESEL(sbrk16_api_seg)		/* sbrk cs */
	movw	sbrk16_first_byte+6,%dx /* selector for allocated DOS mem */
	movw	$0x101, %ax
	int	$0x31			/* Free block and selector */
9:
	movl	__stubinfo, %edx
	movl	STUBINFO_CS_SELECTOR(%edx), %eax
	movw	%ax, sbrk16_api_seg
	xorl	%edi, %edi
	movl	%edi, sbrk16_api_ofs	/* Offset is zero */

	movw	STUBINFO_DS_SELECTOR(%edx), %es
	movb	%cl, %dl		/* Exit status */
	movl	$exit16_first_byte, %esi
	movl	$(exit16_last_byte - exit16_first_byte), %ecx
	cld
	rep
	movsb

#if 0
	movw	%es,%ax			/* We will free stack! */
	movw	%ax,%ss
	movl	$0x400,%esp		/* Transfer buffer >= 1024 bytes */
#endif

#ifdef MULTIBLOCK
	movl	___djgpp_memory_handle_pointer, %ebx
	jmp	7f
6:	subl	$8, %ebx
	movl	(%ebx), %edi
	movw	2(%ebx), %si
	movw	$0x502, %ax
	int	$0x31
7:	cmpl	$___djgpp_memory_handle_list+8, %ebx
	jne	6b
#endif /* MULTIBLOCK */
	xorl	%ebp, %ebp				/* V1.10 bug fix */
	movl	___djgpp_memory_handle_list, %edi
	movl	___djgpp_memory_handle_list+2, %esi	/* Skip word prefixes */

#if 0
	FREESEL(%ds)
	movw	%cs, %bx
/* Call exit procedure with BX=32-bit CS; SI+DI=32-bit handle; DL=exit status */
	.byte 0x2e
	LJMP(sbrk16_api_ofs)
#else
	movb	$0x4c, %ah
    int		$0x21
#endif
/*-----------------------------------------------------------------------------*/

/*	.lcomm	__what_size_app_thinks_it_is, 4 */
.data
__what_size_app_thinks_it_is:
/*	.long	end */
	.long	-1
.text
	.lcomm	__what_we_return_to_app_as_old_size, 4
	.lcomm	__what_size_dpmi_thinks_we_are, 4

lock_memory:
	/* BX:CX should be linear address; size is pushed on stack */
	testb	$0x10, __crt0_startup_flags+1		/* include/crt0.h */
	jz	13f
	pushl	%esi
	pushl	%edi
	pushl	%eax
	movl	16(%esp),%edi
	movw	18(%esp),%si
	movw	$0x600,%ax
	int	$0x31
	popl	%eax
	popl	%edi
	popl	%esi
13:	ret	$4			/* Pop the argument */


#if 0
brk_hook_ret:
	ret
	.globl ___sbrk_brk_hook
___sbrk_brk_hook:
	.long	brk_hook_ret
#endif

	.global	___sbrk
	.balign	16,,7
___sbrk:
	movl	__what_size_app_thinks_it_is, %eax
	movl	4(%esp), %ecx			/* Increment size */
	addl	%ecx, %eax
	jnc	brk_common
	/* Carry is only set if a negative increment or wrap happens.  Negative
	   increment is semi-OK, wrap (only for multiple zone sbrk) isn't. */
	test	$0x80000000, %ecx		/* Clears carry */
	jnz	brk_common
	stc					/* Put carry back */
	jmp	brk_common

	.globl	___brk
	.balign	16,,7
___brk:
	movl	4(%esp), %eax
	clc

	.balign	16,,7
brk_common:
	pushl	%esi
	pushl	%edi
	pushl	%ebx

	movl	__what_size_app_thinks_it_is, %edx		/* save info */
	movl	%edx, __what_we_return_to_app_as_old_size
	movl	%eax, __what_size_app_thinks_it_is

	jc	10f						/* Wrap for multi-zone */
	cmpl	__what_size_dpmi_thinks_we_are, %eax		/* don't bother shrinking */
	jbe	brk_nochange

/* Current allocation not large enough, get another block */
10:	movl	%ecx, %eax					/* Add amt */
14:	pushl	%eax						/* Save orig */

/* Prevent handle exhaustion:  Block size of later allocated handles is larger.
   Block Size = 2^(16+handle#/32) which allows 512Mb on default 256 handles. */

	movl	___djgpp_memory_handle_pointer, %ecx
	xorl	%edx, %edx
	subl	$___djgpp_memory_handle_list, %ecx		/* 8*hand# */
	shrl	$8, %ecx	/* hand#/32, tuneable, big shifts = old way */
	incl	%edx						/* EDX = 1 */
	addb	$16, %cl					/* 2^16=64K */
	shll	%cl, %edx
	decl	%edx
	movl	%edx, %ecx
	notl	%edx
	addl	%ecx, %eax				/* Round up to block */
	andl	%edx, %eax

	movl	%eax, %edx					/* Save size */
	movl	%eax, %ecx
	movl	%eax, %ebx
	shrl	$16, %ebx					/* BX:CX size */
	movw	$0x501,%ax
	int	$0x31
	popl	%eax						/* Orig size */
	jc	brk_error

	pushw	%bx
	pushw	%cx
	popl	%ecx						/* Linear address */
	pushl	%edx						/* Size */
	call	lock_memory

	cmpl	%ecx, __what_size_dpmi_thinks_we_are		/* Back to back ? */
	je	4f
	movl	%ecx, __what_size_dpmi_thinks_we_are
	movl	%ecx, __what_we_return_to_app_as_old_size
4:
	movl	__what_we_return_to_app_as_old_size, %ebx	/* Base for new block */
	addl	%ebx, %eax					/* Final address */
	movl	%eax, __what_size_app_thinks_it_is
/* Note - save adjusted memory base and memory handle SI:DI here */
	movl	___djgpp_memory_handle_pointer, %ebx
	movl	%edi, (%ebx)
	movw	%si, 2(%ebx)
	movl	%ecx, 4(%ebx)
	addl	$8, %ebx
	cmpl	$___djgpp_memory_handle_list+2040, %ebx		/* At end? */
	je	11f
	movl	%ebx, ___djgpp_memory_handle_pointer		/* Only if not at end */
11:
	testb	$0x60, __crt0_startup_flags	/* include/crt0.h */
	jz	no_fill_sbrk_memory
	pushl	%ds
	popl	%es

	movl	__what_size_dpmi_thinks_we_are, %edi		/* set all newly resized bytes zero */
	movl	%edx, %ecx					/* Limit */
	xorl	%eax, %eax
	testb	$0x40, __crt0_startup_flags
	jz	no_deadbeef
	movl	$0xdeadbeef, %eax		/* something really easy to spot */
no_deadbeef:
	shrl	$2, %ecx			/* div 4 Longwords not bytes */
	cld
	rep
	stosl
no_fill_sbrk_memory:
	movl	%edx, __what_size_dpmi_thinks_we_are

brk_nochange:					/* successful return */
	movl	__what_we_return_to_app_as_old_size, %eax
	jmp	brk_return

brk_error:					/* error return */
	movl	__what_we_return_to_app_as_old_size, %eax
	movl	%eax, __what_size_app_thinks_it_is
	movl	$-1, %eax

brk_return:
	popl	%ebx
	popl	%edi
	popl	%esi
	ret

	.globl	__crt0_init_mcount
__crt0_init_mcount:
#ifdef IN_GCRT0
	jmp	__mcount_init
#else
	ret
#endif
