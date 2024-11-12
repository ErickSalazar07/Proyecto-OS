#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "suscriber.h"

int main(int argc, char** argv) {
  if(argc-1 != 2) perror("\n\nLa canitidad de parametros no coincide.\nRevise\n\a"),exit(EXIT_FAILURE);
  
  struct Suscriber suscriptor;
  leerArgumentos(argv+1,&suscriptor);
  mostrarInfoSuscriptor(&suscriptor);
  escucharMensajes(&suscriptor);
  return 0;
}

void escucharMensajes(struct Suscriber* suscriptor) {
  int fileDes;
  const unsigned int PIPEMODE = 0666;
  char message[100] = {0};

  while((fileDes = open(suscriptor->pipeNominal,PIPEMODE)) == -1);

  while((read(fileDes,message,100)) > 0) {
    if(strcmp(message,"END") == 0) { 
      printf("\n\nLa comunicacion ha terminado\n\n");
      break;
    }
    printf("%s\n",message);  
    memset(message,0,sizeof(message));
  }
  close(fileDes);
}

void pedirTopicos(struct Suscriber* suscriptor) {
  int numTopicos = 0;
  int deseaIngresarTopico = 1;
  char topico = '\0';
  printf("\t\t\033[91mBIENVENIDO AL PROGRAMA SUSCRIPTOR\033[0m\n\n");
  printf("\n\033[31mDebe suscribirse al menos a 1 topico\033[0m\n\n");
  
  while(deseaIngresarTopico || numTopicos <= 0) {
    if(deseaIngresarTopico) {
      printf("Por favor dijite la letra del topico al que se quiere suscribir. ej['A','E','C','P','S']: ");
      scanf("%c",&topico);
    }
    printf("Desea ingresar otro topico 1 para si, 0 para no: ");
    scanf("%i",&deseaIngresarTopico);
  }

}

void leerArgumentos(char** argv, struct Suscriber* suscriptor) {
  for(size_t i = 0; argv[i]; i++)
    for(size_t j = 0; argv[i][j]; j++)
      if(argv[i][j] == '-')
        switch(argv[i][++j]){
          case 's': strncpy(suscriptor->pipeNominal, argv[i+1],50);
          break;
          default: perror("\n\nLa bandera, no se identifica\n\a"),exit(-1);
        }
}

void mostrarInfoSuscriptor(const struct Suscriber* suscriptor) {
  printf("\n\t\t\tINFORMACION DEL SUSCRIPTOR\n\n");
  printf("Pipe: %s\n\n",suscriptor->pipeNominal);
}

unsigned int perteneMensaje(struct Suscriber* suscriptor,char topico) {
  for(int i = 0; i < suscriptor->numTopicos; i++) 
    if(suscriptor->topicos[i] == topico) 
      return 1;
  return 0;
}