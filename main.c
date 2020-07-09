#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void loadNeighbourhood(neighbourhoodADT neighbourhood, char* nameNeighbourhood, char* population) { //Llama a addNeighbourhood()
	neighbourhoodType newType;
	strcpy(newStructure.name, nameNeighbourhood);
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
			if (!firstLine)
				loadNeighbourhood(neighbourhood, nameNeighbourhood, population); //Carga los datos de la fila
			countComma = 0;
			countString = 0;
			colNumber = 1;
			nameNeighbourhood = NULL;
			population = NULL; 
			firstLine = 0; //Todo esto se podria meter en una funcion newRow()
		}
		if (firstLine)
			continue;
		if (c == ';') {
			colNumber++;
			countString = 0;
		}
		if (colNumber == 1) {
			nameNeighbourhood[countString++] = c;
		}
		if (colNumber == 2) {
			population[countString++] = c;
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

	FILE *archivoArboles = fopen(argv[1], "r");
	if (archivoArboles == NULL) {
		perror("Error: Can't open file");
		return (-1);
	}
	arbolesADT arboles = newArbol();
	leeFilas(arboles, archivoArboles);
	fclose(archivoArboles);

}
