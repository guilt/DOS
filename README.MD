# DOS Development Environment

My DOS development environment for DOS and DOSBox-X, 
containing compilers, libraries, and tools for C/C++,
Pascal, Assembler, and retro-development.

## Quick Start

1. `git clone --recursive` this repo to a folder called `DOS`.
2. Install **DOSBox-X >= 2025.05.03**.
3. Open `DOSBOX-XRC` in an editor. Change `D:\\WS\\DOS\\DOSROOT` to wherever you
cloned the repo, e.g. `C:\\Users\\John\\Workspace\\DOS\\DOSROOT`.
4. Copy `DOSBOX-XRC` to your DOSBox-X install directory as `dosbox-x.conf`.
5. Launch DOSBox-X.

## Directory Layout

Inside the DOSBox `C:\\` drive (mapped to `DOSROOT\\`):

```
C:\\
├── EXTDEV\\            — Development tools (compilers, libraries, utilities)
│   ├── 3DGFX\\         — 3D Graphics Library (submodule)
│   ├── BC45\\          — Borland C++ 4.5
│   ├── BORLANDC\\      — Borland C++ 3.1 (disabled by default)
│   ├── DJGPP\\         — DJGPP GCC (DOS)
│   ├── FG\\            — FastGraph graphics library
│   ├── MASM\\          — Microsoft Macro Assembler
│   ├── MLL\\           — MLL compression suite (submodule)
│   ├── MSC\\           — Microsoft C 7.0
│   ├── PP\\            — Free Pascal Compiler
│   ├── TASM\\          — Turbo Assembler
│   ├── TP\\            — Turbo Pascal
│   ├── TVISION\\       — Turbo Vision
│   ├── WATCOM\\        — Open Watcom C/C++
│   ├── UPX520\\        — UPX executable packer
│   ├── PKZIP\\         — PKZIP/PKUNZIP
│   ├── EDB19\\         — Zip-Case-X (ZCX)
│   └── HWINF623\\      — HWiNFO hardware info
├── HXRT216\\           — HX DOS Extender (DPMI, disabled by default)
├── SB16\\              — Sound Blaster 16 drivers
├── MTCP\\              — MTCP network stack (disabled by default)
├── WINDOWS\\           — Windows 3.11  (disabled by default)
└── AUTOEXEC.BAT        — System startup script
```

## AUTOEXEC.BAT

The startup script uses an `EXTDEV` variable pattern adapted from my Windows
CMD environment:

* **Recursion guard**: `IF "%AUTOEXECED%"=="YES" GOTO END` prevents re-entry.
* **EXTDEV variable**: `SET EXTDEV=C:\\EXTDEV` as the base for all tools.
* **Conditional loading**: Each tool section checks for its directory with
`IF NOT EXIST %EXTDEV%\\TOOL\\NUL GOTO NOTOOL`, enabling only what's installed.
* **System drivers** (SB16, MTCP, WINDOWS) stay at `C:\\` root and load normally.

Tools without `IF NOT EXIST` guards (3DGFX, FG, SB16 sound) load unconditionally.

### DPMI Notes

DJGPP uses its own `CWSDPMI` DPMI host (auto-loaded via GO32 stub). The HX DOS
Extender's `HDPMI16`/`HDPMI32` is disabled by default (`GOTO NOHX`) to avoid
conflicts. Uncomment to enable HX if needed.

## Compilers

|Tool|Path|Command|
|-|-|-|
|Borland C++ 3.1|`C:\\EXTDEV\\BORLANDC\\BIN\\BCC.EXE`|`bcc`|
|Borland C++ 4.5|`C:\\EXTDEV\\BC45\\BIN\\BCC.EXE`|`bcc`|
|Borland C++ 4.5|`C:\\EXTDEV\\BC45\\BIN\\BCW.EXE`|`bcc32` (IDE: `bcw`)|
|DJGPP GCC|`C:\\EXTDEV\\DJGPP\\BIN\\GCC.EXE`|`gcc`|
|Turbo Assembler|`C:\\EXTDEV\\TASM\\BIN\\TASM.EXE`|`tasm`|
|Turbo Pascal|`C:\\EXTDEV\\TP\\TURBO.EXE`|`turbo`|
|Free Pascal|`C:\\EXTDEV\\PP\\BIN\\GO32V2\\PPC386.EXE`|`ppc386`|
|Open Watcom|`C:\\EXTDEV\\WATCOM\\BINW\\WCL.EXE`|`wcl`|
|Microsoft C 7.0|`C:\\EXTDEV\\MSC\\BIN\\CL.EXE`|`cl`|
|Microsoft MASM|`C:\\EXTDEV\\MASM\\BIN\\ML.EXE`|`ml`|

## Windows 3.11

Windows 3.11 is installed at `C:\\WINDOWS`.

## Submodules

* **3DGFX** ([github.com/guilt/3DGFX](https://github.com/guilt/3DGFX)) — 3D
graphics library with software rendering, BMP loader, and examples.
* **MLL** ([github.com/guilt/MLL](https://github.com/guilt/MLL)) — Multi-Layer
Lossless compression suite with PSNR evaluation.

Clone with `--recursive` or run `git submodule update --init --recursive`.

## Configuration

`DOSBOX-XRC` is the DOSBox-X configuration file. Key settings:

```
memsize = 32            — 32 MB extended memory
machine = svga\_s3      — SVGA S3 video chipset
output = ttf            — TrueType font output
```

The `\[autoexec]` section mounts `C:` to your `DOSROOT` and runs `AUTOEXEC.BAT`.

## License

[MIT License](LICENSE.md).

## Feedback

All feedback welcome!

* Author: Karthik Kumar Viswanathan
* Web: http://karthikkumar.org
* Email: me@karthikkumar.org

