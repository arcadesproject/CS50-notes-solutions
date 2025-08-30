Here’s a concise and helpful **Markdown (`.md`) explanation** of your Tideman implementation, with an emphasis on both **bubble sort and merge sort**, particularly **how and why merge sort is structured the way it is**.

---

# 🗳️ Tideman Election Algorithm (CS50)

This program implements the **Tideman ranked-choice voting system**, where voters rank candidates in order of preference, and a directed graph is used to determine the winner without cycles.

---

## 🧱 Data Structures

* **`preferences[i][j]`**: Number of voters who prefer candidate `i` over `j`.
* **`locked[i][j]`**: Whether candidate `i` is locked in over `j` (edge exists).
* **`pair` struct**: Holds a winner and loser candidate index.
* **`pairs[]`**: Array of all pairs where one candidate is preferred over another.
* **`candidates[]`**: List of candidate names.

---

## 🔁 Process Overview

1. **Input candidates and voter rankings.**
2. **Build the `preferences` matrix** from all voters' rankings.
3. **Build `pairs[]`** where one candidate is preferred over another.
4. **Sort `pairs[]`** in decreasing order of strength of victory.
5. **Lock in pairs**, avoiding cycles (graph theory).
6. **Print the source** of the graph — the candidate with no incoming edges.

---

## 🔢 Sorting `pairs[]`

### 📌 Bubble Sort (Commented Out)

* Compares adjacent elements and swaps if out of order.
* Repeats until no swaps are made.
* Easy to implement but inefficient for large datasets (`O(n^2)`).

### ✅ Merge Sort (Used in Final Code)

* **Efficient** divide-and-conquer algorithm (`O(n log n)`).
* **Stable** (preserves order of equal elements — optional benefit).
* Recursively splits array into halves, then merges sorted halves.

---

## 📦 Merge Sort Breakdown

### 🧠 Key Concepts to Remember:

* You **divide** until your array is trivially sorted (1 element).
* You **merge** back upward, **comparing and combining** two halves.
* A temporary array is needed to **avoid overwriting** during the merge.

### 🛠️ In This Implementation:

```c
void sort_pairs(void)
{
    merge_sort(0, pair_count - 1);
}
```

#### 📌 `merge_sort(start, end)`

* Recursively calls itself on:

  * Left half: `start` to `mid`
  * Right half: `mid + 1` to `end`
* Calls `merge()` to combine them.

#### 📌 `merge(start, mid, end)`

* Uses two pointers: one for each half.
* Compares **strength of victory**:

  ```c
  preferences[pairs[left].winner][pairs[left].loser]
  ```
* Merges in **descending order** of strength.
* Copies result back into `pairs[]`.

---

## 🧠 Merge Sort Template for Any Array

For sorting a custom array `arr[]` based on some `compare(a, b)` logic:

```c
void merge_sort(int start, int end)
{
    if (start >= end) return;
    int mid = (start + end) / 2;
    merge_sort(start, mid);
    merge_sort(mid + 1, end);
    merge(start, mid, end);  // where merge() uses custom comparison
}
```

And in `merge()`:

* Use a temp array to merge two sorted subarrays.
* Merge based on a **comparison rule** (`>`, `<`, custom function, etc).
* Copy result back into the original array.

---

## 🔄 Cycle Detection (`creates_cycle`)

* Recursive DFS to check if locking a pair would create a loop.
* Prevents creating cycles in the graph — **core to Tideman**.

---

## 🏆 Printing the Winner (`print_winner`)

* Checks which candidate **has no incoming edges** in `locked[][]`.
* This candidate is the **source node** of the graph — the winner.

---

## ✅ Tips to Remember Merge Sort

| Concept           | Tip                                                     |
| ----------------- | ------------------------------------------------------- |
| Base Case         | Always check `if (start >= end)`                        |
| Divide Step       | Calculate `mid = (start + end) / 2`                     |
| Recursive Calls   | `merge_sort(start, mid)` and `merge_sort(mid + 1, end)` |
| Temporary Storage | Allocate a temp array of size `end - start + 1`         |
| Merge Logic       | Use `while` loops with two pointers (`left`, `right`)   |
| Copy Back         | After merging, copy sorted data back to original array  |

---

## 📌 Example Strength Comparison

```c
int left_strength = preferences[pairs[left].winner][pairs[left].loser];
int right_strength = preferences[pairs[right].winner][pairs[right].loser];
```

Change this if sorting by **margin** instead of just preference count:

```c
int left_margin = left_strength - preferences[pairs[left].loser][pairs[left].winner];
int right_margin = right_strength - preferences[pairs[right].loser][pairs[right].winner];
```

---

## ✅ Summary

* Merge sort is ideal here due to better performance.
* Understanding how to **split, merge, and use temp arrays** is key.
* With `merge_sort()` and `merge()`, you can adapt this to sort **any array** based on **any rule**.

Absolutely — here’s the **expanded Markdown explanation** with a **deeper dive into the DFS-based cycle detection** used in `creates_cycle()`, along with **helpful tips** to remember how DFS works in this context.

## Extra DFS algo explained

## 🔄 Cycle Detection with DFS: `creates_cycle`

In Tideman, we **must avoid cycles** when locking in winning pairs, otherwise the graph would not have a clear source (i.e., a winner).

### ✅ Why Cycle Detection Is Needed

* Each locked pair adds a **directed edge** from `winner → loser`.
* If an edge **creates a cycle**, then there’s **no true winner**, as every candidate would eventually point back to themselves.
* We use **DFS (Depth-First Search)** to check if adding an edge `winner → loser` would cause a path from `loser → winner` to form — which is a cycle.

---

## 🧠 How DFS Works in `creates_cycle`

```c
bool creates_cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false;
}
```

### 🔍 Explanation

* You’re checking: **"If I add this edge, can I get back to where I started?"**
* **Start** from `loser`, and **recursively visit** all candidates `i` that `loser` points to (`locked[loser][i] == true`).
* If you ever reach `winner`, you have formed a **cycle**.

---

## 🧭 Visual Example

Imagine the graph so far:

```
A → B
B → C
```

Now consider adding:

```
C → A
```

Calling `creates_cycle(A, C)`:

1. Is `C == A`? ❌
2. Check who `C` points to (let’s say `C → A`) ✅
3. Recursive call: `creates_cycle(A, A)` → this returns `true`, so we **detect a cycle**.

---

## 💡 DFS Tips to Remember

| Concept                       | Tip                                                                                                                |
| ----------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| Recursive Exploration         | DFS dives as deep as possible along each path before backtracking.                                                 |
| Cycle Check Logic             | "If I can return to where I started, there’s a cycle."                                                             |
| Base Case (`loser == winner`) | Always set this first. It defines the **stop condition** for a detected cycle.                                     |
| Recursive Step                | For every node that current node points to, recursively search deeper.                                             |
| Guard Against Infinite Loops  | Make sure you're not revisiting nodes unnecessarily.                                                               |
| Think in Terms of Graph Edges | Each `locked[i][j] == true` is an edge from `i → j`. Visualize these!                                              |
| Pre-order vs Post-order       | In cycle detection, we're doing more of a **pre-order check**: “If I reach this early node again, I found a loop.” |
| Use Debug Printing            | Print `winner`, `loser`, and recursive calls to trace logic while testing.                                         |

---

## 🧠 DFS General Template (Recursive)

You can generalize this pattern to other DFS problems in graphs:

```c
bool dfs(int current, int target)
{
    if (current == target)
        return true;

    for (int i = 0; i < node_count; i++)
    {
        if (edge[current][i])
        {
            if (dfs(i, target))
                return true;
        }
    }
    return false;
}
```

* Use it for **reachability**, **cycle detection**, **component checking**, etc.
* You can add a `visited[]` array if you want to avoid revisiting nodes.

---

## ✅ Summary: DFS in Tideman

* The DFS prevents **invalid graph states** (cycles).
* It ensures the final graph is a **Directed Acyclic Graph (DAG)**.
* DAGs have a **clear source**: the winner.
* Recursive logic is clean and fits naturally with the graph structure.