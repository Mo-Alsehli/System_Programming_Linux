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

### Implementing System Calls Directly Using Assembly on x86-64 Machine:

1. We First Open the Manul to know what asm instruction is used for our machine:

```shell
man 2 syscall
```

- _For the x86-64 machine the instruction is `syscall` and the system call number is stored in the **rax** register and the return value is returned in the **rax** too._
- _The arguemnts are `rdi`, `rsi`, `rdx`..etc. and they are mentioned in the manual too._
