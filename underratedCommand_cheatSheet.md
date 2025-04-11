# Linux Command Cheat Sheet

This README documents useful Linux commands I've learned, including some underrated but powerful commands.

## Process and Terminal Related Commands

### 1. `ls -lt /dev/pts/[num]`

- **Purpose**: List terminal devices with timestamps
- **Details**:
  - `-l` shows long listing format
  - `-t` sorts by modification time (newest first)
  - `/dev/pts/` contains pseudo-terminal devices
- **Example**:
  ```bash
  ls -lt /dev/pts/1  # Show info about specific pseudo-terminal
  ```

### 2. `ls -l /proc/[pid]/fd`

- **Purpose**: List file descriptors for a process
- **Details**:
  - Shows all open files/sockets for a process
  - Useful for debugging what files a process has open
  - `0` = stdin, `1` = stdout, `2` = stderr
- **Example**:
  ```bash
  ls -l /proc/1234/fd  # Show file descriptors for process ID 1234
  ```

## Command Substitution with Backticks

### Usage of `` ` `` (backtick) character

- **Purpose**: Execute command inside another command
- **Details**:
  - Enclosing a command in backticks substitutes its output
  - Modern alternative: `$(command)` syntax
- **Examples**:

  ```bash
  echo "Today is `date`"  # Old style
  echo "Today is $(date)" # New preferred style

  # Count files in directory
  filecount=`ls | wc -l`
  ```

## History Commands

### `!command`

- **Purpose**: Execute last command starting with "command"
- **Details**:
  - Part of bash history expansion
  - Saves retyping long commands
- **Examples**:
  ```bash
  !ls     # Run last ls command
  !echo   # Run last echo command
  !123    # Run command #123 from history
  ```

## Underrated But Powerful Commands

### 1. `watch`

- **Purpose**: Execute program periodically
- **Example**:
  ```bash
  watch -n 1 'ls -l'  # Refresh ls output every second
  ```

### 2. `column`

- **Purpose**: Format output into columns
- **Example**:
  ```bash
  mount | column -t  # Nicely formatted mount output
  ```

### 3. `tac`

- **Purpose**: Reverse of `cat` - prints file in reverse
- **Example**:
  ```bash
  tac /var/log/syslog  # View log from newest to oldest
  ```

### 4. `script`

- **Purpose**: Record terminal session
- **Example**:
  ```bash
  script session.log  # Records all terminal input/output
  ```

### 5. `tree`

- **Purpose**: Display directory structure as tree
- **Example**:
  ```bash
  tree -L 2  # Show directory tree 2 levels deep
  ```

### 6. `ncdu`

- **Purpose**: NCurses Disk Usage analyzer
- **Example**:
  ```bash
  ncdu /home  # Interactive disk usage analysis
  ```

## File Descriptor Tricks

### Redirect stderr to stdout

```bash
command 2>&1
```

### Redirect both stdout and stderr to file

```bash
command &> output.log
```

### Create a quick empty file

```bash
> file.txt  # Creates/truncates file
```

## Process Management

### Show process tree

```bash
pstree
```

### Find process using a file

```bash
lsof /path/to/file
```

### Run command immune to hangups

```bash
nohup long_running_command &
```

## Networking

### Test if port is open

```bash
nc -zv hostname port
```

### Quick web server

```bash
python3 -m http.server 8000
```

## Tips

1. Use `Ctrl+R` to search command history
2. `Alt+.` inserts last argument of previous command
3. `!!` repeats the last command
4. `{1..10}` expands to `1 2 3 4 5 6 7 8 9 10`

This cheat sheet combines practical commands we've discussed with other underrated Linux utilities that can significantly improve productivity.
