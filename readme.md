# SPL Compiler

A mini compiler for a pascal-like language.

## Dependency

- bison
- flex
- llvm-6.0 
- CMake 3.9 or higher version
- clang to make executable file
- Graphviz

## Usage

lib.sql and the generated binary should be placed under the same directory.

File `ast.dot` is automatically generated, and you will need it to visualize AST.

Usage: splc [-OPTIONS] inputfile
Options:

-o \<file\> Place the output into \<file\>

-s Generate assembly.

-ll Generate llvm-IR

-c Generate Object file

To generate executable file, run the following command:

```
clang -o <binary> <object>
```

visualization command

```
dot -Tpng -o ast.png ast.dot
```

