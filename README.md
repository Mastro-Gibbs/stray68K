
	███████╗████████╗██████╗  █████╗ ██╗   ██╗ ██████╗  █████╗ ██╗  ██╗
	██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝ ██╔══██╗██║ ██╔╝
	███████╗   ██║   ██████╔╝███████║ ╚████╔╝ ███████╗ ╚█████╔╝█████╔╝ 
	╚════██║   ██║   ██╔══██╗██╔══██║  ╚██╔╝  ██╔═══██╗██╔══██╗██╔═██╗ 
	███████║   ██║   ██║  ██║██║  ██║   ██║   ╚██████╔╝╚█████╔╝██║  ██╗
	╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝  ╚════╝ ╚═╝  ╚═╝

[![forthebadge](https://img.shields.io/badge/C-BASED-gray?style=for-the-badge&logo=c&labelColor=0000FF&logoColor=darkgray)]()
[![forthebadge](https://img.shields.io/badge/Yacc-BASED-gray?style=for-the-badge&labelColor=0000FF&logoColor=darkgray)]()
[![forthebadge](https://img.shields.io/badge/Lex-BASED-gray?style=for-the-badge&labelColor=0000FF&logoColor=darkgray)]()

---                                                     

## Description
              
Stray motorola 68000 emulator, include assembler and emulator

---

## Compiling

Just clone and invoke makefile

---

## Usage

- Commands & Options|Arguments
  ```bash
        stray68K: emulator for Motorola 68000.
        
        Options:
         -a [opts|args]   -Invoke assembler. See below.
         -e [path]        -Input executable file. To generate it use assembler options, must be .B68 file extesion.
         -s [path]        -Like option '-e' but run executable file step by step, must be .B68 file extesion.
         -[e|s] [path] -d -Like options '-e' and '-s' but prints opcode and mnemonic.
         -[e|s] [path] -q -Like options '-e' and '-s' but but avoid to print system status (quiet).
        
        Step by step mode options asked from stdin:
           'c' -Print a snapshot of the cpu.
           'm' -Print a snapshot of the ram, asks for start and end addresses to extract a ram slice.
           'b' -Options c and m combined together.
           'a' -Options b combined with auto ram slice printing.
           's' -Skip current step.
           't' -Full skip steps. The execution proceeds to the end.
        
        Assembler: an assembler for the Motorola 68000. (thanks to Clownacy)
        
        Options:
         -i [path] -Input file, must be .X68 file extesion.
         -o [path] -Output file, must be .B68 file extesion.
         -l [path] -Listing file. Optional.
         -s [path] -asm68k-style symbol file. Optional.
         -c        -Enable case-insensitive mode.
         -b        -Enable Bison's debug output.
         -d        -Allow EQU/SET to descope local labels.
  ```


- Invoke for help
  ```bash
  $ ./stray68K 
  ```
- To perform a ```compilation```
  ```bash
  $ ./stray68K -a -i <input_file_path>.X68 -o <output_file_path>.B68
  ```
- To perform a ```execution```
  ```bash
  $ ./stray68K -e <output_file_path>.B68 -q
  ```
- To perform a ```execution step by step```
  ```bash
  $ ./stray68K -s <output_file_path>.B68 -d
  ```

---

## License
- Emulator License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/LICENSE)

- Assembler License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/assembler/LICENCE.txt)

