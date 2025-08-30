# Algorithm and C Fundamentals

## Topics Covered

- [Asymptotic Notation](#asymptotic-notation)  
- [Search Algorithms](#search-algorithms)  
  - [Linear Search](#linear-search)  
  - [Binary Search](#binary-search)  
- [String Comparison](#string-comparison)  
- [Structs in C](#structs-in-c)  
- [Sorting Algorithms](#sorting-algorithms)  
  - [Selection Sort](#selection-sort)  
  - [Bubble Sort](#bubble-sort)  
  - [Merge Sort](#merge-sort)  
- [Recursion](#recursion)  

---

## Asymptotic Notation

Asymptotic notation allows you to describe how an algorithm’s running time or space requirement grows relative to the size of its input \(n\), focusing on the dominant terms and ignoring constant factors.  

Big O (\(O\)) gives an upper bound on growth (worst case), Big Omega (\(\Omega\)) gives a lower bound (best case), and Big Theta (\(\Theta\)) applies when those bounds match, indicating a tight bound on performance.  

Understanding these bounds helps compare algorithms abstractly—regardless of hardware or implementation details—and choose the right one for large inputs.

---

## Search Algorithms

### Linear Search

```c
// O(n) time, O(1) space
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}
```

Linear search scans elements one by one until it finds the target or reaches the end.  

- Best case: \(Ω(1)\) (target at index 0)  
- Average & worst case: \(Θ(n)\)  
- Space complexity: \(O(1)\)  
- Use it on small or unsorted arrays, or data streams where sorting upfront isn’t possible.

### Binary Search

```c
// O(log n) time, O(1) space
int binary_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        // avoid overflow: mid = low + (high - low) / 2
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}
```

Binary search repeatedly divides the search interval in half, requiring random-access, sorted data.  

- Best, average, and worst case: \(Θ(\log n)\)  
- Space complexity: \(O(1)\) (iterative)  
- Precondition: data must be sorted.  
- Common pitfalls: integer overflow when computing mid (use `low + (high - low)/2`) and handling duplicates (decide whether to return first, last, or any matching index).

---

## String Comparison

C’s `strcmp` lets you compare NUL-terminated strings lexicographically:

```c
int result = strcmp(s1, s2);
```

- Returns <0 if `s1` precedes `s2`, 0 if equal, >0 if `s1` follows `s2`.  
- Time complexity: \(O(k)\), where \(k\) is the length of the shorter string.  
- For fixed-length or safer comparisons, consider `strncmp(s1, s2, n)` to avoid overruns.

---

## Structs in C

Use `struct` and `typedef` to group related data:

```c
typedef struct {
    char *name;
    char *number;
} person;

const int NUM_PEOPLE = 3;
person people[NUM_PEOPLE];
people[0].name   = "Lewis";
people[0].number = "123-4567";
```

- Structs are laid out in memory with potential padding for alignment.  
- `typedef` makes it easier to refer to the struct type.  
- You can allocate arrays on the stack (fixed size) or dynamically via `malloc`, but remember to `free` when done.

---

## Sorting Algorithms

Sorting rearranges elements into ascending (or descending) order. Below are three classic algorithms, each illustrating different strategies:

---

### Selection Sort

```c
// always Θ(n^2) time, O(1) extra space
for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
        if (arr[j] < arr[min_idx]) {
            min_idx = j;
        }
    }
    swap(&arr[i], &arr[min_idx]);
}
```

How it works:

- Treat the left portion of the array (initially empty) as the sorted region.  
- On each iteration, scan the unsorted portion to find the smallest element.  
- Swap that element into the next position of the sorted region.  
- Shrink the unsorted region by one and repeat.

Key points:

- Always makes \(\frac{n(n-1)}{2}\) comparisons, regardless of initial order.  
- In-place: uses only constant extra memory.  
- Unstable: equal elements may change relative order.  
- Use when memory is severely constrained or for small arrays.

---

### Bubble Sort

```c
// Θ(n^2) worst, Ω(n) best (with early exit), O(1) space
bool swapped;
for (int pass = 0; pass < n - 1; pass++) {
    swapped = false;
    for (int i = 0; i < n - pass - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(&arr[i], &arr[i + 1]);
            swapped = true;
        }
    }
    if (!swapped) break;  // no swaps means the array is sorted
}
```

How it works:

- Repeatedly step through the list.  
- Compare adjacent elements and swap them if they’re in the wrong order (“bubbling” larger items toward the end).  
- After each pass, the largest unsorted element settles into its final position.  
- Stop early if an entire pass requires no swaps.

Key points:

- Adaptive: best-case linear when the array is already sorted.  
- Stable: preserves the order of equal elements.  
- Educational: simple to understand but inefficient for large arrays.  
- Rarely used in production; replaced by insertion sort or more advanced algorithms.

---

### Insertion Sort

```c
// Θ(n²) worst-case, Ω(n) best-case, O(1) extra space
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Shift elements of arr[0..i-1] that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert key into its correct position
        arr[j + 1] = key;
    }
}
```

How it works:

- Treat the first element as a sorted subarray of size 1.  
- For each subsequent element (`key`), compare it to elements in the sorted portion, moving larger elements one slot to the right.  
- When you find the slot where `key` belongs (either because you reach the start or find a smaller element), insert it there.  
- Repeat until all elements have “been inserted” into the sorted portion.

Key points:

- Stable sort: preserves the order of equal elements.  
- Adaptive: runs in linear time \(\Omega(n)\) when the array is already (or nearly) sorted.  
- In-place: only uses a constant amount of extra memory.  
- Efficient for small datasets or lists that are mostly sorted (online insertion).   
- Simple to implement and often used as the base case in hybrid sorting algorithms.

---

### Merge Sort

```c
// Θ(n log n) time in all cases; O(n) extra space
void merge_sort(int arr[], int left, int right) {
    if (left >= right) return;  // base case: one element
    int mid = left + (right - left) / 2;

    // Recursively sort halves
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    // Merge sorted halves
    merge(arr, left, mid, right);
}
```

How it works:

1. **Divide**: split the array into two roughly equal halves.  
2. **Conquer**: recursively sort each half until you reach subarrays of size 1.  
3. **Combine**: merge the two sorted halves by repeatedly picking the smaller front element from either half.

Key points:

- Stable: equal elements remain in the same relative order.  
- Predictable \(n \log n\) performance in all cases.  
- Requires additional memory proportional to \(n\) for merging.  
- Excellent for large datasets, external sorting (on disk), and linked lists (can be done in-place on pointers).

---

### Quicksort

```c
// Θ(n log n) best/average‐case, O(n²) worst‐case, O(log n) extra space
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];      // choose last element as pivot
        int i = low - 1;

        // partition: elements ≤ pivot to the left, > pivot to the right
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }

        // place pivot in its correct position
        arr[high] = arr[i + 1];
        arr[i + 1] = pivot;
        int pi = i + 1;

        // recursively sort left and right subarrays
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
```

How it works:

- Pick a pivot (here, the last element) and partition the array so that all values ≤ pivot come before it and all values > pivot come after.  
- Recursively apply the same process to the subarray left of the pivot and the subarray right of the pivot.  
- The base case is a subarray of size 0 or 1, which is already sorted.  

Key points:

- Divide and conquer strategy with average‐case time complexity \(\Theta(n \log n)\).  
- Worst‐case time \(\Theta(n^2)\) arises when partitions are highly unbalanced (e.g., already sorted input with a poor pivot choice).  
- In‐place: uses only O(log n) extra space for recursion on average.  
- Not stable by default (equal elements may be reordered).  
- Pivot selection matters: random or “median‐of‐three” pivots reduce the chance of worst‐case behavior.  
- Often combined with insertion sort for small partitions (e.g., size < 10) to improve practical performance.  

---

## Recursion

Recursion is a technique where a function calls itself to solve smaller instances of the same problem.  

- Requires a **base case** to stop further calls (e.g., `n <= 1`).  
- Each call uses a new stack frame—be mindful of stack depth.  
- Ideal for tree/graph traversals, divide-and-conquer, and problems with overlapping subproblems if you add **memoization**.

```c
// O(n) time, O(n) space (call stack)
int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}
```
```c
// O(2^n) time, O(n) space (call stack)
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
```

How it works:

- Check the base case (`n <= 1`); if true, return 1 and stop recursing.  
- Otherwise, call `factorial(n - 1)` and multiply its result by `n`.  
- Each call waits for its deeper call to return before completing.

Key points:

- Every recursive call consumes a stack frame; max depth equals the initial `n`.  
- A clear base case is essential to avoid infinite recursion.  
- Natural fit for problems that split into similar subproblems (divide-and-conquer, tree traversals).  
- Can overflow the call stack if recursion goes too deep.  
- Tail-call optimization (in languages that support it) can eliminate extra frames when the recursive call is the function’s last action.

### Example: Fast Fibonacci with Memoization (Python)

```python
def fib(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo)
    return memo[n]
```

- Memoization caches results to avoid redundant work, turning exponential algorithms into linear-time.

---

## Next Topics to Study

- Quick Sort and its partitioning schemes  
- Heap Sort and priority queues  
- Hash tables: design and collision resolution  
- Graph algorithms: BFS, DFS, Dijkstra’s, A*  
- Dynamic programming paradigms  
- Self-balancing trees: AVL, Red-Black  
- Amortized analysis (e.g., vector resizing)  
- Bitwise operations and low-level optimizations  
- Parallel and concurrent algorithm design  
- Profiling and benchmarking in C