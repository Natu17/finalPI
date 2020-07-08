#include <stdio.h>
#include "neighbourhood.h"
#define BLOQUE = 5;
#define MAX_LENGHT = 25;
typedef struct neighbourhoodCDT {
	neighbourhoodType* neighbourhoods;
	int index; // indice donde estoy.
	int dim; //Cant de elementos del vector
	int count; //Cant total de barrio
} neighbourhoodCDT;

//crea un nuevo neighbourhoooADT
neighbourhoodADT newNeighbourhoods(){
	newNeighbourhoodADT newNeighbourhoodADT = calloc(1, sizeof(neighbourhoodCDT));
	return newNeighbourhoodADT;
}

//Agrega nombres de barrios
void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood){
	if(errno == ENOMEN){
		//mensaje de error	
	}
	if(neighbourhoods->dim == neighbourhoods->count){
		newNeighbourhoodADT = realloc(newNeighbourhoodADT, (BLOQUE+neighbourhoods->dim)*sizeof(newNeighbourhoodADT));
		neighbourhoods->dim += BLOQUE;
	}

	int i = AlphIndex(neighbourhoods, neighbourhood->name);
	//falta agregarlo al vector y correr los que estan atras.
	
}

//Indica el indice donde debe estar el elemento para que el vector quede ordenado alfabeticamente por nombre del barrio
int AlphIndex(neighbourhoodADT neighbourhoods, char * name){
	int i =-1;
	int found = 0

	while(i<=neighbourhoods->count && !found){
		int c = newNeighbourhoods[i]-> name.strcmp(name);
		if(c > 0){
			found = 1;
		}
		if(c == 0){
			//mensaje de error
		}
		i++;
	}
	return i;
}

//Agrega un arbol en el barrio que corresponde
void addTree(neighbourhoodADT neighbourhood, char* name){//busqueda binaria

}

void toBegin(neighbourhoodADT neighbourhoods){
	neighbourhoods->index = 0;
}

int hasNext(neighbourhoodADT neighbourhoods){
	if (neighbourhoods->index < neighbourhoods->count)
		return 0;
	return 1;
}


void freeNeighbourhood(neighbourhoodADT neighbourhoods){
	for(i=0;i<neighbourhoods->dim;i++){
		free(neighbourhoods[i]->name);
		free(neighbourhoods[i]);
	}
	free(neighbourhoods);

}

