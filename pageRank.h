#ifndef __PAGERANK_H__
#define __PAGERANK_H__

/**------LIBRAIRIES-------**/
#include <stdio.h>
#include <string.h> // --> strlen, strcpy, strcat
#include <stdlib.h> // atoi --> from char to int
#include <math.h> //fabs --> absolute value
#include <time.h> //clock()

/**----GLOBAL VARIABLES---------**/
#define EPSILON 0.000001
#define JUMPING 0.15
#define DAMPING 0.85
#define ITERMAX 100

/**----STRUCTURE---------**/
typedef struct WebPage
{
	int id;
	unsigned int outwardLink;
}WebPage;

typedef struct sparseMatrix
{
	double value;
    unsigned int row;
    unsigned int column;
}sparseMatrix;

/**-----PROTOTYPE---------**/
unsigned int get_highest_node_number(unsigned int* lineNbr, char* fileToRead);
void get_matrix_from_file(WebPage * nbrOutwardLink,sparseMatrix* matrix, unsigned int fileLineNbr,char* fileToRead);
void matrix_Vector_multiplication(sparseMatrix matrix[],unsigned int fileLineNbr,double* VectorResult,unsigned int totalNode);
void print_result_in_txt(char* fileToRead, unsigned int totalNode,double VectorResult[], double sum, unsigned long millis);
void print_outward_link(WebPage nbrOutwardLink[], unsigned int highestNodeNbr);
void print_sparse_matrix(sparseMatrix matrix[],unsigned int fileLineNbr);
void print_vector_result(double VectorResult[], unsigned int totalNode);

#endif