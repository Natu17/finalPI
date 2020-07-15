#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "neighbourhood.h"
#include "treeADT.h"
#include "queries.h"

#define BLOQUE 5
#define MAX_LENGHT 1000

//Asigna valores a una nueva estructura y la almacena
void loadNeighbourhood(neighbourhoodADT neighbourhood, char* nameNeighbourhood, const char* population) { 
	neighbourhoodType newNeighbourhood;
	newNeighbourhood.name = nameNeighbourhood;
	newNeighbourhood.population = atoi(population); 
	addNeighbourhood(neighbourhood, newNeighbourhood);
} 

//copia caracteres al string hasta formar la palabra y luego cierra el string
char * fill(char c, char * string, FILE * file){
	errno=0;
	int countString = 0;
	while (c != ';' && c != '\n') {
		if (countString % BLOQUE == 0) {
			string = realloc(string, (countString + 1 + BLOQUE) * sizeof(char));
			if(errno == ENOMEM){
				perror("Not enough memory");
				return NULL;
			}
		}
		string[countString++] = c;
		c = fgetc(file);
	}
	string[countString] = '\0';
	string = realloc(string, (countString + 1) * sizeof(char));
	return string;
}



//Recorre el archivo csv de barrios y separa cada file en dos strings: uno para el nombre del barrio y otro para sus habitantes
void readNeighbourhood(neighbourhoodADT neighbourhood, FILE* fileNeighbourhood) {
	char c;
	char *nameNeighbourhood = NULL;
	char *population = NULL;
	int firstLine = 1, colNumber = 1;
	while((c = fgetc(fileNeighbourhood)) != EOF) {
		if (c == '\n') {
			firstLine = 0;	
		} 
		else {

			if (!firstLine) {
				if (colNumber == 1) {
					nameNeighbourhood = fill(c, nameNeighbourhood, fileNeighbourhood);
					colNumber++;
					c = fgetc(fileNeighbourhood);
				}
				if (colNumber == 2) {
					population = fill(c, population, fileNeighbourhood);
					colNumber = 1;
					loadNeighbourhood(neighbourhood, nameNeighbourhood, population);
				}
			}
		}
	}
	free(nameNeighbourhood);
	free(population);
}

//Devuelve un puntero a int con los indices de las columnas utiles
int* readFirstRow(FILE* fileTrees) {
	errno = 0;
	int countCol = 1;
	char row[1000];
	int* index;
	index = malloc(3 * sizeof(int));
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return NULL;
	}
	fgets(row, MAX_LENGHT, fileTrees);
	char* token = strtok(row, ";");
	while (token != NULL)
    {
    	if (strcmp(token, "comuna") == 0 || strcmp(token, "NEIGHBOURHOOD_NAME") == 0) {
    		index[0] = countCol;
    	}
    	else if (strcmp(token, "nombre_cientifico") == 0 || strcmp(token, "COMMON_NAME") == 0) {
    		index[1] = countCol;
    	}
    	else if (strcmp(token, "diametro_altura_pecho") == 0 || strcmp(token, "DIAMETER") == 0) {
    		index[2] = countCol;
    	}
    	
    	token = strtok(NULL, ";");
    	countCol++;
    }
    return index;
}	

//Almacena los valores proporcionados por readTrees()
void loadTrees(treeADT tree, neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* nameSpecies, char* diameter) {
	addTree(tree, nameSpecies, atof(diameter));              
	addOneTree(neighbourhood, nameNeighbourhood);
}

//Recorre el archivo csv arboles, separando en strings los valores de las columnas utiles, proveidas por readFirstRow()
void readTrees(treeADT tree, neighbourhoodADT neighbourhood, FILE* fileTrees) {
	char c;
	char *nameNeighbourhood = NULL;
	char *nameSpecies = NULL;
	char *diameter = NULL;
	int count = 1;
	int* index = readFirstRow(fileTrees);
	while ((c = fgetc(fileTrees)) != EOF) {
		if (c == ';') {
			count++;	
		} 
		else {

			if (count == index[0]) {
				nameNeighbourhood = fill(c, nameNeighbourhood, fileTrees);
				count++;
			}
			else if (count == index[1]) {
				nameSpecies = fill(c, nameSpecies, fileTrees);
				count++;
			}
			else if (count == index[2]) {
				diameter = fill(c, diameter, fileTrees);
				count++;				
			}
			if (c == '\n') {
				loadTrees(tree, neighbourhood, nameNeighbourhood, nameSpecies, diameter);
				count = 1;
			}
		}
	}
	free(nameNeighbourhood);
	free(nameSpecies);
	free(diameter);
	free(index);

}

//retorna 0 si no tuvo ningun problema, 1 o 2 si tuvo un problema
int main(int argc, char const *argv[])
{

	if (argc != 3) {
		perror("Incorrect number of arguments\n");
		return 2;
	}

	FILE *fileNeighbourhood = fopen(argv[2], "r");
	if (fileNeighbourhood == NULL) {
		perror("Error: Can't open file");	
		return 2;
	}

	neighbourhoodADT neighbourhood = newNeighbourhoods();
	if(errno != 0)
		return 1;

	readNeighbourhood(neighbourhood, fileNeighbourhood);
	if(errno != 0)
		return 1;
	
	fclose(fileNeighbourhood);


	FILE *fileTrees = fopen(argv[1], "r");
	if (fileTrees == NULL) {
		perror("Error: Can't open file");
		return 2;
	}

	treeADT tree = newTree();
	if(errno != 0)
		return 1;

	readTrees(tree, neighbourhood, fileTrees);
	if(errno != 0)
		return 1;

	query1and2(neighbourhood);
	if(errno != 0)
		return 1;

	query3(tree);
	if(errno != 0)
		return 1;

	freeNeighbourhood(neighbourhood);
	freeTree(tree);
	fclose(fileTrees);
	return 0;
}
