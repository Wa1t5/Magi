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
      default = pkgs.pkgsCross.i686-embedded.stdenvNoCC.mkDerivation {
        name = "neon_genesis";
        version = "0.0.1";
        nativeBuildInputs = with pkgs; [ clang lld  clang-tools qemu ];
      };
    });
  };
}
