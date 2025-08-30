# Data Strucutres

## Queues
FIFO - first in first out on the stack - QUEUES
LIFO - last in first out on the stack - STACKS

array and linked lists are stacks. LIFO.

void push(stack *s, VALUE data) - array based implementation increments top of stack
stack s;
s.top = 0;
push(&s, 28);
push(&s, 33);

VALUE pop(stack *s); - array based still
int x = pop(&s);

in a list need to create new node to push

struct
.
*

Arrays are contiguous
Malloc assings memory contiguously
malloc returns address of chunk of memory, so needs pointer

Queue

typedef struct _queue
{
    VALUE array[CAPACITY];
    int front;
    int size;
} queue;

queue q;
enqueue/dequeue
enqueue(&q, 40);
int x = dequeue(&q);

maintain pointers to head and tail of linked list


### realloc
realloc needs address of original chunk of memory so list here
when original list was different size
int *list = malloc(3 * sizeof(int));
int *tmp = realloc(list, 4 * sizeof(int));

## Linked List

Stitch together using pointers
Use 8 bytes to also point. So more memory but easier to use.
NULL for end of list 0x0

Node - generic container

typedef struct node
{
    int number;
    struct node *next;
} node;

next points to address of another node
need to name node first before can be used hence verbosity

n->number follow arrow to location in memoery
same but cleaner version of (*n).number
brackets just there for precedence, otherwise . (member access) has higher precedence than * (dereference)

Takes O(n) to search a Linked List as always going over it, while 0(1) for an array.
But with Linked List reversed inserting is 0(1), start of list always constant there. Trade off is it being backwards. LIFO. So append? To keep sorted order and FIFO. But appending will be O(n) unless keeping track of last place, but that takes memory.

As soon as you free address in memory, you cannot touch it again.

Extra space, more complicated but more flexible than arrays. Can't do binary search.

Doubly linked lists have next and previous node. Better for insertion and deletion than singly.

Clearing linked lists with recursion and from hash tables maybe can cause stack overflow? Iteration better?

## Trees

2d data structure. While arrays, lists are mostly 1d. Left to right, linear.

Binary search tree. 2d, can do binary search on.

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;

Every nodes left child is smaller, even right child is large

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else if (number == tree->number)
    {
        return true;
    }
}

O(log 2 n) running time if structured evenly, not devolving into linked list
Higher level algorithms for balanced trees, pointers and rotating

## Dictionaries

key: value

With hashing has O(1) lookup
can decide where value goes in memory

use **buckets** - put input into a location, take large domain into smaller range values

hash functions takes inputs as value, put output as value from large domain to finite range of values

**Hash Tables**
sort of combinations of array and linked list
collisions are an issue, e.g. if looking at first letter of name where that's how buckets are sorted

typedef struct node
{
    char *name;
    char *number;
    struct node *next;
} node;

node *table[26];

so rather than bucket of first letter, can do say a bucket of first 4 characters, unlikely but is still O(n) technically though usually O(n/k) with k no. of buckets so can still save some (a lot) time and well designed usually O(1)

#include <ctype.h>

int hash(char *word)
{
    return toupper(word[0]) - 'A';
}
always returns 0-25, but could add more to go up to 17000, but downside of memory space upfront even with returning unsigned value

Bad for sorting

## Tries

short for retrieval
can implement dictionaries (could also do with array, linked list, hash table)

Tree of arrays
Array of pointers

search and adding names doesn't matter how many names are in the structure already
only depends on length of name
so constant time O(length of name)

typedef struct node
{
    struct node *children[26];
    char *number;
} node

26 for english alphabet

BUT a lot of memory. Array for every possible alphabet for each name.

good for lookup/deletion and naturally sorted, bad initial insertion