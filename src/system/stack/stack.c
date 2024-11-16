#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stack.h"


void initStack(struct Stack* pila){
  if(pila->cima){
    pila->cima = 0;
    pila->numItems = 0;
  }
}

void limpiarStack(struct Stack* pila) {
  struct Node* aux = pila->cima;

  while(aux) {
    write(aux->data.filePipe,"END",strlen("END"));
    unlink(aux->data.nombrePipe);
    close(aux->data.filePipe);
  }

  while(!empty(*pila)) 
    pop(pila);
}

void terminarComunicacion(struct Stack* pila) {
  struct Node* aux = pila->cima;

  while(aux) {
    write(aux->data.filePipe,"END",strlen("END"));
    unlink(aux->data.nombrePipe);
    close(aux->data.filePipe);
  }

}

void mostrarSuscritos(struct Stack* pila) {
  struct Node* aux = pila->cima;

  while(aux) {
    mostrarSusSistema(&aux->data);
    aux = aux->next;
  }
}

bool empty(struct Stack pila){
  if(!pila.cima) return true;
  return false;
}

void pop(struct Stack* pila){
  if(!pila->cima) return;

  struct Node* aux = pila->cima;
  pila->cima = pila->cima->next;
  free((void*)aux);
  pila->numItems--;
}

void sendMessage(struct Stack* pila, char topico, char* mensaje, unsigned int tamMensaje) {
  struct Node* aux = pila->cima;

  while(aux) {
    if(topico == '0') {
      printf("\n\nMensaje general enviado a proceso \033[35msuscriptor\033[0m con pipe %s\n\n",aux->data.nombrePipe);
      write(aux->data.filePipe,mensaje,tamMensaje);
    }else if(estaSuscrito(aux->data.topicos,topico)) {
      printf("\n\nEnviando mensaje a proceso \033[35msuscriptor\033[0m con pipe %s\n\n",aux->data.nombrePipe);
      write(aux->data.filePipe,mensaje,tamMensaje);
    }
    aux = aux->next;
  }

}

bool estaSuscrito(char* topicos, char topico) {
  for(int i = 0; topicos[i]; i++)
    if(topicos[i] == topico) return true;
  return false;
}

void push(struct Stack* pila, struct SusSistema* newData){
  struct Node* aux = malloc(sizeof(struct Node));

  aux->data.filePipe = newData->filePipe;
  aux->data.idSus = newData->idSus;
  strcpy(aux->data.nombrePipe,newData->nombrePipe);
  strcpy(aux->data.topicos,newData->topicos);
  aux->next = pila->cima;
  pila->cima = aux;
  pila->numItems++;
}