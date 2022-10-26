#ifndef _ZORC_H
#define _ZORC_H

#include"list.h"
#include"graph.h"

FILE *openFile(char *);
void outTable(char *, int *);

int **allocGraph(int );
void freeGraph(int **, int);

void community_insert(FILE *,Povo **, int);

void zorcPath(FILE *);

void monta_Exercito (Povo **, int **, int, int, int, int *);
int encontraCaminho (Povo **, int **, int, int, int, int *);

#endif
