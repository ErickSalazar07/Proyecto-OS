#ifndef SUSCRIBER_H
#define SUSCRIBER_H

struct Suscriber{
  char pipeNominal[50];
  unsigned int numTopicos;
  char topicos[5];
};

void escucharMensajes(struct Suscriber*);
void leerArgumentos(char**, struct Suscriber*);
int topicoIngresado(char,char*);
void pedirTopicos(struct Suscriber*);
char obtenerTopico(struct Suscriber*);
void enviarTopicos(struct Suscriber*);
unsigned int perteneceMensaje(struct Suscriber*,char);
int topicoValido(char);
void mostrarInfoSuscriptor(const struct Suscriber*);

#endif  // SUSCRIBER_H
