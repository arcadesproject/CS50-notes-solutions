# Data Structures Notes

## Topics Covered

- [Queues](#queues)
- [Stacks](#stacks)
- [Memory Allocation & Realloc](#memory-allocation--realloc)
- [Linked Lists](#linked-lists)
- [Trees](#trees)
- [Dictionaries & Hash Tables](#dictionaries--hash-tables)
- [Tries](#tries)
- [Further Reading](#further-reading)

---

## Queues

**Definition**: A linear data structure following **FIFO** (First In, First Out) principle.

### Array-Based Implementation

```c
typedef struct _queue {
    VALUE array[CAPACITY];
    int front;
    int size;
} queue;

queue q;
enqueue(&q, 40);
int x = dequeue(&q);
```

- `enqueue`: Adds element to the rear.
- `dequeue`: Removes element from the front.
- `front` tracks the first element.
- `size` tracks number of elements.

### Linked List-Based Implementation

- Maintain pointers to both **head** and **tail**.
- Efficient for dynamic memory usage.
- Can achieve O(1) enqueue and dequeue if tail is tracked.

---

## Stacks

**Definition**: A linear data structure following **LIFO** (Last In, First Out) principle.

### Array-Based Implementation

```c
typedef struct {
    VALUE array[CAPACITY];
    int top;
} stack;

stack s;
s.top = 0;
push(&s, 28);
push(&s, 33);
int x = pop(&s);
```

- `push`: Adds element at `top`.
- `pop`: Removes element from `top`.

### Linked List-Based Implementation

- Each push involves creating a new node.
- Insert at head for O(1) time.
- More flexible than arrays but uses more memory.

---

## Memory Allocation & Realloc

### malloc

- Allocates contiguous memory.
- Returns pointer to the beginning of the block.

```c
int *list = malloc(3 * sizeof(int));
```

### realloc

- Resizes previously allocated memory.
- Requires original pointer.

```c
int *tmp = realloc(list, 4 * sizeof(int));
```

---

## Linked Lists

**Definition**: A collection of nodes where each node points to the next.

### Singly Linked List

```c
typedef struct node {
    int number;
    struct node *next;
} node;
```

- `next` points to the next node.
- `NULL` marks end of list.
- Access: `n->number` is shorthand for `(*n).number`.

### Operations

- **Search**: O(n)
- **Insert at head**: O(1)
- **Append**: O(n) unless tail is tracked
- **Delete**: O(n) unless previous node is known

### Doubly Linked List

- Each node has `next` and `prev` pointers.
- Easier deletion and bidirectional traversal.

### Memory Management

- Once memory is freed, it must not be accessed.
- Recursive deletion can cause stack overflow; iteration is safer.

---

## Trees

**Definition**: A hierarchical data structure. Binary trees are most common.

### Binary Search Tree (BST)

```c
typedef struct node {
    int number;
    struct node *left;
    struct node *right;
} node;
```

- Left child < parent
- Right child > parent

### Search Operation

```c
bool search(node *tree, int number) {
    if (tree == NULL) return false;
    else if (number < tree->number) return search(tree->left, number);
    else if (number > tree->number) return search(tree->right, number);
    else return true;
}
```

- Time complexity: O(log n) if balanced
- Can degrade to O(n) if unbalanced

### Balanced Trees

- AVL, Red-Black Trees
- Use rotations and height tracking for balance

---

## Dictionaries & Hash Tables

**Definition**: Key-value pairs with fast lookup using hashing.

### Hash Table Structure

```c
typedef struct node {
    char *name;
    char *number;
    struct node *next;
} node;

node *table[26];
```

- Uses buckets indexed by hash function
- Handles collisions via chaining (linked lists)

### Hash Function Example

```c
int hash(char *word) {
    return toupper(word[0]) - 'A'; // Maps A-Z to 0–25
}
```

- Can be extended to more buckets (e.g., 17,000)
- Trade-off: More memory upfront

### Performance

- Lookup: O(1) average, O(n) worst
- Sorting: Poor, not naturally ordered

---

## Tries

**Definition**: Tree-like structure for efficient retrieval, especially strings.

### Structure

```c
typedef struct node {
    struct node *children[26];
    char *number;
} node;
```

- Each node has 26 children (for English alphabet)
- Lookup time: O(length of word)
- Memory-intensive due to large number of pointers

### Pros & Cons

- ✅ Fast lookup and deletion
- ✅ Naturally sorted
- ❌ High memory usage
- ❌ Slower initial insertion

---

## Further Reading

- [Stacks vs Queues](https://www.geeksforgeeks.org/difference-between-stack-and-queue-data-structures/)
- [Linked List Operations](https://www.programiz.com/dsa/linked-list)
- [Binary Search Trees](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
- [Hash Tables Explained](https://www.freecodecamp.org/news/hash-tables-in-javascript/)
- [Trie Data Structure](https://www.geeksforgeeks.org/trie-insert-and-search/)
