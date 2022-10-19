#ifndef _ZORC_H
#define _ZORC_H

#include<stdio.h>
#include<stdlib.h>

typedef struct povo_t povo; 
typedef struct list List;

FILE *openFile(char *);
void outTable(char *, int *);

int **allocGraph(int );
void freeGraph(int **, int);

void community_insert(FILE *, int, List*);

void zorcPath(FILE *);

void insertEnd(List *, int, int, int);

#endif