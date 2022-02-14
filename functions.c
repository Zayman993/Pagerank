#include "pageRank.h"

/**
    get_highest_node_number : Get the highest node number in a txt file using the "node1 node2\n" format
    							and counts the number of line in the file

    Parameters
    ----------
    lineNbr : unsigned int*
        pointer of the line counter
    fileToRead : char*
    	name of the file to read

    Returns
    -------
    highestNodeIndex int
        the highest node number in the txt file

**/
unsigned int get_highest_node_number(unsigned int* lineNbr, char* fileToRead)
{
	FILE * file;
	char word[50];
	int highestNodeIndex = -1;
	unsigned int tmp = 0;
	 
	// Opening file 
	if ((file = fopen(fileToRead, "r")) == NULL)
		perror("Erreur : lecture du fichier échouée.");
	 
	else {
		//Get the node with the highest id
		while (fscanf(file, "%s", word) != EOF)
        {
        	if (tmp %2 == 0) //conting number of lines in file
        		(*lineNbr)++;
        	tmp ++;
            if (atoi(word)>highestNodeIndex) //checking the maximum
			{
				highestNodeIndex = atoi(word);
			}
        }
	}
	
	// Closing file 
	fclose(file);

	return highestNodeIndex;
}

/** 
    get_matrix_from_file : from the txt file, returns transfer matrix in the form of sparse matrix and list of node
                            with the number of their outward links

    Parameters
    ----------
    nbrOutwardLink : WebPage*
        pointer of WebPage array that contains each node's id and outward links number

    Matrix : sparseMatrix*
        one-dimensional tab that contains the value, row and column for non-null elements of the transfer matrix


    fileLineNbr : unsigned int
        number of line in txt file + size of matrix
    
    fileToRead : char*
        name of the fila to read
**/
void get_matrix_from_file(WebPage* nbrOutwardLink,sparseMatrix* matrix, unsigned int fileLineNbr, char* fileToRead)
{
	unsigned int i = 0;
	unsigned int tmp;
	sparseMatrix tmpElement;
	FILE * file;
	char word[50];

	// Opening file 
	if ((file = fopen(fileToRead, "r")) == NULL)
		perror("Erreur : lecture du fichier échouée.");
	 
	else 
	{
		while (fscanf(file, "%s", word) != EOF)
        {

	        nbrOutwardLink[atoi(word)].id = atoi(word); //filling in nbrOutwardLink
	        nbrOutwardLink[atoi(word)].outwardLink ++;
	        tmp = atoi(word);
	        fscanf(file, "%s", word);

	        tmpElement.value = 1.0;
	        tmpElement.row = atoi(word);
	        tmpElement.column = tmp;
	        matrix[i] = tmpElement; //filling in sparse matrix
	        i++;
        }
	}
	
	for (i = 0; i < fileLineNbr; i++) //dividing all sparse matrix value by the number of outwardLink for each node
	{
        matrix[i].value = matrix[i].value / nbrOutwardLink[matrix[i].column].outwardLink;
	}

	// Closing file 
	fclose(file);

	return;
}

/** 
    matrix_Vector_multiplication : calculates vector = DAMPING(Matrix * Vector) + JUMPING (1/totalNode)

    Parameters
    ----------

    Matrix : sparseMatrix*
    	one-dimensional tab that contains the value, row and column for non-null elements of the transfer matrix

	fileLineNbr : unsigned int
    	number of line in txt file + size of matrix
    
    VectorResult : double*
       vector result with the eigen values

    totalNode : unsigned int
    	number of node in graph
**/
void matrix_Vector_multiplication(sparseMatrix matrix[],unsigned int fileLineNbr,double* VectorResult,unsigned int totalNode)
{
	unsigned int i;
	float result[totalNode];

	for (i = 0; i < totalNode; ++i) //initializing the calculation vector
	{
		result[i]=0;
	}

	for (i = 0; i < fileLineNbr; ++i) //sparse Matrix x vector
	{
        result[matrix[i].row] = result[matrix[i].row] + (matrix[i].value * VectorResult[matrix[i].column]);
	}
    
    for (i = 0; i < totalNode; ++i) //multiplying by DAMPING factor and adding JUMPING factor
    {
        result[i] = (result[i]*DAMPING) + (JUMPING/totalNode);
    }

	for (i = 0; i < totalNode; ++i) //copying the results in vectorResult
    {
        VectorResult[i] = result[i];
    }

    return;
}


/** PRINT FUNCTIONS **/

void print_result_in_txt(char* fileToRead, unsigned int totalNode,double VectorResult[], double sum,unsigned long millis)
{
	unsigned int i;

	FILE *fp;

	char* extension = "_Result.txt";
	char* name_with_extension;
	name_with_extension = malloc((strlen(fileToRead)-4)+strlen(extension)+1); // name of result file : <fileToRead>_Result.txt
	for (int i = 0; i < strlen(fileToRead)-4; ++i)
	{
		name_with_extension[i] = fileToRead[i]; //take out the '.txt' part in fileToRead
	}
	strcat(name_with_extension, extension);

	fp=fopen(name_with_extension, "wb"); //opening file
	if(fp == NULL)
	{
	    perror("Erreur : lecture du fichier échouée.");
	}

	fprintf(fp, "-------------VECTOR RESULT-------------\n"); //priting
	for (i = 0; i < totalNode; ++i)
	{
    	fprintf(fp,"%d : %lf\n",i, VectorResult[i]);
 	}
	fprintf(fp, "PRECISION ERROR : %lf\n",sum);
	fprintf(fp, "Finished in %ld ms\n", millis );
	fclose(fp); //closinf file

	printf("--> Resultats sauvegardés dans %s\n.",name_with_extension);
	free(name_with_extension); //free space
}

void print_outward_link(WebPage nbrOutwardLink[], unsigned int highestNodeNbr)
{
	unsigned int i;

	printf("%s\n", "---------OUTWARD-LINK---------");
	for (i = 0; i < highestNodeNbr+1; ++i)
	{
		printf("%d : <id :%d outwardLink :%d> \n" ,i, nbrOutwardLink[i].id, nbrOutwardLink[i].outwardLink );
	}
	return;
}

void print_sparse_matrix(sparseMatrix matrix[], unsigned int fileLineNbr)
{
	unsigned int i;

	printf("%s\n", "---------MATRIX---------");
	for (i = 0; i < fileLineNbr; ++i)
	{
		printf("%d : <value :%lf row :%d column: %d \n" ,i, matrix[i].value, matrix[i].row, matrix[i].column );
	}
	return;
}

void print_vector_result(double VectorResult[], unsigned int totalNode)
{
	unsigned int i;

	printf("%s\n", "---------VECTOR-RESULT---------");
	for (i = 0; i < totalNode; ++i)
	{
		printf("%d : %lf \n" ,i, VectorResult[i] );
	}
	return;
}