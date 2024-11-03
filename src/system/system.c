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

void enviarMensaje(const struct System* sistema,const char* mensaje){
  int fd=open(sistema->pipeNomP, O_WRONLY);
  if(fd == -1){
    perror("Error al abrir la tuberia del publisher para escribir");
    return;
  }
  if(write(fd,mensaje,strlen(mensaje) + 1) == -1){
    perror("Error al escribir en la tuberia del publisher");
  }
  else{
    printf("Mensaje enviado: %\n",mensaje);
  }
  close(fd);
}
void recibirMensaje(const struct System* sistema) {
    int fd = open(sistema->pipeNomS, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir la tubería del suscriptor para lectura");
        return;
    }

    char buffer[50];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        printf("Mensaje recibido: %s\n", buffer);
    } else {
        perror("Error al leer de la tubería del suscriptor");
    }

    close(fd);
}
