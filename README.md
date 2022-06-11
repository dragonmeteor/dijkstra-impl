# Implementation of Dijkstra's Algorithm in Multiple Programming Languages

I want to learn how to use various programming languages and tools to do things. Reading tutorials can help me get some feel, but that's not enough exposure. It's only you have implemented something complicated with a set of tools that you start to get a real feel for it.

[Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) is a faily complicated algorithm. It requires you to implement a graph abstraction. It also requires you to implement a priority queue that allows key mutation. I believe it is a good programming exercise that can get you familiar with new programming languages.

## Input Specification

The input is contained in a file. It contains an undirected graph with non-negative weights. On the last line, there's a pair of vertex where the shortest path between them should be specified.

```
<n = number of vertices>
<name of vertex 1>
<name of vertex 2>
<name of vertex 3>
  :
  :
<name of vertex n>
<m = number of edges>
<name-of-vertex-1> <name-of-vertex-2> <weight-of-edge>
<name-of-vertex-1> <name-of-vertex-2> <weight-of-edge>
  :
  :
<name-of-vertex-1> <name-of-vertex-2> <weight-of-edge>
<source-vertex> <destination-vertex>
```

Vertex names are alpha-numeric strings that can contain underscores. Weights are floaing point numbers.

## Output Specification

The output is also contained in a file. If there is no path between the source vertex and the destination vertex, the file should contain only one line with the number ``-1``.

If there is a path, the first line should contain the shortest distance between the source and destnation. Then, starting from the next line, the vertices of the shortest path between the source and the destination should be printed, with one vertex name on its own line.

## Example Inputs and Outputs

### Example 1
```
3
A
B
C
3
A B 10
B C 10
A C 30
A C
```

### Example Output 1
```
20
A
B
C
```

### Example Input 2
```
4
A
B
C
D
2
A B
C D
A D
```

### Example Input 2
```
-1
```

## Program Specification

An implementation must be invocable from the command line. The program should take two inputs: the input file name and the output file name.

## Languages with Implementations

