# Recovering JPEGs from a Forensic Image

This program is a simplified data recovery tool: it scans a raw memory card image and extracts JPEG files by detecting their **file signatures**. Along the way, it demonstrates several core concepts in C programming and computer science.

---

## 1. Command-Line Arguments
```c
int main(int argc, char *argv[])
````

* `argc`: argument count (number of arguments passed).
* `argv`: argument vector (array of strings, one for each argument).
* Example:

  ```bash
  ./recover card.raw
  ```

  * `argc == 2`
  * `argv[1] == "card.raw"`

**Key Idea**: Command-line arguments let programs accept input without hardcoding filenames.

---

## 2. File I/O in C

```c
FILE *input_file = fopen(input_name, "r");
```

* `fopen()` opens a file (here, for **reading**).
* Returns a `FILE*` handle used for reading/writing.
* Always check for `NULL` (open may fail).
* `fread()` reads binary data:

  ```c
  fread(buffer, 1, 512, input_file);
  ```

  * Reads 512 **bytes** into `buffer`.
* `fwrite()` writes binary data to a file.

**Key Idea**: C handles files as byte streams. Low-level binary reads/writes are critical for systems programming and data recovery.

---

## 3. Memory and Buffers

```c
uint8_t buffer[512];
```

* A fixed-size array used as a **buffer** to hold one block of raw data.
* `uint8_t` (from `<stdint.h>`) is an **8-bit unsigned integer**, perfect for raw bytes.

**Key Idea**: Buffers are temporary storage areas for input/output. They allow processing fixed-size chunks instead of the entire file at once.

---

## 4. Block-Oriented Storage

* Many file systems (e.g., FAT) use a **block size** of 512 bytes.
* Reading data in block-sized chunks mirrors how data is physically stored on disk or flash memory.

**Key Idea**: Understanding block sizes is essential in systems like file recovery, operating systems, and databases.

---

## 5. File Signatures (Magic Numbers)

JPEG files start with a fixed sequence of bytes:

```
0xff 0xd8 0xff 0xe0 to 0xef
```

```c
if (buffer[0] == 0xff &&
    buffer[1] == 0xd8 &&
    buffer[2] == 0xff &&
    (buffer[3] & 0xf0) == 0xe0)
```

* The first three bytes are constant.
* The fourth byte can vary between `0xe0` and `0xef`, so we mask the lower 4 bits (`& 0xf0`).

**Key Idea**: File signatures ("magic numbers") are how forensic tools identify file types in raw data.

---

## 6. Dynamic File Creation

```c
char output_name[8];
sprintf(output_name, "%03i.jpg", jpeg_count++);
output_file = fopen(output_name, "w");
```

* Creates filenames like `000.jpg`, `001.jpg`, etc.
* `%03i` ensures numbers are zero-padded to 3 digits.

**Key Idea**: Programs can generate filenames dynamically to organize recovered or processed data.

---

## 7. Resource Management

* Always close files when done:

  ```c
  fclose(output_file);
  fclose(input_file);
  ```
* Prevents memory leaks, corruption, and file locks.

**Key Idea**: Resource management (files, memory, network sockets) is a cornerstone of reliable systems programming.

---

## 8. Control Flow and State

* The program tracks whether we’re **currently writing a JPEG**:

  * If a new JPEG header is found, close the old file (if any) and start a new one.
  * If inside a JPEG, keep writing blocks until a new header appears.

**Key Idea**: Programs often need to maintain *state* across iterations of a loop (here: “currently writing a file or not”).

---

# Summary

This small program teaches:

* Handling command-line arguments.
* File I/O in binary mode.
* Buffers and block-based data processing.
* File signatures and forensic recovery.
* Resource management in C.
* Control flow based on state.