
	███████╗████████╗██████╗  █████╗ ██╗   ██╗ ██████╗  █████╗ ██╗  ██╗
	██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝ ██╔══██╗██║ ██╔╝
	███████╗   ██║   ██████╔╝███████║ ╚████╔╝ ███████╗ ╚█████╔╝█████╔╝ 
	╚════██║   ██║   ██╔══██╗██╔══██║  ╚██╔╝  ██╔═══██╗██╔══██╗██╔═██╗ 
	███████║   ██║   ██║  ██║██║  ██║   ██║   ╚██████╔╝╚█████╔╝██║  ██╗
	╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝  ╚════╝ ╚═╝  ╚═╝

[![forthebadge](https://img.shields.io/badge/BASED-gray?style=for-the-badge&logo=c&labelColor=546CAF)]()
[![forthebadge](https://img.shields.io/badge/Yacc-BASED-gray?style=for-the-badge&labelColor=991030&logoColor=darkgray)]()
[![forthebadge](https://img.shields.io/badge/Lex-BASED-gray?style=for-the-badge&labelColor=10AA10&logoColor=darkgray)]()

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

- Commands & Options|Arguments aka man-page
  ```bash
        stray68K an emulator for Motorola 68000.

        Modality
        -Assembler:
          -a [opts|args] -Invoke assembler. See help.
        -Emulator:
          -e [path] -STANDARD MODE. Input executable file. To generate it use assembler options.
          -s [path] -STEP-BY-STEP MODE. Like option '-e' but run executable file step by step (debug mode).

        Emulator options list
        [-q] -Mean quiet output.
              This option is prohibited in STEP-BY-STEP MODE.
        [-d] -Mean descriptive output.
              This option is prohibited in STANDARD MODE.
        [-t] -Perform a chrono calculation and print it.
              This option is prohibited in STEP-BY-STEP MODE.
        [-j] -Perform JSON machine encoding output.

        You cannot combine '-d' and '-q' options.
        You cannot combine '-j' and '-t' options.
        You cannot use JSON encoding option (-j) alone.
        You cannot use JSON chrono encoding (-j chrono) in step-by-step mode.

        JSON encoding commands
        [cpu]      -Mean cpu encoding.
        [ram]      -Mean ram encoding.
        [chrono]   -Mean chrono encoding (ms).
        [code]     -Mean operation code encoding (base 10).
        [mnemonic] -Mean mnemonic operation encoding.
        [concat]   -Perform JSON concat, must pass at least two listed above commands.

        STEP-BY-STEP MODE's options asked from stdin
        [s] -Asks for offsets and print current stack.
        [n] -Execute next istruction.
        [k] -Skip current step.
        [t] -Full skip steps. The execution proceeds to the end.
        
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
- To perform a ```execution``` with JSON encoding output
  ```bash
  $ ./stray68K -e <output_file_path>.B68 -j cpu time concat -q
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

