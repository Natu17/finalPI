#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void add(PList list, char* name, float number){
	list->first = addListRec(list->first, name, number);
}

void toBeginList(PList list) {
	list->current = list->first;
}

int hasNextList(PList list) {
	return list->current != NULL;
}

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

void freeListRec(PNode first) { 
	if(first != NULL) {
		free(first->elem.name);
		freeListRec(first->tail);
	}
	free(first);
}

void freeList(PList list) {
	freeListRec(list->first);
	free(list);
}

void query3(treeADT tree){
	PList listQ3 = calloc(1, sizeof(list));
	FILE * file;
	file = fopen ("./query3.csv", "w+");
	toBeginTree(tree);
	while(hasNextTree(tree)) {
		treeType * treeAux = nextTree(tree);
		add(listQ3, treeAux->name, treeAux->diameter);	
		free(treeAux->name);
		free(treeAux);
	}
	toBeginList(listQ3);
	while(hasNextList(listQ3)) {
		elemType * ans = nextList(listQ3);
		fprintf(file, "%s;%.2f\n", ans->name, ans->number);
		free(ans->name);
		free(ans);
	}
	freeList(listQ3);
	fclose(file);
}

