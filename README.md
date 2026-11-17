# Lab 7 Vector Calculator

A C calculator for named 3D vectors with addition, subtraction, scalar
multiplication, dynamic storage, and CSV loading/saving.

## Build and run

```sh
make
./minimat
./minimat -h
```

Run without options to start the calculator. The `-h` option displays help.
Use `make clean` to remove the executable and object files.

## Calculator commands

- `name = x y z` or `name = x,y,z`: create or replace a vector.
- `name`: display a stored vector.
- `a + b`: add two vectors.
- `a - b`: subtract vector b from vector a.
- `a * number` or `number * a`: multiply a vector by a scalar.
- `result = expression`: store an operation's result as a named vector.
- `list`: display all stored vectors.
- `load filename`: load CSV vectors, replacing matching names.
- `save filename`: overwrite a CSV file with all stored vectors.
- `clear`: remove all vectors and release their memory.
- `quit`: exit the calculator. End of input also exits.

Use spaces around arithmetic operators. Names are case-sensitive, start with a
letter or underscore, and contain up to 15 letters, digits, or underscores.
Command names are reserved. Dot and cross products are not supported.

## Dynamic memory

Vectors are stored in a dynamically allocated array. The first allocation holds
10 vectors. When full, the array doubles in capacity using `realloc()`. Reusing a
name replaces its vector without adding an entry. `clear` and normal program exit
call `free()` to release the array. Loading files also uses a dynamically allocated
line buffer, which is freed when loading finishes.

## CSV files

Each row contains `name,x,y,z`, with no header. For example:

```csv
a,1,2,3
b,4,5,6
```

Loading merges vectors into current storage. Malformed rows are reported and
skipped. LF/CRLF line endings and blank lines are accepted. Saving overwrites the
file with all stored vectors. Both commands accept relative or absolute filenames
without spaces and do not add a file extension.

## Memory check

```sh
valgrind --leak-check=full ./minimat
```
