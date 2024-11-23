# Command-Line Utilities

A collection of custom implementations of common command-line tools written in C. These utilities mimic the functionality of popular tools like `ls`, `find`, and `tree`, with additional options and features.

---

## Available Programs

- **`ls.c`**  
  Lists files in a directory with optional sorting and additional information.

- **`find.c`**  
  Searches for a specified pattern recursively through all subdirectories.

- **`tree.c`**  
  Displays the file and directory structure in a tree format.

---

## Build Instructions

Use the `Makefile` to easily compile and manage the programs. Available targets:  

- `make ls` — Compiles `ls.c`.  
- `make find` — Compiles `find.c`.  
- `make tree` — Compiles `tree.c`.  
- `make all` — Compiles all programs (`ls.c`, `find.c`, and `tree.c`).  
- `make clean` — Removes all compiled executables.

---

## Usage

Run the compiled executables from the terminal as follows:  

### `ls`
- `./ls` — Lists all files in the current directory sorted in lexicographic order.  
- `./ls -l` — Lists all files with detailed information (permissions, size, timestamps).

### `find`
- `./find <pattern>` — Searches recursively for the given `<pattern>` in the current directory and all subdirectories.

### `tree`
- `./tree` — Prints a tree-like structure of all files and directories sorted in lexicographic order.
