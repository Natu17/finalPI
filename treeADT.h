#ifndef treeADT_h
#define treeADT_h
#include <stdio.h>

typedef struct treeCDT;
typedef treeCDT* treeADT;

typedef struct treeType {
	float diameter;
	char* name;
} treeType;


//Devuelve nuevo arbol
treeADT newTree();

//Agrega si no esta, si esta recalcula el promedio
void addTree(treeADT tree, char* name, float diameter);


void toBegin(treeADT tree);

int hasNext(treeADT tree);

treeType next(treeADT tree);

void freeTree(treeADT tree);



#endif