//Set The Ball Rolling ....
//The Entry point of this Library Starts Here .
#include "dos.h"

#define sgn(x) ((x<0)?-1:((x>0)?1:0))
#define rad(o) (o*M_PI)/180
#define word_out(port,register,value) \
	outp(port,(((word)value<<8) + register))
#define VIDEO_INT           0x10
#define SET_MODE            0x00
#define TEXT_MODE           0x03
#define VGA_256_COLOR_MODE  0x13
#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9
#define NUM_COLORS          256


typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

byte *VGA=(byte *)0xA0000000L;

word screen_width=320,screen_height=200;

void set_mode(byte mode)
{
union REGS regs;

regs.h.ah = SET_MODE;
regs.h.al = mode;
int86(VIDEO_INT, &regs, &regs);
}