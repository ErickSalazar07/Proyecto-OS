#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

int main(int argc, char** argv){
  if(argc != 7) perror("\n\nLa cantidad de parametros no es correcta.\nRevise\a\n"),exit(EXIT_FAILURE);

  struct System sistema;
  leerArgumentos(argv+1,&sistema);
  mostrarInfoSistema(&sistema);

  return 0;
}

void leerArgumentos(char** argv, struct System* sistema){
  for(size_t i = 0; argv[i]; i++)
    for(size_t j = 0; argv[i][j]; j++)
      if(argv[i][j] == '-')
        switch(argv[i][++j]){
          case 'p': strncpy(sistema->pipeNomP, argv[i+1], 50);
            break;
          case 's': strncpy(sistema->pipeNomS, argv[i+1], 50);
            break;
          case 't': sistema->timeF = atof(argv[i+1]);
            break;
          default: perror("\n\nLa bandera ingresada no se indentifica.\nRevise su entrada\n\a"),exit(-1);
        }
}

void mostrarInfoSistema(const struct System* sistema){
    printf("\n\nINFORMACION DEL SISTEMA\n\n");
    printf("Pipe Pulbicador: %s\n",sistema->pipeNomS);
    printf("Pipe Suscriptor: %s\n",sistema->pipeNomP);
    printf("Time F: %lf\n\n",sistema->timeF);
}