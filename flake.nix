{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    systems,
    nixpkgs,
    ...
  } @inputs: let
    eachSystem = f:
      nixpkgs.lib.genAttrs (import systems) (
        system:
          f nixpkgs.legacyPackages."${system}"
    );
  in {
    devShells = eachSystem (pkgs: {
      default = pkgs.llvmPackages_17.stdenv.mkDerivation {
        name = "neon_genesis";
        version = "0.0.1";
        nativeBuildInputs = with pkgs; [ 
          # Qemu for testing
          qemu 

          # LLVM Toolchain
          clang-tools_17
          llvmPackages_17.bintools
          llvmPackages_17.clang
          llvmPackages_17.compiler-rt
          llvmPackages_17.libcxx
          llvmPackages_17.libcxxabi
          llvmPackages_17.libunwind
          llvmPackages_17.lld
        ];
      };
    });
  };
}
