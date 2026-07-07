# DOS Development Environment

My DOS development environment for DOS and DOSBox-X,
containing compilers, libraries, and tools for C/C++,
Pascal, Assembler, and retro-development.

## Quick Start

1. `git clone --recursive` this repo to a folder called `DOS`.
2. Install **DOSBox-X >= 2025.05.03**.
3. Open `DOSBOX-XRC` in an editor. Change `D:\WS\DOS\DOSROOT` to wherever you
   cloned the repo, e.g. `C:\Users\John\Workspace\DOS\DOSROOT`.
4. Copy `DOSBOX-XRC` to your DOSBox-X install directory as `dosbox-x.conf`.
5. Launch DOSBox-X.

## Directory Layout

Inside the DOSBox `C:\` drive (mapped to `DOSROOT\`):

```
C:\
├── EXTDEV\            — Development tools (compilers, libraries, utilities)
│   ├── 3DGFX\         — 3D Graphics Library (submodule)
│   ├── BC45\          — Borland C++ 4.5
│   ├── BORLANDC\      — Borland C++ 3.1 (disabled by default)
│   ├── DJGPP\         — DJGPP GCC (DOS)
│   ├── FG\            — FastGraph graphics library
│   ├── MASM\          — Microsoft Macro Assembler
│   ├── MLL\           — MLL compression suite (submodule)
│   ├── MSC\           — Microsoft C 7.0
│   ├── PP\            — Free Pascal Compiler
│   ├── TASM\          — Turbo Assembler
│   ├── TP\            — Turbo Pascal
│   ├── TVISION\       — Turbo Vision
│   ├── WATCOM\        — Open Watcom C/C++
│   ├── UPX520\        — UPX executable packer
│   ├── PKZIP\         — PKZIP/PKUNZIP
│   ├── EDB19\         — Zip-Case-X (ZCX)
│   └── HWINF623\      — HWiNFO hardware info
├── DTEXT23\           — DynaText Help System
├── HXRT216\           — HX DOS Extender (DPMI, disabled by default)
├── SB16\              — Sound Blaster 16 drivers
├── ULTRASND\          — Gravis UltraSound (GUS) drivers
├── MTCP\              — MTCP network stack (disabled by default)
├── WINDOWS\           — Windows 3.11 with networking (disabled by default)
└── AUTOEXEC.BAT       — System startup script
```

## AUTOEXEC.BAT

The startup script uses an `EXTDEV` variable pattern adapted from my Windows
CMD environment:

- **Recursion guard**: `IF "%AUTOEXECED%"=="YES" GOTO END` prevents re-entry.
- **EXTDEV variable**: `SET EXTDEV=C:\EXTDEV` as the base for all tools.
- **Conditional loading**: Each tool section checks for its directory with
  `IF NOT EXIST %EXTDEV%\TOOL\NUL GOTO NOTOOL`, enabling only what's installed.
- **System drivers** (SB16, ULTRASND, MTCP, WINDOWS) stay at `C:\` root.

Tools without `IF NOT EXIST` guards (3DGFX, FG, SB16 sound) load unconditionally.

### DPMI Notes

DJGPP uses its own `CWSDPMI` DPMI host (auto-loaded via GO32 stub). The HX DOS
Extender's `HDPMI16`/`HDPMI32` is disabled by default (`GOTO NOHX`) to avoid
conflicts. Uncomment to enable HX if needed.

## DOSBox-X Configuration

The `DOSBOX-XRC` file contains a pre-configured DOSBox-X setup. Below are the
key sections and what they enable.

### CPU & Memory

```
cputype = auto            — Auto-detects CPU (486/Pentium)
cycles  = auto            — Auto-scaled cycles for smooth performance
memsize = 32              — 32 MB extended memory (XMS)
```

`memsize = 32` provides 32 MB of extended memory, sufficient for DJGPP (GCC
needs ~8 MB DPMI), Windows 3.11, and most DOS development tools. CWSDPMI will
auto-configure itself from the available XMS.

### Video

```
machine  = svga_s3        — S3 Trio64V+ SVGA chipset emulation
output   = ttf            — TrueType font output (scalable, sharp text)
scaler   = normal2x       — 2x scaling for non-TTF modes
vmemsize = -1             — Auto video memory (up to 8 MB)
```

The S3 Trio64V+ chipset provides broad VBE (VESA BIOS Extensions) support:

|VBE Version|Modes|Max Resolution|
|-|-|-|
|VBE 1.2|800x600, 1024x768|256 colors @ 1024x768|
|VBE 2.0|Banked + Linear Frame Buffer|1600x1200 @ 256 colors|
|VBE 3.0|Protected mode interface|1600x1200 @ 16M colors|

Color depths: 8-bit (256), 15-bit (32K), 16-bit (64K), 24-bit (16M), 32-bit.

`output = ttf` renders the DOS console with smooth TrueType fonts at any
window size — ideal for reading code. Switch to `output = openglpp` for
pixel-perfect scaling in games. The `[ttf]` section allows selecting a custom
`.ttf` font file.

The `glshader` option enables GLSL shaders for CRT effects (scanlines,
curvature) with OpenGL output — great for retro gaming.

### Game Compatibility

This configuration targets development more than gaming, but handles most
DOS games well:

**VGA Games (1987–1995)**: Full compatibility at 320x200x256. The S3 chipset
handles Mode 13h, Mode-X, and all standard VGA text/graphics modes.

**SVGA Games (1992–1998)**: VBE 2.0 linear framebuffer support means most
SVGA titles work — including those using DJGPP + Allegro, Watcom + DOS/4GW,
or Borland BGI at higher resolutions.

**Known quirks**:
- Build engine games (Duke3D, Shadow Warrior) benefit from `vmemsize = 4`
  for triple buffering.
- Some 386/486 era games timing-sensitive games may need `cputype = 486`
  or `cycles = fixed 20000` instead of `auto`.
- Sound Blaster 16 is the safest choice; GUS is available but less tested.

**Windows 3.11**: The S3 Trio64V+ driver (`S3TRIO.DRV`) is pre-installed with
800x600 @ 16M colors. Higher resolutions can be set via Windows Display
settings if needed.

### Sound

Two sound cards are pre-configured:

**Sound Blaster 16** (primary):

```
[SBLaster]
sbtype      = sb16         — Creative Sound Blaster 16
sbbase      = 220           — I/O port 0x220
sbirq       = 5             — IRQ 5
sbdma       = 1             — 8-bit DMA channel 1
sbdma16     = 5             — 16-bit DMA channel 5
mididevice  = default       — FM synthesis via OPL3
```

The `AUTOEXEC.BAT` sets the `BLASTER` environment variable and runs
`DIAGNOSE /S` + `MIXERSET /P /Q` to initialize the card. In Windows 3.11, the
SB16 driver is loaded via `SYSTEM.INI`:

```ini
[drivers]
Wave=sb16snd.drv
MIDI=sb16fm.drv
```

**Gravis UltraSound** (secondary):

```
gusbase = 240              — I/O port 0x240
gusirq  = 3                — IRQ 3
gusdma  = 3                — DMA channel 3
ultradir = C:\ULTRASND     — GUS driver directory
```

The `ULTRADIR` and `ULTRASND` environment variables are set by `AUTOEXEC.BAT`.

### Networking (NE2000 / Packet Driver)

The MTCP stack provides TCP/IP over a packet driver. The NE2000 NIC is
emulated by DOSBox-X:

```
[NE2000]
ne2000     = true            — Enable NE2000 ethernet emulation
ne2000c    = 0x60            — Software interrupt 0x60 for packet driver
ne2000irq  = 3               — IRQ 3
ne2000io   = 0x300           — I/O port 0x300
macaddr    = AC:DE:48:89:2D:EB  — MAC address (change if on same bridge)
realnic    = tap              — TAP or bridged adapter on host
```

On the DOS side, `AUTOEXEC.BAT` loads the packet driver and obtains an IP via
DHCP:

```batch
SET MTCP_HOME=C:\MTCP
SET PKTDRV_NAME=NE2000
SET PKTDRV_ARGS=0x60 3 0x300
NE2000 0x60 3 0x300
DHCP
```

TCP/IP utilities included with MTCP: `PING`, `TELNET`, `FTP`, `NETSTAT`,
`IPCONFIG`, `TRACERT`, `ROUTE`, and more — all in `C:\MTCP\BIN`.

To enable networking, remove the `REM` before `GOTO NOMTCP` in `AUTOEXEC.BAT`.

## Windows 3.11

Windows 3.11 for Workgroups is installed at `C:\WINDOWS` with full networking
(WFW 3.11 TCP/IP stack via MSTCP). Enable it by removing the `REM` before
`GOTO NOWIN` in `AUTOEXEC.BAT`.

### Network Stack

Windows networking uses the NDIS driver model over the same NE2000 adapter.
Configuration is in `C:\WINDOWS\SYSTEM.INI`:

```ini
[386Enh]
network=*vnetbios,*vwc,vnetsup.386,vredir.386,vserver.386
netcard=ne2000.386
transport=vip.386,vdhcp.386,vtdi.386,vtcp.386,vnbt.386,netbeui.386
```

The `PROTOCOL.INI` and `SYSTEM.INI` files set up the NDIS wrapper, TCP/IP
binding, DHCP client, and NetBEUI. Shares can be accessed via
**File Manager** → **Disk** → **Connect Network Drive**.

### Sound in Windows

SB16 drivers pre-installed. MCI drivers for WaveAudio, MIDI Sequencer, and
CD Audio are configured in `SYSTEM.INI [mci]` and `WIN.INI`.

### Startup Flow

When enabled, `AUTOEXEC.BAT` runs:

```batch
SET WINDIR=C:\WINDOWS
DEVICE %WINDIR%\IFSHLP.SYS    — Installable File System helper
%WINDIR%\NET.EXE START        — Start the network redirector
IF EXIST %WINDIR%\FAKESHAR.COM %WINDIR%\FAKESHAR.COM  — Enable file sharing
%WINDIR%\WIN.COM              — Launch Windows 3.11
```

Press `Ctrl+F9` to exit Windows back to DOS.

## Compilers

|Tool|Path|Command|
|-|-|-|
|Borland C++ 3.1|`C:\EXTDEV\BORLANDC\BIN\BCC.EXE`|`bcc`|
|Borland C++ 4.5|`C:\EXTDEV\BC45\BIN\BCC.EXE`|`bcc`|
|Borland C++ 4.5 (IDE)|`C:\EXTDEV\BC45\BIN\BCW.EXE`|`bcw`|
|DJGPP GCC|`C:\EXTDEV\DJGPP\BIN\GCC.EXE`|`gcc`|
|Turbo Assembler|`C:\EXTDEV\TASM\BIN\TASM.EXE`|`tasm`|
|Turbo Pascal|`C:\EXTDEV\TP\TURBO.EXE`|`turbo`|
|Free Pascal|`C:\EXTDEV\PP\BIN\GO32V2\PPC386.EXE`|`ppc386`|
|Open Watcom|`C:\EXTDEV\WATCOM\BINW\WCL.EXE`|`wcl`|
|Microsoft C 7.0|`C:\EXTDEV\MSC\BIN\CL.EXE`|`cl`|
|Microsoft MASM|`C:\EXTDEV\MASM\BIN\ML.EXE`|`ml`|

## Building MLL

The MLL compression suite supports multiple platforms:

```
BUILD DJGPP     — DJGPP GCC (DOS, uses CWSDPMI)
BUILD MSVC      — Microsoft Visual C++ (Windows)
BUILD MINGW     — MinGW-w64 (Windows)
```

The script auto-detects `%EXTDEV%` for DJGPP paths under DOSBox.

## Submodules

- **3DGFX** ([github.com/guilt/3DGFX](https://github.com/guilt/3DGFX)) — 3D
  graphics library with software rendering, BMP loader, unicode, and examples.
- **MLL** ([github.com/guilt/MLL](https://github.com/guilt/MLL)) — Multi-Layer
  Lossless compression suite with PSNR evaluation.
- **EP** ([github.com/guilt/EP](https://github.com/guilt/EP)) — Installer — 
  Extractor/Packer for DOS & Windows

Clone with `--recursive` or run `git submodule update --init --recursive`.

## License

[MIT License](LICENSE.MD).

## Feedback

All feedback welcome!

- Author: Karthik Kumar Viswanathan
- Web: http://karthikkumar.org
- Email: me@karthikkumar.org
