#!/usr/bin/env bash

# Clear previous build artifacts
rm -rf out

# Recreate dir
mkdir -p out/boot/grub

# Copy grub.cfg to /boot/grub
cp src/grub.cfg out/boot/grub/

# Copy linker script
cp src/linker.* out/

# Build boot image with nasm
nasm -f elf32 -o out/boot.o src/boot/boot.asm

# Build kernel
clang++ -c -target i686-none-elf -fuse-ld=ld.lld -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-rtti -fno-exceptions -Wall src/adam/adam.cpp -o out/adam.o

# Link kernel
ld.lld  out/boot.o out/adam.o -o out/boot/neon_genesis.bin
