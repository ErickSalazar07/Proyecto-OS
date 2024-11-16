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
  initSisComunicacion(&sistema,argv+1);
  mostrarInfoSistema(&sistema);
  crearPipesSusSistema(&sistema);
  escucharMensajes(&sistema);
  limpiarPipes(&sistema);

  return 0;
}

void limpiarPipes(struct System* sistema) {
  printf("\n\nCERRANDO COMUNICACION\n\n\n");
  unlink(sistema->pipeNomP);
  unlink(sistema->pipeNomS);
  limpiarStack(&sistema->suscritos);
}

void crearPipesSusSistema(struct System* sistema) {
  int fileDesPipeNomS;
  struct SusSistema auxSus;
  char mensaje[20] = {0};
  
  
  while((fileDesPipeNomS = open(sistema->pipeNomS,O_RDONLY)) == -1);

  while(read(fileDesPipeNomS,mensaje,sizeof(mensaje)) > 0) {
    createSusSistema(&auxSus,mensaje);
    push(&sistema->suscritos,&auxSus);
    limpiarSusSistema(&auxSus);
    memset(mensaje,0,sizeof(mensaje));
  }

  close(fileDesPipeNomS);
  printf("\n\nSe crearon todos los pipes, y ya no hay mas procesos suscriptores para mandar pipes\n\n");
}

void initSisComunicacion(struct System* sistema, char** argv) {
  const unsigned int PIPEMODE = 0666;

  memset(sistema->pipeNomP,0,50);
  memset(sistema->pipeNomS,0,50);
  initStack(&sistema->suscritos);
  sistema->timeF = 0.0;

  leerArgumentos(sistema,argv);
  unlink(sistema->pipeNomS);
  unlink(sistema->pipeNomP);
  mkfifo(sistema->pipeNomS,PIPEMODE);
}


void escucharMensajes(struct System* sistema) {
  const unsigned int FILE_DES_PUB_MODE = 0666;
  int fileDesPub = 0666;
  char mensaje[80];

  mkfifo(sistema->pipeNomP,FILE_DES_PUB_MODE);

  while((fileDesPub = open(sistema->pipeNomP,O_RDONLY)) == -1);

  while(read(fileDesPub,mensaje,sizeof(mensaje)) > 0) {
enviarMensajes:
    printf("%s\n",mensaje);
    switch(mensaje[0]) {
      case 'A': sendMessage(&sistema->suscritos,'A',mensaje+2,sizeof(mensaje)-2);
      break;
      case 'E': sendMessage(&sistema->suscritos,'E',mensaje+2,sizeof(mensaje)-2);
      break;
      case 'C': sendMessage(&sistema->suscritos,'C',mensaje+2,sizeof(mensaje)-2);
      break;
      case 'P': sendMessage(&sistema->suscritos,'P',mensaje+2,sizeof(mensaje)-2);
      break;
      case 'S': sendMessage(&sistema->suscritos,'S',mensaje+2,sizeof(mensaje)-2);
      break;
    }
    memset(mensaje,0,sizeof(mensaje));
  }

  sleep(sistema->timeF);

  if(read(fileDesPub,mensaje,sizeof(mensaje)) > 0) goto enviarMensajes;

  printf("\n\nSe cierra el pipe de los publicadores\n\n");
  close(fileDesPub);
}

void leerArgumentos(struct System* sistema, char** argv) {
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