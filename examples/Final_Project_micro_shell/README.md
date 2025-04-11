# Micro Shell - README

## Overview

Micro Shell is a lightweight Unix shell implementation written in C. It provides basic shell functionality including command execution, I/O redirection, environment variable management, and local variable support.

## Features

### Core Functionality

- Command line interface with prompt showing user and current directory
- Execution of external programs via `execvp()`
- Built-in commands (see below)
- I/O redirection (stdin, stdout, stderr)
- Environment variable support
- Local variable support

### Built-in Commands

1. `echo [args...]` - Print arguments to stdout
2. `pwd` - Print current working directory
3. `cd [dir]` - Change directory
4. `exit` - Exit the shell
5. `export VAR=value` - Set environment variable
6. `unset VAR` - Unset environment variable
7. Local variables (`VAR=value` syntax)

### I/O Redirection

- `>` - Redirect stdout to file (overwrite)
- `<` - Redirect stdin from file
- `2>` - Redirect stderr to file

## Building and Running

### Prerequisites

- GCC compiler
- Linux/Unix environment

### Compilation

```bash
gcc micro_shell.c -o micro_shell
```

### Execution

```bash
./micro_shell
```

## Usage Examples

1. Run a command:

   ```bash
   ls -l
   ```

2. Redirect output to file:

   ```bash
   ls > file_list.txt
   ```

3. Use environment variables:

   ```bash
   echo $HOME
   ```

4. Set local variable:

   ```bash
   message=Hello
   echo $message
   ```

5. Set environment variable:

   ```bash
   export PATH=/usr/local/bin:$PATH
   ```

6. Change directory:
   ```bash
   cd /tmp
   ```

### Video Demonestration

https://github.com/user-attachments/assets/bfadc0bd-e652-43d7-a562-359ef9f52608

## Implementation Details

### Key Components

1. **Command Parsing**:

   - `tokenize()` function splits input into command and arguments
   - Handles variable expansion (`$VAR`)
   - Processes I/O redirection operators

2. **Command Execution**:

   - Built-in commands execute directly
   - External commands fork() and execvp()
   - Proper file descriptor management for redirection

3. **Variable System**:

   - Local variables stored in `shellLocalVar` array
   - Environment variables accessed via `environ`
   - Variable expansion during tokenization

4. **I/O Redirection**:
   - Uses `dup2()` to redirect file descriptors
   - Saves/restores original descriptors for built-ins
   - Handles stdin, stdout, stderr separately

### Memory Management

- All dynamically allocated memory is properly freed
- `freeParsedCommand()` cleans up after each command
- Uses `strdup()` for safe string copying

## Limitations

1. Does not support:

   - Pipes (`|`)
   - Background processes (`&`)
   - Command history
   - Tab completion
   - Signal handling
   - Complex quoting in arguments

2. Current restrictions:
   - Limited to simple variable expansion
   - Basic error handling
   - No command line editing

## Future Enhancements

1. Planned features:
   - Pipeline support
   - Job control
   - Command history
   - Improved quoting handling
   - Better error messages

## License

This project is open source. Feel free to use and modify as needed.
