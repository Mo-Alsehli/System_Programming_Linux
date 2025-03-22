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

### Explanation of System Call Handling in Linux

> Quoted From LPI Book

When a system call is invoked, the kernel handles it through a well-defined process. Here's a breakdown of the steps:

1. **Saving Register Values**:

   - The kernel saves the current state of the CPU registers onto the kernel stack to preserve the execution context of the user program.

2. **Validating the System Call Number**:

   - The kernel checks if the system call number provided by the user program is valid and corresponds to a supported system call.

3. **Executing the System Call Service Routine**:

   - The kernel uses the system call number to locate the appropriate service routine in the `sys_call_table`.
   - If the service routine requires arguments, their validity is checked (e.g., ensuring memory addresses are within the user space).
   - The service routine performs the requested operation, which may involve modifying user memory or transferring data between user and kernel memory.
   - The routine returns a result or status code to the kernel.

4. **Restoring Register Values**:

   - The kernel restores the saved CPU register values from the kernel stack to resume the user program's execution context.

5. **Returning to User Mode**:
   - The kernel places the system call's return value on the stack and switches the processor back to user mode, returning control to the user program.

This structured approach ensures that system calls are handled securely and efficiently, maintaining the stability and integrity of the operating system.

## `open()` System Call:

The `open()` system call is used to open a file in Linux. It returns a file descriptor, which is a non-negative integer used to identify the opened file in subsequent system calls.

#### Syntax

```c
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *pathname, int flags, mode_t mode);
```

#### Parameters

1. **`pathname`**: The path to the file to be opened.
2. **`flags`**: Specifies the access mode and other options. Common flags include:
   - `O_RDONLY`: Open for read-only access.
   - `O_WRONLY`: Open for write-only access.
   - `O_RDWR`: Open for both reading and writing.
   - `O_CREAT`: Create the file if it does not exist (requires `mode`).
   - `O_TRUNC`: Truncate the file to zero length if it exists.
   - `O_APPEND`: Append data to the end of the file.
3. **`mode`**: Specifies the permissions to use if the file is created (used with `O_CREAT`). Common values include:
   - `S_IRUSR`: Read permission for the owner.
   - `S_IWUSR`: Write permission for the owner.
   - `S_IRGRP`: Read permission for the group.
   - `S_IROTH`: Read permission for others.

#### Return Value

- On success: Returns a file descriptor (non-negative integer).
- On failure: Returns `-1` and sets `errno` to indicate the error.

#### Example

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    write(fd, "Hello, World!", 13);
    close(fd);
    return 0;
}
```

#### Notes

- Always check the return value of `open()` to handle errors.
- Use `close()` to release the file descriptor when done.
- The `mode` parameter is ignored if `O_CREAT` is not specified.
- The `errno` variable can be used to determine the specific error if `open()` fails.

#### Common Errors

- `EACCES`: Permission denied.
- `ENOENT`: File does not exist, and `O_CREAT` is not specified.
- `EEXIST`: File exists, and `O_CREAT | O_EXCL` is specified.
- `EMFILE`: Too many file descriptors are open in the process.

The `open()` system call is fundamental for file I/O operations in Linux and is often used in conjunction with other system calls like `read()`, `write()`, and `close()`.

## `read()` System Call

The `read()` system call is used to read data from a file descriptor into a buffer.

#### Syntax

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

#### Parameters

1. **`fd`**: The file descriptor to read from, which is returned from the `open()` operation.
2. **`buf`**: A pointer to the buffer where the read data will be stored.
3. **`count`**: The maximum number of bytes to read.

#### Return Value

- On success: Returns the number of bytes actually read (can be less than `count`).
- On failure: Returns `-1` and sets `errno` to indicate the error.
- On end-of-file: Returns `0`.

#### Example

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   char buffer[128];
   int fd = open("example.txt", O_RDONLY);
   if (fd == -1) {
      perror("Error opening file");
      return 1;
   }
   ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
   if (bytesRead == -1) {
      perror("Error reading file");
      close(fd);
      return 1;
   }
   buffer[bytesRead] = '\0'; // Null-terminate the buffer
   printf("Read %zd bytes: %s\n", bytesRead, buffer);
   close(fd);
   return 0;
}
```

#### Notes

- Always check the return value to handle errors or end-of-file conditions.
- The buffer should be large enough to hold the data being read.
- Use `close()` to release the file descriptor after reading.
- Reading from a file descriptor associated with a terminal or pipe may return fewer bytes than requested.

#### Common Errors

- `EAGAIN`: The file descriptor is set to non-blocking, and no data is available.
- `EBADF`: The file descriptor is not valid or not open for reading.
- `EFAULT`: The buffer is outside the accessible address space.
- `EINTR`: The call was interrupted by a signal before any data was read.

The `read()` system call is a fundamental operation for reading data from files, pipes, sockets, and other file descriptors in Linux.

## `write()` System Call

The `write()` system call is used to write data from a buffer to a file descriptor.

#### Syntax

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

#### Parameters

1. **`fd`**: The file descriptor to write to, typically obtained from `open()`.
2. **`buf`**: A pointer to the buffer containing the data to be written.
3. **`count`**: The number of bytes to write from the buffer.

#### Return Value

- On success: Returns the number of bytes actually written (can be less than `count`).
- On failure: Returns `-1` and sets `errno` to indicate the error.

#### Example

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
   if (fd == -1) {
      perror("Error opening file");
      return 1;
   }
   const char *text = "Hello, World!";
   ssize_t bytesWritten = write(fd, text, 13);
   if (bytesWritten == -1) {
      perror("Error writing to file");
      close(fd);
      return 1;
   }
   printf("Wrote %zd bytes\n", bytesWritten);
   close(fd);
   return 0;
}
```

#### Notes

- Always check the return value to ensure all data was written.
- Writing to a file descriptor associated with a terminal or pipe may write fewer bytes than requested.
- Use `close()` to release the file descriptor after writing.
- The `errno` variable can be used to determine the specific error if `write()` fails.

#### Common Errors

- `EAGAIN`: The file descriptor is set to non-blocking, and the operation would block.
- `EBADF`: The file descriptor is not valid or not open for writing.
- `EFAULT`: The buffer is outside the accessible address space.
- `EFBIG`: The file size exceeds the maximum allowed.
- `EINTR`: The call was interrupted by a signal before any data was written.

The `write()` system call is essential for performing output operations in Linux, whether writing to files, sockets, or other file descriptors.

## `close()` System Call

The `close()` system call is used to close a file descriptor, releasing the resources associated with it.

#### Syntax

```c
#include <unistd.h>

int close(int fd);
```

#### Parameters

- **`fd`**: The file descriptor to be closed, typically obtained from `open()` or other system calls.

#### Return Value

- On success: Returns `0`.
- On failure: Returns `-1` and sets `errno` to indicate the error.

#### Example

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   int fd = open("example.txt", O_RDONLY);
   if (fd == -1) {
      perror("Error opening file");
      return 1;
   }
   // Perform operations with the file descriptor
   if (close(fd) == -1) {
      perror("Error closing file");
      return 1;
   }
   return 0;
}
```

#### Notes

- Always close file descriptors when they are no longer needed to avoid resource leaks.
- Closing a file descriptor makes it available for reuse by subsequent `open()` or other system calls.
- Attempting to use a file descriptor after it has been closed results in an error (`EBADF`).

#### Common Errors

- `EBADF`: The file descriptor is not valid or was already closed.
- `EINTR`: The call was interrupted by a signal before it could complete.

The `close()` system call is essential for proper resource management in Linux, ensuring that file descriptors are not left open unnecessarily.

# Command Line Arguments in Linux

Command line arguments allow users to pass information to a program at runtime. In Linux, these arguments are accessible in a C program through the `main` function's parameters.

### Syntax of `main` Function

```c
int main(int argc, char *argv[]);
```

#### Parameters:

1. **`argc`**: The argument count, which indicates the number of arguments passed to the program, including the program's name.
2. **`argv`**: The argument vector, which is an array of strings representing the arguments.

### Example 1: Printing Command Line Arguments

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
   printf("Number of arguments: %d\n", argc);
   for (int i = 0; i < argc; i++) {
      printf("Argument %d: %s\n", i, argv[i]);
   }
   return 0;
}
```

#### Explanation:

- `argc` contains the number of arguments.
- `argv` contains the arguments as strings, where `argv[0]` is the program's name.

#### Usage:

```bash
./program arg1 arg2 arg3
```

#### Output:

```
Number of arguments: 4
Argument 0: ./program
Argument 1: arg1
Argument 2: arg2
Argument 3: arg3
```

### Example 2: Summing Numbers Passed as Arguments

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   if (argc < 3) {
      printf("Usage: %s num1 num2 ...\n", argv[0]);
      return 1;
   }

   int sum = 0;
   for (int i = 1; i < argc; i++) {
      sum += atoi(argv[i]); // Convert argument to integer
   }

   printf("Sum: %d\n", sum);
   return 0;
}
```

#### Explanation:

- The program expects at least two numbers as arguments.
- `atoi` is used to convert strings to integers.

#### Usage:

```bash
./program 10 20 30
```

#### Output:

```
Sum: 60
```

### Notes:

- Always validate `argc` to ensure the required number of arguments are provided.
- Use functions like `atoi` or `strtol` to convert string arguments to numeric types.
- Command line arguments are a powerful way to make programs more flexible and user-friendly.

## How the Shell and Kernel Handle Command Line Arguments

When a program is executed in Linux, the shell and kernel work together to pass command line arguments to the program.
Here's an explanation of the process:

#### 1. **Shell's Role**

- The shell parses the command line input provided by the user.
- It splits the input into the program name and its arguments based on whitespace or quotes.
- The shell then prepares an array of strings (`argv`) where:
  - `argv[0]` contains the program's name.
  - `argv[1]`, `argv[2]`, ..., `argv[argc-1]` contain the arguments.
- The shell invokes the `exec()` family of system calls to load the program into memory and pass the arguments.

#### 2. **Kernel's Role**

- When the `exec()` system call is made, the kernel:
  1.  Validates the program's executable file.
  2.  Loads the program into memory.
  3.  Sets up the stack with the `argc` (argument count) and `argv` (argument vector) values.
  4.  Transfers control to the program's entry point (usually the `main` function in C programs).
- The kernel ensures that the arguments are accessible to the program in a secure and structured manner.

#### 3. **Accessing Arguments in the Program**

- The program accesses the arguments through the `main` function's parameters:
  ```c
  int main(int argc, char *argv[]);
  ```
- `argc` and `argv` are populated by the kernel based on the values passed by the shell.

This seamless interaction between the shell, kernel, and program ensures that command line arguments are handled efficiently and securely.
