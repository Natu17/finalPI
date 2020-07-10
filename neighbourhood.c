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
		errno = 0;
		if(neighbourhoodsData->dim % BLOQUE == 0){
			neighbourhoodsData->neighbourhoods = realloc(neighbourhoodsData->neighbourhoods, (neighbourhoodsData->dim + BLOQUE)*sizeof(neighbourhoodType));
			if(errno == ENOMEM){
				perror("Not enough memory");
				return;
	}
		}

	int index = AlphIndex(neighbourhoodsData, neighbourhood.name);
	if(index == -1){
		perror("ERROR two neighbourhoods with the same name");
		return;
	}
	neighbourhoodType * aux = malloc(sizeof(neighbourhoodType));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return;
	}
	*aux = neighbourhood; 
	neighbourhood.name= malloc(strlen(aux->name));
	if(errno == ENOMEM){
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
	
}

//se fija con una busqueda binaria recursiva si el barrio esta en el vector y retorna el indice si esta, y -1 si no esta
int recursiveIndexSearch(neighbourhoodType * neighbourhoods, int dim, char * name){
	if(dim == -1 ){
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
	return neighbourhoodsData->index < neighbourhoodsData->dim
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
	next->name = malloc(strlen(neighbourhoodsData->neighbourhoods[neighbourhoodsData->index].name) + 1); //Es mejor con el Max Lenght?
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	strcpy(next->name, neighbourhoodsData->neighbourhoods[neighbourhoodsData->index].name);
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

/*int main(int argc, char *argv[]){ //funciono.
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
	
}*/


