#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "neighbourhood.h"
#include "treeADT.h"
#include "queries.h"

#define BLOQUE 5
#define MAX_LENGHT 1000


void loadNeighbourhood(neighbourhoodADT neighbourhood, const char* nameNeighbourhood, const char* population) { 
	neighbourhoodType newType;
	newType.name = malloc((strlen(nameNeighbourhood) + 1) * sizeof(char));
	strcpy(newType.name, nameNeighbourhood);
	newType.population = atoi(population); 
	addNeighbourhood(neighbourhood, newType);
	free(newType.name);
} 


void readNeighbourhood(neighbourhoodADT neighbourhood, FILE* fileNeighbourhood) {
	char c;
	char *nameNeighbourhood = NULL;
	char *population = NULL;
	int firstLine = 1, countString = 0, colNumber = 1;
	while((c = fgetc(fileNeighbourhood)) != EOF) {
		if (c == '\n') {
			firstLine = 0;
			continue;
		}
		if (firstLine) {
			continue;
		}
		if (colNumber == 1) {
			while (c != ';') {
				if (countString % BLOQUE == 0) {
					nameNeighbourhood = realloc(nameNeighbourhood, (countString + 1 + BLOQUE) * sizeof(char));
				}
				nameNeighbourhood[countString++] = c;
				c = fgetc(fileNeighbourhood);
			}
			nameNeighbourhood[countString] = '\0';
			nameNeighbourhood = realloc(nameNeighbourhood, (countString + 1) * sizeof(char));
			countString = 0;
			colNumber++;
			c = fgetc(fileNeighbourhood);
		}
		if (colNumber == 2) {
			while (c != '\n') {
				if (countString % BLOQUE == 0) {
					population = realloc(population, (countString + 1 + BLOQUE) * sizeof(char));
				}
				population[countString++] = c;
				c = fgetc(fileNeighbourhood);
			}
			population[countString] = '\0';
			population = realloc(population, (countString + 1) * sizeof(char));
			countString = 0;
			colNumber = 1;

			loadNeighbourhood(neighbourhood, nameNeighbourhood, population);
		}
	}
	free(nameNeighbourhood);
	free(population);
}

//Devuelve un puntero a int con los indices de las columnas que sirven
int* readFirstRow(FILE* fileTrees) {
	int countCol = 1;
	char row[1000];
	int* index;
	index = malloc(3 * sizeof(int));
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

void loadTrees(treeADT tree, neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* nameSpecies, char* diameter) {
	addTree(tree, nameSpecies, atof(diameter));                 
	addOneTree(neighbourhood, nameNeighbourhood);
}

void readTrees(treeADT tree, neighbourhoodADT neighbourhood, FILE* fileTrees) {
	char c;
	char *nameNeighbourhood = NULL;
	char *nameSpecies = NULL;
	char *diameter = NULL;
	int count = 1, countString = 0;
	int* index = readFirstRow(fileTrees);
	while ((c = fgetc(fileTrees)) != EOF) {
		if (c == ';') {
			count++;
			continue;
		}
		if (count == index[0]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					nameNeighbourhood = realloc(nameNeighbourhood, (countString + 1 + BLOQUE) * sizeof(char));
				}
				nameNeighbourhood[countString++] = c;
				c = fgetc(fileTrees);
			}	
			nameNeighbourhood[countString] = '\0';
			nameNeighbourhood = realloc(nameNeighbourhood, (countString + 1) * sizeof(char));
			countString = 0;
			count++;
		}
		else if (count == index[1]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					nameSpecies = realloc(nameSpecies, ((countString + 1) + BLOQUE) * sizeof(char));
				}
				nameSpecies[countString++] = c;
				c = fgetc(fileTrees);
			}
			nameSpecies[countString] = '\0';
			nameSpecies = realloc(nameSpecies, (countString + 1) * sizeof(char));
			countString = 0;
			count++;
		}
		else if (count == index[2]) {
			while (c != ';' && c != '\n') {
				if (countString % BLOQUE == 0) {
					diameter = realloc(diameter, ((countString + 1) + BLOQUE) * sizeof(char));
				}
				diameter[countString++] = c;
				c = fgetc(fileTrees);
			}
			diameter[countString] = '\0';
			diameter = realloc(diameter, (countString + 1) * sizeof(char));
			countString = 0;
			count++;
		}
		if (c == '\n') {
			loadTrees(tree, neighbourhood, nameNeighbourhood, nameSpecies, diameter);
			count = 1;
		}
	}
	free(nameNeighbourhood);
	free(nameSpecies);
	free(diameter);
	free(index);

}

int main(int argc, char const *argv[])
{
	FILE *fileNeighbourhood = fopen(argv[2], "r");
	if (fileNeighbourhood == NULL) {
		perror("Error: Can't open file");	
		return (-1);
	}
	neighbourhoodADT neighbourhood = newNeighbourhoods();
	readNeighbourhood(neighbourhood, fileNeighbourhood);
	fclose(fileNeighbourhood);

	FILE *fileTrees = fopen(argv[1], "r");
	if (fileTrees == NULL) {
		perror("Error: Can't open file");
		return (-1);
	}
	treeADT tree = newTree();
	readTrees(tree, neighbourhood, fileTrees);

	query1(neighbourhood);

	query3(tree);

	freeNeighbourhood(neighbourhood);
	freeTree(tree);
	fclose(fileTrees);
}
