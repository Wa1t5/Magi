#!/usr/bin/env sh
###
# Author Waltz (Wa1t5)
# Project: Neon Genesis
###

# Kernel flags
[[ -z ${KERNEL_ARCH} ]] && export KERNEL_ARCH="i686"

# Build flags
export CXX="clang++"
export LD="ld.lld"
export LDFLAGS=-nostdlib
export CXXFLAGS_NO_STDLIBS=-ffreestanding\ -nostdlib\ -nostdinc\ -fno-builtin\ -fno-rtt
export CXXFLAGS_WARNINGS=-Wno-unused-command-line-argument
export CXXFLAGS=-c\ -std=c++2b\ -target\ ${KERNEL_ARCH}-none-elf\ -fuse-ld=ld.lld\ -fno-exceptions\ -fstack-protector-all\ ${CXXFLAGS_WARNINGS}\ ${CXX_FLAGS_NO_STDLIB}

# Reminders:
# In Clang -c serves to only run preprocess, assemble and compile, thus avoiding calls to gcc

# Clear previous build artifacts
function clear() {
  echo "[0] Clearing build artifacts"
  rm -rf out
}

function build() {
  clear

  echo "[1] Building..."
  
  # Recreate dir
  mkdir -p out/{boot,include/lilith,linker,bin}
  
  # Copy linker script
  cp adam/arch/${KERNEL_ARCH}/linker/linker.ld out/linker
  cp -r lilith/include/* out/include/lilith

  build_boot
  build_libc
  build_kernel
  link
}

function build_boot() {
  echo "[2] Building boot..."
    
  # Build boot image with clang 
  "$CXX" -c ${CXXFLAGS}  adam/arch/${KERNEL_ARCH}/boot/boot.asm -o out/bin/boot.lcl
}

# Build libc
function build_libc() {
  echo "[3] Building lilith..."
  for f in $(ls "lilith/src/"); do
    name_wo_ext=$(basename ${f} | awk -F. '{print $1}')
    "$CXX"  ${CXXFLAGS} lilith/src/${name_wo_ext}.cpp -o out/bin/${name_wo_ext}.lcl
  done
}

# Build kernel
function build_kernel() {
  echo "[4] Building adam..."
  for f in $(ls "adam/arch/${KERNEL_ARCH}/src/"); do
    
    name=$(basename ${f})
    name_wo_ext=$(basename ${f} | awk -F. '{print $1}')
    
    "$CXX"  ${CXXFLAGS} adam/arch/${KERNEL_ARCH}/src/${name} -o out/bin/${name_wo_ext}.lcl
   done;
}

# Link everything in one binary
function link() {
  echo "[5] Linking..."
  "$LD" ${LDFLAGS}  out/bin/*.lcl  -o out/boot/neon_genesis.kernel
}

# Run
function run() {
  echo "[6] Starting the first impact..."
  qemu-system-i386 -kernel out/boot/neon_genesis.kernel &
}


for f in $@; do 
  case ${f} in
    "--arch="*) export KERNEL_ARCH=$(echo ${f} | awk -F\= '{print $2}') ;;
    *) ${f} ;; # Get parameters and run as functions
  esac
  
  
done
