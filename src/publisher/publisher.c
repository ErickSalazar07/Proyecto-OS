#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "publisher.h"

int main(int argc, char** argv){
  if(argc < 7){ printf("ERROR: Hay menos de 7 argumentos.\nRevise su entrada\n\n"); exit(-1); }

  struct Publisher publicador;

  leerArgumentos(argv+1, &publicador);
  // leerArchivo(&publicador);
  mostrarInfoPublicador(&publicador);

  return 0;
}

void leerArgumentos(char** string, struct Publisher* publicador){
  for(int i = 0; string[i]; i++)
    for(int j = 0; string[i][j]; j++)
      if(string[i][j] == '-')
        switch(string[i][++j]){
          case 'p': strncpy(publicador->pipeNominal,string[i+1],50);
            break;
          case 'f': strncpy(publicador->rutaArchivo,string[i+1],50);
            break;
          case 't': publicador->tiempo = atoi(string[i+1]);
            break;
          default:
        }
}

void leerArchivo(struct Publisher* publicador){
  FILE* archivo = fopen(publicador->rutaArchivo,"r");
  
  char aux;

  if(!archivo){ perror("El archivo tuvo un error.\nPor favor verifique"); exit(-1);}

  for(int i = 0; i < 5; i++){
    publicador->noticias[i].tipo = fgetc(archivo);
    printf("\nTipo[%i]: %c\n\n",i,publicador->noticias[i].tipo);
    if(!noticiaValida(publicador->noticias[i].tipo)){ continue; }
    fseek(archivo,2,SEEK_CUR);
    for(int j = 0; j < 59; j++){
      if((aux = fgetc(archivo)) == '.'){ publicador->noticias[i].contenido[j] = '\0'; break;}
      publicador->noticias[i].contenido[j] = aux;
    }
    while(fgetc(archivo) != '\n');
    publicador->noticias[i].contenido[59] = '\0';
  }
}

bool noticiaValida(char tipo){ return tipo == 'A' || tipo == 'P' || tipo == 'S' || tipo == 'C' || tipo == 'E'; }

void mostrarInfoPublicador(const struct Publisher* publicador){
  printf("\n\t\tINFORMACION DEL PUBLICADOR\n\n");

  printf("Pipe: %s\n",publicador->pipeNominal);
  printf("File: %s\n",publicador->rutaArchivo);
  printf("Tiempo: %i\n\n", publicador->tiempo);
  puts("\n\t\tINFORMACION NOTICIAS\n");

  for(int i = 0; i < 5; i++){
    printf("Noticia[%i]:\n",i);
    printf("       Tipo: %c\n", publicador->noticias[i].tipo);
    printf("  Contenido: %s\n\n", publicador->noticias[i].contenido);
  }
}