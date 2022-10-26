#ifndef _GRAPH_H
#define _GRAPH_H

#include<stdbool.h>   
#include"index.h"
#include"list.h"

int **allocGraph(int );
int **montaGrafo(FILE *, int **, int);

void printGraph(int  **,int);
void freeGraph(int **, int);

int searchGraph(int **, int , int);

#endif