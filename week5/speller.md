Here’s a comprehensive README in Markdown format explaining your dictionary implementation and the key CS/programming concepts it demonstrates:

````markdown
# Dictionary Implementation in C

## Overview

This project implements a **dictionary** in C using a **hash table** with linked lists for collision resolution. It supports the following operations:

- `load(dictionary)`: Load words from a file into memory.
- `check(word)`: Check if a word exists in the dictionary.
- `size()`: Return the number of words loaded.
- `unload()`: Free all memory used by the dictionary.

The implementation is designed to handle large English dictionaries (~140,000 words) efficiently while being case-insensitive.

---

## Data Structures

### 1. Hash Table
- The hash table is an array of pointers (`node *table[N]`) where each element points to a **linked list** of nodes.  
- **Buckets:** `N = 19,391` (a prime number chosen to minimize collisions).  
- Each bucket represents a subset of words determined by the **hash function**.

### 2. Linked List
- Each node in the linked list stores:
  - `word[LENGTH + 1]`: A word from the dictionary.
  - `next`: Pointer to the next node in the chain.
- Used for **separate chaining**, which handles hash collisions by storing multiple words in the same bucket.

---

## Key Functions

### 1. Hash Function
- Maps a word to an integer bucket index:

```c
unsigned int hash(const char *word)
{
    unsigned int bucket = 0;
    for (int i = 0; i < 13 && word[i] != '\0'; i++)
    {
        char c = toupper(word[i]);
        bucket += c * (i + 1);
    }
    return bucket % 19391;
}
````

**Concepts:**

* Weighted sum of first 13 letters spreads words more uniformly.
* `toupper()` ensures case-insensitivity.
* Modulo prime (`19391`) keeps the index within table bounds and reduces collisions.

---

### 2. Loading the Dictionary

* Opens the dictionary file and reads each word into a buffer.
* Allocates a new node, copies the word, and inserts it at the head of the linked list in the appropriate bucket.

**Concepts:**

* Dynamic memory allocation (`malloc`) for variable-sized data structures.
* Linked list insertion at head for simplicity and efficiency.
* Tracking dictionary size for quick `size()` queries.

---

### 3. Checking a Word

* Hash the word to find the appropriate bucket.
* Traverse the linked list recursively, comparing words using `strcasecmp` for case-insensitivity.

**Concepts:**

* **Recursion:** Simplifies traversal of linked lists.
* **String comparison:** `strcasecmp` handles case-insensitive comparisons.
* **Hash table lookup:** Reduces search from O(n) in the full dictionary to O(average bucket size).

---

### 4. Unloading Memory

* Recursively frees each node in all buckets.
* Ensures no memory leaks.

**Concepts:**

* **Recursion:** Simplifies freeing a linked list.
* **Pointer management:** Important in C to prevent memory leaks.
* **Base case / recursive case:** Key for safe recursive functions.

---

## CS / Programming Concepts Demonstrated

1. **Hash Tables**

   * Efficient key-value storage.
   * Collisions handled via **separate chaining** (linked lists).

2. **Linked Lists**

   * Dynamic size data structures.
   * Efficient insertion and traversal.

3. **Dynamic Memory Management**

   * `malloc` and `free` for allocating and deallocating memory at runtime.
   * Avoiding memory leaks is critical in C.

4. **Recursion**

   * Used for traversing and freeing linked lists.
   * Requires base cases to terminate safely.

5. **Strings and Pointers**

   * `char *` for dynamic string access.
   * Null-terminated strings (`\0`) in C.
   * Case-insensitive operations (`toupper`, `strcasecmp`).

6. **Modular Arithmetic**

   * Hash function uses modulo to ensure bucket index is within array bounds.

7. **Performance Optimization**

   * Large prime number of buckets reduces collisions.
   * Weighted sum of multiple letters in hash spreads words evenly.
   * Iterative traversal can replace recursion for speed in large dictionaries.

---

## Notes / Tips

* Choosing a good **hash function** is key for performance.
* Linked lists are simple but can be slower for very large buckets; alternative approaches include open addressing or dynamic arrays.
* Always ensure **memory is freed** to avoid leaks.
* Case-insensitivity is handled consistently both in hashing and lookup.

---

## Conclusion

This project is a practical exercise in **data structures (hash tables, linked lists)**, **dynamic memory management**, and **algorithmic efficiency**. It demonstrates how to handle large datasets in C while keeping operations like search and load fast and safe.
