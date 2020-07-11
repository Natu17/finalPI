#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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
	errno=0;
	neighbourhoodADT newNeighbourhoodADT = calloc(1, sizeof(neighbourhoodCDT));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	return newNeighbourhoodADT;
}

//Indica el indice donde debe estar el elemento para que el vector quede ordenado descendentemente por cantiad de arboles y luego alfabeticamente por nombre del barrio
/*int AlphIndex(neighbourhoodADT neighbourhoodsData, char * name){
	int i =0;
	
	while(i<neighbourhoodsData->dim && !found){
		
		i++;
	}
	return i;
}
*/
void insertNeighbourhood(neighbourhoodType* neighbourhoods, neighbourhoodType neighbourhood, int dim){
	for(int i = 0; i < dim; i++){
		int c = strcmp(neighbourhoods[i].name,neighbourhood.name);
		if(c > 0){
			neighbourhoods[dim] = neighbourhoods[i];
			neighbourhoods[i] = neighbourhood;
			neighbourhood = neighbourhoods[dim];
		}
		if(c == 0){
			perror("ERROR two neighbourhoods with the same name");
			return;
		}
	}
	neighbourhoods[dim] = neighbourhood;

}

//Agrega nombres de barrios
void addNeighbourhood(neighbourhoodADT neighbourhoodsData, neighbourhoodType neighbourhood){
	errno = 0;
	if(neighbourhoodsData->dim % BLOQUE == 0){
		neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim + BLOQUE)*sizeof(neighbourhoodType));
		if(errno == ENOMEM){
			perror("Not enough memory");
			return;
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
		return;

	}
	strcpy(neighbourhood.name,aux->name);
	free(aux);
	if(neighbourhoodsData->dim == 0){
		neighbourhoodsData->neighbourhoods[neighbourhoodsData->dim] = neighbourhood;
	}else{
		insertNeighbourhood(neighbourhoodsData->neighbourhoods, neighbourhood,neighbourhoodsData->dim);
	}
	neighbourhoodsData->dim++;
	
}

//se fija con una busqueda binaria recursiva si el barrio esta en el vector y retorna el indice si esta, y -1 si no esta
int recursiveIndexSearch(neighbourhoodType * neighbourhoods, int dim, char * name){
	if(dim == -1 )
		return -1;
	
	int aux = strcmp(neighbourhoods[dim/2].name, name);
	if(dim == 1 && aux != 0)
		return -1;
	
	if(aux == 0 )
			return dim/2;
		
	if(aux > 0)
		return recursiveIndexSearch(neighbourhoods, dim/2 , name);

	return recursiveIndexSearch(neighbourhoods + dim/2+1, dim-dim/2-1, name);
}

//Agrega un arbol en el barrio que corresponde
void addOneTree(neighbourhoodADT neighbourhoodsData, char* name){
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
	return neighbourhoodsData->index < neighbourhoodsData->dim;
}
neighbourhoodType * next(neighbourhoodADT neighbourhoodsData){
	if(!hasNext(neighbourhoodsData)){
		perror("The element not exist");
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
	next->name = malloc(MAX_LENGHT); //Es mejor con el Max Lenght?
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	strcpy(next->name, neighbourhoodsData->neighbourhoods[neighbourhoodsData->index].name);
	neighbourhoodsData->index ++;
	//printf("%d\n",neighbourhoodsData->index);
	return next; 
}


void freeNeighbourhood(neighbourhoodADT neighbourhoodsData){
	//neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim)*sizeof(neighbourhoodType));
	for(int i=0;i<neighbourhoodsData->dim;i++){
		free(neighbourhoodsData->neighbourhoods[i].name);
	}
	free(neighbourhoodsData->neighbourhoods);
	free(neighbourhoodsData);

}

/*
int main(int argc, char *argv[]){ //funciono.
	neighbourhoodADT nADT = newNeighbourhoods();
	neighbourhoodType ne = {"h", 12, 123456};
	neighbourhoodType tyu = {"hola", 16, 123456};
	addNeighbourhood(nADT, ne);
	addNeighbourhood(nADT,tyu);
	addOneTree(nADT, "h");
	addOneTree(nADT, "hola");
	toBegin(nADT);
	neighbourhoodType * new = next(nADT);
	free(new->name);
	free(new);
	freeNeighbourhood(nADT);
	
}

*/
