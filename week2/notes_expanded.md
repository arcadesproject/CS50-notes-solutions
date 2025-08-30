# C Programming Notes

## Topics Covered

- [Constants and Array Sizes](#constants-and-array-sizes)  
- [Type Casting](#type-casting)  
- [Characters vs. Strings](#characters-vs-strings)  
- [Working with C-Style Strings](#working-with-c-style-strings)  
- [Looping Over Strings](#looping-over-strings)  
- [Command-Line Arguments](#command-line-arguments)  
- [Return Values and Exit Status](#return-values-and-exit-status)  
- [Passing to Functions](#passing-to-functions)  
- [Array Initialization](#array-initialization)  

---

## Constants and Array Sizes

```c
const int N = 3;    // preferred style: uppercase name
int scores[N];      // array of length N (3)
```

- Use `const` to define symbolic constants.  
- Naming convention: uppercase identifiers for constants.  
- Array sizes must be compile-time constants in C.  

---

## Type Casting

```c
int a = 5, b = 2;
float ratio = (float) a / b;  // cast to float for fractional result
```

- Cast between types with `(type)` to avoid implicit narrowing or integer division.  
- Common pattern: `(float)` or `(double)` when you need floating-point precision.  

---

## Characters vs. Strings

- Single quotes (`'H'`) denote a single `char`.  
- Double quotes (`"HI!"`) denote a string literal (`char[]`) ending with `'\0'`.  
- Every string has an extra byte for the null terminator (`'\0'`), marking its end.  

```c
char c1 = 'H';
char greeting[] = "HI!";
printf("%i\n", c1);  // prints 72 (ASCII code for 'H')
```

---

## Working with C-Style Strings

```c
string s = "HI!";      // CS50 alias for char*
printf("%c%c%c\n", s[0], s[1], s[2]);
```

- Access characters by index (`s[i]`).  
- Beware that string literals are typically in read-only memory—modify only arrays, not literals.  

---

## Looping Over Strings

Bad pattern (inefficient):

```c
for (int i = 0; i < strlen(str); i++)
```

Better pattern (compute length once):

```c
int n = strlen(str);
for (int i = 0; i < n; i++)
```

- Avoid calling `strlen()` on every iteration; store its result in a variable.  

---

## Command-Line Arguments

```c
int main(int argc, char *argv[])
{
    // argc: number of arguments (including program name)
    // argv: array of strings (argv[0] is program name)
}
```

- Check `argc` to ensure the user provided the expected number of arguments.  
- Access actual inputs via `argv[1]` through `argv[argc-1]`.  

---

## Return Values and Exit Status

- Use `return 0;` in `main` to signal successful execution.  
- After C99, `return 0;` at end of `main` is implicit but still clear.  
- In the shell, retrieve exit status with `echo $?`.  

---

## Passing to Functions

- In C, all primitive variables are passed **by value** (copies).  
- Use pointers to pass by reference and modify the original.  
- Arrays decay to pointers, so passing an array is effectively passing its address.

```c
void process_array(int arr[], int length);
```

---

## Array Initialization

```c
int hours[5] = {1, 2, 3, 4, 5};
```

- Aggregate initialization sets all elements in one line.  
- Unspecified elements default to zero.  

---

## Next Topics to Study

- Pointer arithmetic and pointer subtleties  
- Dynamic memory allocation (`malloc`, `free`)  
- Defining and using `struct`s with `typedef`  
- File I/O (`fopen`, `fread`, `fprintf`, `fclose`)  
- Recursive functions and divide-and-conquer  
- Linked lists and other data structures  
- Function pointers and callbacks  
- Error handling with `errno` and `perror`  
- Preprocessor directives and macros  
- Multi-file projects and Makefiles  