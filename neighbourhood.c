#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
#include "neighbourhood.h"
#define BLOQUE  5
#define MAX_LENGHT 25

typedef struct neighbourhoodCDT {
	neighbourhoodType* neighbourhoods;
	int index; // indice donde estoy.
	int dim; //Cant total de barrio
} neighbourhoodCDT;


//crea un nuevo neighbourhoooADT
neighbourhoodADT newNeighbourhoods(){
	neighbourhoodADT newNeighbourhoodADT = calloc(1, sizeof(neighbourhoodCDT));
	return newNeighbourhoodADT;
}

//Indica el indice donde debe estar el elemento para que el vector quede ordenado descendentemente por cantiad de arboles y luego alfabeticamente por nombre del barrio
int AlphIndex(neighbourhoodADT neighbourhoodsData, char * name){
	int i =0;
	int found = 0;
	int c;
	while(i<neighbourhoodsData->dim && !found){

		c = strcmp(neighbourhoodsData->neighbourhoods[i].name, name);
		if(c > 0){
			found = 1;
			return i;
		}
		if(c == 0){
			perror("ERROR two neighbourhoods with the same name");
			return -1;
		}
		i++;
	}
	return i;
}

//Agrega nombres de barrios
void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood){
		
		if(neighbourhoodsData->dim % BLOQUE == 0){
			neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim + BLOQUE)*sizeof(neighbourhoodType));
			if (neighbourhoodsData->neighbourhoods == NULL) {
				perror("Not enough memory");
				return;
			}
		}

	int index = AlphIndex(neighbourhoodsData, neighbourhood.name);
	printf("%s\n", "SALIII!!!!!!!!!!!!!!!!!");
	if(index == -1){
		perror("ERROR two neighbourhoods with the same name");
		return;
	}
	neighbourhoodType * aux = malloc(sizeof(neighbourhoodType));
	*aux = neighbourhood; 
	neighbourhood.name= malloc(MAX_LENGHT);
	if (neighbourhood.name == NULL) {
			perror("Not enough memory");
			return;
		}
	strcpy(neighbourhood.name,aux->name);
	*aux= neighbourhoodsData->neighbourhoods[index];
	neighbourhoodsData->neighbourhoods[index]= neighbourhood;
	for(int i=index;i<neighbourhoodsData->dim;i++){
		neighbourhoodsData->neighbourhoods[neighbourhoodsData->dim] = neighbourhoodsData->neighbourhoods[i];
		neighbourhoodsData->neighbourhoods[i] = *aux;
		*aux = neighbourhoodsData->neighbourhoods[neighbourhoodsData->dim];
	}
	free(aux);
	neighbourhoodsData->dim++;
	printf("%s\n", "lo agrego");
	
}

int recursiveIndexSearch(neighbourhoodType * neighbourhoods, int dim, char * name){
	printf("%d\n", dim);
	if(dim == -1 ){
		printf("%s\n", name);
		return -1;
	}
	int aux = strcmp(neighbourhoods[dim/2].name, name);
	if(dim == 1 && aux != 0)
		return -1;

	
	if(aux == 0 )
			return dim/2;
		
	if(aux > 0)
		return recursiveIndexSearch(neighbourhoods, dim/2 -1 , name);

	return recursiveIndexSearch(neighbourhoods + dim/2, (dim + 1)/2, name);
}

//Agrega un arbol en el barrio que corresponde
void addTree(neighbourhoodADT neighbourhoodsData, char* name){//busqueda binaria
	int index = recursiveIndexSearch(neighbourhoodsData-> neighbourhoods, neighbourhoodsData->dim, name);
	if(index == -1){
		perror("Not such neighbourhood");
		return;
	}
	neighbourhoodsData->neighbourhoods[index].treeCount ++;


}


void toBegin(neighbourhoodADT neighbourhoodsData){
	neighbourhoodsData->index = 0;
}

int hasNext(neighbourhoodADT neighbourhoodsData){
	if (neighbourhoodsData->index < neighbourhoodsData->dim)
		return 1;
	return 0;
}
neighbourhoodType * next(neighbourhoodADT neighbourhoodsData){
	if(!hasNext(neighbourhoodsData)){
		perror("The element not exist");
			return NULL;
	}

	neighbourhoodType *next;
	next = calloc(1, sizeof(neighbourhoodType));
	if (next == NULL) {
			perror("Not enough memory");
			return NULL;
		}
	*next = neighbourhoodsData->neighbourhoods[neighbourhoodsData->index];
	next->name = malloc(MAX_LENGHT);
	if (next->name == NULL) {
			perror("Not enough memory");
			return NULL;
		}
	strcpy(next->name, neighbourhoodsData->neighbourhoods[neighbourhoodsData->index].name);
	return next; 
}


void freeNeighbourhood(neighbourhoodADT neighbourhoodsData){
	//neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim)*sizeof(neighbourhoodType));
	//printf("%s\n", "hi");
	for(int i=0;i<neighbourhoodsData->dim;i++){
		free(neighbourhoodsData->neighbourhoods[i].name);
	}
	free(neighbourhoodsData->neighbourhoods);
	free(neighbourhoodsData);

}

int main(int argc, char *argv[]){
	neighbourhoodADT nADT = newNeighbourhoods();
	neighbourhoodType ne = {"h", 12, 123456};
	neighbourhoodType tyu = {"hola", 16, 123456};
	addNeighbourhood(nADT, ne);
	addNeighbourhood(nADT,tyu);
	addTree(nADT, "h");
	addTree(nADT, "hola");
	toBegin(nADT);
	neighbourhoodType * new = next(nADT);
	free(new->name);
	free(new);
	freeNeighbourhood(nADT);
	
}


