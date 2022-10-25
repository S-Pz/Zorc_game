#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "index.h"

void zorcPath(FILE *file){
  
  Povo *lista;
  int *path = malloc(100 * sizeof(int));

  int K, P, D, W, C,**graph;
  
  fscanf(file,"%d",&K);

  while(K!=0){

    fscanf(file,"%d %d %d %d",&P,&D,&W,&C);
    
    graph = allocGraph(P);

    community_insert(file, &lista, P);

    graph = montaGrafo(file, graph, C);
  
    monta_Exercito (&lista, graph,  W,  D, P, path);
    
    for(int i=0;i<path[99]+1;i++){
      printf("%d ",path[i]);
    }
    printf("\n");
    
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

void community_insert(FILE *arq, Povo **lista , int P){

  int id; 
  float w, h;

  while (P != 0){

    fscanf(arq, "%d %f %f", &id,&w,&h);
    insert(lista,id,w,h);

    P--;
  }
}

int encontraCaminho (Povo **lista, int **grafo, int povID, int ultimo_visitado, int D , int P , int *path){
        
    int existe = 0;
    int d = D;
    int j = ultimo_visitado;
    int i = povID;

    path[97] = path[97] + 1;
    
    Povo *auxPovo = criar_povo(); // cria um novo nó auxiliar
    auxPovo = *lista;  // aponta para o inicio da lista
    
    path[98] = 0; // inicializa como povo 1.
  
    for( ; path[98] < P ; path[98]++){
      if( path[98] != i && path[98] != j){
        if ((grafo[i][path[98]] > 0 && grafo[i][path[98]] < d) && ( grafo[j][path[98]] > 0 && grafo[j][path[98]] < d)){ 
          existe = 1;
          
          path[path[99]] = path[98]+1;
          path[path[99]+1] = 0;
          path[99] = path[99] + 2;
          
          return existe;
        }    
      }
    }
    path[98] = 0;

    if (path[97] == P - 1){
      return 0;
    }   
    for( ; path[98] < P ; path[98]++){
            
      if( path[98] != i && path[98] != j){
                
        existe = encontraCaminho (lista, grafo, path[98] , ultimo_visitado, d , P , path);
        path[97] = path[97] - 1;

        if (existe == 1){
          path[97] = 0;
          existe = encontraCaminho (lista, grafo, path[98] , povID, d , P , path);
          if (existe == 1){
            return existe;
          }            
        }        
      }
    }
  free(auxPovo);
  return existe;
}
//ver se o povo é realemte necessário ser criado, talvez so utilizando a lista ja basta

void monta_Exercito (Povo **lista, int **grafo, int W, int D, int P , int *path){

  int hab_total = 0; // habilidade do exercito
  int quantidade; // quantidade de povos + 1 pq o povo 0 vai ficar no P[1]
  int existe_caminho = 1; // verifica se existe caminho, sempre vai existir para o Primeiro da lista, então começa com 1.
  int ultimo_visitado;
  int pov = 1;
  int d = D;
  path[99] = 1;
  
  Povo *auxPovo = criar_povo(); // cria um novo nó auxiliar
  auxPovo = *lista;        // auxPovo pega as informações do primeiro da lista

  while(auxPovo != NULL && W > 0){   // verifica se cabe mais gente na Nave
    quantidade = W/auxPovo->peso;  // verifica a quantidade maxima de um Povo que cabe na nave
    
    if (quantidade > 0){ // verifica se o povo vai ser utilizado
      if(pov>1){
          existe_caminho = 0;
          if ( grafo[ultimo_visitado - 1][auxPovo->id - 1] > 0 && grafo[ultimo_visitado - 1][auxPovo->id - 1] < D){   // verifica se existe caminho direto de j (ultimo caminho visitado) até i.
            existe_caminho = 1;
            
            //##############
            //d = d - lista->distancia;   //verificar qual a distancia percorrida
            //##############
            
          }
          else{
            path[97] = 0;
            existe_caminho = encontraCaminho (lista, grafo, auxPovo->id - 1, ultimo_visitado - 1, d , P , path); // verifica se existe caminho
          }
      }
      if (existe_caminho == 1){
          
        path[path[99]] = auxPovo->id;    // guarda na posição impar o ID
        path[path[99]+1] = quantidade; // guarda na posição par a quantidade
        path[99] = path[99] + 2;  // incrementa (de 2 em 2)
        
        W = W - (quantidade * auxPovo->peso);  // atualiza o peso restante da nave
        ultimo_visitado = auxPovo->id; //  ultimo povo visitado
        hab_total = hab_total + (auxPovo->habilidade * quantidade); // calcula qual a habilidade total da nave até agora
      }
    }
    auxPovo = auxPovo->next; // proximo povo
    pov++;
  }
  path[0] = hab_total;
}