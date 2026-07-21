*This project has been created as part of the 42 curriculum by thamoliv, gproenca.*

# push_swap

Sorting a stack seems trivial — sorting it using only two stacks and a handful of limited operations, with the smallest possible number of moves, is another story entirely. `push_swap` is our answer to that challenge.

---

## Description

`push_swap` takes a list of integers (no duplicates) as arguments and prints, to standard output, the smallest possible sequence of instructions capable of sorting that list in ascending order, using only two stacks (`a` and `b`) and a restricted set of operations.

The program starts with all numbers in stack `a` and stack `b` empty. The goal is to move and reorder the values using `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, and `rrr` until `a` is fully sorted, using the smallest possible number of operations.

In addition to `push_swap` itself, the project implements **four different sorting strategies** (with distinct complexities), a **disorder metric** to characterize the initial state of the stack, and a **benchmark mode** (`--bench`) that reports detailed execution statistics.

### Available operations

| Operation | Effect |
|----------|--------|
| `sa` | Swaps the first two elements at the top of `a`. |
| `sb` | Swaps the first two elements at the top of `b`. |
| `ss` | Executes `sa` and `sb` simultaneously. |
| `pa` | Moves the top of `b` to the top of `a`. |
| `pb` | Moves the top of `a` to the top of `b`. |
| `ra` | Rotates `a` upward (the first element becomes the last). |
| `rb` | Rotates `b` upward (the first element becomes the last). |
| `rr` | Executes `ra` and `rb` simultaneously. |
| `rra` | Rotates `a` downward (the last element becomes the first). |
| `rrb` | Rotates `b` downward (the last element becomes the first). |
| `rrr` | Executes `rra` and `rrb` simultaneously. |

---

## Instructions

### Compilation

```bash
make

```

This generates the `push_swap` binary from the source files, with the `-Wall -Wextra -Werror` flags, following the `NAME`, `all`, `clean`, `fclean`, and `re` rules required by the subject.

```bash
make clean   # removes object files
make fclean  # removes object files and the binary
make re      # rebuilds from scratch

```

### Execution

```bash
./push_swap [--simple|--medium|--complex|--adaptive] <list of integers>

```

* Integers can be passed as separate arguments (`./push_swap 2 1 3`) or as a single string with the numbers separated by spaces (`./push_swap "2 1 3"`).
* The strategy selector is optional. If omitted, `--adaptive` is used by default.
* If no numeric argument is provided, the program prints nothing and returns the prompt.
* In case of an error (non-numeric argument, out of integer bounds, or duplicate values), the program prints `Error` to standard error (`stderr`).

### Usage examples

```bash
$> ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
...
pa

$> ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13

$> shuf -i 0-9999 -n 500 > args.txt ; ./push_swap$(cat args.txt) | wc -l
4323

$> ./push_swap --adaptive 0 one 2 3
Error

```

### Benchmark mode (`--bench`)

Adding the `--bench` flag makes the program print to `stderr`, after sorting:

* The calculated disorder of the initial stack (as a % with two decimal places);
* The name of the strategy used and its theoretical complexity class;
* The total number of operations generated;
* The individual count of each type of operation executed.

```bash
$> ./push_swap --bench --complex 5 4 3 2 1 1>/dev/null
Strategy: Complex O(n*log(n))
Disorder: 100.00%
Total: 7
sa: 1 | pb: 2 | ra: 1 | rra: 1 | pa: 2 |

```

---

## Implemented Algorithms

The subject requires distinct sorting strategies, all generating exclusively operation sequences from the Push_swap model.

### 1. Simple — $O(n^2)$ (`--simple`)

An adaptation of **selection sort**: at each iteration, the smallest value still present in `a` is located, brought to the top by the shortest path (`ra` or `rra`), and pushed to `b`. At the end, all elements return to `a`, resulting in the sorted stack. Suitable as a *baseline* strategy.

### 2. Medium — $O(n\sqrt{n})$ (`--medium`)

A **chunk partitioning** strategy: the range of indexes is divided into blocks of size dynamically calculated based on the input. The values of `a` that fit into the current block are pushed to `b` (with minor rotation adjustments to keep `b` partially sorted). At the end, the largest values in `b` are located and returned to `a`. Splitting the stack into chunks ensures the strategy's high computational performance.

### 3. Complex — $O(n \log n)$ (`--complex`)

An adaptation of **quicksort with median-based partitioning**: at each recursive call, the median pivot is estimated; the stack is traversed, pushing smaller/larger elements to the opposite stack. Recursion is applied separately to each partition, with proper *backtracking* compensation (rewinding with reverse rotations) to handle the circular nature of the stacks.

### 4. Adaptive (`--adaptive`, default behavior)

The subject requires the adaptive strategy to internally choose among
the three complexity regimes **based on the measured disorder** of
the initial stack:

| Disorder | Expected regime |
|----------|------------------|
| `< 0.20` | O(n²) — low disorder |
| `0.20` to `0.50` | O(n√n) — medium disorder |
| `>= 0.50` | O(n log n) — high disorder |

The rationale behind these thresholds is that the closer the stack already is to its sorted state, the less advantage an asymptotically better algorithm (but with higher constant overhead, such as median-based partitioning) provides in practice — a simple selection algorithm already solves the near-sorted case with few operations. As disorder increases, the quadratic cost of the simple algorithm stops paying off, and partitioning strategies (chunk / quicksort) start generating fewer operations.

---

## Disorder Metric

Disorder is a coefficient between `0.0` and `1.0` that measures how far the initial stack is from perfect order, by analyzing discrepant pairs. The measurement is calculated **before** any operation is executed, and displayed as a bonus of the `--bench` flag.

* `0.0` → Stack already sorted (no pair out of order).
* `1.0` → Stack in the worst possible order (all pairs out of order).

---

## Project Structure

| File(s) | Responsibility |
| --- | --- |
| `main.c` | Entry point, strategy selection, overall orchestration. |
| `argument_parser.c`, `split_validations.c`, `string_validation.c` | Rigorous parsing and validation of arguments. |
| `stack_creation.c`, `node_helpers.c` | Creation, freeing, and manipulation of linked lists. |
| `operations_*.c` | Implementation of the 11 official Push_swap operations. |
| `assign_indexes.c` | Conversion of raw values into relative sorting indexes. |
| `algorithm_*.c` | Implementation of the sorting strategies (Simple, Medium, Complex). |
| `disorder.c` | Calculation of the mathematical disorder metric. |
| `bench.c`, `bench_utils.c` | Detailed benchmark of memory usage and instructions. |
| `error_handling.c` | Safe exit in case of invalid data or allocation failures. |

---

## Contributions

This project was developed in a pair, as required by the subject.

- **thamoliv** — argument parsing and validation, stack creation/management,
  Push_swap operations, the four sorting strategies
  (`simple`, `medium`, `complex`), disorder calculation, and `main.c`.
- **gproenca** — algorithm helper functions (`algorithm_utils.c`:
  `is_sorted`, `find_position`, `stack_min_index`, `stack_max_index`), benchmark
  mode, and rotation operations (`operations_rotate.c`).

Both team members understand the entirety of the implemented
algorithms and are able to explain and defend any part of the
code during evaluation.

## Resources

- [Official push_swap subject (42)](https://www.42.fr) — rules, allowed operations, and delivery requirements.
- [o-reo/push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer) — graphical visualizer to debug the generated operation sequence.
- [Push_swap Tutorial (Medium)](https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e) — overview of approaches (radix, chunks, quicksort) used in this type of project.
- [Sorting algorithms overview (LAMFO)](https://lamfo-unb.github.io/2019/04/21/Sorting-algorithms/) — review of classic sorting algorithms and their complexities.
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) — quick reference for time/space complexities.
- [42 Norminette](https://github.com/42School/norminette) — official Norm-checking tool.

### AI usage

AI tools (**Claude**, by Anthropic, and **Gemini**, by Google)
were used as a reference aid throughout the project's development, to:

- Better understand the sorting algorithms required by the subject
  (selection sort, chunk/bucket sort, stack-adapted quicksort) and
  their complexity classes;
- Draft and structure this `README.md` — organizing the sections
  required by the subject, describing the algorithms based on reading
  the already-implemented source code, and formatting the tables.

All of the `push_swap` code was written, reviewed, and is fully
understood by the pair (**thamoliv** and **gproenca**), who are able to
explain and defend any part of it during evaluation; AI served
only as a support and reference tool, never as the author of the
final code.
```
