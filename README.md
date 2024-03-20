Nicolas Corfmat<br>
CruzID: ncorfmat<br>
Assignment: pa2

```
DESCRIPTION
``` 
This program implements a Graph ADT to print path information of vertices from a specified input file.

```
FILES
```
+ `List.h` Header file containing the interface for the List ADT.
+ `List.c` C file containing the List ADT.
+ `Graph.h` Header file containing the interface for the Graph ADT.
+ `Graph.c` C file containing the Graph ADT.
+ `GraphTest.c` C file containing code for testing the Graph ADT functions.
+ `FindPath.c` Contains the main() function that implements the Graph algorithms.
+ `Makefile` Supports the compilation of all the .c programs in the pa2 directory.
+ `README.md` Contains information regarding the files in the pa2 directory and how to run them.

```
BUILD
``` 
To build, run `make` on the terminal command line within the pa2 assignment directory. This creates the **'FindPath'**, **'Graph'**, **'List'**, and **'GraphTest'**  executable files which can then be run.
```
CLEAN
```
Running `make clean` will remove all the executable (.o) files from the pa2 assignment directory as well as other compiler-generated files.
```
RUNNING
```
To run, type `./FindPath` followed by a space separated **input** and **output** text file.
