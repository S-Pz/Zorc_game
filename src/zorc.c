#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "index.h"

void zorcPath(FILE *file){
  
  Povo *lista=NULL;
  int *path;
  int K=0, P=0, D=0, W=0, C=0,**graph;
  
  fscanf(file,"%d",&K);

  while(K!=0){

    path = (int *)calloc(200, sizeof(int));

    fscanf(file,"%d %d %d %d",&P,&D,&W,&C);
    
    //Aloco grafo e realizo e o retorno
    graph = allocGraph(P);

    //Realizo a inserção do povo na lista lido do arquivo
    community_insert(file, &lista, P);

    //Realizo a montagem do meu grafo
    graph = montaGrafo(file, graph, C);

    //Realizada a chamada para a montagem do exercíto e o salva no vetro path
    monta_Exercito (&lista, graph, W, D, P, path);
    
    for(int i=0; i<path[99] ;i++){
      printf("%d ",path[i]);
    }
    printf("\n");
   
   //Realizo a liberação do vetor, grafo e da lista.
    free(path);
    freeGraph(graph, P);
    freeList(lista);
    lista = NULL;
    
    K--;
  }
}

FILE *openFile(char *file){
  
  FILE *arq;
  arq = fopen(file,"r");
  return arq;
}

void outTable(char *file, int *cont){

  FILE *saved;
  saved = fopen(file,"a+");

  fprintf(saved,"%d\n", *cont);

  fclose(saved);
}

//Realiza a inserção do povo lido do arquivo na lista
void community_insert(FILE *arq, Povo **lista , int P){

  int id; 
  float w, h;

  while (P != 0){

    fscanf(arq, "%d %f %f", &id,&w,&h);
    insert(lista,id,w,h);
    P--;
  }
}

int encontraCaminho (Povo **lista, int **grafo, int povID, int ultimo_visitado , int P , int *path){
        
  int existe = 0;
  int j = ultimo_visitado;
  int i = povID;

  path[97] = path[97] + 1;
  path[98] = 0; // inicializa como povo 1.

  for( ; path[98] < P ; path[98]++){
    if( path[98] != i && path[98] != j){
      if ((grafo[i][path[98]] > 0  &&  grafo[j][path[98]] > 0) && ((grafo[j][path[98]] + grafo[i][path[98]])  < path[96])){ 
        existe = 1;
        
        path[path[99]] = path[98]+1;
        path[path[99]+1] = 0;
        path[99] = path[99] + 2;
        //path[96] = path[96] - (grafo[i][path[98]] + grafo[j][path[98]]); // distancia percorrida

        return existe;
      }    
    }
  }
  
  if (path[97] >= P ){
    return 0;
  }

  path[98] = 0;
     
  for( ; path[98] < P ; path[98]++){
          
    if( path[98] != i && path[98] != j){
              
      existe = encontraCaminho (lista, grafo, path[98] , ultimo_visitado , P , path);
      path[97] = path[97] - 1;

      if (existe == 1){
        path[97] = 0;
        existe = encontraCaminho (lista, grafo, path[98] , povID, P , path);
        if (existe == 1){
          return existe;
        }            
      }        
    }
  }
  return existe;
}
//ver se o povo é realemte necessário ser criado, talvez so utilizando a lista ja basta

void monta_Exercito (Povo **lista, int **grafo, int W, int D, int P , int *path){

  int hab_total = 0; // habilidade do exercito 
  int quantidade; // quantidade de povos + 1 pq o povo 0 vai ficar no P[1]
  int existe_caminho = 1; // verifica se existe caminho, sempre vai existir para o Primeiro da lista, então começa com 1.
  int ultimo_visitado;
  int pov = 1;
  path[96] = D;
  path[99] = 1;
  
  while(*lista != NULL && W > 0){   // verifica se cabe mais gente na Nave
    quantidade = W/((*lista)->peso);  // verifica a quantidade maxima de um Povo que cabe na nave
    
    if (quantidade > 0){ // verifica se o povo vai ser utilizado
      if(pov>1){
          existe_caminho = 0;
          if( grafo[ultimo_visitado - 1][(*lista)->id - 1] > 0 && grafo[ultimo_visitado - 1][(*lista)->id - 1] < path[96]){   // verifica se existe caminho direto de j (ultimo caminho visitado) até i.
            existe_caminho = 1;
          }
          else{
            path[97] = 0;
            existe_caminho = encontraCaminho (lista, grafo, (*lista)->id  - 1, ultimo_visitado - 1,  P , path); // verifica se existe caminho
          }
      }
      if (existe_caminho == 1){
          
        path[path[99]] = (*lista)->id ;   // guarda na posição impar o ID
        path[path[99]+1] = quantidade; // guarda na posição par a quantidade
        path[99] = path[99] + 2;  // incrementa (de 2 em 2)
        
        W = W - (quantidade * (*lista)->peso);  // atualiza o peso restante da nave
        ultimo_visitado = (*lista)->id ; //  ultimo povo visitado
        path[96] = path[96] - grafo[ultimo_visitado - 1][(*lista)->id - 1]; // distancia percorrida
        hab_total = hab_total + ((*lista)->habilidade * quantidade); // calcula qual a habilidade total da nave até agora
      }
    }
    *lista = (*lista)->next; // proximo povo
    pov++;
  }
  path[0] = hab_total;  // path[0] guarda a habilidade total do exército que será mostrada na saída do código.
}