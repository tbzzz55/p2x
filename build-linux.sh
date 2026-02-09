#!/bin/bash
sudo apt-get update
sudo apt-get install -y build-essential zlib1g-dev libtomcrypt-dev
gcc main.c p2x.c pt.c -ltomcrypt -lz -static -Os -s -fvisibility=hidden -fno-ident -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables -fdata-sections -ffunction-sections -Wl,--gc-sections -Wl,--strip-all -o p2x