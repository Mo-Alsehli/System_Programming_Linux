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
