#ifndef SUSCRIBER_H
#define SUSCRIBER_H

struct Suscriber{
  char pipeNominal[50];
  unsigned int numTopicos;
  char topicos[5];
};

void escucharMensajes(struct Suscriber*);
void leerArgumentos(char**, struct Suscriber*);
void pedirTopicos(struct Suscriber*);
unsigned int perteceMensaje(struct Suscriber*,char);
void mostrarInfoSuscriptor(const struct Suscriber*);

#endif  // SUSCRIBER_H
