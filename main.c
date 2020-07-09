#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOQUE 5
#define MAX_LENGHT 100

void loadNeighbourhood(neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* population) { //Llama a addNeighbourhood()
	neighbourhoodType newType;
	newType.name = malloc((strlen(nameNeighbourhood) + 1) * sizeof(char));
	strcpy(newType.name, nameNeighbourhood);
	newType.population = atoi(population);
	addNeighbourhood(neighbourhood, newType);
} 

void readNeighbourhood(neighbourhoodADT neighbourhood, FILE* fileNeighbourhood) {
	char c;
	char *nameNeighbourhood = NULL;
	char *population = NULL;
	int firstLine = 1, countComma = 0, countString = 0, colNumber = 1;
	while((c = fgetc(fileNeighbourhood)) != EOF) {
		if (c == '\n') {
			if (!firstLine) {
				population = realloc(population, countString * sizeof(char));
				loadNeighbourhood(neighbourhood, nameNeighbourhood, population); //Carga los datos de la fila
				countComma = 0;
				countString = 0;
				colNumber = 1;
			}
			firstLine = 0; //Todo esto se podria meter en una funcion newRow()
		}
		if (firstLine)
			continue;
		if (c == ';') {
			colNumber++;
			nameNeighbourhood = realloc(nameNeighbourhood, countString * sizeof(char));
			countString = 0;
		}
		if (colNumber == 1) {
			if (countString % BLOQUE == 0) {
				nameNeighbourhood = realloc(nameNeighbourhood, (countString+BLOQUE) * sizeof(char));
			}
			nameNeighbourhood[countString++] = c;
		}
		if (colNumber == 2) {
			if (countString % BLOQUE == 0) {
				population = realloc(population, (countString+BLOQUE) * sizeof(char));
			}
			population[countString++] = c;
		}
	}
}

int* readFirstRow(FILE* fileTrees) {
	char* row;
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
        token = strtok(NULL, ";");
        countCol++;
    }
    return index;
}

void loadTrees(treeADT tree, neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* nameSpecies, char* diameter) {
	addTree(tree, nameSpecies, atof(diameter));                //Son dos funciones distintas
	addTree(neighbourhood, nameNeighbourhood, nameSpecies);	   //Este es el que sube a neighbourhoodADT
}

void readTrees(treeADT tree, neighbourhoodADT neighbourhood, FILE* fileTrees) {
	char c;
	char *nameNeighbourhood = NULL;
	char *nameSpecies = NULL;
	char *diameter = NULL;
	int count = 1, countString = 0;
	int* colIndex = readFirstRow(fileTrees);
	while ((c = fgetc(fileTrees)) != EOF) {
		if (c == '\n') {
			loadTrees(tree, neighbourhood, nameNeighbourhood, nameSpecies, diameter);
			count = 1;
		}
		if (c == ';') {
			countString = 0;
			count++;
		} 
		//Faltaria hacer un while interno de cada if para cerrar los strings (tomar en cuenta el caso '\n')
		if (count == index[0]) {
			if (countString % BLOQUE == 0) {
				nameNeighbourhood = realloc(nameNeighbourhood, (countString + BLOQUE) * sizeof(char));
			}
			nameNeighbourhood[countString++] = c; 
		}
		else if (count == index[1]) {
			if (countString % BLOQUE == 0) {
				nameSpecies = realloc(nameSpecies, (countString + BLOQUE) * sizeof(char));
			}
			nameSpecies[countString++] = c; 
		}
		else if (count == index[2]) {
			if (countString % BLOQUE == 0) {
				diameter = realloc(diameter, (countString + BLOQUE) * sizeof(char));
			}
			diameter[countString++] = c; 
		}
	}
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
	fclose(fileNeighbourhood);

	FILE *fileTrees = fopen(argv[1], "r");
	if (fileTrees == NULL) {
		perror("Error: Can't open file");
		return (-1);
	}
	treeADT tree = newTree();
	readTrees(tree, neighbourhood, fileTrees);
	fclose(fileTrees);
}
