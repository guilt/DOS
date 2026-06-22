/* READCHAR.H - Key codes, masks, and macros for use with ReadChar in
 *              custom PWB extensions
 *
 * Copyright (C) Microsoft Corp. 1991-1992, All Rights Reserved
 *
 */

/*
 *  The low word of the ReadChar return value is the ASCII code of
 *  the key, if there is one. If there is no ASCII code for the
 *  key, it is the virtual key code.
 *
 */

/*  For codes lower than VK_MIN, there is no virtual key code: it
 *  is an ASCII code. ASCII is used mostly for punctuation keys.
 */
#define VK_MIN          0x100

#define VK_LBUTTON      0x101
#define VK_RBUTTON      0x102
#define VK_CANCEL       0x103
#define VK_MBUTTON      0x104
#define VK_BACK         0x108
#define VK_TAB          0x109
#define VK_CLEAR        0x10C
#define VK_RETURN       0x10D
#define VK_SHIFT        0x110
#define VK_CONTROL      0x111
#define VK_ALT          0x112
#define VK_PAUSE        0x113
#define VK_CAPLOCK      0x114

#define VK_ESCAPE       0x11B
#define VK_SPACE        0x120
#define VK_PRIOR        0x121   /* Page Up   */
#define VK_NEXT         0x122   /* Page Down */
#define VK_END          0x123
#define VK_HOME         0x124
#define VK_LEFT         0x125
#define VK_UP           0x126
#define VK_RIGHT        0x127
#define VK_DOWN         0x128

#define VK_0            0x130
#define VK_1            0x131
#define VK_2            0x132
#define VK_3            0x133
#define VK_4            0x134
#define VK_5            0x135
#define VK_6            0x136
#define VK_7            0x137
#define VK_8            0x138
#define VK_9            0x139

#define VK_A            0x141
#define VK_B            0x142
#define VK_C            0x143
#define VK_D            0x144
#define VK_E            0x145
#define VK_F            0x146
#define VK_G            0x147
#define VK_H            0x148
#define VK_I            0x149
#define VK_J            0x14A
#define VK_K            0x14B
#define VK_L            0x14C
#define VK_M            0x14D
#define VK_N            0x14E
#define VK_O            0x14F
#define VK_P            0x150
#define VK_Q            0x151
#define VK_R            0x152
#define VK_S            0x153
#define VK_T            0x154
#define VK_U            0x155
#define VK_V            0x156
#define VK_W            0x157
#define VK_X            0x158
#define VK_Y            0x159
#define VK_Z            0x15A

#define VK_INSERT       0x12D
#define VK_DELETE       0x12E

#define VK_NUMPAD0      0x160
#define VK_NUMPAD1      0x161
#define VK_NUMPAD2      0x162
#define VK_NUMPAD3      0x163
#define VK_NUMPAD4      0x164
#define VK_NUMPAD5      0x165
#define VK_NUMPAD6      0x166
#define VK_NUMPAD7      0x167
#define VK_NUMPAD8      0x168
#define VK_NUMPAD9      0x169
#define VK_MULTIPLY     0x16A   /* *  */
#define VK_ADD          0x16B   /* +  */
#define VK_SEPARATOR    0x16C   /* NUM in Kanji PWB */
#define VK_SUBTRACT     0x16D   /* -  */
#define VK_DECIMAL      0x16E   /* .  */
#define VK_DIVIDE       0x16F   /* /  */

#define VK_F1           0x170
#define VK_F2           0x171
#define VK_F3           0x172
#define VK_F4           0x173
#define VK_F5           0x174
#define VK_F6           0x175
#define VK_F7           0x176
#define VK_F8           0x177
#define VK_F9           0x178
#define VK_F10          0x179
#define VK_F11          0x17A
#define VK_F12          0x17B
#define VK_F13          0x17C
#define VK_F14          0x17D
#define VK_F15          0x17E
#define VK_F16          0x17F

#define VK_NUMLOCK      0x190
#define VK_SCRLOCK      0x191


/*  Masks for fields of the high word of the long returned by
 *  ReadChar
 */
#define KK_EXTENDED     0x8000  /* From extended number pad     */
#define KK_CAPLOCK      0x4000  /* CAPSLOCK is turned ON        */
#define KK_NUMLOCK      0x2000  /* NUMLOCK is turned ON         */
#define KK_SCRLOCK      0x1000  /* SCROLLLOCK is ON             */
#define KK_ALT          0x0800  /* The ALT key is held down     */
#define KK_CONTROL      0x0400  /* The CONTROL key is held down */
#define KK_SHIFT        0x0200  /* The SHIFT key is held down   */
#define KK_VK           0x01FF  /* The virtual key code         */

/*  Macros to extract parts of key record */

/*
 *  LOWORD(Key)            ASCII code, VK code if no ASCII code
 *  HIWORD(Key) & KK_VK    VK code always
 *  HIWORD(Key) & ~KK_VK   Shift state
 *  KeyCode & KK_VK        VK code, or ASCII if VK is VK_MIN
 *  KeyCode & ~KK_VK       Shift state
 *
 */

#ifndef WORD
typedef unsigned short WORD;
#endif
#ifndef DWORD
typedef unsigned long  DWORD;
#endif

#define LOWORD(l)       ((WORD)(l))
#define HIWORD(l)       ((WORD)(((DWORD)(l) >> 16) & 0xffff))

#define VKEYSTATE(ks)   (HIWORD(ks) & ~KK_VK)
#define VKEYCODE(ks)    ((HIWORD(ks) & KK_VK) == \
                            VK_MIN ? LOWORD(ks) : HIWORD(ks) & KK_VK)

#define KEYCODE(k)      ((k) & (KK_VK|KK_EXTENDED))
#define KEYSHIFT(k)     ((k) & ~KK_VK)

/*  Test macros: Booleans that affirm the specified state  */

#define FKEYCTRL(k)     (KEYSHIFT(k) & KK_CONTROL)
#define FKEYALT(k)      (KEYSHIFT(k) & KK_ALT)
#define FKEYSHIFT(k)    (FISLETTER(k) ? \
                            (((KEYSHIFT(k) & (KK_SHIFT)) == 0) != \
                            (((KEYSHIFT(k) & (KK_CAPLOCK)) == 0) \
                             || FKEYCTRL(k))) \
                            : (KEYSHIFT(k) & (KK_SHIFT)))
#define FISLETTER(k)    ((KEYCODE(k) >= VK_A) && (KEYCODE(k) <= VK_Z))
