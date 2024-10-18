#ifndef SYSTEM_H
#define SYSTEM_H

struct System{
    char pipeNomP[50];
    char pipeNomS[50];
    double timeF;
};

void leerArgumentos(char**, struct System*);
void mostrarInfoSistema(const struct System*);

#endif // SYSTEM_H