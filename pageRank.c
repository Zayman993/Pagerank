#include "pageRank.h"

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("%s\n", "Veuillez executer le programme comme ceci : ");
		printf("%s\n", "./pageRank_exe <nom du fichier txt> <nombre de noeud> ");
	}
	else
	{
		/** CLOCK START **/
		clock_t begin = clock();

		/** VARIABLES **/
		unsigned int i;
		unsigned long millis;

		char* fileToRead = argv[1];
		unsigned int totalNode = atoi(argv[2]);

		unsigned int cpt = 0; //iteration cpt
		unsigned int convergence =1; //True
		unsigned int highestNodeNbr =0; //highest id number for a node (size of nbrOutwardLink)
		unsigned int fileLineNbr = 0; //number of line in file (size of sparse matrix)

		double sum = 0;

		highestNodeNbr = get_highest_node_number(&fileLineNbr,fileToRead);

		/** ARRAY AND MATRIX **/
		/** ARRAY AND MATRIX **/
		double VectorResult[totalNode]; 
		double VectorBackup[totalNode]; 


		sparseMatrix* matrix = (sparseMatrix*) malloc(fileLineNbr*sizeof(sparseMatrix)); //sparse matrix
		WebPage* nbrOutwardLink =(WebPage*) malloc((highestNodeNbr+1)*sizeof(WebPage)); //array of nodes with their outward links

		/** INITIALIZATION **/
		for (i = 0; i < highestNodeNbr+1; i++) //nbrOutwardLink
		{
			nbrOutwardLink[i].id = -1;
			nbrOutwardLink[i].outwardLink = 0;
		}
 		
 		get_matrix_from_file(nbrOutwardLink,matrix,fileLineNbr, fileToRead); //fill in nbrOutwardLink & Matrix


 		for (i = 0; i < totalNode; ++i) //VectorResult & VectorBackup initialized at 1/totalNode
 		{
 			VectorResult[i] = (1.0/totalNode);
 			VectorBackup[i] = (1.0/totalNode);
 		}


 		/** ITERATION **/
 		while (cpt < ITERMAX  && convergence == 1 ) 
 		{
			convergence = 0;
			for (i = 0; i < totalNode; ++i) //save old vector result
			    VectorBackup[i] = VectorResult[i];

			matrix_Vector_multiplication(matrix,fileLineNbr,VectorResult,totalNode); //matrix x vector

			for (i = 0; i < totalNode; ++i) //check for convergence
			{
			    if ((VectorResult[i] - VectorBackup[i]) > EPSILON)
			    {
			    	convergence = 1;
			        break;
			    }
			}

			cpt ++;
		}


		/** PRECISION ERROR **/
		for (i = 0; i < totalNode; ++i) 
 		{
 			sum += VectorResult[i];
 		}
 		sum -= 1;
 		sum = fabs(sum); //absolute value


 		/** CLOCK END **/
 		clock_t end = clock();
 		millis = (end -  begin) * 1000 / CLOCKS_PER_SEC;

		/** WRITE RESULT IN TXT FILE**/
		print_result_in_txt(fileToRead,totalNode,VectorResult, sum, millis);

		/** FREE **/
		free(nbrOutwardLink);
		free(matrix);

	}

	return 0;
}