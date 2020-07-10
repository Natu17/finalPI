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


static PNode addListRec(PNode first, char * name, float number) {
	int c;
	errno = 0;
	if(first == NULL ||   first->elemType.number - number < 0){
		PNode aux = malloc(sizeof(node));
		if(errno == ENOMEM) { 
			perror("Not enough memory");
			return first;
		}
		aux->elemType.name = malloc(strlen(name) + 1);
		if(errno == ENOMEM) {
			perror("Not enough memory");
			return first;
		}
		strcpy(aux->elemType.name, name);
		aux->elemType.number = number;
		aux->tail = first;
		return aux;
	}
	first->tail = addRec(first->tail, name, number);
	return first;
}

void add(list list, char* name, float number){
	list->first = addRec(list->first, name, number);
}

void toBeginList(list list) {
	list->current = list->first;
}

int hasNextList(list list) {
	return list->current != NULL;
}

elemType * nextList(list list) {
	errno = 0;
	if(!hasNext(list)) {
		perror("There are no more elements");
		return NULL;
	}
	elemType * ans = malloc(sizeof(elemType));
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return first;
	}
	ans->number = list->current->list.diameter;
	ans->name = malloc(strlen(list->current->elemType.name) + 1);
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return first;
	}
	strcpy(ans->name, list->current->elemType.name);
	list->current = list->current->tail;
	return ans;
}
