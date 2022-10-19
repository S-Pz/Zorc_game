#include "index.h"

struct povo_t {
	int id;               // povo 1,2...i;
	float peso;           
	float habilidade;
	float media_de_batalha; // h1 dividido por w1 , posteriormente é só verificar a melhor média para saber o povo melhor.
  
  povo *next;
};
struct list{

  povo *start,*end;
  int tam;

};

// K = intânicas
// P = Povos
// D = Distânica
// W = Peso da nave
// C = Quantidade de caminhos que existe entre os povos

// H = Habilidades dos soldados

void zorcPath(FILE *file){
  
  List lista;

  int K, P, D, W, C;

  int **graph;

  lista.start=NULL;
  lista.end=NULL;
  lista.tam=0;

  fscanf(file,"%d",&K);

  while(K!=0){

    printf("K= %d\n", K);

    fscanf(file,"%d %d %d %d",&P,&D,&W,&C);
        
    graph = allocGraph(P);

    community_insert(file, P, &lista);

    printList(&lista);

    freeGraph(graph, P);

    K--;
  }    
}

povo *criar_povo(){
  
  povo *u = (povo *) malloc(sizeof(povo));
  
  return u;
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

void community_insert(FILE *arq , int P,List *lista){

  int id; 
  float w, h;

  printf("P= %d\n",P);

  while (P != 0){

    fscanf(arq, "%d %f %f", &id,&w,&h);
    insertEnd(lista,id,w,h);

    P--;
  }
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

void freeGraph(int **matriz, int P){

    for(int i=0; i<P; i++){
        free(matriz[i]);
    }
    free(matriz);
}

// inserir no final da lista
void insertEnd(List *lista, int id, float peso, float habilidade){

  povo *newPovo = criar_povo(); // cria um novo nó

  float media = habilidade/peso;

  printf("%f ", media);

  newPovo->id= id;
  newPovo->peso = peso;
  newPovo->habilidade = habilidade;
  newPovo->media_de_batalha = media;
  newPovo->next = NULL;

  if(lista->start == NULL) { // lista vazia
    lista->start = newPovo;
    lista->end = newPovo;

  }else { // lista não vazia
      lista->end->next = newPovo;
      lista->end = newPovo;
    }
  lista->tam++;
}

// imprimir a lista
void printList(List *lista) {

  povo *start = lista->start;

  printf("Tamanho da lista: %d\n", lista->tam);

  while(start != NULL) {

    printf("Id = %d\n", start->id);
    printf("Peso = %0.1f\n", start->peso);
    printf("Habilidade = %0.1f\n", start->habilidade);
    printf("Média = %0.3f\n", start->media_de_batalha);

    start = start->next;
  }

  printf("\n\n");
}