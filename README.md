
	███████╗████████╗██████╗  █████╗ ██╗   ██╗ ██████╗  █████╗ ██╗  ██╗
	██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝ ██╔══██╗██║ ██╔╝
	███████╗   ██║   ██████╔╝███████║ ╚████╔╝ ███████╗ ╚█████╔╝█████╔╝ 
	╚════██║   ██║   ██╔══██╗██╔══██║  ╚██╔╝  ██╔═══██╗██╔══██╗██╔═██╗ 
	███████║   ██║   ██║  ██║██║  ██║   ██║   ╚██████╔╝╚█████╔╝██║  ██╗
	╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝  ╚════╝ ╚═╝  ╚═╝

[![forthebadge](https://img.shields.io/badge/BASED-gray?style=for-the-badge&logo=c&labelColor=546CAF)]()  
[![forthebadge](https://img.shields.io/badge/BASED-gray?style=for-the-badge&logo=qt&labelColor=16B216)]()  
[![forthebadge](https://img.shields.io/badge/Lex-BASED-gray?style=for-the-badge&labelColor=10AA10&logoColor=darkgray)]()  
[![forthebadge](https://img.shields.io/badge/Yacc-BASED-gray?style=for-the-badge&labelColor=991030&logoColor=darkgray)]()   

---                                                     

## Description
              
Stray motorola 68000 emulator, include assembler and emulator.  

UI branch, contains a graphics component developed in Qt/C++ 5.15.3 which aims to wrap the stray68K core.  


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
  But in the **stray68K** implementation there is no vector of routines stored in that offset. Simply, the system will go into a state known as **TRAP_STATE**, from which it cannot resume, which will terminate the executed program by associating the corresponding code and mnemonic of the routine that the OS should have executed. This situation is not true for numbers #14 and #15 which correspond to C routines for scanf and printf respectively. See below.    
  <br>
- **Operating mode**  
  Given the assumption that the TRAP vector does not correspond to routine addresses stored somewhere, the machine is in **supervisor mode** all the time.

#### Input/Output
- **How to**  
  By invoking **TRAP #14** or **TRAP #15** you can invoke a **scanf** or **printf**, respectively.
  * **TRAP #14**  
    First you will need a formatter string like in scanf. Commonly we will use a string that **must** be loaded into **A0** via the **LEA** operation. Based on the formatted string with placeholders the scans will be performed, any characters extraneous to the characters recognized as placeholder will be ignored.
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
        **Numbers 0 to 7** represent the register target index. **Mandatory**.  
        For some clarification see 'examples/IO/io.X68' file.  
      * %[**T**|**t**][**0**-**1**-**2**-**3**-**4**-**5**-**6**-**7**]  
        **T** | **t** symbolize time scanning, **Mandatory**. **0** to **7** represent the register target index, **Mandatory**. This placeholder will only be evaluated in TRAP #14 (scan) mode.  
  
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
  $ make -j<number_of_cpu_cores>
  ```
  ```bash
  $ cd build
  ```

  Enjoy. See [Usage](https://github.com/Mastro-Gibbs/stray68K#usage).

---

## Usage

- To run.
  ```bash
  $ ./stray68K 
  ```

---

## License
- Emulator License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/LICENSE)

- Assembler License  
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/src/assembler/LICENCE.txt)

