#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "neighbourhood.h"
#define BLOQUE  5
#define MAX_LENGHT 60

typedef struct neighbourhoodCDT {
	neighbourhoodType* neighbourhoods;
	int index; // indice donde estoy.
	int dim; //Cant total de barrios.
} neighbourhoodCDT;


neighbourhoodADT newNeighbourhoods(){
	errno=0;
	neighbourhoodADT newNeighbourhoodADT = calloc(1, sizeof(neighbourhoodCDT));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	return newNeighbourhoodADT;
}

//algoritmo para insericion de barrios
void insertNeighbourhood(neighbourhoodType* neighbourhoods, neighbourhoodType neighbourhood, int dim){
	errno = 0;
	for(int i = 0; i < dim; i++){
		int c = strcmp(neighbourhoods[i].name,neighbourhood.name);
		if(c > 0){
			neighbourhoods[dim] = neighbourhoods[i];
			neighbourhoods[i] = neighbourhood;
			neighbourhood = neighbourhoods[dim];
		}
		if(c == 0){
			perror("ERROR two neighbourhoods with the same name");
			errno = EPERM;  //no se permiten dos barrios con el mismo nombre (Operation not permitted)
			return;
		}
	}
	neighbourhoods[dim] = neighbourhood;

}

void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood){
	errno = 0;
	if(neighbourhoodsData->dim % BLOQUE == 0){
		neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim + BLOQUE)*sizeof(neighbourhoodType));
		if(errno == ENOMEM){
			perror("Not enough memory");
			errno = -1;
		}
	}

	neighbourhoodType * aux = malloc(sizeof(neighbourhoodType));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return;
	}
	*aux = neighbourhood; 
	neighbourhood.name= malloc(MAX_LENGHT);
	if(errno == ENOMEM){
		perror("Not enough memory");
		return;
	}
	if(aux->name == NULL){
		perror("Invalid name");
		errno = EINVAL;  //el NULL es un argumento invalido (Invalid argument)
		return;

	}
	strcpy(neighbourhood.name,aux->name);
	free(aux);
	neighbourhood.treeCount = 0;
	if(neighbourhoodsData->dim == 0){
		neighbourhoodsData->neighbourhoods[neighbourhoodsData->dim] = neighbourhood;
	}else{
		insertNeighbourhood(neighbourhoodsData->neighbourhoods, neighbourhood,neighbourhoodsData->dim);
	}
	if(errno != 0)
		return;
	neighbourhoodsData->dim++;
	
}

//se fija con una busqueda binaria recursiva si el barrio esta en el vector, agrega 1 arbol al contador de arboles y retorna 1 si esta y -1 si no esta
int recursiveSearchAddTree(neighbourhoodType * neighbourhoods, int dim, char * name){
	if(dim == -1 )
		return -1;
	
	int aux = strcmp(neighbourhoods[dim/2].name, name);
	if(dim == 1 && aux != 0)
		return -1;
	
	if(aux == 0 ){
		 neighbourhoods[dim/2].treeCount = neighbourhoods[dim/2].treeCount  + 1;
		 return 1;
	}
	if(aux > 0)
		return recursiveSearchAddTree(neighbourhoods, dim/2 , name);

	return recursiveSearchAddTree(neighbourhoods + dim/2+1, dim-dim/2-1, name);
}

void addOneTree(neighbourhoodADT neighbourhoodsData, char* name){
	int ans = recursiveSearchAddTree(neighbourhoodsData-> neighbourhoods, neighbourhoodsData->dim, name);
	if(ans == -1){
		perror("no such neighbourhood");
		errno = EPERM;  //no se permite buscar un barrio que no existe (Operation not permitted)
	}
}

void toBegin(neighbourhoodADT neighbourhoodsData){
	neighbourhoodsData->index = 0;
}

int hasNext(neighbourhoodADT neighbourhoodsData){
	return neighbourhoodsData->index < neighbourhoodsData->dim;
}
neighbourhoodType * next(neighbourhoodADT neighbourhoodsData){
	if(!hasNext(neighbourhoodsData)){
		perror("The element not exist");
		errno = EPERM;  //no se permite hacer next a algo que no existe (Operation not permitted)
		return NULL;
	}
	errno = 0;

	neighbourhoodType *next;
	next = calloc(1, sizeof(neighbourhoodType));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	*next = neighbourhoodsData->neighbourhoods[neighbourhoodsData->index];
	next->name = malloc(MAX_LENGHT); 
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	strcpy(next->name, neighbourhoodsData->neighbourhoods[neighbourhoodsData->index].name);
	neighbourhoodsData->index ++;
	return next; 
}


void freeNeighbourhood(neighbourhoodADT neighbourhoodsData){
	for(int i=0;i<neighbourhoodsData->dim;i++){
		free(neighbourhoodsData->neighbourhoods[i].name);
	}
	free(neighbourhoodsData->neighbourhoods);
	free(neighbourhoodsData);

}

