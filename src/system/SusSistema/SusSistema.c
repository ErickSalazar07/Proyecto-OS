#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "SusSistema.h"

void mostrarSusSistema(struct SusSistema* suscriptor) {
  printf("ID: %i\n",suscriptor->idSus);
  printf("Topicos: %s\n",suscriptor->topicos);
  printf("NombrePipe: %s\n",suscriptor->nombrePipe);
  printf("FilePipe: %i\n\n",suscriptor->filePipe);
}

void limpiarSusSistema(struct SusSistema* suscriptor) {
  suscriptor->filePipe = 0;
  suscriptor->idSus = 0;
  memset(suscriptor->nombrePipe,0,10);
  memset(suscriptor->topicos,0,5);
}

void createSusSistema(struct SusSistema* suscriptorSis, char* mensaje) {
  int i;
  char id[9] = {0};

  for(i = 0; mensaje[i] != ':'; i++) 
    id[i] = mensaje[i];
    
  suscriptorSis->idSus = atoi(id);

  memset(id,0,sizeof(id));
  memset(suscriptorSis->nombrePipe,0,10);
  sprintf(id,"%d",suscriptorSis->idSus);
  strcpy(suscriptorSis->nombrePipe,id);

  strcpy(suscriptorSis->topicos,mensaje+i+1);
  unlink(id);
  mkfifo(id,0666);
  suscriptorSis->filePipe = open(id,0666);
}
