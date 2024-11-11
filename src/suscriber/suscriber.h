#ifndef SUSCRIBER_H
#define SUSCRIBER_H

struct Suscriber{
  char pipeNominal[50];
  char topicos[5];
};

void initSuscriptor(struct Suscriber*);
void leerArgumentos(char**, struct Suscriber*);
void mostrarInfoSuscriptor(const struct Suscriber*);
void limpiarBuffer(char*);

#endif  // SUSCRIBER_H
