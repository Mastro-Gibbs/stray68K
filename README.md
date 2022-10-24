
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

About 25k, but what? :)

---

## Compiling

Just clone and invoke makefile   

  ```bash
  $ git clone https://github.com/Mastro-Gibbs/stray68K.git
  ```
  ```bash
  $ cd stray68K
  ```
  ```bash
  $ make
  ```
  ```bash
  $ cd build
  ```

  Enjoy. See [Usage](https://github.com/Mastro-Gibbs/stray68K#usage).

---

## Usage

- Commands & Options|Arguments
  ```bash
        stray68K: emulator for Motorola 68000.
        
        Options:
         -a [opts|args]     -Invoke assembler. See below.
         -e [path]  [-q|-t] -Input executable file. To generate it use assembler options.
                             [-q] mean quiet option.
                             [-t] mean timer option.

         -s [path]  [-d]    -Like option '-e' but run executable file step by step (debug mode).
                             [-d] mean descriptive opt.
           
        step-by-step mode options asked from stdin:
            's' -Asks for offsets and print current stack.
            'n' -Execute next istruction.
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
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/src/assembler/LICENCE.txt)

