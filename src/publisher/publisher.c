#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "publisher.h"

int main(int argc, char** argv){
  if(argc < 7){
    printf("ERROR: Hay menos de 7 argumentos.\nRevise su entrada\n\n");
    exit(-1);
  }
  
  struct Publisher publicador;
  leerEntrada(argv+1, &publicador);
  mostrarInfoPublicador(&publicador);

  return 0;
}

bool leerEntrada(char** string, struct Publisher* publicador){
  FILE* file;
  for(int i = 0; string[i]; i++)
    for(int j = 0; string[i][j]; j++)
      if(string[i][j] == '-')
        switch(string[i][++j]){
          case 'p': strncpy(publicador->pipeNominal,string[i+1],50);
            break;
          case 'f': strncpy(publicador->rutaArchivo,string[i+1],50);
            break;
          case 't': publicador->tiempoNoticia = atoi(string[i+1]);
            break;
          default:
        }
  
  if(!(file = fopen(publicador->rutaArchivo,"r"))){ perror("ERROR: El archivo tuvo un problema\nPor favor verifique\n\n\n"); exit(-1);}
  
  
  return false;
}

void mostrarInfoPublicador(const struct Publisher* publicador){
  printf("\n\t\tINFORMACION DEL PUBLICADOR\n\n");

  printf("Pipe: %s\n",publicador->pipeNominal);
  printf("File: %s\n",publicador->rutaArchivo);
  printf("Tiempo: %i\n\n", publicador->tiempoNoticia);
}