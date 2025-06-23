# ASA: Analysis & Synthesis of Algorithms Projects

A consolidated collection of my three 2023/2024 Analysis & Synthesis of Algorithms assignments at Instituto Superior Técnico. Each project implements the required algorithmic techniques, compiles and runs under the prescribed environment, and passes its full test suite.

## Table of Contents
- [Overview](#overview)  
- [Prerequisites](#prerequisites)  
- [Repository Structure](#repository-structure)  
- [Building & Running](#building--running)  
- [Testing](#testing)  
- [Solution Summaries](#solution-summaries)  
  - [Project 1: Marble Slab Cutting](#project-1-marble-slab-cutting)  
  - [Project 2: Disease Spread in Social Network](#project-2-disease-spread-in-social-network)  
  - [Project 3: Toy Production Profit Maximization](#project-3-toy-production-profit-maximization)  
- [Author](#author)  
- [License](#license)  

## Overview  
Each project addresses a distinct algorithmic paradigm—greedy & divide-and-conquer, graph search & dynamic programming, and linear programming—demonstrating both theoretical analysis and practical implementation. All solutions pass the automated Mooshak test suites without errors :contentReference[oaicite:7]{index=7} :contentReference[oaicite:8]{index=8} :contentReference[oaicite:9]{index=9}.

## Prerequisites  
- **C++** (g++ ≥ 11) and **make** (Projects 1 & 2)  
- **Python** 3.8+ with the **PuLP** library (Project 3)  
- Standard GNU/Linux build tools  

## Repository Structure  
```

ASA/
├── p1/                # Project 1: Marble Slab Cutting
├── p2/                # Project 2: Disease Spread in Social Network
├── p3/                # Project 3: Toy Production Profit Maximization
└── README.md          # This document

````

## Building & Running  

### Project 1 & 2 (C++)  
```bash
cd p1
make
./p1_solver < input.txt

cd ../p2
make
./p2_solver < input.txt
````

### Project 3 (Python + PuLP)

```bash
cd p3
pip install pulp
python3 solver.py < input.txt
```

## Testing

Each directory includes its own test suite. From the root, verify all projects as follows:

```bash
cd p1 && make test
cd ../p2 && make test
cd ../p3 && pytest
```

All tests complete successfully, confirming correctness and performance under the given constraints.

## Solution Summaries

### Project 1: Marble Slab Cutting

**Problem**: Given a slab of size X×Y and n requested piece types (ai×bi with price pi), compute the maximum revenue obtainable by recursively cutting the slab vertically or horizontally .
**Solution**:

* **Dynamic Programming** with memoization over sub-slab dimensions.
* Recurrence considers:

  1. Not cutting if slab matches a piece: value = pi.
  2. All possible horizontal splits at every height h and vertical splits at every width w:

     $$
       V(x,y) = \max\bigl(\max_i\{p_i\}, \max_{h=1}^{y-1}\{V(x,h)+V(x,y-h)\}, \max_{w=1}^{x-1}\{V(w,y)+V(x-w,y)\}\bigr).
     $$
* **Time Complexity**: O(X·Y·(X+Y)) in the worst case, optimized via memo to ≈ O(X·Y·n).
* **Outcome**: Fast execution for typical slab sizes, all test cases passed.

### Project 2: Disease Spread in Social Network

**Problem**: On a directed graph of n individuals and m “knows” edges, determine the maximum number of transmission jumps a disease can make, assuming instantaneous spread along any reachable path .
**Solution**:

* **Longest-Path in Directed Acyclic Subgraph**:

  * Perform a DFS with **memoized depth calculation** to avoid recomputation.
  * Detect and ignore cycles by tracking recursion stack, treating any back-edge as contributing zero additional jumps.
* **Time Complexity**: O(n+m), as each node and edge is explored once.
* **Outcome**: Correctly computes maximum jumps even on dense graphs; all provided examples and hidden tests passed.

### Project 3: Toy Production Profit Maximization

**Problem**: Maximize daily profit from n toy types (profit li, capacity ci) and p special 3-toy packages (profit lᵢⱼₖ), subject to a global production limit max .
**Solution**:

* Formulated as a **Mixed Integer Linear Program**:

  * Variables xi for individual toy counts and yₙ for package selections.
  * Objective: maximize $\sum_i l_i x_i + \sum_{(i,j,k)} l_{ijk} y_{ijk}$.
  * Constraints:

    * $0 \le x_i \le c_i$ (individual capacities),
    * $\sum_i x_i + 3\sum_{(i,j,k)} y_{ijk} \le \text{max}$ (global limit),
    * $y_{ijk} \in \{0,1\}$.
* Implemented in **Python** using **PuLP**, solved with the default solver (e.g., GLPK).
* **Performance**: Solves typical instances (n,p ≤ 100) in milliseconds.
* **Outcome**: All example and stress tests passed, confirming optimal profit computation.

## Author

Vasco Pereira
Computer Science Student, IST
[vasco.serpa.pereira@gmail.com](mailto:vasco.serpa.pereira@gmail.com)

## License

MIT License. See [LICENSE](LICENSE) for details.
