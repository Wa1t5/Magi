#!/usr/bin/env sh

###
# Author Waltz (Wa1t5)
# Project: Neon Genesis
###

# Build flags
export CXX="clang++"
export LD="ld.lld"
export CXXFLAGS_NO_STDLIBS=-ffreestanding\ -nostdlib\ -nostdinc\ -fno-builtin\ -fno-rtti
export CXXFLAGS=-target\ i686-none-elf\ -fuse-ld=ld.lld\ -fno-exceptions\ -Wno-unused-command-line-argument ${CXX_FLAGS_NO_STDLIB}
  
# Clear previous build artifacts
function clear() {
  echo "[0] Clearing build artifacts"
  rm -rf out
}

function build() {
  clear

  echo "[1] Building..."
  
  # Recreate dir
  mkdir -p out/boot/grub
  
  # Copy linker script
  cp src/linker.* out/

  build_boot
  build_libc
  build_kernel
  link
}

function build_boot() {
  echo "[2] Building boot..."
    
  # Build boot image with clang 
  "$CXX" -c ${CXXFLAGS}  src/boot/boot.asm -o out/boot.o
}

# Build libc
function build_libc() {
  echo "[3] Building libc..."
  "$CXX" -c ${CXXFLAGS} src/lilith/src/*.cpp -o out/lilith.o
}

# Build kernel
function build_kernel() {
  echo "[4] Building kernel..."
  "$CXX" -c ${CXXFLAGS} src/adam/adam.cpp -o out/adam.o
}

# Link everything in one binary
function link() {
  echo "[5] Linking..."
  "$LD"  out/boot.o out/adam.o  out/lilith.o -o out/boot/neon_genesis.bin
}

# Run
function run() {
  echo "[6] Running."
  qemu-system-i386 -kernel out/boot/neon_genesis.bin
}

# Get parameters and run as functions
for f in $@; do 
  "$f"
done
