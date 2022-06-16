# CS170-Eight-Puzzle

## About the Code

This is a project that uses A\* Search algorithm using one of three possible
heuristics: `Uniform Cost Search`, `Misplaced Tiles`, and `Euclidean Distance`
to solve a variant of Eight puzzle problem.

## Design

### Problem class

This class holds the problem space i.e. the `initial state` of the problem, the
`goal state` of the problem and the `operators` that will enable a change in the
state of a problem. The `initial states` and `goal state` are represented by a
2D array of integers with the value `0` representing the empty tile in
traditional eight puzzle games.

### node class

This class creates a tree structure using the `Problem` class. This class is
used to keep track of child and parent nodes the current node object.

### Search class

This class encapsulates the `Problem` and `node` object and will perform the
search operation on the `problem` state.

## Optimization

A priority queue is used to store the nodes that are being expanded, ordered
based on their total path cost. A map object is also used to store the
previously nodes. This map serves as a look up table to help us optimize the
process of eliminating visiting duplicate nodes. This search was implemented
using `graph search` optimization method.

## Dependencies

a `C++ 11` enabled compiler

## Results

After conduction a simple research on a number of problem states, A\* search
with Uniform cost heuristic is the slowest of the three heuristics while
Misplaced tiles comes second and euclidean distance solves the problem much
faster that the two heuristics.
