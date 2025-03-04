# System Programming In Linux

## Environment Preparation:

1. Install VirtualBox:

   - Download the VirtualBox installer from the [official website](https://www.virtualbox.org/).
   - Run the installer and follow the on-screen instructions to complete the installation.
   - Verify the installation by opening VirtualBox and checking the version information.

2. Download ubuntu and run it on VM.
3. Install gcc, make, perl:
   **Open a Terminal and write the following command**

- `sudo apt install gcc make perl`.

## Linux Commands:

#### Help Commands:

1. `man` command to get the manual of any command:

- Example usage for `man` command

```
man command
Ex:
man ls
man mkdir ..etc
```

- We can use the `man` command with normal commands, C library functions.

```
man printf
man scanf
...etc
```

- We can use the `man` command with the `man` command.

```
man man
```

- We can search a keyword in the manual using the option `-k` after the `man` command.

```
man -k printf
```

**Note: `--help` Option gets a short explination of the specified command**

```
ls --help
```

**Note: Every Command is a program (executable) in linux**

```
To get where a command program is located:
which command
Ex:
which ls
which mkdir
...etc
```

#### Navigation Commands:

- `pwd`: Print Working Directory. Displays the full path to the current directory.
- `ls`: List directory contents. Shows files and directories in the current directory.
  - `ls -l`: Lists files in long format, showing permissions, ownership, size, and modification date.
  - `ls -a`: Lists all files, including hidden files (those starting with a dot).
- `cd`: Change Directory. Moves you to a different directory.
  - `cd ..`: Moves up one directory level.
  - `cd /path/to/directory`: Moves to the specified directory.
- `mkdir`: Make Directory. Creates a new directory.
- `rmdir`: Remove Directory. Deletes an empty directory.
- `rm -r`: Remove recursively. Deletes a directory and its contents.
- `find`: Search for files and directories within a directory hierarchy.
  - `find /path -name filename`: Searches for a file with the specified name within the given path.
- `locate`: Quickly find the location of files.
  - `locate filename`: Searches for the specified filename in the database of indexed files.
- `touch`: Create an empty file or update the timestamp of an existing file.
- `cp`: Copy files or directories.
  - `cp source destination`: Copies the source file to the destination.
  - `cp -r source destination`: Recursively copies the source directory to the destination.
- `mv`: Move or rename files or directories.
  - `mv oldname newname`: Renames a file or directory.
  - `mv source destination`: Moves the source file to the destination.
- `ln`: Create links between files.
  - `ln source linkname`: Creates a hard link.
  - `ln -s source linkname`: Creates a symbolic (soft) link.

## Linux File Structure

The Linux file structure is organized as a hierarchical directory tree. The top of this hierarchy is the root directory, denoted by a forward slash (`/`). All other directories and files are nested under this root directory. Here are some key directories in the Linux file structure:

- `/bin`: Contains essential binary executables.
- `/boot`: Contains files related to the boot loader.
- `/dev`: Contains device files.
- `/etc`: Contains system configuration files.
- `/home`: Contains personal directories for users.
- `/lib`: Contains shared library files.
- `/media`: Contains mount points for removable media.
- `/mnt`: Contains mount points for temporary mounts.
- `/opt`: Contains optional software packages.
- `/proc`: Contains virtual files representing system and process information.
- `/root`: The home directory for the root user.
- `/sbin`: Contains system binary executables.
- `/tmp`: Contains temporary files.
- `/usr`: Contains user programs and data.
- `/var`: Contains variable data like logs and databases.

**NOTE: Commands Type**

- There are two types of commands:
  - Build-in Commands: Commands which are builtin in the shell.
  - External Commands: Commands that aren't parts of shell it self but they are located in another place and the shell calls their function.
- We know the type of a command using the `type` command:

```
type command
type cd
type ls
...etc
```

- Executing the type command with different command types:

```
1. External command.
mohamed-magdi@MM:/$ type ls
ls is aliased to `ls --color=auto'
2. builtin command.
mohamed-magdi@MM:/$ type cd
cd is a shell builtin
```

#### Dealing With Files Commands:

1. Copy a file.

```
cp ./file_path/file_name ./file_distination
```

2. Move(cut) a file.

```
mv ./file_path/file_name ./file_distination
```

**We can rename a file using the `mv` command:**

```
// This will rename the file inplace(in the same directorty).
mv file_name new_file_name
```

```
// This will move the file to another location and rename it.
mv file_name ./new_path/new_file_name
```

3. View(Read) Files:

- `cat` Command:
  // This Command View(dump) all the data inside the file.

```
cat file_name
```

- `more` Command:
  // This command views the file data but as a line by line.

```
more file_name
```

- `less` Command:
  // This command views the file data in a new window.

```
less file_name
// To exit from this view press 'q'.
```

## **We can search in the new window using the '/' and write the keyword after it**

---

### Vim Editor:

- Vim is a highly configurable text editor built to enable efficient text editing.
- It is an improved version of the vi editor distributed with most UNIX systems.
- Vim is often called a "programmer's editor," and so useful for programming that many consider it an entire IDE.
- It's not just for programmers, though. Vim is perfect for all kinds of text editing, from composing email to editing configuration files.
- Vim has a steep learning curve, but once mastered, it can significantly increase productivity.
- Key features include:

  - **Modes**: Vim operates in different modes, primarily Normal, Insert, and Visual. Each mode serves a different purpose and allows for efficient text manipulation.
  - **Customization**: Vim can be extensively customized using configuration files (like `.vimrc`) and plugins.
  - **Keyboard Shortcuts**: Vim relies heavily on keyboard shortcuts for navigation and editing, which can be much faster than using a mouse.
  - **Search and Replace**: Powerful search and replace functionality using regular expressions.
  - **Macros**: Ability to record and replay sequences of commands to automate repetitive tasks.
  - **Split Windows**: Edit multiple files or different parts of the same file in split windows.
  - **Syntax Highlighting**: Supports syntax highlighting for many programming languages.
  - **Extensibility**: A large number of plugins are available to extend Vim's functionality.

  #### Useful Vim Commands:

  1. **Basic Navigation**:

  - `h`, `j`, `k`, `l`: Move the cursor left, down, up, and right respectively.
  - `gg`: Go to the beginning of the file.
  - `G`: Go to the end of the file.
  - `0`: Move to the beginning of the line.
  - `$`: Move to the end of the line.
  - `w`: Move to the beginning of the next word.
  - `b`: Move to the beginning of the previous word.

  2. **Editing**:

  - `i`: Enter Insert mode before the cursor.
  - `a`: Enter Insert mode after the cursor.
  - `o`: Open a new line below the current line and enter Insert mode.
  - `dd`: Delete the current line.
  - `yy`: Yank (copy) the current line.
  - `p`: Paste the yanked or deleted text after the cursor.
  - `u`: Undo the last change.
  - `Ctrl + r`: Redo the undone change.

  3. **Searching**:

  - `/pattern`: Search for `pattern` in the file.
  - `n`: Move to the next occurrence of the search pattern.
  - `N`: Move to the previous occurrence of the search pattern.
  - `:%s/old/new/g`: Replace all occurrences of `old` with `new` in the file.

  4. **Visual Mode**:

  - `v`: Enter Visual mode to select text.
  - `V`: Enter Visual Line mode to select whole lines.
  - `Ctrl + v`: Enter Visual Block mode to select a block of text.

  5. **Saving and Exiting**:

  - `:w`: Save the file.
  - `:q`: Quit Vim.
  - `:wq`: Save the file and quit Vim.
  - `:q!`: Quit Vim without saving changes.

  6. **Split Windows**:

  - `:split filename`: Open `filename` in a horizontal split.
  - `:vsplit filename`: Open `filename` in a vertical split.
  - `Ctrl + w, s`: Split the current window horizontally.
  - `Ctrl + w, v`: Split the current window vertically.
  - `Ctrl + w, w`: Switch between split windows.

  7. **Macros**:

  - `q<register>`: Start recording a macro into the specified register.
  - `q`: Stop recording the macro.
  - `@<register>`: Play back the macro from the specified register.

  8. **Buffers**:

  - `:e filename`: Open `filename` in a new buffer.
  - `:bnext` or `:bn`: Move to the next buffer.
  - `:bprev` or `:bp`: Move to the previous buffer.
  - `:bd`: Delete the current buffer.

  **Note: Some other Useful Commands In the Command Mode**
  _Note: All Of these commands won't show up on the screen we only write it and the vim recieves it in the background._

  - To Copy a line in the editor we use the command `yy`.
  - To paste the copied line we use the command `p`.
  - To copy multiple line we write the number of lines and the command yy ->
    `n yy`.
  - To delete a line or mutliptle lines we write the command `dd` or `n dd` for multiple lines.
    - Note This command actually cuts the line and If you want to paste it just write the command `p`.

  These commands can help you become more efficient while using Vim for text editing and programming tasks.

---

### I/O Redirections

I/O redirections are used in Unix-like operating systems to control where the input and output of commands go. This can be useful for saving the output of a command to a file, using a file as input to a command, or chaining commands together.

#### Standard Input (stdin), Output (stdout), and Error (stderr)

- **stdin**: Standard input, usually from the keyboard.
- **stdout**: Standard output, usually to the terminal.
- **stderr**: Standard error, usually to the terminal.

#### Redirecting Output

1. **Redirect stdout to a file**

   ```sh
   command > output.txt
   ```

2. **Append stdout to a file**

   ```sh
   command >> output.txt
   ```

3. **Redirect stderr to a file**

   ```sh
   command 2> error.txt
   ```

4. **Redirect both stdout and stderr to a file**

   ```sh
   command > output.txt 2>&1
   ```

5. **Redirect stdout to a file and stderr to another file**

   ```sh
   command > output.txt 2> error.txt
   ```

6. **Redirect stdin from a file**

   ```sh
   command < input.txt
   ```

7. **Use a file as input and redirect output to another file**

   ```sh
   command < input.txt > output.txt
   ```

8. **Pipe output of one command as input to another**

   ```sh
   command1 | command2
   ```

9. **Suppress command output**

   ```sh
   command > /dev/null 2>&1
   ```

---

### Piping

Piping is a powerful feature in Unix-like operating systems that allows the output of one command to be used as the input for another command. This enables the chaining of multiple commands to perform complex tasks efficiently.

### Piping Commands:

1. **Basic Pipe**:

```sh
command1 | command2
```

- The output of `command1` is used as the input for `command2`.

2. **Combining Multiple Commands**:

```sh
command1 | command2 | command3
```

- The output of `command1` is passed to `command2`, and the output of `command2` is passed to `command3`.

3. **Example Usage**:

- **List files and search for a pattern**:

  ```sh
  ls -l | grep "pattern"
  ```

  - Lists files in long format and searches for lines containing "pattern".

- **Count the number of lines in a file**:

  ```sh
  cat file.txt | wc -l
  ```

  - Displays the contents of `file.txt` and counts the number of lines.

- **Sort and remove duplicate lines**:

  ```sh
  sort file.txt | uniq
  ```

  - Sorts the lines in `file.txt` and removes duplicates.

4. **Using Pipes with Filters**:

- **Filter out specific columns**:

  ```sh
  cat file.txt | awk '{print $1}'
  ```

  - Prints the first column of each line in `file.txt`.

- **Display the top N lines**:

  ```sh
  cat file.txt | head -n 10
  ```

  - Displays the first 10 lines of `file.txt`.

5. **Combining Pipes with Redirection**:

```sh
command1 | command2 > output.txt
```

- The output of `command1` is passed to `command2`, and the final output is redirected to `output.txt`.

Piping is an essential tool for efficient command-line operations, allowing users to create powerful command sequences by combining simple commands.

### Differences from Windows File Structure

1. **Root Directory**:

   - **Linux**: The root directory is denoted by `/`.
   - **Windows**: Each drive has its own root directory, such as `C:\`.

2. **Path Separator**:

   - **Linux**: Uses a forward slash (`/`) as the path separator.
   - **Windows**: Uses a backslash (`\`) as the path separator.

3. **Case Sensitivity**:

   - **Linux**: File and directory names are case-sensitive (`File.txt` and `file.txt` are different files).
   - **Windows**: File and directory names are case-insensitive (`File.txt` and `file.txt` are considered the same file).

4. **File Permissions**:

   - **Linux**: Uses a detailed permission system with read, write, and execute permissions for the owner, group, and others.
   - **Windows**: Uses Access Control Lists (ACLs) to manage permissions.

5. **Hidden Files**:

   - **Linux**: Files and directories starting with a dot (`.`) are hidden.
   - **Windows**: Files and directories can be marked as hidden using file properties.

6. **System Files**:
   - **Linux**: System files are typically located in specific directories like `/etc`, `/bin`, and `/usr`.
   - **Windows**: System files are often located in the `C:\Windows` directory and its subdirectories.
