# Examples Directory Overview

This folder contains examples demonstrating different ways to interact with system calls in C and assembly. The examples are divided into two directories:

1. **cat_utility**: Contains a simple C program that mimics the `cat` command in Unix-like systems.
2. **syscall_examples**: Contains examples of system calls in both C and assembly (x86_64).

## Directory Structure

```
examples/
├── cat_utility/
│   └── cat_utility.c
└── syscall_examples/
    ├── syscall64.nasm
    └── sysCalls.c
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
