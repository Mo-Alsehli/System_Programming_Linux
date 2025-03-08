## C Program Build Steps:

### 1. Preprocessing Stage:

```
gcc -E file.c > file.i
```

> file.c ➡️ file.i

### 2. Assembling Stage:

```
gcc -s file.i
```

> file.i ➡️ file.s

### 3. Compiling Stage (Assembly To Object File):

```
gcc -c file.s
```

> file.s ➡️ file.o
> file.o Here is called relocatable file as the addresses in it are not real and need to be allocated in the next stage which is the linking stage.

### 4. Linking Stage:

```
gcc file.o -o myexeFile
```

> file.o ➡️ executable file
> Executable file in linux has no extention as the extension .exe is for windows application only.

**Note: File extension in Linux is not so much important in most cases**

## ELF Format

> Executable and Linkable Format
> ELF files are the main executable format in linux systems.

- ELF file contents (what does it describe).

| Section         | Description                                                                          |
| --------------- | ------------------------------------------------------------------------------------ |
| ELF header      | Describes the type of the file (says its an Elf file)                                |
| .init section   | Contains initialization code that runs before the main function                      |
| .text section   | Consists of code information                                                         |
| .rodata section | Consists of read only data(const variables)                                          |
| .data section   | consists of Global and initialized data(variables)                                   |
| .bss section    | consists of uninitialized data                                                       |
| .symtab         | consists of the symbols (variables and functions names and addresses) of the program |
| .debug          | consists of debugging information and it's optional                                  |
| .line           | consists of lines numbers information                                                |

### Some commands to deal with ELF files

- Type of file:

```
file fileName
```

> This command is used to now the type of a file and some other information.

- Read ELF file Command:

```
readelf executable
```

> This command is used to read the information of an executable elf file.

- Read header section data.

```
readelf -h
```

> To read the header section in the ELF file.

- get ELF Sections info.

```
readelf -S
```

- get ELF Symbols Section info.

```
readelf -s
```

## Dynamic Linking Vs Static Linking

### Dynamic Linking vs Static Linking

| Feature         | Dynamic Linking                                 | Static Linking                                      |
| --------------- | ----------------------------------------------- | --------------------------------------------------- |
| Linking Time    | Runtime                                         | Compile time                                        |
| Executable Size | Smaller                                         | Larger                                              |
| Memory Usage    | Shared libraries, saving space                  | Each executable has its own copy of the library     |
| Flexibility     | Easier updates to libraries without recompiling | Self-contained executable, no external dependencies |

## Processes In linux:

**Processes is an instance of an executing program.**

- `tty` Command.

  > prints the file name of the terminal connected to standard input.

- `ps` Command.

  > Prints the current working processes with its _TTY_ and _ID_.

  Examples:

  - List all processes for the current user:

    ```
    ps
    ```

  - List all processes with full details:

    ```
    ps -ef
    ```

  - List processes by a specific user:

    ```
    ps -u username
    ```

  - List processes in a tree format:

    ```
    ps -ejH
    ```

  - List processes with a specific PID:

    ```
    ps -p 1234
    ```

  - List processes with a specific command name:

    ```
    ps -C commandname
    ```

  - List Processes for a specific terminal.
    ```
    ps -t TTY
    ```

- `top` Command.

  ```
  top
  ```

  > Displays real-time system summary information, including a list of tasks currently being managed by the kernel.

- `kill` Command.

  ```
  kill 1234
  ```

  > Sends a signal to a process, usually to terminate it. (1234 is the process ID)

- `pstree` Command.

  ```
  pstree
  ```

  > Displays a tree of processes, showing the parent-child relationships.

- `nice` Command.

  ```
  nice -n 10 command
  ```

  > Runs a command with a modified scheduling priority. (10 is the priority level)

- `renice` Command.

  ```
  renice 15 -p 1234
  ```

  > Alters the priority of an already running process. (15 is the new priority level, 1234 is the process ID)

- `bg` Command.

  ```
  bg %1
  ```

  > Resumes a suspended job in the background. (%1 is the job number)

- `fg` Command.

  ```
  fg %1
  ```

  > Brings a background job to the foreground. (%1 is the job number)

- `jobs` Command.

  ```
  jobs
  ```

  > Lists the active jobs in the current shell session.
