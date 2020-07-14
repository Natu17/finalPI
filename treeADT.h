#ifndef treeADT_h
#define treeADT_h
#include <stdio.h>

typedef struct treeCDT* treeADT;

typedef struct treeType {
	float diameter;
	char* name;
} treeType;


//Devuelve nuevo arbol
treeADT newTree();

//Agrega si no esta, si esta recalcula el promedio
void addTree(treeADT tree, char* name, float diameter);


void toBeginTree(treeADT tree);

int hasNextTree(treeADT tree);

treeType * nextTree(treeADT tree);

void freeTree(treeADT tree);



#endif