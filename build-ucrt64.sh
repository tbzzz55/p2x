#!/bin/sh
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-zlib mingw-w64-ucrt-x86_64-libtomcrypt
gcc main.c p2x.c pt.c -ltomcrypt -lz -static -Os -s -fvisibility=hidden -fno-ident -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables -fdata-sections -ffunction-sections -Wl,--gc-sections -Wl,--strip-all -o p2x.exe
