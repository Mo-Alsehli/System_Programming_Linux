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
![copy1](https://github.com/user-attachments/assets/ad5585f2-5fdf-41c6-8b5c-e41fce29e939)
![copy2](https://github.com/user-attachments/assets/9daae03a-238b-43e5-8cbb-01d0bcba1708)

### 2.echo

```bash
./echo [arguments...]
##for example
./echo Hello World
```

- Prints all arguments separated by spaces.
- Uses direct write syscalls.
- Adds newline at end.
![echo](https://github.com/user-attachments/assets/559ceebc-070c-4301-9024-068219895d50)

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
![move](https://github.com/user-attachments/assets/be480ae4-9fa0-4beb-925d-6ce57e5f7ddd)

### 4.pwd

```bash
./pwd
```

- Prints current working directory.
- Uses getcwd() system call.
- Includes error handling.
![pwd](https://github.com/user-attachments/assets/35d592eb-3b8f-404a-bf98-f0e275eaca8f)

## Error Handling

**All programs include:**

- Argument count verification.
- File operation error checking.
- System call failure handling.
- Meaningful exit codes.
