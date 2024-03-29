#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "neighbourhood.h"
#include "treeADT.h"


typedef struct elemType {
	char* name;
	float number;
} elemType;

typedef struct node {
	elemType elem;
	struct node* tail;
} node;

typedef node * PNode;

typedef struct list {
	PNode first;
	PNode current;
} list;

typedef list * PList;

//crea una nueva lista
PList newlist() {
	PList newList = calloc(1, sizeof(list));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	return newList;
}

//agrega recursivamente y con orden descendiente por "number" 
PNode addListRec(PNode first, char * name, float number) {
	errno = 0;
	if(first == NULL ||   first->elem.number - number < 0){
		PNode aux = malloc(sizeof(node));
		if(errno == ENOMEM) { 
			perror("Not enough memory");
			return first;
		}
		aux->elem.name = malloc(strlen(name) + 1);
		if(errno == ENOMEM) {
			perror("Not enough memory");
			return first;
		}
		strcpy(aux->elem.name, name);
		aux->elem.number = number;
		aux->tail = first;
		return aux;
	}
	first->tail = addListRec(first->tail, name, number);
	return first;
}

//agrega un nodo a la lista
void add(PList list, char* name, float number){
	list->first = addListRec(list->first, name, number);
}

// iguala el nodo current a first
void toBeginList(PList list) {
	list->current = list->first;
}

//retorna 1 si hay un nodo siguiente 0 si no
int hasNextList(PList list) {
	return list->current != NULL;
}

//retorna el siguiente nodo
elemType * nextList(PList list) {
	errno = 0;
	if(!hasNextList(list)) {
		perror("There are no more elements");
		return NULL;
	}
	elemType * ans = malloc(sizeof(elemType));
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return NULL;
	}
	ans->number = list->current->elem.number;
	ans->name = malloc(strlen(list->current->elem.name) + 1);
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return NULL;
	}
	strcpy(ans->name, list->current->elem.name);
	list->current = list->current->tail;
	return ans;
}

//free recursivo de los nodos de la lista
void freeListRec(PNode first) { 
	if(first != NULL) {
		free(first->elem.name);
		freeListRec(first->tail);
	}
	free(first);
}

//free de la lista
void freeList(PList list) {
	freeListRec(list->first);
	free(list);
}


void query1and2(neighbourhoodADT neighbourhood){
	PList listQ1 = newlist();
	PList listQ2 = newlist();
	if(errno != 0)
		return;
	FILE * file1 = fopen ("./query1.csv", "w+");
	FILE * file2 = fopen ("./query2.csv", "w+");
	toBegin(neighbourhood);
	while(hasNext(neighbourhood)) {
		neighbourhoodType * aux = next(neighbourhood);
		if(errno != 0)
			return;
		add(listQ1, aux->name, aux->treeCount);
		if(errno != 0)
			return;
		float value =(float) aux->treeCount/aux->population;
		add(listQ2, aux->name, ((truncf(100 * value))) / 100.0);
		if(errno != 0)
			return;
		free(aux->name);
		free(aux);	
	}
	toBeginList(listQ1);
	fprintf(file1, "%s;%s\n","BARRIO", "ARBOLES");
	while(hasNextList(listQ1)) {
		elemType * elem = nextList(listQ1);
		if(errno != 0)
			return;
		fprintf(file1, "%s;%0.f\n", elem->name, elem->number);
		free(elem->name);
		free(elem);	
	}
	freeList(listQ1);
	toBeginList(listQ2);
	fprintf(file2, "%s;%s\n","BARRIO", "ARBOLES_POR_HABITANTE");
	while(hasNextList(listQ2)) {
		elemType * elem = nextList(listQ2);
		if(errno != 0)
			return;
		fprintf(file2, "%s;%.2f\n", elem->name, elem->number);
		free(elem->name);
		free(elem);	
	}
	freeList(listQ2);
	fclose(file1);
	fclose(file2);
}

void query3(treeADT tree){
	PList listQ3 = newlist();
	if(errno != 0)
		return;
	FILE * file3 = fopen ("./query3.csv", "w+");
	toBeginTree(tree);
	while(hasNextTree(tree)) {
		treeType * treeAux = nextTree(tree);
		if(errno != 0)
			return;
		add(listQ3, treeAux->name, ((truncf(100 * treeAux->diameter))) / 100.0);
		if(errno != 0)
			return;	
		free(treeAux->name);
		free(treeAux);
	}
	toBeginList(listQ3);
	fprintf(file3, "%s;%s\n","NOMBRE_CIENTIFICO", "PROMEDIO_DIAMETRO");
	while(hasNextList(listQ3)) {
		elemType * ans = nextList(listQ3);
		if(errno != 0)
			return;
		fprintf(file3, "%s;%.2f\n", ans->name, ans->number);
		free(ans->name);
		free(ans);
	}
	freeList(listQ3);
	fclose(file3);
}


