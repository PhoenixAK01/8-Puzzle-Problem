# 8-Puzzle-Problem
using BFS, DFS and Best First Search.

8-Puzzle Solver using BFS
Features:-
Uses BFS (Breadth-First Search) to explore the puzzle states level by level.
Tracks visited states to avoid repetition using an unordered_set (hash set).
Automatically detects if a solution exists and prints "Success" if the goal state is reached, otherwise prints "No solution".
Time Complexity is O(9!) ≈ O(362,880) in the worst case.
Space Complexity is O(9!) ≈ O(362,880) in the worst case.

8-Puzzle Solver using DFS
Features:-
Uses Depth-First Search (DFS) for exploring possible states.
Detects already visited states using an unordered_set to avoid infinite loops.
Terminates upon finding a solution or when no solution exists.
Compact and straightforward implementation in C++.
Time Complexity is O(9!) ≈ O(3.6 × 10⁵) in the worst case.
Space Complexity is O(V) ≈ O(9!) ≈ O(3.6 × 10⁵) in the worst case.

8-Puzzle Solver using Best First Search
Features:-
Implements a Greedy Best-First Search (not A*, because path cost g(n) is not added).
Detects if the puzzle is unsolvable before searching.
Prints the solution path (from initial to goal state).
Uses unordered_set to track visited states and avoid cycles.
Time Complexity is O(9!) ≈ O(362,880) in the worst case.
Space Complexity is O(9!) ≈ O(362,880) in the worst case.
