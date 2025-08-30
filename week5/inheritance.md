# Genetic Inheritance Simulation in C

This program simulates the inheritance of blood type alleles through a family tree across multiple generations. It demonstrates key concepts in **C programming**, including memory allocation, recursion, pointers, and randomness.

---

## Key Concepts

### 1. **Structures**
```c
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;
````

* A `person` has two parent pointers and two alleles (`A`, `B`, or `O`).
* This models biological inheritance in a tree structure.

---

### 2. **Dynamic Memory Allocation**

```c
person *child = malloc(sizeof(person));
```

* Each new `person` is allocated dynamically.
* Memory must be **freed** later using `free_family` to avoid leaks.

---

### 3. **Recursion**

* **`create_family`** builds the tree recursively:

  * Base case: last generation → no parents, random alleles.
  * Recursive case: create parents, inherit alleles randomly.
* **`free_family`** frees memory recursively, traversing back through ancestors.
* **`print_family`** recursively prints the tree with indentation for generations.

---

### 4. **Randomness**

```c
srandom(time(0));
```

* Seeds the random number generator with the current time.
* **`random_allele()`** randomly chooses an allele (`A`, `B`, `O`).
* Inheritance is simulated by randomly picking one allele from each parent.

---

### 5. **Pointer Relationships**

* Each `person` stores pointers to their parents.
* Children and parents are connected through references, forming a tree.
* Null pointers represent the absence of parents at the base generation.

---

## Functions Overview

* **`create_family(int generations)`**
  Builds the family tree of a specified depth.

* **`print_family(person *p, int generation)`**
  Displays each family member and their alleles, with indentation showing ancestry.

* **`free_family(person *p)`**
  Frees memory used by the family tree to prevent memory leaks.

* **`random_allele()`**
  Returns a random allele (`A`, `B`, or `O`).

---

## Example Output

```
Child (Generation 0): blood type AO
    Parent (Generation 1): blood type AB
        Grandparent (Generation 2): blood type BO
        Grandparent (Generation 2): blood type AA
    Parent (Generation 1): blood type AO
        Grandparent (Generation 2): blood type OO
        Grandparent (Generation 2): blood type AB
```

---

## Key Takeaways

* **Recursion** models hierarchical structures like family trees.
* **Dynamic allocation and freeing** are essential for managing memory in C.
* **Pointers** enable linked data structures.
* **Randomization** introduces variability, simulating genetic inheritance.
