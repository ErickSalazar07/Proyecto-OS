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
  pedirTopicos(&suscriptor);
  enviarTopicos(&suscriptor);
  mostrarInfoSuscriptor(&suscriptor);
  escucharMensajes(&suscriptor);

  return 0;
}

void escucharMensajes(struct Suscriber* suscriptor) {
  int fileDes;
  char message[100] = {0};
  
  printf("\nAbriendo: %s\n",suscriptor->pipeNominal);
  while((fileDes = open(suscriptor->pipeNominal,O_RDONLY)) == -1);

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

void enviarTopicos(struct Suscriber* suscriptor) {
  int fileDesPipeNomS;
  char mensaje[20] = {0};

  while((fileDesPipeNomS = open(suscriptor->pipeNominal,O_WRONLY)) == -1);

  sprintf(mensaje,"%d:",getpid());
  strncpy(mensaje+strlen(mensaje),suscriptor->topicos,suscriptor->numTopicos);
  printf("Mensaje: %s\n\n",mensaje);
  if(write(fileDesPipeNomS,mensaje,20) == -1) printf("Hubo un error");
  memset(suscriptor->pipeNominal,0,50);
  sprintf(suscriptor->pipeNominal,"%d",getpid());
  close(fileDesPipeNomS);
}

int topicoIngresado(char topico, char* topicos) {
  for(int i = 0; topicos[i]; i++) 
    if(topicos[i] == topico) {
      printf("\n\n\033[91mDijite otro topico, ya que el dijitado, ya se encuentra registrado.\033[0m\n\n");
      return 1;
    }
  return 0;
}

void pedirTopicos(struct Suscriber* suscriptor) {
  int numTopicos = 0;
  int deseaIngresarTopico = 0;

  printf("\t\t\033[35mBIENVENIDO AL PROGRAMA SUSCRIPTOR\033[0m\n\n");
  printf("\n\033[36mDebe suscribirse al menos a 1 topico\033[0m\n\n");
  
  do {
    suscriptor->topicos[numTopicos++] = obtenerTopico(suscriptor);
    printf("\nDesea ingresar otro topico, dijite 1 para si 0 para no.\nDijite: ");
    scanf("%i",&deseaIngresarTopico);
  } while(deseaIngresarTopico && (1 <= numTopicos && numTopicos <= 5));

  suscriptor->numTopicos = numTopicos;
}

char obtenerTopico(struct Suscriber* suscriptor) {
  int opc;
  char c;

opciones:
  printf("\n1. Para Arte 'A'\n");
  printf("2. Para Farandula y Espectaculo 'E'\n");
  printf("3. Para Ciencia 'C'\n");
  printf("4. Para Politica 'P'\n");
  printf("5. Para Sucesos 'S'\n");
  printf("Dijite: ");
  while(scanf("%i",&opc) != 1) {
    printf("\n\nDijite un \033[91mnumero\033[0m: ");
    while((c = getchar() != '\n' && c != EOF));
  }
  
  switch(opc) {
    case 1: c = 'A';
    break;
    case 2: c = 'E';
    break;
    case 3: c = 'C';
    break;
    case 4: c = 'P';
    break;
    case 5: c = 'S';
    break;
    default: printf("\n\n\033[091mDijite un una opcion valida.\033[0m\n\n"); goto opciones;
  }

  if(!topicoIngresado(c,suscriptor->topicos))
    return c;
  goto opciones;
}

int topicoValido(char topico) {
  if(topico == 'A' || topico == 'E' || topico == 'C' || topico == 'P' || topico == 'S') return 1;
  printf("\n\n\033[91mDijite un topico valido.\033[0m\n\n");
  return 0;
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
  char procesIdString[20] = {0};

  sprintf(procesIdString,"%d:",getpid());
  strncpy(procesIdString+strlen(procesIdString),suscriptor->topicos,suscriptor->numTopicos);

  printf("\n\t\t\tINFORMACION DEL SUSCRIPTOR\n\n");
  printf("Linea a enviar por pipe: %s\n",procesIdString);
  printf("NumTopicos: %i\n",suscriptor->numTopicos);
  printf("Pipe: %s\n\n",suscriptor->pipeNominal);
  printf("\n\n\t\t\tTOPICOS\n\n");

  for(int i = 0; i < suscriptor->numTopicos; i++) 
    printf("[%i]: %c\n",i,suscriptor->topicos[i]);
}

unsigned int perteneceMensaje(struct Suscriber* suscriptor,char topico) {
  for(int i = 0; i < suscriptor->numTopicos; i++) 
    if(suscriptor->topicos[i] == topico) 
      return 1;
  return 0;
}