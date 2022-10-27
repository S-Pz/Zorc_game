#include"list.h"
#include<stdio.h>
#include<stdlib.h>
/*


*/


//Função para alocar uma célula povo na lista
Povo *criar_povo(){
  
  Povo *u = (Povo *) malloc(sizeof(Povo));
  return u;
}

//Função para inserir um novo povo na lista criada 
void insert(Povo **lista, int id, float peso, float habilidade){//Recebo como parâmetro a minha lista o ID do povo, peso e habilidade.

  Povo *aux, *newPovo = criar_povo(); // cria uma nova célula povo

  //Pega os valores e atribui a cada individuo
  newPovo->id= id;
  newPovo->peso = peso;
  newPovo->habilidade = habilidade;
  newPovo->media_de_batalha = habilidade/peso;
  
  //Verifico se minha lista está vazia analisando a primeira célula da minha lista
  if(*lista == NULL){ // Caso a lista eteja vaiza insiro no início
    newPovo->next = NULL;
    newPovo->prev = NULL;
    *lista = newPovo;

    
  }else if(newPovo->media_de_batalha > (*lista)->media_de_batalha){ //lista nao vazia , verifica se a media é a MAIOR e o coloca em primeiro.
    newPovo->next = *lista;
    (*lista)->prev = newPovo;
    *lista = newPovo;      
  }
  else{ // A partir desse else, realizo a verificação e comparação dos demais povos, e os ordeno.
    
    aux = *lista;

    //aux recebe o início da lista e navega até o final e vai comparando e realizando a ordenação na lista
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

//Função que realiza o free na lista recebendo como parâmetro a lista
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

//Função para buscar um povo específico na lista
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