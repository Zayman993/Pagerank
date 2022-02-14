# Pagerank
PageRank algorithm coded in C.

## Description
Done as part of a school assignment.
The objective is to implement the PageRank algorithm with the power method, to apply it on a real dataset and observe/interpret the results.

## Usage

### Execution
This program takes two arguments : file name (.txt) and the number of nodes in the associated graph.

Example :
```
PageRank>$ make
PageRank>$ ./pageRank_exe email-Eu-core.txt 1005
```
or
```
PageRank>$ make
PageRank>$ ./pageRank_exe Slashdot0811.txt 77360
```

### Output 
```
PageRank>$ ./pageRank_exe Slashdot0811.txt 77360
--> Resultats sauvegardés dans Slashdot0811_Result.txt
```
 
#### Slashdot0811_Result.txt 
```
-------------VECTOR RESULT-------------
0 : 0.000181
1 : 0.000106
2 : 0.000040
3 : 0.000085
4 : 0.000076
5 : 0.000007
...
77358 : 0.000012
77359 : 0.000012
PRECISION ERROR : 0.001482
Finished in 688 ms
```

## Contributing
Made by Imane AZIZ IATIC5 year 2022.
