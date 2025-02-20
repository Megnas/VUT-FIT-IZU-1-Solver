# VUT FIT IZU - Project 1
Simple pathfinding algorith specificaly made for 1. project in IZU

## Compilation
```
make
```

## Running program
```
./prog < [TABLE]
```
or
```
make run #run default data/TABLE
```

## Table format
```
xSize   ySize
xStart  yStart
xEnd    yEnd
0x-0y Value . . . Nx-Oy Value
.                 .
.                 .
.                 .
Ox-Ny Value. . . Nx-Ny Value
```
Value Ranges:
```
o        =  impassable tile
<1-inf>  =  tile move cost
```
## Example
Run:
```
./prog < data/TABLE
```
Table content:
```
10 10
3 2
6 5
9 9 9 9 0 9 9 9 9 9
9 0 0 0 0 0 0 0 9 7
9 0 6 2 0 8 9 9 9 6
9 0 5 4 0 3 3 3 3 3
3 3 3 3 3 9 4 0 9 7
9 9 8 8 0 9 2 0 8 9
6 6 5 7 0 0 0 0 7 8
7 7 7 5 0 8 7 8 7 9
8 8 8 8 0 9 7 7 8 9
8 8 6 7 0 9 9 9 9 9
```
Output:
### Start of program
![Screenshot of a loaded table](/img/start.png)
### Middle of program (6th iteration)
![Screenshot of 6th iteration](/img/mid.png)
### End of program
![Screenshot of a found path](/img/end.png)
