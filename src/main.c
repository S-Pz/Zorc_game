#include"index.h"

//input type = ./tp2 -i entrada.txt

int main(int argc, char **argv){

    FILE *file;
    file = openFile(argv[2]);

    zorcPath(file);
    return 0;
}