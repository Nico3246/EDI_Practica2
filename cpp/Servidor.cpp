#include "../h/Servidor.h"

#include "cabeceras.h"

Servidor::Servidor(char *dS, char *nJ, int i, int mxL, int mxC, int p, char *lG) {
    strcpy(direccionServidor,ds);
    strcpy(nombreJuego,nJ);
    id=i;
    maxJugadoresConectados=mxL;
    maxJugadoresEnEspera=mxC;
    puerto=p;
    strcpy(localizacionGeografica,lG);
    strcpy(estado,"INACTIVO");



}