# Adversarial Search for Gene Sequence Generation

![Python](https://img.shields.io/badge/Python-3.x-blue)
![Algorithm](https://img.shields.io/badge/Algorithm-Minimax%20%2B%20Alpha--Beta-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Type](https://img.shields.io/badge/Project-AI%20Assignment-orange)

This repository contains a Python implementation of an adversarial search problem for gene sequence generation. Two agents take turns choosing nucleotides from a shared pool to construct a sequence, where:

- Agent 1 tries to maximize similarity to a target gene.
- Agent 2 tries to minimize that similarity.

The solution uses minimax search with alpha-beta pruning and includes support for a special nucleotide `S` in Task II.

## Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Utility Function](#utility-function)
- [Task I](#task-i)
- [Task II](#task-ii)
- [Getting Started](#getting-started)
- [Sample Run](#sample-run)
- [Notes](#notes)
- [Future Improvements](#future-improvements)

## Overview

The project is based on an AI assignment about adversarial search in a gene-sequence game.

Inputs:

- a nucleotide pool such as `A,T,C,G`
- a target gene such as `ATGC`
- a student ID used to generate positional weights

Output:

- the best gene sequence under optimal play
- the corresponding utility score
- for Task II, whether using the special nucleotide `S` is beneficial

The main implementation is in `adversarial_search.py`.

## Features

- Minimax search for two-player optimal decision making
- Alpha-beta pruning to reduce unnecessary search
- Interactive command-line interface
- Task I support for the standard game
- Task II support for the special nucleotide `S`
- Weight generation from the last `n` digits of the student ID

## Project Structure

```text
.
|-- adversarial_search.py
|-- ass.py
|-- gg.py
|-- Assignment 3_ Adversarial Search.pdf
|-- Assignment 3_ Adversarial Search.docx
|-- README.md
```

Files:

- `adversarial_search.py` - main and most complete implementation
- `ass.py` - alternative draft implementation
- `gg.py` - alternative draft implementation
- `Assignment 3_ Adversarial Search.pdf` - assignment description
- `Assignment 3_ Adversarial Search.docx` - assignment description

## How It Works

At each turn:

1. An agent selects one nucleotide from the remaining pool.
2. That nucleotide is appended to the growing gene sequence.
3. The selected nucleotide is removed from the pool.
4. Control passes to the other agent.

The search continues until the pool is empty. The final sequence is then scored against the target using a weighted utility function.

### Algorithm

The implementation uses minimax with alpha-beta pruning:

- Agent 1 is the maximizing player.
- Agent 2 is the minimizing player.
- Each recursive call explores one possible nucleotide choice.
- Alpha-beta pruning cuts off branches that cannot improve the final decision.

This is implemented in the `minimax(...)` method of `GeneSequenceGame`.

## Utility Function

The score is based on weighted ASCII distance:

```text
utility = -sum(weight_i * abs(ASCII(gene[i]) - ASCII(target[i])))
```

Rules used by the implementation:

- `N = max(len(gene_sequence), len(target))`
- if a position is missing in either string, its ASCII value is treated as `0`
- if no weight exists for a position, the default weight is `1`
- a higher utility is better because the score is negative distance

### Weight Generation

If the target length is `n`, the program takes the last `n` digits of the student ID as weights.

Example:

```text
Student ID: 18104052
Target length: 4
Weights: [4, 0, 5, 2]
```

If the student ID has fewer than `n` digits, the implementation left-pads the weight list with `0`.

## Task I

Task I solves the standard adversarial gene-building problem without relying on the special nucleotide.

Expected output:

```text
Task I Solution (Basic Minimax)
Best gene sequence generated: <sequence>
Utility score: <score>
```

## Task II

Task II introduces a special nucleotide `S`.

Behavior in this implementation:

- if Task II is selected and `S` is missing from the pool, it is added automatically
- if Agent 1 selects `S`, a genetic booster is activated
- starting from the position where `S` is selected, all remaining weights are multiplied by:

```text
first two digits of student ID / 100
```

The script compares:

- the best score without `S`
- the best score with `S`

and then prints whether using `S` is beneficial.

Expected output shape:

```text
Task II Solution (With Special Nucleotide)
Decision: YES|NO
With special nucleotide:
  Sequence: <sequence>
  Score: <score>
```

## Getting Started

### Requirements

- Python 3.x

No external dependencies are required.

### Run

From the project directory:

```bash
python adversarial_search.py
```

You will be asked for:

1. nucleotide pool
2. target gene sequence
3. student ID as space-separated digits
4. task selection: `1` or `2`

## Sample Run

### Example Input

```text
Enter nucleotides pool (comma-separated, e.g., A,T,C,G): A,T,C,G
Enter target gene sequence (e.g., ATGC): ATGC
Enter student ID (space-separated digits, e.g., 1 8 1 0 4 0 5 2): 1 8 1 0 4 0 5 2
Which task do you want to solve? Enter 1 for Task I or 2 for Task II: 1
```

### Example Output Format

```text
Task I Solution (Basic Minimax)
Best gene sequence generated: AGCT
Utility score: -54
```

For Task II, the program prints the decision and the best sequence found with the special nucleotide case.

## Notes

- `adversarial_search.py` is the recommended entry point for this repository.
- The two other Python files appear to be development drafts and are not the primary version.
- The README reflects the current code behavior, not a rewritten specification.
- In the current environment, Python execution was not available to verify sample output live.

## Future Improvements

- Add unit tests for Task I and Task II
- Add command-line flags for non-interactive execution
- Separate game logic from input/output for easier testing
- Align Task II output wording more closely with the assignment samples
- Add benchmark examples showing pruning effectiveness
