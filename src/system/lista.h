#ifndef LISTA_H
#define LISTA_H
#include "../news/noticia.h"

struct Nodo {
    SusSistema dato;// Suscriptor que usa el sistema 
    Nodo* sig;
};

struct Lista {
    Nodo* nodInicio;
    unsigned int numNodos;
};

void initLista(Lista*);
void clearLista(Lista*);
int isEmpty(Lista);
void push_back(Lista*,SusSistema);
void pop_back(Lista*);
unsigned int getNumNodos(Lista*);
void sendMessage(Lista*,Noticia);

#endif // LISTA_H
