#ifndef SYSTEM_H
#define SYSTEM_H

struct System{
    char pipeNomP[50];
    char pipeNomS[50];
    double timeF;
};

enum TIPO_TOPICO {
  A, // arte
  E, // farandula y espectaculo
  C, // ciencia
  P, // politica
  S // sucesos
};

void initSisComunicacion(struct System*);
void leerArgumentos(char**, struct System*);
void escucharMensajes(struct System*);
void cerrarConexion(struct System*);
void mostrarInfoSistema(const struct System*);

#endif // SYSTEM_H