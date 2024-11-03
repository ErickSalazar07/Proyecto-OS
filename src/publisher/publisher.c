#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "publisher.h"

void endLineFile(FILE**);

int main(int argc, char** argv){
  if(argc != 7) perror("ERROR: Argumentos, debe haber exactamente 6, contando los flags.\nRevise su entrada\n\n"), exit(EXIT_FAILURE);

  struct Publisher publicador;
  leerArgumentos(argv+1, &publicador);
  leerArchivo(&publicador);
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
          default: perror("\n\nLa bandera ingresada, no se reconoce.\nVerifique su entrada\a\n"),exit(-1);
        }
}

void leerArchivo(struct Publisher* publicador){
  FILE* archivo = fopen(publicador->rutaArchivo,"r");
  char aux;

  if(!archivo) perror("El archivo tuvo un error.\nPor favor verifique"),exit(-2);

  publicador->numNoticias = 0;
  for(int i = 0; i < 5; i++){
    
    if((aux = fgetc(archivo)) == EOF) break;
    if(!noticiaValida(aux)) continue;

    publicador->noticias[i].tipo = aux;
    publicador->numNoticias++;
    fseek(archivo,2,SEEK_CUR);

    for(int j = 0; j < 59; j++){
      if((aux = fgetc(archivo)) == '.'){ 
        fseek(archivo,1,SEEK_CUR); 
        publicador->noticias[i].contenido[j] = '\0'; 
        break;
      }
      publicador->noticias[i].contenido[j] = aux;
    }
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

  for(int i = 0; i < publicador->numNoticias; i++){
    printf("Noticia[%i]:\n",i);
    printf("      Tipo: %c\n", publicador->noticias[i].tipo);
    printf(" Contenido: %s\n\n", publicador->noticias[i].contenido);
  }
}

void endLineFile(FILE** archivo){
  char c = 'A';

  while(c != '\n' && c != '\0'){
    c = fgetc(*archivo);
  }
}
