# Graph Coloring

This program colors undirected graphs in <b>DIMACS</b> format using two algorithm: DSatur and greedy coloring with smallest-degree-last-with-remove ordering strategy. 

## Instructions

Place the graphs you want to be colored in ```graphs``` folder. Compile the program with <b>-O3</b> optimization level in Release mode. To run the program, specify the path to the executable, then the coloring mode. Valid coloring modes are the following:
- ```dsatur``` for DSatur algorithm,
- ```smallest_last``` for greedy algorithm,
- ```best``` (run by default, you can omit the name of the mode). This mode will perform both algorithms and choose the best coloring.

The examples of commands on <b>Windows</b> OS:
```
graph_coloring dsatur

graph_coloring smallest_last

graph_coloring best

graph_coloring
```

## Results

The program was executed on a rather old and slow machine with Intel Core i5-3230M CPU and 6 GB of RAM.

Results for DSatur algorithm on benchmark graphs:

|Graph name                |Number of colors|Coloring time (sec)|
|--------------------------|----------------|-------------------|
|graphs\anna.col           | 11             | 0                 |
|graphs\fpsol2.i.1.col     | 65             | 0.01              |
|graphs\games120.col       | 9              | 0.001             |
|graphs\huck.col           | 11             | 0                 |
|graphs\inithx.i.1.col     | 54             | 0.015             |
|graphs\jean.col           | 10             | 0.001             |
|graphs\latin_square_10.col| 130            | 0.232             |
|graphs\le450_15b.col      | 17             | 0.005             |
|graphs\le450_25a.col      | 25             | 0.01              |
|graphs\le450_5a.col       | 10             | 0.003             |
|graphs\miles1000.col      | 42             | 0.002             |
|graphs\miles1500.col      | 73             | 0.003             |
|graphs\mulsol.i.1.col     | 49             | 0.002             |
|graphs\myciel3.col        | 4              | 0                 |
|graphs\myciel7.col        | 8              | 0.002             |
|graphs\queen11_11.col     | 14             | 0.001             |
|graphs\queen5_5.col       | 5              | 0                 |
|graphs\school1.col        | 17             | 0.013             |
|graphs\school1_nsh.col    | 28             | 0.011             |


Results for greedy algorithms with smallest-degree-last-with-remove ordering strategy:

|Graph name                |Number of colors|Coloring time (sec)
|--------------------------|----------------|-------------------|
|graphs\anna.col           | 11             | 0                 |             |
|graphs\fpsol2.i.1.col     | 65             | 0.004             |             |
|graphs\games120.col       | 9              | 0                 |             |
|graphs\huck.col           | 11             | 0                 |             |
|graphs\inithx.i.1.col     | 54             | 0.005             |             |
|graphs\jean.col           | 10             | 0                 |             |
|graphs\latin_square_10.col| 156            | 0.092             |             |
|graphs\le450_15b.col      | 18             | 0.002             |             |
|graphs\le450_25a.col      | 25             | 0.002             |             |
|graphs\le450_5a.col       | 12             | 0.001             |             |
|graphs\miles1000.col      | 42             | 0.001             |             |
|graphs\miles1500.col      | 73             | 0                 |             |
|graphs\mulsol.i.1.col     | 49             | 0.002             |             |
|graphs\myciel3.col        | 4              | 0                 |             |
|graphs\myciel7.col        | 8              | 0                 |             |
|graphs\queen11_11.col     | 19             | 0                 |             |
|graphs\queen5_5.col       | 7              | 0                 |             |
|graphs\school1.col        | 16             | 0.003             |             |
|graphs\school1_nsh.col    | 18             | 0.002             |             |
