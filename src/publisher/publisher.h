#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "../news/noticia.h"

struct Publisher{
  char pipeNominal[50];
  char rutaArchivo[50];
  int timeN;
  unsigned int numNoticias;
  struct Noticia noticias[5];
};

void initPublicador(struct Publisher*);
void leerArgumentos(char**, struct Publisher*);
void leerArchivo(struct Publisher*);
void mostrarInfoPublicador(const struct Publisher*);
bool noticiaValida(char);

#endif // PUBLISHER_H
