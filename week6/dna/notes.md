Here’s a concise **markdown write-up** of your program, followed by explanations of the **key programming/software concepts** and **Python best practices** it demonstrates.

---

# DNA Matcher in Python

This program takes a DNA sequence and a CSV file containing Short Tandem Repeat (STR) counts for a list of individuals. It then identifies which person the DNA most likely belongs to.

---

## How the Program Works

1. **Command-line arguments**
   The program expects two arguments:

   * A CSV file containing names and STR counts.
   * A text file containing the DNA sequence.

   ```python
   if (len(sys.argv) != 3):
       print("Please provide one csv file and one txt file in cli arguments")
       sys.exit(1)
   ```

2. **Load the database (CSV)**
   Uses `csv.DictReader` to load the CSV into a list of dictionaries.
   Each dictionary represents one person, with keys for `"name"` and STRs.

   ```python
   with open(sys.argv[1]) as db_file:
       db_content = list(csv.DictReader(db_file))
   ```

3. **Load the DNA sequence (TXT)**
   Reads the entire DNA string into memory.

   ```python
   with open(sys.argv[2]) as dna_file:
       dna_content = dna_file.read().strip()
   ```

4. **Find STR counts in the DNA**
   For each STR (e.g., `"AGAT"`, `"AATG"`), compute the **longest consecutive run** in the DNA sequence.

   ```python
   for key in db_content[0]:
       if key != 'name':
           matches[key] = longest_match(dna_content, key)
   ```

   `longest_match()` scans the sequence and tracks the maximum number of consecutive repeats.

5. **Compare with database**
   For each person in the database, check if their STR counts match the computed counts. If so, print the name.

   ```python
   for person in db_content:
       if all(matches[key] == int(person[key]) for key in person if key != 'name'):
           print(person['name'])
           return
   ```

   If no matches are found, print `"No match"`.

---

## Key Programming & Software Concepts

### 1. **Data Structures**

* **List of dictionaries (`db_content`)**: convenient for row-based CSV data.
* **Dictionary (`matches`)**: maps STR names to computed counts.

### 2. **File I/O**

* `with open(...)` ensures files are closed automatically (context managers).
* Uses `csv.DictReader` to parse structured CSV data.

### 3. **String Processing**

* Indexing and slicing are used to check DNA substrings efficiently.
* Example: `sequence[start:end]`.

### 4. **Algorithmic Thinking**

* `longest_match()` implements a sliding window to detect repeated subsequences.
* Time complexity: O(n·m) where *n* = sequence length, *m* = subsequence length.

### 5. **Defensive Programming**

* Input validation with `sys.argv` length check.
* Early exit with `sys.exit(1)` if inputs are invalid.

### 6. **Readability & Maintainability**

* Functions (`main()`, `longest_match()`) improve modularity.
* Descriptive variable names (`longest_run`, `dna_content`, `matches`) make code self-documenting.

---

## Python Best Practices Illustrated

✅ Use of **`with open(...)`** for safe file handling.
✅ Use of **`csv.DictReader`** for structured data instead of manual parsing.
✅ **List/dict comprehensions** (`all(matches[key] == ... for key in person ...)`) for concise logic.
✅ **PEP 8 conventions**: lowercase function names, consistent indentation, spacing.
✅ Clear separation of logic: file reading, STR counting, and matching are distinct steps.

---

⚡ In summary:
This code demonstrates **good Python practices** (safe file handling, clear structure, dictionaries for mapping), as well as **core software engineering principles** (modularity, readability, input validation).

---

Would you like me to also add a **"Potential Improvements"** section (e.g., error handling for file not found, performance tweaks, type casting upfront) so your markdown looks more like professional documentation?
