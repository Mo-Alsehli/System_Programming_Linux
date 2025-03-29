# Femto Shell - README

## Overview

This is an extremely minimal shell implementation called "Femto Shell" written in C. It demonstrates basic shell functionality with a focus on simplicity and direct system calls.

## Features

### Basic Functionality

1. Displays a command prompt
2. Reads user input
3. Processes simple commands

### Supported Commands

1. `echo`: Reads input and echoes it back
2. `exit`: Terminates the shell

### System Call Usage

- Uses low-level `read()` and `write()` system calls for I/O operations
- Implements basic error handling for system calls

## Implementation Details

### Main Components

1. **Main Loop**:

   - Displays prompt message
   - Reads user input
   - Processes commands until "exit" is entered

2. **Command Processing**:

   - Simple string comparison for command recognition
   - Basic echo functionality
   - Exit command handling

3. **Error Handling**:
   - Checks return values of system calls
   - Provides different exit codes for different error conditions

## Usage

1. Compile the program: `gcc femto_shell.c -o femto_shell`
2. Run the executable: `./femto_shell`
3. Enter commands at the prompt

## Example Usage

```
Please Enter a Command $ echo
Hello World!
Hello World!
Please Enter a Command $ invalid
Invalid Command
Please Enter a Command $ exit
Good Bye :)
```

## Notes

- This is a minimal implementation for educational purposes
- Uses direct system calls rather than standard library functions
- Demonstrates basic shell concepts in a very compact form

## Limitations

- Only supports two commands (echo and exit)
- No argument processing
- No process creation or external command execution
- Very basic error handling
- Fixed buffer size for input
