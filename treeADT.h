#ifndef treeADT_h
#define treeADT_h
#include <stdio.h>

typedef struct treeCDT* treeADT;

typedef struct treeType {
	float diameter; //es el promedio del diametro de la especie
	char* name; //nombre de la especie de arbol.
} treeType;


//Devuelve un nuevo tree vacio.
treeADT newTree();

//Si ya existe el arbol pasado, recalcula el promedio. Sino agrega un nuevo arbol.
void addTree(treeADT tree, char* name, float diameter);

//Inicializa el iterador para poder recorrer el tree.
void toBeginTree(treeADT tree);

//Retorna 1 si hay un elemento siguiente. Sino retorna 1.
int hasNextTree(treeADT tree);

//Retorna un puntero a una copia de un elemento tipo treeType y mueve el iterador. 
treeType * nextTree(treeADT tree);

//libera toda la memoria reservada.
void freeTree(treeADT tree);



#endif