
  HXGUI Test Programs
  
  These are some test applications which may be useful in case of problems
  with HX's Win32 emulation:
    
  þ DITEST.EXE: a Win32 console application using DirectInput for keyboard
    and mouse and displaying the values received from these devices. As far
    as SDL is concerned: if DirectInput doesn't work, one can rename
    DINPUT.DLL to any other name. SDL will then fall back to use the standard
    Win32 messages for input and GDI DIBs for output.

  þ DSTEST.EXE: simple wave sound player (Win32 console). To check sound
    output with DirectSound.

  þ GETSB.EXE: displays information about a SoundBlaster device installed
    on the computer. HX requires at least a SoundBlaster Pro, which has a
    DSP version of 3.xx. For 16-bit sound a SoundBlaster 16 compatible
    device is required (DSP version >= 4).

  þ OGLTEST.EXE: this is an OpenGL sample (NeHe's OpenGL lesson 5).
    Screen resolution should be set to 32 bpp for it.

  þ PLAYWAVE.EXE: simple wave sound player (Win32 console) using Multimedia
    API. To check sound output with WinMM.

  þ SDLAUDIO.EXE: simple wave sound player using SDL.

  þ SDLTEST.EXE: this is a SDL application and will display mouse and   
    keyboard events. In 8 bpp graphics mode it might also be used to verify
    the palette is displayed correctly.

  þ TESTMIDI.EXE: tests if MPU-401 sound (midi) works. A SB 16 compatible
    card is required.

  þ WSTEST.EXE: test if the Winsocket emulation works. The program will
    try to find the internet address of a given host name.

  þ HTTPREAD.EXE: slightly more sophisticated Winsocket test. Reads a
    file (max 64 kB) via HTTP from a web server.


  Japheth
