#ifndef SUS_SISTEMA_H
#define SUS_SISTEMA_H

struct SusSistema {
    unsigned int idSus;
    char nombrePipe[10];
    char topicos[5];
    int filePipe; // es el descriptor del archivo, para el pipe nominal del suscriptor
};

void mostrarSusSistema(struct SusSistema*); 
void createSusSistema(struct SusSistema*,char*);
void limpiarSusSistema(struct SusSistema*);

#endif // SUS_SISTEMA_H
