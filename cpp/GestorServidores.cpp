//
// Created by nicob on 15/05/2025.
//

#include "../h/GestorServidores.h"
#include "cabeceras.h"

GestorServidores::GestorServidores() {
    primerServidor= nullptr;
}

GestorServidores::~GestorServidores(){
    Servidor *actual=primerServidor;
    while(actual != nullptr)
    {
        Servidor *siguiente = actual->getSiguienteServidor();
        delete actual;
        actual=siguiente;
    }
}


int GestorServidores::getNumServidores() {
    return numServidores;
}

bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG) {
    Servidor *aux;

    cadena direccion;
    while(aux != nullptr)
    {
        if(aux->getId()==i)//si ya hay uno con el mismo id
            return false;

        aux->getDireccionServidor(direccion);

        if(strcmp(direccion,dS)==0)//si ya hay uno con la misma direccion
            return false;

        aux=aux->getSiguienteServidor();
    }
    Servidor *nuevo= new Servidor(dS,nJ,i,mxL,mxC,p,lG);
    if(nuevo== nullptr)
        return false;


    if(primerServidor== nullptr)
    {
        primerServidor=nuevo;
        nuevo->setSiguienteServidor(nullptr);
        numServidores++;
        return true;
    }

    cadena pais1,pais2;
    nuevo->getLocalizacionGeografica(pais1);
    primerServidor->getLocalizacionGeografica(pais2);

    if(strcmp(pais1,pais2)<0)//si el nuevo servidor va antes que el primero
    {
        nuevo->setSiguienteServidor(primerServidor);
        primerServidor=nuevo;
        numServidores++;
        return true;
    }

    aux=primerServidor;
    while(aux->getSiguienteServidor()!= nullptr)
    {
        Servidor *sig=aux->getSiguienteServidor();
        cadena pais3;
        sig->getLocalizacionGeografica(pais3);

        if(strcmp(pais1,pais3)<0)
        {
            nuevo->setSiguienteServidor(sig);
            aux->setSiguienteServidor(nuevo);
            numServidores++;
            return true;
        }
        aux=sig;
    }
    //si no se ha insertado se inserta al finsal
    aux->setSiguienteServidor(nuevo);
    nuevo->setSiguienteServidor(nullptr);
    numServidores++;
    return true;
}



bool GestorServidores::desconetarServidor(cadena dS) {

    Servidor *aux;
    aux=primerServidor;


}



bool GestorServidores::conectarServidor(cadena dS) {



}


bool GestorServidores::realizarMantenimiento(cadena dS) {


}


bool GestorServidores::eliminarServidor(cadena dS) {


}

bool GestorServidores::alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera) {
    Servidor *aux = primerServidor;
    cadena *activos = new cadena[10];
    int elementos=0;
    int capacidad=10;

    while(aux != nullptr)//buscar servidores activos
    {
        cadena nombreJuego;
        aux->getNombreJuego(nombreJuego);

        if(aux->estaActivo()&& strcmp(nombreJuego,nomJuego)==0)
        {
            if(elementos==capacidad) {
                capacidad+=10;
                cadena *auxActivos = new cadena[capacidad];
                for (int i = 0; i < elementos; i++) {
                    strcpy(auxActivos[i], activos[i]);
                }
                delete[] activos;
                activos = auxActivos;
            }
            aux->getDireccionServidor(activos[elementos]);
            elementos++;
        }
        aux=aux->getSiguienteServidor();
    }

    if(elementos==0)//si no hay servidores activos
    {
        cout<<"No hay servidores activos para el juego " << nomJuego << endl;
        enEspera= false;
        delete[] activos;
        return false;
    }

    Servidor *servidorMax= nullptr;
    int maxdiferencia=-1;//con 0 falla

    for(int i=0;i<elementos;i++)//buscar mayor diferencia
    {
        aux = primerServidor;
        cadena direccion;

        while(aux != nullptr)
        {
            aux->getDireccionServidor(direccion);
            if(strcmp(direccion,activos[i])==0) {
                int max = aux->getMaxJugadoresConectados();
                int conect = aux->getNumJugadoresConectados();
                int diferencia = max - conect;

                if (diferencia > maxdiferencia) {
                    maxdiferencia = diferencia;
                    servidorMax = aux;
                }
                break;
            }
            aux=aux->getSiguienteServidor();
        }
    }

    if(servidorMax!= nullptr && maxdiferencia>0)
    {
        servidorMax->conectarJugador(j);
        servidorMax->getDireccionServidor(host);
        enEspera=false;
        delete[] activos;
        return true;
    }

    //si todos estan llenos
    Servidor *servidorEsperaMax= nullptr;
    int diferenciaEspera=-1;

    for(int i=0;i<elementos;i++)//buscar mayor diferencia
    {
        aux=primerServidor;
        cadena direccion;
        while(aux!= nullptr)
        {
            aux->getDireccionServidor(direccion);
            if(strcmp(direccion,activos[i])==0)
            {
                int max=aux->getMaxJugadoresEnEspera();
                int conect=aux->getNumJugadoresEnEspera();
                int diferencia=max-conect;

                if(diferencia>diferenciaEspera)
                {
                    diferenciaEspera = diferencia;
                    servidorEsperaMax=aux;
                }
                break;

            }
            aux=aux->getSiguienteServidor();
        }
    }
    if(servidorEsperaMax!= nullptr && diferenciaEspera>0)
    {
        servidorEsperaMax->ponerJugadorEnEspera(j);
        servidorEsperaMax->getDireccionServidor(host);
        enEspera= true;
        cout << "El jugador no se ha podido alojar, se ha puesto en espera";
        delete[] activos;
        return false;
    }

    //si no se ha conectado ni metido en espera
    enEspera= false;
    delete[] activos;
    return false;
}



