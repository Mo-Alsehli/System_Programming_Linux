# Create a Process From User Space.

## `exec()` System Call

The `exec()` system call is used in Unix-like operating systems to replace the current process image with a new process image. It is part of the `exec` family of functions, which includes `execl`, `execv`, `execle`, `execve`, `execlp`, and `execvp`. These functions differ in how they accept arguments and environment variables.

### Key Features:

- **Process Replacement**: When `exec()` is called, the current process is replaced entirely by the new program. The process ID (PID) remains the same, but the memory, code, and stack are replaced.
- **No Return on Success**: If the `exec()` call is successful, it does not return to the calling process. Instead, the new program starts executing from its entry point.
- **Error Handling**: If the `exec()` call fails (e.g., if the specified program does not exist), it returns `-1` and sets `errno` to indicate the error.

### Common Use Case:

The `exec()` system call is often used after a process is created using `fork()`. The parent process continues execution, while the child process uses `exec()` to load and execute a new program.

### Example:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    printf("Before exec()\n");
    execv("/bin/ls", args);
    perror("execv failed"); // This will only execute if execv fails
    return 1;
}
```

### Variants:

- **`execl`**: Takes the program path and a variable list of arguments.
- **`execv`**: Takes the program path and an array of arguments.
- **`execlp` and `execvp`**: Search for the program in the `PATH` environment variable.
- **`execle` and `execve`**: Allow specifying the environment variables explicitly.

### Notes:

- The `exec()` family of functions does not create a new process; it replaces the current process.
- File descriptors remain open across an `exec()` call unless explicitly marked with the `FD_CLOEXEC` flag.

## `fork()` System Call

The `fork()` system call is used in Unix-like operating systems to create a new process by duplicating the calling process. It is one of the fundamental system calls for process creation.

### Key Features:

- **Process Duplication**: The `fork()` system call creates a new process, called the child process, which is an exact copy of the calling (parent) process.
- **Unique Process ID**: The child process gets a unique process ID (PID) different from the parent process.
- **Execution Context**: Both the parent and child processes continue execution from the point where `fork()` was called.
- **Return Values**:
  - `0`: Returned to the child process.
  - Positive PID: Returned to the parent process, representing the PID of the child.
  - `-1`: Returned if the `fork()` call fails, and `errno` is set to indicate the error.

### Common Use Case:

The `fork()` system call is often used to create a new process that can execute a different program (using `exec()`), while the parent process continues its own execution.

### Example:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("This is the child process. PID: %d\n", getpid());
    } else {
        printf("This is the parent process. PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
```

### Notes:

- The child process inherits most of the parent's attributes, such as file descriptors, environment variables, and memory layout.
- The child process does not inherit pending signals from the parent.
- The `fork()` system call is often followed by `exec()` in the child process to replace its memory space with a new program.
- Proper error handling is essential to ensure that the system resources are not exhausted due to excessive process creation.

## `wait()` System Call

The `wait()` system call is used in Unix-like operating systems to make a parent process wait until one of its child processes terminates. It allows the parent process to retrieve the termination status of the child process.

### Key Features:

- **Blocking Behavior**: The `wait()` system call blocks the parent process until a child process exits or a signal is received.
- **Child Termination Status**: It provides information about how the child process terminated (e.g., normal exit, signal termination).
- **Return Value**:
  - On success: Returns the process ID (PID) of the terminated child.
  - On failure: Returns `-1` and sets `errno` to indicate the error.

### Variants:

- **`waitpid()`**: A more flexible version of `wait()` that allows the parent to wait for a specific child process or to avoid blocking.
- **`waitid()`**: Provides additional options for retrieving detailed information about the child process.

### Common Use Case:

The `wait()` system call is typically used in conjunction with `fork()` to ensure that the parent process can clean up resources used by the child process after it terminates.

### Example:

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process. PID: %d\n", getpid());
        return 42; // Exit with a specific status
    } else {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Child process %d terminated with exit status %d\n", child_pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process %d terminated by signal %d\n", child_pid, WTERMSIG(status));
            }
        } else {
            perror("wait failed");
        }
    }

    return 0;
}
```

### Notes:

- The `wait()` system call helps prevent zombie processes by allowing the parent to clean up after child processes.
- If a parent process terminates without calling `wait()`, the child processes become orphaned and are adopted by the `init` process.
- Use `WIFEXITED(status)` and `WEXITSTATUS(status)` macros to check if the child exited normally and to retrieve its exit status.
- Use `WIFSIGNALED(status)` and `WTERMSIG(status)` macros to check if the child was terminated by a signal and to retrieve the signal number.

## Orphan and Zombie Processes in Linux

### Orphan Processes

An orphan process is a process whose parent has terminated or exited before the child process. In Linux, when a parent process terminates, its orphaned child processes are automatically adopted by the `init` process (PID 1). The `init` process ensures that orphan processes are properly managed and eventually terminated when they complete execution.

#### Key Points:

- Orphan processes are not harmful as they are managed by the `init` process.
- The `init` process periodically checks and cleans up orphan processes.
- Orphan processes continue to execute normally until they finish their tasks.

#### Example:

If a parent process exits without waiting for its child:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process. PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(5); // Simulate some work
        printf("Child process after parent exits. New Parent PID: %d\n", getppid());
    } else {
        printf("Parent process exiting. PID: %d\n", getpid());
    }

    return 0;
}
```

### Zombie Processes

A zombie process is a process that has completed execution but still has an entry in the process table. This happens when the parent process has not yet read the termination status of the child process using `wait()` or a similar system call. Zombie processes do not consume system resources like CPU or memory, but they do occupy an entry in the process table, which is a limited resource.

#### Key Points:

- Zombie processes occur when the parent process does not clean up after its child.
- They can be identified by the `Z` state in the output of the `ps` command.
- Accumulation of zombie processes can exhaust the process table, leading to system issues.

#### Example:

If a parent process does not call `wait()`:

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process. PID: %d\n", getpid());
        return 0; // Child exits
    } else {
        printf("Parent process. PID: %d\n", getpid());
        sleep(10); // Parent does not call wait()
    }

    return 0;
}
```

#### Preventing Zombie Processes:

- Use `wait()` or `waitpid()` in the parent process to clean up child processes.
- Use signal handlers like `SIGCHLD` to automatically reap child processes.

### Summary:

- Orphan processes are adopted by `init` and are not harmful.
- Zombie processes can cause issues if not cleaned up, but they can be prevented by proper use of `wait()` or signal handling.
- Proper process management is essential to maintain system stability.
