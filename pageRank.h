#ifndef __PAGERANK_H__
#define __PAGERANK_H__

/**------LIBRAIRIES-------**/
#include <stdio.h>
#include <string.h> // --> strlen, strcpy, strcat
#include <stdlib.h> // atoi --> from char to int
#include <math.h> //fabs --> absolute value

/**----GLOBAL VARIABLES---------**/
#define EPSILON 0.00000001
#define JUMPING 0.15
#define DAMPING 0.85
#define ITERMAX 500

/**----STRUCTURE---------**/
typedef struct WebPage
{
	int id;
	int outwardLink;
}WebPage;

typedef struct sparseMatrix
{
	double value;
    int row;
    int column;
}sparseMatrix;

/**-----PROTOTYPE---------**/
int get_highest_node_number(int* lineNbr, char* fileToRead);
void get_matrix_from_file(WebPage * nbrOutwardLink,sparseMatrix* matrix, int fileLineNbr,char* fileToRead);
void matrix_Vector_multiplication(sparseMatrix* matrix,int fileLineNbr,double* VectorResult,int totalNode);
void print_result_in_txt(char* fileToRead, int totalNode,double VectorResult[], double sum);
void print_outward_link(WebPage nbrOutwardLink[], int highestNodeNbr);
void print_sparse_matrix(sparseMatrix matrix[],int fileLineNbr);
void print_vector_result(double VectorResult[], int totalNode);

#endif