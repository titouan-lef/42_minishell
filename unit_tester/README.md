# Tester

## Description

Before starting the project, we created this tester that allowed us to perform unit tests. This allowed us to verify that the code was working properly after each update and to test new features. These unit tests are therefore used to test our internal functions, not the program itself. So, the tests were added gradually, throughout the project.

This tester uses Valgrind to detect memory leaks.

## Instructions

All commands are executed in the unit_tester directory.

> [!TIP]
> If readline or valgrind aren't installed, you can use the [nix terminal](../README.md#nix)

### Makefile

Use the provided `Makefile` to compile, run and manage the tester:

| Command | Description |
|--------|-------------|
| `make` / `make all` | Compile and run the tester |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executables |
| `make re` | Clean, recompile and run the tester |
