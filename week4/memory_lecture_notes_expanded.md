Certainly — here’s your revised and structured Markdown notes, now without emojis, with added clarity on **endianness** and **dereferencing**, and a list of next topics to explore:

---

# C Memory & Systems Programming Notes

## Topics Covered

- [Pointers](#pointers)  
- [Dereferencing](#dereferencing)  
- [Strings & Memory Layout](#strings--memory-layout)  
- [Pointer Arithmetic](#pointer-arithmetic)  
- [Dynamic Memory & malloc](#dynamic-memory--malloc)  
- [Valgrind](#valgrind)  
- [Passing by Value vs Reference](#passing-by-value-vs-reference)  
- [Memory Regions](#memory-regions)  
- [Buffer Overflows](#buffer-overflows)  
- [scanf](#scanf)  
- [File I/O](#file-io)  
- [Files as Structs](#files-as-structs)  
- [Endianness](#endianness)  
- [getopt & optind](#getopt--optind)  
- [Sobel Edge Detection & Table-Driven Programming](#sobel-edge-detection--table-driven-programming)  
- [Next Topics to Study](#next-topics-to-study)

---

## Pointers

- A pointer stores the **memory address** of a variable.
- On a 64-bit system, pointers are typically **8 bytes**.
- Use `&` to get the address of a variable, and `*` to access the value at that address.

```c
int n = 50;
int *p = &n;

printf("%p\n", p);     // prints address
printf("%i\n", *p);    // prints value at that address (50)
```

---

## Dereferencing

- Dereferencing means accessing the value stored at a memory address.
- You use the `*` operator to dereference a pointer.
- Example: `*p` gives the value of the variable that `p` points to.
- Dereferencing is essential when modifying values through pointers or accessing dynamically allocated memory.

---

## Strings & Memory Layout

- Strings in C are arrays of characters ending in a **null terminator** (`'\0'`).
- A string literal like `"HI!"` is stored in **read-only memory**, and `char *s = "HI!"` points to its first byte.
- `printf` prints characters until it hits `'\0'`.

> In higher-level languages (Python, Java), strings store their length explicitly. In C, the null terminator marks the end.

---

## Pointer Arithmetic

```c
char *s = "HI!";
printf("%c\n", *s);       // 'H'
printf("%c\n", *(s + 1)); // 'I'
printf("%c\n", *(s + 2)); // '!'
```

- You can access array elements using pointer arithmetic, though `[]` is clearer.
- Arrays are stored **contiguously** in memory (1 byte apart for `char`).

---

## Dynamic Memory & malloc

- Use `malloc` to allocate memory on the **heap**.
- Strings require `malloc` because they span multiple bytes.

```c
char *t = malloc(strlen(s) + 1);
if (t == NULL) return 1;
strcpy(t, s);
```

- Always `free()` memory when done to avoid leaks.
- `NULL` is a pointer to address 0. `NUL` is the character `'\0'`.

### Example with ints:

```c
int m = 10;
int *a;
int *b = malloc(sizeof(int));

a = &m;
a = b;
*b = m + 2;  // b points to 12
free(b);
*a = 11;     // segfault: a points to freed memory
```

---

## Valgrind

- Use to detect memory leaks and invalid memory access.

```bash
valgrind ./program
```

> Like `debug50`, but for memory—not logic.

---

## Passing by Value vs Reference

- C passes arguments **by value** (copies).
- To modify original variables, pass **pointers**.

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

swap(&x, &y);
```

---

## Memory Regions

- **Heap**: dynamic memory (`malloc`, `calloc`, `realloc`)  
- **Stack**: function calls, local variables  
- **Read-only**: string literals, constants

Memory layout (top to bottom):

```
Machine code
↓
Globals
↓
Heap
↓
Stack
```

---

## Buffer Overflows

- A **buffer** is a chunk of memory (e.g., an array).
- Writing past its bounds causes a **buffer overflow**.
- Heap overflow: too much `malloc`.  
- Stack overflow: too many recursive calls.

---

## scanf

### With integers:

```c
int n;
scanf("%i", &n);
```

### With strings (unsafe):

```c
char *s;
scanf("%s", s); // unsafe: no memory allocated
```

> Always allocate memory for strings before using `scanf`.

---

## File I/O

- Use `fopen`, `fclose`, `fread`, `fwrite`, `fseek`, `fprintf`, `fscanf`.

```c
FILE *ptr = fopen("file.txt", "r");
char ch = fgetc(ptr);     // read one char
fputc('A', ptr);          // write one char
```

```c
fread(buffer, size, qty, ptr); // read qty units of size into buffer
```

---

## Files as Structs

### 1. Byte Stream

- Files are just raw bytes until interpreted.

```hex
52 49 46 46 24 8C 00 00
```

### 2. Struct Mapping

```c
typedef struct {
    char chunkID[4];      // "RIFF"
    uint32_t chunkSize;   // File size - 8
    char format[4];       // "WAVE"
} RIFFHeader;

RIFFHeader riff;
fread(&riff, sizeof(RIFFHeader), 1, file);
```

### 3. Benefits

- Easier to read, modify, and validate file contents.
- Avoids magic offsets.

### 4. Caution

- **Padding**: compilers may insert extra bytes.
  - Use `#pragma pack(1)` or `__attribute__((packed))`.
- **Endianness**: see below.

---

## Endianness

Endianness refers to the **byte order** used to store multi-byte values in memory or files:

- **Little-endian**: least significant byte comes first (used by most modern CPUs).
- **Big-endian**: most significant byte comes first (used in some network protocols and older architectures).

When reading binary files or communicating across systems, you may need to convert between formats using functions like `ntohl()` or manual bit shifts.

---

## getopt & optind

### getopt

Used for parsing command-line options.

```c
int opt;
while ((opt = getopt(argc, argv, "vf:")) != -1) {
    switch (opt) {
        case 'v': verbose = 1; break;
        case 'f': factor = atof(optarg); break;
        default:
            fprintf(stderr, "Usage: %s [-v] [-f factor] input output\n", argv[0]);
            exit(EXIT_FAILURE);
    }
}
```

### optind

- Global variable that gives index of first non-option argument.

```c
char *input_file = argv[optind];
char *output_file = argv[optind + 1];
```

---

## Sobel Edge Detection & Table-Driven Programming

### Table-Driven Programming

Instead of long `if`/`switch` chains, store logic in a **lookup table** (array, matrix, struct).

### Convolution

- Slide a **kernel** (small grid) over an image.
- Multiply overlapping values, sum them, and store the result.

```text
New pixel = Σ(kernel[i][j] × image[x+i][y+j])
```

Used in edge detection, blurring, sharpening, etc.

---

## Next Topics to Study

- `struct` alignment and padding  
- `calloc` vs `malloc`  
- `realloc` and resizing buffers  
- Bitwise operations (`&`, `|`, `^`, `<<`, `>>`)  
- Memory-mapped files (`mmap`)  
- Signal handling (`SIGINT`, `SIGSEGV`)  
- Threads and concurrency (`pthread`)  
- Networking with sockets (`bind`, `listen`, `accept`)  
- Makefiles and build systems  
- Debugging with `gdb` and breakpoints  