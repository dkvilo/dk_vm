{ pkgs ? import <nixpkgs> {} }:

with pkgs;

let
  ubuntuPackages = import <nixpkgs> {
    system = "x86_64-linux";
  };
in
mkShell {
  buildInputs = with ubuntuPackages; [
    clang
    binutils
  ];
}
