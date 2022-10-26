#include<stdio.h>
#include<stdlib.h>

struct povo_t {

	int id;               
	float peso, habilidade, media_de_batalha; 
};

int compare (const void * a, const void * b){
  return ( *(int*)b - *(int*)a );
}

void insertPeople(FILE *file, struct povo_t *lista,int sizeLista){

    int id;
    float w,h;

    for(int i=0;i<sizeLista;i++){
       fscanf(file, "%d %f %f", &id,&w,&h);

        lista->id = id;
        lista->peso = w;
        lista->habilidade = h;
        lista->media_de_batalha = h/w;
    }
}
FILE *openFile(char *file){
  
  FILE *arq;
  arq = fopen(file,"r");
  return arq;
}

int main(int argc, char **argv){

    FILE *file;
    int K, P, D, W, C;

    file = openFile(argv[2]);

    fscanf(file,"%d",&K);
    while(K!=0){

        fscanf(file,"%d %d %d %d",&P,&D,&W,&C);

        struct povo_t lista[P];

        insertPeople(file,lista,P);

        qsort(lista,P,sizeof(struct povo_t),compare);

        for (int n=0; n<P; n++)
            printf ("%d %f %f %f",lista[n].id,lista[n].peso,lista[n].habilidade,lista[n].media_de_batalha);

    }

    fclose(file);
}