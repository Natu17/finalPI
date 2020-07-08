#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "treeADT.h"

typedef struct node {
	size_t cout;
	treeType tree;
	struct node* tail;
} node;

typedef node * PNode;

typedef struct treeCDT {
	PNode first;
	PNode current;
} treeCDT;

treeADT newTree() {
	return calloc(1, sizeof(treeCDT));
}

static PNode addTreeRec(PNode first, char * name, float diameter) {
	int c;
	if(first == NULL || c = (strcmp(name, first->tree->name)) < 0){
		PNode aux = malloc(sizeof(node));
		if(errno == ENOMEN) { //Falta ver como chequear esto

			return ;
		}
		aux->tree->name = malloc(strlen(name) + 1);
		if(errno == ENOMEN) {

			return ;
		}
		strcpy(aux->tree->name, name);
		aux->tree.diameter = diameter;
		aux->count = 1;
		aux->tail = first;
		return aux;
	}
	if(c == 0) {
		first->tree.diameter = ((first->tree.diameter * first->count) + diameter) / first->count;
		first->count++;
		return first;
	}
	first->tail = addTreeRec(first->tail, name, diameter);
	return first;
}

void addTree(treeADT tree, char* name, float diameter){
	tree->first = addTreeRec(tree->first, name, diameter);
}


void toBegin(treeADT tree) {
	tree->current = tree->first;
}

int hasNext(treeADT tree) {
	return list->current != NULL;
}

treeType next(treeADT tree) {
	if(!hasNext)
		Error("There are no more elements");
	treeType ans = tree->current->tree;
	tree->current = tree->current->tail;
}

static void freeTreeRec(PNode first) { //Ver como liberar los treeType
	if(first != NULL)
		freeTreeRec(first->tail);
	free(first);
}

void freeTree(treeADT tree) {
	freeTreeRec(tree->first);
	free(tree);
}
