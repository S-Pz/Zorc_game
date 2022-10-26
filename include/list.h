#ifndef _LIST_H
#define _LIST_H

struct povo_t {

	int id;               
	float peso, habilidade, media_de_batalha;  
  	struct povo_t *prev;
  	struct povo_t *next;
};

typedef struct povo_t Povo;

Povo *criar_povo();

void insert(Povo **, int, float, float);
void printList(Povo *);
void freeList(Povo *);
Povo *searchList(Povo **,  int);

#endif