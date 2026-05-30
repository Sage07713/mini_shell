Here's your README:

---

```markdown
# Mini Shell & Memory Allocator

A Unix-like shell and custom memory allocator built from scratch in C.

## What it does

### Shell
- Prints a prompt and reads user input
- Parses commands and arguments
- Executes system commands as child processes
- Built-in commands: `cd`, `pwd`, `exit`
- Supports pipes: `cmd1 | cmd2`

### Memory Allocator
- Custom implementation of `malloc()` and `free()`
- Uses a free-list linked list to track memory blocks
- Reuses freed blocks instead of always requesting new memory
- Each block has a hidden header storing size and availability

## Concepts covered
- Processes and system calls
- File descriptors and I/O redirection
- Pipes and inter-process communication
- Pointers and manual memory management
- Linked lists in C
- Structs

## How to build and run

### Shell
```
gcc -o shell shell.c
.\shell.exe
```

### Memory Allocator
```
gcc -o malloc malloc.c
.\malloc.exe
```

## Example usage

```
> gcc --version
gcc (MinGW-W64 x86_64) 16.1.0

> gcc --version | findstr gcc
gcc (MinGW-W64 x86_64) 16.1.0

> pwd
C:\Users\LENOVO\myshell

> cd ..
> pwd
C:\Users\LENOVO

> exit
```

## Why I built this
To understand how a shell and memory allocator work under the hood — concepts that are usually hidden behind standard library functions.
