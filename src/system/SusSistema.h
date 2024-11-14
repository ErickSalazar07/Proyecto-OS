#ifndef SUS_SISTEMA_H
#define SUS_SISTEMA_H

struct SusSistema {
    unsigned int idSus;
    char topicos[5];
    int filePipe; // es el descriptor del archivo, para el pipe nominal del suscriptor
};

#endif SUS_SISTEMA_H
