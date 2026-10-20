# Travelling-Salesman-Problem
Travelling Salesman Problem in C++ using Held-Karp DP and backtracking with pruning
# Travelling Salesman Problem (C++)

Two C++ solutions to the Travelling Salesman Problem.

| File | Approach | Max cities |
|------|----------|-----------|
| tsp_held_karp.cpp | Held-Karp bitmask dynamic programming | 16 |
| tsp_backtracking.cpp | DFS backtracking with pruning and a nearest-neighbour starting bound | 12 |

## Build and run
g++ -std=c++17 tsp_held_karp.cpp -o tsp
./tsp

## Sample input
4
A B C D
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

Use -1 where there is no direct road.

## Sample output
Minimum cost: 80
