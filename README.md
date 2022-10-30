
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
              
Stray motorola 68000 emulator, include assembler and emulator.  

#### Emulation Machine
The emulator is based on a **pseudo-state machine** and a series of functions that emulate the behavior of the operations performed by the Motorola 68000 processor.
Possible states:
  - **BEGIN_STATE**: initial state.
  - **EXECUTION_STATE**: state in which the machine executes the instructions.
  - **FINAL_STATE**: accepting final state.
  - **PANIC_STATE**: state in which an unresolvable condition occurred, such as internal errors, it's a no-accepting final state.
  - **TRAP_STATE**: the state in which a TRAP exception is raised, see below, it's a no-accepting final state.
  - **MERR_STATE**: state in which an internal error occurred during the assembly of the machine, it's a no-accepting final state.
  - **IO_STATE**: state in which the machine performs an IO type operation.

#### Assumption
This emulator tries to be as faithful as possible to the Motorola 68000 processor. But some things have been implemented differently:
- **TRAPS**  
  Depending on the number #xx used, the trap operation will jump to any of the 16 possible callbacks from the memory area \$80 to $BC.
  But in the **stray68K** implementation there is no vector of routines stored in that offset. Simply, the system will go into a state known as **TRAP_STATE**, from which it cannot resume, which will terminate the executed program by associating the corresponding code and mnemonic of the routine that the OS should have executed. This situation is not true for numbers #14 and #15 which correspond to C routines for scanf and printf respectively.   
  <br>
- **Operating mode**
  Given the assumption that the TRAP vector does not correspond to routine addresses stored somewhere, the machine is in **supervisor mode** all the time.

#### Input/Output
- **How to**
  By invoking **TRAP #14** or **TRAP #15** you can invoke a **scanf** or **printf**, respectively.
  * **TRAP #14**
    First you will need a formatter string like in scanf. Commonly we will use a string that **must** be loaded into **A0** via the **LEA** operation. Based on the formatter escapes the scans will be performed, any characters extraneous to the characters recognized as escapes will be ignored.
    Below are a number of escapes and placeholders.
  * **TRAP #15**
    Unlike the scan (TRAP #14), here, the presence of placeholders and escapes is not mandatory. It will be possible to print a classic string by loading its address in **A0** with the **LEA** operation and invoking **TRAP # 15**. **If placeholders and escapes** are evaluated in the string, a **dynamic formatting** of the string will be performed before printing.

- **Supported placeholders and escapes list**
    * ANSI escapes '**\033**'
    * Classic escapes: '**\n**', '**\t**', '**\r**', '**\\\\**'
    * **%** placeholders:
      * %[**B**-**W**-**L**][**A**-**D**-**X**][**0**-**1**-**2**-**3**-**4**-**5**-**6**-**7**]
      * %[**b**-**w**-**l**][**a**-**d**-**x**][**0**-**1**-**2**-**3**-**4**-**5**-**6**-**7**]
        **B-W-L** | **b-w-l** symbolize the value size to be printed, BYTE, WORD, LONG. **Mandatory**.
        **A-D-X** | **a-d-x** symbolize registers, A-a for base 16 address registers, D-d for base 10 data registers, X-x for base 16 data registers. Omitting these formatters will print the signed value in the **Dx** data register. **Not mandatory**.
        **Numbers 0 to 7** represent the register index. **Mandatory**.
  
      By concatenating these symbols it is possible to have all the **I/O combinations** on the registers.

About **26k**, but what? **:kissing_smiling_eyes:**

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

- Commands & Options and Arguments aka man-page
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
        You cannot combine JSON encoding option 'dump' and 'concat'.
        You cannot use JSON encoding option (-j) alone.
        You cannot use JSON chrono encoding (-j chrono) in step-by-step mode.

        JSON encoding commands
        [cpu]    -Mean cpu encoding.
        [ram]    -Mean ram encoding.
        [chrono] -Mean chrono encoding (ns).
        [op]     -Mean op mnemonic and code encoding (base 10).
        [io]     -Show io operation in JSON format.
        [dump]   -Perform sys dump in JSON format.
        [concat] -Perform JSON concat, must pass at least two listed above commands.

        STEP-BY-STEP MODE's options asked from stdin
        [s] -Asks for top address and print current stack.
        [r] -Asks for ram offsets and print selected ram chunk.
        [n] -Execute next istruction.
        [t] -Terminate the program. The execution proceeds to the end.
        
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


- Print help.
  ```bash
  $ ./stray68K 
  ```
- To perform a ```compilation```.
  ```bash
  $ ./stray68K -a -i examples/scripts/generic.X68 -o examples/scripts/generic.B68
  ```
- To perform a quiet ```execution```.
  ```bash
  $ ./stray68K -e examples/scripts/io.B68 -q
  ```
- To perform a quiet ```execution``` with cpu, ram and chrono dumps in JSON format.
  ```bash
  $ ./stray68K -e examples/scripts/io.B68 -j cpu ram chrono concat -q
  ```
- To perform a descriptive ```execution step by step```.
  ```bash
  $ ./stray68K -s examples/scripts/generic.B68 -d
  ```
- To perform a descriptive ```execution step by step``` with system dump in JSON format.
  ```bash
  $ ./stray68K -s examples/scripts/generic.B68 -d -j dump
  ```

---

## License
- Emulator License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/LICENSE)

- Assembler License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/src/assembler/LICENCE.txt)

