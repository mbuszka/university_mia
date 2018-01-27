with import <nixpkgs> {}; {
  env = stdenv.mkDerivation {
    name = "test";
  };
}