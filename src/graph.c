#include<stdio.h>
#include<stdlib.h>
 
#include"graph.h"

//Função ao qual realiza a montagem do grafo dinâmicamente
int **montaGrafo(FILE *arq, int **grafo, int C){
    
  int px,py,d;
 
  while (C != 0){

    fscanf(arq, "%d", &px); 
    fscanf(arq, "%d", &py); 
    fscanf(arq, "%d", &d); 

    grafo[px-1][py-1]= d;    
    grafo[py-1][px-1]= d;
  
    C--;
  }
  return grafo; // retorna a grafo montado
}

//Função que realiza a limpeza no grafo
void freeGraph(int **grafo, int P){

  for(int i=0; i<P; i++){
    free(grafo[i]);
  }
  free(grafo);
}

int **allocGraph(int P){

  int **x;

  //Aloca as colunas 
  x = malloc(P * sizeof * x);

  //Aloca as linhas 
  for (int i=0; i<P; i++){

    x[i] = malloc(P * sizeof * x[i]);
  }

  return x;
}

//Função para limpar o grafo
void printGraph(int  **graph,int P){
  
  for(int i= 0; i<P;i++){
    for(int j=0;j<P;j++){
      printf("%d",graph[i][j]);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n\n");
}

//Função que verifica se um detreminado povo possui caminho até o outro
int searchGraph(int **graph, int from , int to){
  
  if(graph[from][to] == 1 && graph[to][from] == 1){
    return 1;
  }else{
    return 0;
  }
}