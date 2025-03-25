# Updated Examples Directory Overview

This repository contains examples demonstrating different ways to interact with system calls in C and assembly, as well as implementations of common Linux utilities. The examples are divided into three directories:

1. **cat_utility**: Contains a simple C program that mimics the `cat` command in Unix-like systems.
2. **syscall_examples**: Contains examples of system calls in both C and assembly (x86_64).
3. **linux_utilities**: Contains implementations of common Linux utilities (`copy`, `echo`, `move`, and `pwd`) in C.

## Directory Structure

```
examples/
├── cat_utility/
│   └── cat_utility.c
├── syscall_examples/
│   ├── syscall64.nasm
│   └── sysCalls.c
└── linux_utilities/
    ├── copy.c
    ├── echo.c
    ├── move.c
    └── pwd.c
```

## 1. cat_utility

### `cat_utility.c`

This C program is a simple implementation of the `cat` command, which reads the content of a file and prints it to the standard output.

- **Functionality**:

  - The program takes a single argument, which is the name of the file to be read.
  - It opens the file in read-only mode and reads its content in chunks of 100 bytes.
  - The content is then written to the standard output (stdout).

- **Usage**:

  ```bash
  ./cat_utility <file-name>
  ```

- **Error Handling**:
  - If the number of arguments is incorrect, the program prints an error message and exits.
  - If the file cannot be opened, an error message is displayed.
  - If the write operation fails, the program exits with an error.

## 2. syscall_examples

### `syscall64.nasm`

This is an assembly program written for x86_64 architecture that demonstrates how to make system calls directly in assembly.

- **Functionality**:

  - The program prints the message "Hello World From x86_64 Machine" to the standard output using the `write` system call.
  - After printing the message, the program exits using the `exit` system call.

- **Key Points**:
  - The `write` system call is invoked with the following parameters:
    - File descriptor: `1` (stdout)
    - Message buffer: `msg`
    - Message length: `len_msg`
  - The `exit` system call is invoked with the return value from the `write` system call.

### `sysCalls.c`

This C program demonstrates how to replace the standard `printf` function with a direct system call to `write`.

- **Functionality**:

  - The program writes the string "hello linux\n" to the standard output using the `write` system call.
  - If the `write` call fails, the program exits with an error.

- **Key Points**:
  - The `write` system call is used instead of `printf` to directly interact with the operating system.
  - The program showcases how system calls can be used in C to perform low-level operations.

## 3. linux_utilities

### `copy.c`

This C program implements a simple file copy utility, similar to the `cp` command in Linux.

- **Functionality**:

  - The program takes two arguments: the source file and the destination file.
  - It reads the content of the source file in chunks of 100 bytes and writes it to the destination file.
  - The destination file is created with read/write permissions for all users.

- **Usage**:

  ```bash
  ./copy <source-file> <destination-file>
  ```

- **Error Handling**:
  - If the number of arguments is incorrect, the program prints an error message and exits.
  - If either the source or destination file cannot be opened, an error message is displayed.
  - If the write operation fails, the program exits with an error.

### `echo.c`

This C program mimics the `echo` command in Linux, which prints its arguments to the standard output.

- **Functionality**:

  - The program takes any number of arguments and prints them to the standard output, separated by spaces.
  - It uses the `write` system call for output.

- **Usage**:

  ```bash
  ./echo <arguments...>
  ```

- **Error Handling**:
  - If the `write` operation fails, the program prints an error message and exits.

### `move.c`

This C program implements a file move utility, similar to the `mv` command in Linux.

- **Functionality**:

  - The program takes two arguments: the source file and the destination file.
  - It copies the content of the source file to the destination file and then deletes the source file.
  - The destination file is created with read/write permissions for all users.

- **Usage**:

  ```bash
  ./move <source-file> <destination-file>
  ```

- **Error Handling**:
  - If the number of arguments is incorrect, the program prints an error message and exits.
  - If either the source or destination file cannot be opened, an error message is displayed.
  - If the write operation fails, the program exits with an error.

### `pwd.c`

This C program mimics the `pwd` command in Linux, which prints the current working directory.

- **Functionality**:

  - The program retrieves the current working directory using the `getcwd` function and prints it to the standard output.
  - It uses the `write` system call for output.

- **Usage**:

  ```bash
  ./pwd
  ```

- **Error Handling**:
  - If `getcwd` fails, the program prints an error message and exits.
  - If the `write` operation fails, the program prints an error message and exits.

## How to Compile and Run

### cat_utility

1. Navigate to the `cat_utility` directory.
2. Compile the program:
   ```bash
   gcc cat_utility.c -o cat_utility
   ```
3. Run the program:
   ```bash
   ./cat_utility <file-name>
   ```

### syscall_examples

1. Navigate to the `syscall_examples` directory.
2. Compile the C program:
   ```bash
   gcc sysCalls.c -o sysCalls
   ```
3. Run the C program:
   ```bash
   ./sysCalls
   ```
4. Compile the assembly program (requires `nasm` and `ld`):
   ```bash
   nasm -f elf64 syscall64.nasm -o syscall64.o
   ld syscall64.o -o syscall64
   ```
5. Run the assembly program:
   ```bash
   ./syscall64
   ```

### linux_utilities

1. Navigate to the `linux_utilities` directory.
2. Compile all programs:
   ```bash
   gcc copy.c -o copy
   gcc echo.c -o echo
   gcc move.c -o move
   gcc pwd.c -o pwd
   ```
3. Run the programs:
   ```bash
   ./copy <source-file> <destination-file>
   ./echo <arguments...>
   ./move <source-file> <destination-file>
   ./pwd
   ```
