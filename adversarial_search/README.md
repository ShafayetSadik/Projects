# Adversarial Search

Python implementation of a two-player adversarial search assignment for gene-sequence generation. The solver uses minimax with alpha-beta pruning to construct a sequence from a nucleotide pool against a target gene.

## Overview

- Agent 1 maximizes the final utility score.
- Agent 2 minimizes the final utility score.
- Positional weights are derived from the last digits of the student ID.
- Task 2 introduces a special nucleotide `S` and applies a multiplier from the first two digits of the student ID after `S` is selected.

## Project Files

- `adversarial_search.py` - primary interactive solver
- `ass.py` - additional assignment implementation
- `gg.py` - additional assignment implementation
- `Assignment 3_ Adversarial Search.pdf` - assignment brief
- `Assignment 3_ Adversarial Search.docx` - assignment brief

## Execution Flow

1. Enter the nucleotide pool, target gene, and student ID.
2. Select Task `1` or Task `2`.
3. The program evaluates valid move sequences with minimax.
4. Alpha-beta pruning removes branches that cannot improve the final decision.
5. The final sequence is scored using the weighted ASCII-distance utility function implemented in the code.

## Run

```bash
python adversarial_search.py
```

The script prompts for:

1. Nucleotide pool in comma-separated form
2. Target gene
3. Student ID digits
4. Task selection: `1` or `2`

## Notes

- The implementation is self-contained and does not require external packages.
- In Task 2, the script adds `S` to the pool automatically if it is not already present.
