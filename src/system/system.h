#ifndef SYSTEM_H
#define SYSTEM_H
#include "stack/stack.h"

struct System{
    char pipeNomP[50];
    char pipeNomS[50];
    struct Stack suscritos;
    double timeF;
};

void crearPipesSusSistema(struct System*);
void initSisComunicacion(struct System*,char**);
void limpiarPipes(struct System*);
void leerArgumentos( struct System*,char**);
void escucharMensajes(struct System*);
void mostrarInfoSistema(const struct System*);

#endif // SYSTEM_H