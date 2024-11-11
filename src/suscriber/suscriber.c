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
  initSuscriptor(&suscriptor);
  return 0;
}

void initSuscriptor(struct Suscriber* suscriptor) {
  int fileDes;
  const unsigned int PIPEMODE = 0222;
  char message[100] = {0};

  while((fileDes = open(suscriptor->pipeNominal,PIPEMODE)) == -1);

  while((read(fileDes,message,100)) > 0) {
    printf("%s\n",message);  
    if(strcmp(message,"END") == 0) { 
      printf("\n\nLa comunicacion ha terminado\n\n");
      break;
    }
    memset(message,0,sizeof(message));
  }
  close(fileDes);
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
