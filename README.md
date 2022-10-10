
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

Invoke for help
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
[AGPLV3](https://github.com/Mastro-Gibbs/stray68K/blob/main/LICENSE)