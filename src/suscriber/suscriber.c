#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suscriber.h"

int main(int argc, char** argv){
    if(argc != 3) perror("\n\nLa canitidad de parametros no coincide.\nRevise\n\a"),exit(EXIT_FAILURE);
    
    struct Suscriber suscriptor;
    suscriptor.topicos[0] = 'A';
    mostrarInfoSuscriptor(&suscriptor);

    return 0;
}

void leerArgumentos(char** argv, struct Suscriber* suscriptor){
  for(size_t i = 0; argv[i]; i++)
    for(size_t j = 0; argv[i][j]; j++)
      if(argv[i][j] == '-')
        switch(argv[i][++j]){
          case 's': strncpy(suscriptor->pipeNominal, argv[i+1],50);
            break;
          default: perror("\n\nLa bandera, no se identifica\n\a"),exit(-1);
        }
}

void mostrarInfoSuscriptor(const struct Suscriber* suscriptor){
  printf("\n\t\t\tINFORMACION DEL SUSCRIPTOR\n\n");
  printf("Pipe: %s\n\n",suscriptor->pipeNominal);
}