#ifndef neighbourhood_h
#define neighbourhood_h
#include <stdio.h>

typedef struct neighbourhoodCDT* neighbourhoodADT;

typedef struct neighbourhoodType {
	char* name;
	unsigned int treeCount;
	unsigned int population;
} neighbourhoodType;

//crea un nuevo TAD de barrios
neighbourhoodADT newNeighbourhoods();

//Agrega los nombres de barrios y la cantidad de habitantes de los barrios y los inserta alfabeticamente segun el nombre del barrio.
void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood);

//Agrega un arbol en el barrio que corresponde
void addOneTree(neighbourhoodADT neighbourhoodsData, char* name);

//inicializa el indice 
void toBegin(neighbourhoodADT neighbourhoodsData);

//devuelve  1 si hay un siguiente y 0 si no
int hasNext(neighbourhoodADT neighbourhoodsData);


//retorna un puntero a una copia del neighbourhoodType siguiente 
neighbourhoodType * next(neighbourhoodADT neighbourhoodsData);


//libera la memoria.
void freeNeighbourhood(neighbourhoodADT neighbourhoodsData);



#endif