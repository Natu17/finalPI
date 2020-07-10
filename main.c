#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "neighbourhood.h"
#include "treeADT.h"

#define BLOQUE 5
#define MAX_LENGHT 100


void loadNeighbourhood(neighbourhoodADT neighbourhood, const char* nameNeighbourhood, const char* population) { 
	neighbourhoodType newType;
	newType.name = malloc((strlen(nameNeighbourhood) + 1) * sizeof(char));
	strcpy(newType.name, nameNeighbourhood);
	newType.population = atoi(population); 
	// addNeighbourhood(neighbourhood, newType);
	free(newType.name);
} 

void readNeighbourhood(neighbourhoodADT neighbourhood, FILE* fileNeighbourhood) {
	char c;
	char *nameNeighbourhood = NULL;
	char *population = NULL;
	int firstLine = 1, countString = 0, colNumber = 1;
	while((c = fgetc(fileNeighbourhood)) != EOF) {
		if (c == '\n') {
			if (!firstLine) {
				population[countString] = '\0';
				population = realloc(population, (countString + 1) * sizeof(char));
				loadNeighbourhood(neighbourhood, nameNeighbourhood, population); //Carga los datos de la fila
				countString = 0;
				colNumber = 1;
			}
			firstLine = 0;
		}
		if (firstLine) {
			continue;
		}
		if (c == ';') {
			colNumber++;
			nameNeighbourhood[countString] = '\0';
			nameNeighbourhood = realloc(nameNeighbourhood, (countString + 1) * sizeof(char));
			countString = 0;
			continue;
		}
		if (colNumber == 1 && c != '\n') {
			if (countString % BLOQUE == 0) {
				nameNeighbourhood = realloc(nameNeighbourhood, (countString + BLOQUE) * sizeof(char));
			}
			nameNeighbourhood[countString++] = c;

		}
		if (colNumber == 2) {
			if (countString % BLOQUE == 0) {
				population = realloc(population, (countString + BLOQUE) * sizeof(char));
			}
			population[countString++] = c;
		}
	}
	free(nameNeighbourhood);
	free(population);
}

//FALTA CERRAR LOS STRINGS
int* readFirstRow(FILE* fileTrees) {
	char* row = NULL;
	int* index = malloc(3 * sizeof(int));
	int countCol = 1;
	fgets(row, MAX_LENGHT, fileTrees);
	char* token = strtok(row, ";");
	while (token != NULL)
    {
    	if (strcmp(token, "comuna") == 0 || strcmp(token, "NEIGHBOURHOOD_NAME") == 0) {
    		index[0] = countCol;
    	}
    	else if (strcmp(token, "nombre_cientifico") == 0 || strcmp(token, "SPECIES_NAME") == 0) {
    		index[1] = countCol;
    	}
    	else if (strcmp(token, "diametro_altura_pecho") == 0 || strcmp(token, "DIAMETER") == 0) {
    		index[2] = countCol;
    	}
    	else {
    		token = strtok(NULL, ";");
    		countCol++;
    	}
    }
    return index;
}

void loadTrees(treeADT tree, neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* nameSpecies, char* diameter) {
	printf("ALGO\n");
	// addTree(tree, nameSpecies, atof(diameter));                //Son dos funciones distintas
	// addTree(neighbourhood, nameNeighbourhood, nameSpecies);	   //Este es el que sube a neighbourhoodADT
}

void readTrees(treeADT tree, neighbourhoodADT neighbourhood, FILE* fileTrees) {
	char c;
	char *nameNeighbourhood = NULL;
	char *nameSpecies = NULL;
	char *diameter = NULL;
	int count = 1, countString = 0;
	int* index = readFirstRow(fileTrees);
	while ((c = fgetc(fileTrees)) != EOF) {
		if (count == index[0]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					nameNeighbourhood = realloc(nameNeighbourhood, (countString + BLOQUE) * sizeof(char));
				}
				nameNeighbourhood[countString++] = c;
				c = fgetc(fileTrees);
			}	
			nameNeighbourhood = realloc(nameNeighbourhood, countString * sizeof(char));
			countString = 0;
			count++;
		}
		else if (count == index[1]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					nameSpecies = realloc(nameSpecies, (countString + BLOQUE) * sizeof(char));
				}
				nameSpecies[countString++] = c;
				c = fgetc(fileTrees);
			}	
			nameSpecies = realloc(nameSpecies, countString * sizeof(char));
			countString = 0;
			count++;
		}
		else if (count == index[2]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					diameter = realloc(diameter, (countString + BLOQUE) * sizeof(char));
				}
				diameter[countString++] = c;
				c = fgetc(fileTrees);
			}	
			diameter = realloc(diameter, countString * sizeof(char));
			countString = 0;
			count++;
		}
		if (c == '\n') {
			loadTrees(tree, neighbourhood, nameNeighbourhood, nameSpecies, diameter);
			count = 1;
		}
	}
	free(index);
}

int main(int argc, char const *argv[])
{
	FILE *fileNeighbourhood = fopen(argv[2], "r");
	if (fileNeighbourhood == NULL) {
		perror("Error: Can't open file");	
		return (-1);
	}
	neighbourhoodADT neighbourhood = newNeighbourhood();
	readNeighbourhood(neighbourhood, fileNeighbourhood);
	free(neighbourhood);
	fclose(fileNeighbourhood);


	// FILE *fileTrees = fopen(argv[1], "r");
	// if (fileTrees == NULL) {
	// 	perror("Error: Can't open file");
	// 	return (-1);
	// }
	// treeADT tree = newTree();
	// readTrees(tree, neighbourhood, fileTrees);
	// fclose(fileTrees);
}
