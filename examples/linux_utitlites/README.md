# Linux Utilities Implementation

This directory contains C implementations of common Linux utilities.

## Programs Included

1. `copy.c` - File copy utility
2. `echo.c` - Argument echoing utility
3. `move.c` - File move utility
4. `pwd.c` - Working directory printer

## Building

```bash
gcc copy.c -o copy
gcc echo.c -o echo
gcc move.c -o move
gcc pwd.c -o pwd
```

## Usage

### 1.copy

```bash
./copy <source> <destination>
## for exmaple
.copy file.txt /tmp/file_copy.txt
```

- Copies file contents from source file to a destination file.
- Creates destination file if needed.
- preserves file permissions.

### 2.echo

```bash
./echo [arguments...]
##for example
./echo Hello World
```

- Prints all arguments separated by spaces.
- Uses direct write syscalls.
- Adds newline at end.

### 3.move

```bash
./move <source> <destination>
## example
./move /tmp/file.txt /tmp/new_name.txt
./move /tmp/file.txt /home/reda/new_name.txt
./move /tmp/file.txt /home/reda/file.txt
```

- Copies then deletes source file.
- Similar to standard `mv` command.
- Handles file opening errors.

### 4.pwd

```bash
./pwd
```

- Prints current working directory.
- Uses getcwd() system call.
- Includes error handling.

## Error Handling

**All programs include:**

- Argument count verification.
- File operation error checking.
- System call failure handling.
- Meaningful exit codes.
