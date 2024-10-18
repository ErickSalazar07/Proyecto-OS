#ifndef SUSCRIBER_H
#define SUSCRIBER_H

struct Suscriber{
  char pipeNominal[50];
  char topicos[5];
};

void leerArgumentos(char**, struct Suscriber*);
void mostrarInfoSuscriptor(const struct Suscriber*);

#endif  // SUSCRIBER_H