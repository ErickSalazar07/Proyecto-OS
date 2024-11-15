#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "SusSistema/SusSistema.h"
#include "system.h"

int main(int argc, char** argv) {
  if(argc-1 != 6) perror("\n\nLa cantidad de parametros no es correcta.\nRevise\a\n"),exit(EXIT_FAILURE);

  struct System sistema;
  leerArgumentos(argv+1,&sistema);
  mostrarInfoSistema(&sistema);
  crearPipesSusSistema(&sistema);
  limpiarPipes(&sistema);

  return 0;
}

void limpiarPipes(struct System* sistema) {
  unlink(sistema->pipeNomP);
  unlink(sistema->pipeNomS);
}

void crearPipesSusSistema(struct System* sistema) {
  const unsigned int PIPEMODE = 0666;
  int fileDesPipeNomS;
  struct SusSistema auxSus;
  char mensaje[20] = {0};
  
  unlink(sistema->pipeNomS);
  mkfifo(sistema->pipeNomS,PIPEMODE);
  
  while((fileDesPipeNomS = open(sistema->pipeNomS,PIPEMODE)) == -1);

  read(fileDesPipeNomS,mensaje,sizeof(mensaje));
  createSusSistema(&auxSus,mensaje);
  mostrarSusSistema(&auxSus);

  write(auxSus.filePipe,"Hola que tal",strlen("Hola que tal"));
  sleep(1);
  write(auxSus.filePipe,"END",strlen("END"));
  close(auxSus.filePipe);
  unlink(auxSus.nombrePipe);
}

void createSusSistema(struct SusSistema* suscriptorSis, char* mensaje) {
  int i;
  char id[9];

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


void initSisComunicacion(struct System* sistema) {
  const unsigned int PIPEMODE = 0666;

  unlink(sistema->pipeNomP);
  unlink(sistema->pipeNomS);

  mkfifo(sistema->pipeNomP,PIPEMODE);
  mkfifo(sistema->pipeNomS,PIPEMODE);

  escucharMensajes(sistema);
}


void escucharMensajes(struct System* sistema) {
  const unsigned int PIPEMODEPUB = 0222;
  const unsigned int PIPEMODESUS = 0666;
  int fileDesPublicador;
  int fileDesSuscriptor;
  char mensaje[100];

  while((fileDesPublicador = open(sistema->pipeNomP,PIPEMODEPUB)) == -1);
  while((fileDesSuscriptor = open(sistema->pipeNomS,PIPEMODESUS)) == -1);

  while((read(fileDesPublicador,mensaje,sizeof(mensaje))) > 0) {
    if(strcmp(mensaje,"END") == 0) {
      break;
    }

    switch(mensaje[0]) {
      case 'A': printf("\nMensaje %s va para topico Arte\n",mensaje+2);
      break;
      case 'E': printf("\nMensaje %s va para topico Farandula\n",mensaje+2);
      break;
      case 'C': printf("\nMensaje %s va para topico Ciencia\n",mensaje+2);
      break;
      case 'P': printf("\nMensaje %s va para topico Politica\n",mensaje+2);
      break;
      case 'S': printf("\nMensaje %s va para topico Sucesos\n",mensaje+2);
      break;
    }
    write(fileDesSuscriptor,mensaje,sizeof(mensaje));
    memset(mensaje,0,sizeof(mensaje));
  }
  write(fileDesSuscriptor,"END",strlen("END"));
  close(fileDesPublicador);
  close(fileDesSuscriptor);
  cerrarConexion(sistema);

}

void cerrarConexion(struct System* sistema) {
  unlink(sistema->pipeNomP);
  unlink(sistema->pipeNomS);
}

void leerArgumentos(char** argv, struct System* sistema) {
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

void mostrarInfoSistema(const struct System* sistema) {
  printf("\n\nINFORMACION DEL SISTEMA\n\n");
  printf("Pipe Publicador: %s\n",sistema->pipeNomP);
  printf("Pipe Suscriptor: %s\n",sistema->pipeNomS);
  printf("Time F: %0.2lf\n\n",sistema->timeF);
}