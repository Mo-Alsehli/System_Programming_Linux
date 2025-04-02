# Nano Shell - README

## Overview

Nano Shell is a simple command-line shell implementation written in C. It provides basic shell functionality including command execution, environment variable management, and local variable support.

## Features

### Built-in Commands

- `echo`: Prints arguments to stdout
- `pwd`: Prints current working directory
- `cd`: Changes current directory
- `exit`: Exits the shell
- `export`: Sets environment variables (usage: `export varName="value"`)
- `unset`: Removes environment variables

### Variable Support

- Local variables: Set using `varName=value` syntax
- Environment variables: Accessible via `$VARNAME` syntax
- Variable expansion: Both local and environment variables can be expanded in commands

### Process Execution

- Supports execution of external programs
- Proper process forking and waiting

## Usage

1. Compile the shell:

   ```bash
   gcc nano_shell.c -o nanoshell
   ```

2. Run the shell:

   ```bash
   ./nanoshell
   ```

3. Example commands:

   ```bash
   # Set local variable
   myvar=hello

   # Set environment variable
   export MYENVVAR="world"

   # Use variables
   echo $myvar $MYENVVAR

   # Run external commands
   ls -l
   ```

## Video Demonstration:

https://github.com/user-attachments/assets/c39c6371-aa0f-40e2-bd67-f3bf7062eee3

https://github.com/user-attachments/assets/d4f66966-f298-41a9-8bd9-9082584601eb

## Implementation Details

### Key Components

- **Tokenization**: Parses user input into command arguments
- **Variable Management**: Handles both local and environment variables
- **Command Execution**: Built-in commands vs external program execution

### Data Structures

- `shellLocalVar`: Structure for local variable storage (key-value pairs)
- Dynamic memory allocation for variable storage and command arguments

### Error Handling

- Basic error checking for process creation and memory allocation
- Error messages for invalid commands

## Limitations

- Limited error handling for some edge cases
- Basic feature set compared to full-fledged shells
- No support for advanced shell features like pipes, redirection, or scripting
