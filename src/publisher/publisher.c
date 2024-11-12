#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "publisher.h"

int main(int argc, char** argv) {
  if(argc-1 != 6) perror("ERROR: Argumentos, debe haber exactamente 6, contando los flags.\nRevise su entrada\n\n"), exit(EXIT_FAILURE);

  struct Publisher publicador;

  leerArgumentos(argv+1, &publicador);
  leerArchivo(&publicador);
  mostrarInfoPublicador(&publicador);
  escribirMensajes(&publicador);

  return 0;
}

void leerArgumentos(char** argv, struct Publisher* publicador) {
  for(int i = 0; argv[i]; i++)
    for(int j = 0; argv[i][j]; j++)
      if(argv[i][j] == '-')
        switch(argv[i][++j]){
          case 'p': strncpy(publicador->pipeNominal,argv[i+1],50);
          break;
          case 'f': strncpy(publicador->rutaArchivo,argv[i+1],50);
          break;
          case 't': publicador->timeN = atof(argv[i+1]);
          break;
          default: perror("\n\nLa bandera ingresada, no se reconoce.\nVerifique su entrada\a\n"),exit(-1);
        }
}

void escribirMensajes(struct Publisher* publicador) {
  int fileDes;
  const unsigned int PIPEMODE = 0666;
  char mensaje[100] = {0};

  while((fileDes = open(publicador->pipeNominal, PIPEMODE)) == -1);

  printf("\nArchivo: %s abierto\n\n",publicador->pipeNominal);
  for(int i = 0; i < publicador->numNoticias; i++) {
    mensaje[0] = publicador->noticias[i].tipo;
    mensaje[1] = ':';
    strcpy(mensaje+2,publicador->noticias[i].contenido);
    mensaje[strlen(mensaje)] = '\n';
    printf("MENSAJE: %s",mensaje);
    write(fileDes,mensaje,100);
    sleep(publicador->timeN);
    memset(mensaje,0,sizeof(mensaje));
  }
  write(fileDes,"END",strlen("END"));
  close(fileDes);
}

void leerArchivo(struct Publisher* publicador) {
  FILE* archivo;
  int i;
  char chLeer;

  if(!(archivo = fopen(publicador->rutaArchivo,"r"))) {
    fprintf(stderr,"\n\nEl archivo %s tuvo un error al abrirse.\nRevise por favor\n",publicador->rutaArchivo);
    exit(-2);
  }

  for(i = 0; (chLeer = fgetc(archivo)) != EOF; i++) {
    if(!noticiaValida(chLeer)) { fprintf(stderr,"\n\nHay una noticia no valida.\n\n"); exit(-3); }
    publicador->noticias[i].tipo = chLeer;
    chLeer = fgetc(archivo);
    if(chLeer != ':') { fprintf(stderr,"\n\nEl delimitar ':', no esta. Verifique.\n\n"); exit(-3); }
    for(int j = 0; (chLeer = fgetc(archivo)) != '.'; j++) {
      publicador->noticias[i].contenido[j] = chLeer;
    }
    fseek(archivo,2,SEEK_CUR);
  }
  publicador->numNoticias = i;
  fclose(archivo);
}

bool noticiaValida(char tipo) { return tipo == 'A' || tipo == 'P' || tipo == 'S' || tipo == 'C' || tipo == 'E'; }

void mostrarInfoPublicador(const struct Publisher* publicador) {
  printf("\n\t\tINFORMACION DEL PUBLICADOR\n\n");

  printf("Pipe: %s\n",publicador->pipeNominal);
  printf("File: %s\n",publicador->rutaArchivo);
  printf("Tiempo: %0.2f\n\n", publicador->timeN);
  puts("\n\t\tINFORMACION NOTICIAS\n");

  for(int i = 0; i < publicador->numNoticias; i++){
    printf("Noticia[%i]:\n",i);
    printf("      Tipo: %c\n", publicador->noticias[i].tipo);
    printf(" Contenido: %s\n\n", publicador->noticias[i].contenido);
  }
}
