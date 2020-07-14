#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "treeADT.h"

typedef struct node {
	size_t count;
	treeType tree;
	struct node* tail;
} node;

typedef node * PNode;

typedef struct treeCDT {
	PNode first;
	PNode current;
} treeCDT;

treeADT newTree() {
	errno = 0;
	treeADT tree = calloc(1, sizeof(treeCDT));
	if(errno == ENOMEM){
		perror("Not enough memory");
		return NULL;
	}
	return tree;
}

static PNode addTreeRec(PNode first, char * name, float diameter) {
	int c;
	errno = 0;
	if(first == NULL || (c = strcmp(name, first->tree.name)) < 0){ //no existe el arbol que se paso, entonces crea un nodo para guardarlo
		PNode aux = malloc(sizeof(node));
		if(errno == ENOMEM) { 
			perror("Not enough memory");
			return first;
		}
		aux->tree.name = malloc(strlen(name) + 1);
		if(errno == ENOMEM) {
			perror("Not enough memory");
			return first;
		}
		strcpy(aux->tree.name, name);
		aux->tree.diameter = diameter;
		aux->count = 1;
		aux->tail = first;
		return aux;
	}
	if(c == 0) { //ya existe dicho arbol, enonces recalcula el primedio del diametro
		first->tree.diameter = ((first->tree.diameter * first->count) + diameter) / (first->count + 1);
		first->count++;
		return first;
	}
	first->tail = addTreeRec(first->tail, name, diameter);
	return first;
}

void addTree(treeADT tree, char* name, float diameter){
	tree->first = addTreeRec(tree->first, name, diameter);
}


void toBeginTree(treeADT tree) {
	tree->current = tree->first;
}

int hasNextTree(treeADT tree) {
	return tree->current != NULL;
}

treeType * nextTree(treeADT tree) {
	errno = 0;
	if(!hasNextTree(tree)) {
		perror("There are no more elements");
		return NULL;
	}
	treeType * ans = malloc(sizeof(treeType));
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return NULL;
	}
	ans->diameter = tree->current->tree.diameter;
	ans->name = malloc(strlen(tree->current->tree.name) + 1);
	if(errno == ENOMEM) {
		perror("Not enough memory");
		return NULL;
	}
	strcpy(ans->name, tree->current->tree.name);
	tree->current = tree->current->tail;
	return ans;
}

static void freeTreeRec(PNode first) { 
	if(first != NULL){
		free(first->tree.name);
		freeTreeRec(first->tail);
	}
	free(first);
}

void freeTree(treeADT tree) {
	freeTreeRec(tree->first);
	free(tree);
}

