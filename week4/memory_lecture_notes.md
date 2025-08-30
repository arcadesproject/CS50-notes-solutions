# Memory Notes

POINTERS

64 bits / 8 bytes

binary base 2 0-1, decimal base 10 0-9, hexadecimal base 16 (v useful for color) 0-9 and A-F
one hex digit is 4 bits so hex codes are 8 bit total so 1 byte (FF, 00, 74 etc)
0x before hex for convention so don't confuse 12 meaning 1 hex and 2 hex and 12 just a single hex code so 0x1 0x2 vs 0x12

& (just one) is address of operator in C
* dereference operator how to get to something
%p so can print pointers

int n = 50;
int *p = &n; 
so the pointer is the address of the integer

printf("%p\n", p);
printf("%p\n", *p); gives same as printf(%i\n", n);

remember when declare pointer need type (creating), but then when use don't need to (dereferencing)
don't need * to print it but almost always using * so it goes there

then there are pointers to pointers etc

contiguous means 1 byte apart in memory, e.g. elements in array

so printf goes to address, then prints characters until nul value \0
string s would store address of first byte, not all of them, thats the use of \0
(in python / java etc the length of the string is also stored)

# string in C
char *s = "HI!";

# POINTER arithmetic
don't technically need to keep using [] to get parts of array, still best to though
char *s = "HI!';
printf("%c\n", *s);
printf("%c\n", (*s + 1));
printf("%c\n", (*s + 2));

This power of being able to get particular parts of memory is powerful but can also make more mistakes

string address reference gets stored in diff part of memory to actual chars

Simply copying a string will just reference same part of memory, so need malloc - its fine to copy ints, longs, floats etc. but strings are taking more contiguous bytes so more complicated

malloc on heap stack, named variables on call stack
last function called on top of call stack, when done gets popped off
then move to next frame

char *s = "HI!';
char *t = s // DONT!
char *t = malloc(strlen(s) + 1);

int = m;
int *a;
int *b = malloc(sizeof(int)); - creates both pointer and memory allocation on heap
a = &m; - a now pointer to m memory location;
a = b; a now points to where b is pointing, does not point to b as it is a pointer
m = 10;
*b = m + 2; - memory pointed to by b now is m + 2 so 10 + 2, 12
free(b); space where b was pointing now removed
*a = 11; - as a was pointing where b was pointing, causes seg fault


if (t == NULL)
{
    return 1;
}

strcpy(t, s); // destination then source

if malloc can't find address of first byte it returns NULL
NULL = pointer / address 0, NUL = character 0

once done with it use free(t); to free up memory again to avoid using too much memory when using malloc

# valgrind

valgrind ./filename
to debug memory
like debug50 ./filename (cs50 provided) but for memory not code

# passing by value

scope
when passing values to a function only passing copies really
so they don't get changed
(pointers passed by reference so would be)

# Heap, stack, read only

Heap for malloc, realloc, calloc
stack for calling function, local variables, arrays, structs (no malloc)
read only for string literals, constants

machine code > globals > heap > stack

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

need the pointers so it isn't just local, passed by address
and used with

swap(&x, &y) // as needs the address so use &

heap overflow using malloc too much
stack overflow too many functions
both buffer overflows, buffer is chunk of memory but poking around past end of it will overflow buffer
so array is a buffer

# scanf
to read input from user like opposite of printf

simple with ints:

int n;
printf("n: ");
scanf("%i\n", &n);
printf("n: %i\n", n)

trickier with strings:

char *s;
printf("s: ");
scanf("%s", s);
printf("s: %s\n", s);
// DO NOT DO THIS! As only allocates starting location of string, don't know how long, how much memory etc

# file io

fopen, fclose, fprintf, fscanf, fread, fwrite, fseek


**Can think of file as sequences of structs instead of bytes**

Exactly — thinking of files as **series of structs** is often the clearest way to reason about **binary file formats**. Here’s what that means:

---

### **1. File as a byte stream**

* At the lowest level, a file is just a **sequence of bytes**.
* Each byte is 8 bits, and the OS doesn’t inherently know what they mean.

Example (hex view of first 8 bytes of a WAV file):

```
52 49 46 46 24 8C 00 00
```

* These are just raw bytes until you interpret them.

---

### **2. File as a series of structs**

* You can map those bytes onto **C structs** that match the file format.
* Each field in the struct corresponds to a specific part of the header or data.

Example: first part of WAV header:

```c
typedef struct {
    char chunkID[4];      // "RIFF"
    uint32_t chunkSize;   // File size - 8
    char format[4];       // "WAVE"
} RIFFHeader;
```

* Reading 12 bytes into this struct gives meaningful fields:

  ```c
  RIFFHeader riff;
  fread(&riff, sizeof(RIFFHeader), 1, file);
  printf("%s %s\n", riff.chunkID, riff.format); // prints "RIFF WAVE"
  ```

---

### **3. Benefits of thinking in structs**

* Makes the code **readable** and **maintainable**.
* Avoids magic offsets and repeated `fread`/`fwrite` calls with numbers like 44 or 12.
* Easier to validate and modify fields (e.g., sample rate, channels).

---

### **4. Caution**

* **Padding/alignment:** Some compilers may insert extra bytes between struct fields.

  * Use `#pragma pack(1)` or `__attribute__((packed))` to match the file layout exactly.
* **Endianness:** Files usually store integers in **little-endian** or **big-endian**; your CPU might differ. You may need to convert using `ntohl()`/`htonl()` or manual byte shifts.

---

### **Summary**

* Yes: conceptually, a **binary file = series of structs**.
* Practically, you often define structs in C that match the format of headers and chunks, then read/write those structs.
* This is how libraries parse WAV, PNG, BMP, or network packets.


___

## getopt

getopt is a standard C library function for parsing command-line options.

Prototype:

#include <unistd.h>
int getopt(int argc, char * const argv[], const char *optstring);

Arguments:

argc, argv → your main() arguments.

optstring → a string listing valid option letters.

Example: "vf:"

v → flag with no argument

f: → option that requires an argument

Returns:

The option character (e.g., 'v') if a match is found.

-1 when no more options remain.

? if an unknown option is found.

int opt;
while ((opt = getopt(argc, argv, "vf:")) != -1) {
    switch (opt) {
        case 'v':
            verbose = 1;
            break;
        case 'f':
            factor = atof(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-v] [-f factor] input output\n", argv[0]);
            exit(EXIT_FAILURE);
    }
}


## optind

optind is a global variable from <unistd.h>.

It tells you the index of the first non-option argument after getopt has finished parsing.

// Suppose command line: ./volume -v -f 2.0 input.wav output.wav
printf("Next arg index: %d\n", optind);  // prints index of "input.wav"

char *input_file = argv[optind];
char *output_file = argv[optind + 1];

FILE *ptr = fopen("file.txt", "r");
char ch = fgetc(ptr); - gets next character from file pointed to, needs to be in read mode

fputc appends char to pointed to file, needs to be in write or append mode

fread(<buffer>, <size>, <qty>, <file pointer>); - read qty units of size size from file pointed to and store in buffer - must be in read mode



## SOBEL edge checking
Instead of writing a long chain of if, else if, or switch statements, you put the “rules” or “decisions” into a table (array, matrix, dictionary, struct, etc.) and then look up the answer.

**TABLE DRIVEN** programming
A form of convolution 

Convolution is a mathematical operation where you take a small grid of numbers (called a kernel or filter) and “slide” it across a bigger grid (like an image). At each position, you multiply the kernel values with the overlapping pixel values, sum them up, and use that as the new pixel value.