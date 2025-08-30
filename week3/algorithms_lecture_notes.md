# NOTES

Asymptotic notation - big O, big Omega, big Theta
big O for worst case 
big Omega for best case
and Theta used is big O and Omega are the same for an algorithm

## search algos
linear search O(n) (simple loop)
binary search O(log n) (divide and conquer, middle, then middle left/right etc)

If its an unsorted list and only want to find something once then linear is fine, but if it could be looking up a lot then you sort first and then implement a better algorithm e.g. binary search

strcmp(string_1, string_2) returns int less than 0 if s1 before s2, 0 if same, over 1 if s1 after s2

## structs
Structs:
typedef struct
{
    string name;
    string number;
}
person;
const int num = 3;
person people[num];
people[0].name = "Lewis";

## sorting
selection sort O(n^2) also Omega n^2 as always goes over the same steps and Theta n^2 loop find smallest and swap with array[n] 
bubble sort O(n^2) but Omega(n) if you check there were no swaps eg with swap counter and if its 0 after a loop you exit (so better than merge if already sorted)
merge sort O(n log n) also for omega and theta (not as good as n but good!) sort left half, sort right half then merge but uses little more space for storage when working out - comparable to binary search due to the halving mechanism? is a bit recursive

Recursion when it calls itself e.b. binary search can be
Iteration is loops, usually easier to code but recursion can be efficient in some cases

Recursion needs base case e.g. height 0 return to then go through rest?

Check factorial.c for example of recursion

Fibonaccia has multiple base cases
Collatz conjecture has multiple recursive cases - if n == 1 return, if n even n/2, if n odd 3n+1

## Recursion

generally slower than loops more more descriptive/expressive
Although good for **tree-based** structures and **divide and conquer** algos (e.g. merge sort)
Also can be faster with **memoization**

# Fast recursive Fibonacci with memoization
def fib(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fib(n-1, memo) + fib(n-2, memo)
    return memo[n]

Also used heavily in functional programming e.g. haskell