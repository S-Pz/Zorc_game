#include"list.h"
#include<stdio.h>
#include<stdlib.h>

Povo *criar_povo(){
  
  Povo *u = (Povo *) malloc(sizeof(Povo));
  return u;
}

void insert(Povo **lista, int id, float peso, float habilidade){

  Povo *aux, *newPovo = criar_povo(); // cria um novo nó

  newPovo->id= id;
  newPovo->peso = peso;
  newPovo->habilidade = habilidade;
  newPovo->media_de_batalha = habilidade/peso;
  
  //*lista = ao inicio da lista

  if(*lista == NULL) { // lista vazia?
    newPovo->next = NULL;
    newPovo->prev = NULL;
    *lista = newPovo;

    //lista nao vazia , verifica se a media é a MAIOR e o coloca em primeiro.
  }
  else if(newPovo->media_de_batalha > (*lista)->media_de_batalha){ 
    newPovo->next = *lista;
    (*lista)->prev = newPovo;
    *lista = newPovo;      
  }
  else{ // ORDENA do segundo elemento até o ultimo.
    
    aux = *lista;

    while (aux->next != NULL && (newPovo->media_de_batalha < aux->next->media_de_batalha)){
      aux = aux->next;
    }
    newPovo->next = aux->next;

    if(aux->next){
      aux->next->prev = newPovo;
    }

    newPovo->prev = aux;
    aux->next = newPovo;
  }
 
}

// imprimir a lista
void printList(Povo *lista) {

  while(lista) {

    printf("Id = %d\n", lista->id);
    printf("Peso = %0.1f\n", lista->peso);
    printf("Habilidade = %0.1f\n", lista->habilidade);
    printf("Média = %0.3f\n", lista->media_de_batalha);
    
    lista = lista->next;
    printf("\n\n");
  }
 
}

void freeList(Povo *lista){

  Povo *aux;

  if(lista != NULL){

    while(lista != NULL){
      aux = lista;
      lista = lista->next;
      free(aux);
    }
    free(lista);
  }
}

Povo *searchList(Povo **lista,  int ID){

  Povo *aux, *povo = NULL;
  aux = *lista;

  while(aux && aux->id != ID){
    aux = aux->next;
  }
  if(aux){
    povo = aux;
  }
  return povo;
}