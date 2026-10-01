{
	description = "Minishell";

	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs?ref=nixpkgs-unstable";
	};

	outputs = { nixpkgs, ... }:
		let
			pkgs = import nixpkgs {
				system = "x86_64-linux";
			};
			stdenv = pkgs.llvmPackages_23.stdenv;
		in {
			devShells.x86_64-linux.default = (pkgs.mkShell.override {
				inherit stdenv;
			}) {
				packages = with pkgs; [
					valgrind
					readline
				];
				shellHook = ''
					source ${pkgs.bash-completion}/share/bash-completion/bash_completion
				'';
			};
		};
}