#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include "../SusSistema/SusSistema.h"

struct Node{
  struct Node* next;
  struct SusSistema data;
};

struct Stack{
  struct Node* cima; 
  unsigned int numItems;
};

void initStack(struct Stack*);
bool empty(struct Stack);
bool estaSuscrito(char*,char);
void limpiarStack(struct Stack*);
void pop(struct Stack*);
void sendMessage(struct Stack*,char,char*, unsigned int);
void mostrarSuscritos(struct Stack*);
void push(struct Stack*,struct SusSistema*);

#endif // STACK_H