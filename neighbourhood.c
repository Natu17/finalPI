#include <stdio.h>
#include "neighbourhood.h"
#define BLOQUE = 5;
#define MAX_LENGHT = 25;
typedef struct neighbourhoodCDT {
	neighbourhoodType* neighbourhoods;
	int index; // indice donde estoy.
	int dim; //Cant total de barrio
} neighbourhoodCDT;


//crea un nuevo neighbourhoooADT
neighbourhoodADT newNeighbourhoods(){
	newNeighbourhoodADT newNeighbourhoodADT = calloc(1, sizeof(neighbourhoodCDT));
	if (newNeighbourhoodADT == NULL) {
			perror("Not enough memory");
			return NULL;
		}
	return newNeighbourhoodADT;
}

//Agrega nombres de barrios
void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood){
	
	if(neighbourhoods->dim % BLOQUE == 0){
		newNeighbourhoodADT = realloc(newNeighbourhoodADT, (neighbourhoods.dim + BLOQUE)*sizeof(newNeighbourhoodADT));
		if (newNeighbourhoodADT == NULL) {
			perror("Not enough memory");
			return NULL;
		}
	}

	int index = AlphIndex(neighbourhoods, neighbourhood->name);
	if(index == -1){
		perror("ERROR two neighborhoods with the same name");
		return;
	}
	neighbourhoodType aux = neighbourhood 
	neighbourhood->name= malloc(MAX_LENGHT);
	if (neighbourhood->name == NULL) {
			perror("Not enough memory");
			return;
		}
	strcpy(neighbourhood->name,aux->name);
	aux= neighbourhoodsData->neighbourhoods[index];
	neighbourhoodsData->neighbourhoods[index]= neighbourhood;
	for(i=index;i<neighbourhoodsData.dim;i++){
		neighbourhoodsData->neighbourhoods[neighbourhoodsData.dim] = neighbourhoodsData->neighbourhoods[i];
		neighbourhoodsData->neighbourhoods[i] = aux;
		aux = neighbourhoodsData->neighbourhood[neighbourhoodsData->dim];
	}
	dim++;
	
}

//Indica el indice donde debe estar el elemento para que el vector quede ordenado alfabeticamente por nombre del barrio
int AlphIndex(neighbourhoodADT neighbourhoodsData, char * name){
	int i =-1;
	int found = 0

	while(i<= neighbourhoodsData.dim && !found){
		int c = strcmp(neighbourhoodsData->neighbourhoods[i]-> name, name);
		if(c > 0){
			found = 1;
		}
		if(c == 0){
			perror("ERROR two neighborhoods with the same name");
			return -1;
		}
		i++;
	}
	return i;
}

//Agrega un arbol en el barrio que corresponde
void addTree(neighbourhoodADT neighbourhoodsData, char* name){//busqueda binaria
	int index = recursiveBinarySearch(neighbourhoodsData-> neighbourhoods, neighbourhoodsData.dim, name);
	neighbourhoodsData->neighbourhoods[index].treeCount ++;

}
int recursiveIndexSearch(neighbourhoodType * neighbourhoods, int dim, char * name){
	int aux = strcpy(neighbourhoods[ dim/2]->name, name);
	if(aux == 0 )
			return dim/2;
		
	if(aux > 0)
		return recursiveIndexSearch(neighbourhoods, dim/2 -1 , name);

	return recursiveIndexSearch(neighbourhoods+ dim/2, (dim + 1)/2, name);
}

void toBegin(neighbourhoodADT neighbourhoods){
	neighbourhoods.index = 0;
}

int hasNext(neighbourhoodADT neighbourhoodsData){
	if (neighbourhoods.index < neighbourhoods->count)
		return 0;
	return 1;
}
neighbourhoodType * next(neighbourhoodADT neighbourhoodsData){
	if(!hasNext(neighbourhoodsData)){
		perror("The element not exist");
			return NULL;
	}

	neighbourhoodType next = neighbourhoodsData->neighbourhoods[neighbourhoodsData.index];
	next->name = malloc(MAX_LENGHT);
	if (next->name == NULL) {
			perror("Not enough memory");
			return NULL;
		}
	strcpy(next->name, neighbourhoodsData->neighbourhoods[neighbourhoodsData.index]->name);
	neighbourhoodType * nextP = next;
	return nextP; 
}


void freeNeighbourhood(neighbourhoodADT neighbourhoods){
	for(i=0;i<neighbourhoodsData->dim;i++){
		free(neighbourhoodsData->neighbourhoods[i]->name);
		free(neighbourhoodsData->neighbourhoods[i]);
	}
	free(neighbourhoodsData);

}

