#ifndef PUBLISHER_H
#define PUBLISHER_H

struct Publisher{
  char pipeNominal[50];
  char rutaArchivo[50];
  int tiempoNoticia;
  char buffer[150];
};

bool leerEntrada(char**, struct Publisher*);
void mostrarInfoPublicador(const struct Publisher*);

#endif // PUBLISHER_H