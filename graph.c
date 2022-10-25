#include<stdio.h>
#include<stdlib.h>
 
#include"graph.h"

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

// int **montaGrafo(FILE *arq, int **grafo, int C, Povo **lista){
    
//   int px,py,d;
//   Povo *x,*y;
  
//   while (C != 0){

//     fscanf(arq, "%d", &px); 
//     fscanf(arq, "%d", &py); 
//     fscanf(arq, "%d", &d); 

//     grafo[px-1][py-1] = 1;    
//     grafo[py-1][px-1] = 1;
    
//     x = searchList(lista,px);
//     y = searchList(lista,py);

//     //setDistanc(x,y,d);
    
//     C--;
//   }
//   return grafo; // retorna a grafo montado
// }

int searchGraph(int **graph, int from , int to){
  
  if(graph[from][to] == 1 && graph[to][from] == 1){
    return 1;
  }else{
    return 0;
  }
}

// void setDistanc(Povo *x, Povo *y, int dist){

//   x->dist=dist;
//   y->dist=dist;
  
// }

// void BFS(int **graph,Povo **lista, int ini, int *visited){

//   int vert, nVert, cont = 1;
//   int *fila , iniFila=0, fimFila=0;
//   Povo *aux;
  
//   for(int i= 0; i < 5; i++){
//     visited[i] = 0;
//   }
//   nVert = 5;
//   fila = (int*)malloc(nVert *sizeof(int));
//   fimFila++;
//   fila[fimFila] = ini;
//   visited[ini]= cont;

//   while(iniFila!=fimFila){
//     iniFila = (iniFila + 1) % nVert;
//     vert = fila[iniFila];
//     cont++;
//     for(int j =0 ) 
//   }

// }