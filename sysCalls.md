# System Calls In Linux

System calls are the fundamental interface between an application and the Linux kernel. They provide the means for a program to request services from the operating system. Here are some key points about system calls in Linux:

## What are System Calls?

System calls are functions used in the kernel to perform tasks that the user-level application does not have the privilege to execute directly. They act as a controlled entry point into the kernel, ensuring that the system's integrity and security are maintained.

## Common System Calls

Some of the most commonly used system calls in Linux include:

- `open()`: Opens a file.
- `read()`: Reads data from a file.
- `write()`: Writes data to a file.
- `close()`: Closes a file descriptor.
- `fork()`: Creates a new process.
- `exec()`: Replaces the current process image with a new one.
- `wait()`: Waits for a process to change state.
- `exit()`: Terminates a process.

## How System Calls Work

When a system call is made, the following steps occur:

1. The application program calls a library function (e.g., `printf`).
2. The library function sets up the system call and invokes a special CPU instruction (e.g., `int 0x80` on x86).
3. The CPU switches to kernel mode and executes the system call handler.
4. The kernel performs the requested service.
5. The CPU switches back to user mode, and control is returned to the application.

## Example

Here is an example of using the `write` system call in C:

```c
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        return 1; // Error opening file
    }
    const char *text = "Hello, World!";
    write(fd, text, 13);
    close(fd);
    return 0;
}
```

This program opens a file called `example.txt`, writes "Hello, World!" to it, and then closes the file.

System calls are essential for performing low-level operations in Linux, and understanding them is crucial for system programming.

**NOTE: We can find the system calls numbers defined in the file loacted at `/usr/include/x86_64-linux-gnu/asm/unistd_64.h`.**

### Implementing System Calls Directly Using Assembly on x86-64 Machine:

1. We First Open the Manul to know what asm instruction is used for our machine:

```shell
man 2 syscall
```

- _For the x86-64 machine the instruction is `syscall` and the system call number is stored in the **rax** register and the return value is returned in the **rax** too._
- _The arguemnts are `rdi`, `rsi`, `rdx`..etc. and they are mentioned in the manual too._

2. We create our assembly file with an extension called .nasm.

- We need to install nasm assembler to be used:

```shell
sudo apt install nasm
```

- We write the code to print a message on the terminal using syscalls.

```asm
global main

SECTION .data
msg: db "Hello World From x86_64 Machine", 0Ah, 0h
len_msg: equ $ - msg

SECTION .text
main:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg
        mov rdx, lenMsg
        syscall         ; write(1, msg, len_msg);

        mov r15, rax
        mov rax, 60
        mov rdi, r15
        syscall         ; exit(write_len)
```

- Then we save and assemble the file using nasm:
  ```shell
  nasm -f elf64 syscall64.nasm
  ```
- Last step is linking the file:

```shell
    ld syscall64.o --entry main -o my64syscall
```

## - `Strace` Tool:

### Using `strace` to Trace System Calls in Linux

`strace` is a powerful diagnostic, debugging, and instructional tool in Linux that allows you to trace system calls and signals made by a program. It is commonly used to understand how a program interacts with the operating system, debug issues, or analyze performance.

## Key Features of `strace`

- Monitors and logs all system calls made by a process.
- Displays the arguments passed to system calls and their return values.
- Tracks signals received by the process, including signal handlers.
- Can attach to a running process or start a new process for tracing.

## Common Use Cases

1. **Debugging**: Identify why a program is failing by observing system calls.
2. **Performance Analysis**: Detect bottlenecks by analyzing system call durations.
3. **Understanding Behavior**: Learn how a program interacts with files, networks, or other system resources.
4. **Troubleshooting**: Diagnose permission issues, missing files, or incorrect configurations.

## Basic Usage

1. **Trace a New Program**:

   ```bash
   strace ./program_name
   ```

   This command starts the program and traces all system calls it makes.

2. **Attach to a Running Process**:

   ```bash
   strace -p <pid>
   ```

   Replace `<pid>` with the process ID of the running program.

3. **Log Output to a File**:

   ```bash
   strace -o output.log ./program_name
   ```

   This saves the trace output to `output.log` for later analysis.

4. **Filter Specific System Calls**:

   ```bash
   strace -e open,read,write ./program_name
   ```

   This traces only the specified system calls (`open`, `read`, `write`).

5. **Count System Call Statistics**:
   ```bash
   strace -c ./program_name
   ```
   This provides a summary of system call usage, including counts and execution times.

**NOTE: `echo $?` this command is used to output the value returned from the last operation and `$?` is a special variable holding this value.**
