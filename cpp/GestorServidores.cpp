//
// Created by nicob on 15/05/2025.
//

#include "../h/GestorServidores.h"

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



