# Pico Shell - README

## Overview

This is a simple shell implementation called "Pico Shell" written in C. It provides basic shell functionality including command execution, built-in commands, and process management.

## Features

### Built-in Commands

1. `echo`: Prints all provided arguments separated by spaces
2. `pwd`: Prints the current working directory
3. `cd`: Changes the current working directory
4. `exit`: Terminates the shell

### External Command Execution

- Can execute any system command by forking a new process
- Uses `execvp()` for command execution
- Parent process waits for child process completion

### Command Line Parsing

- Handles spaces between arguments
- Properly tokenizes input commands
- Manages memory allocation for command arguments

## Implementation Details

### Main Components

1. **Main Loop**:

   - Displays prompt with current directory
   - Reads user input
   - Processes commands

2. **Tokenization**:

   - Splits input string into arguments
   - Handles memory allocation for each argument
   - Properly null-terminates argument array

3. **Process Management**:
   - Uses `fork()` to create child processes
   - Uses `execvp()` for command execution
   - Implements proper waiting for child processes

### Memory Management

- Dynamically allocates memory for command arguments
- Includes memory deallocation at program termination

## Usage

1. Compile the program: `gcc pico_shell.c -o pico_shell`
2. Run the executable: `./pico_shell`
3. Enter commands at the prompt

## Example Usage

```
MM@Pico_shell: /home/user $ echo hello world
hello world
MM@Pico_shell: /home/user $ pwd
/home/user
MM@Pico_shell: /home/user $ cd /tmp
MM@Pico_shell: /tmp $ ls
file1.txt  file2.txt
MM@Pico_shell: /tmp $ exit
```

## Video Demonstration.

## Notes

- The shell handles basic error cases but may not cover all edge cases
- The prompt displays the current working directory
- Memory is freed at program termination
