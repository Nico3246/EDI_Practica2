//
// Created by nicob on 15/05/2025.
//

#include "../h/GestorServidores.h"
#include "cabeceras.h"


Servidor* GestorServidores::getPunteroServidor(int pos) {//metodo que devuelve el servidor d
    if (pos <1 || pos > numServidores)
        return nullptr;

    Servidor *actual=primerServidor;
    int cnt = 1;

    while (actual != nullptr && cnt < pos)
    {
        actual=actual->getSiguienteServidor();
        cnt++;
    }
    return  actual;
}

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
    Servidor *aux=primerServidor;

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

    int pos= getPosicionServidor(dS);
    if(pos==-1)
    {
        cout << "Error, no se encuetnra el sevidor";
        return false;
    }

    Servidor *desactivar= getPunteroServidor(pos);

    if(!desactivar->estaActivo())
        return false;

    cadena nombreJuego;
    desactivar->getNombreJuego(nombreJuego);//obtener el nombre del juego

    int numC=desactivar->getNumJugadoresConectados();//obetener jugadorees conectados
    Jugador *conectados=new Jugador[numC];
    desactivar->exportarJugadoresConectados(conectados);


    int numE=desactivar->getNumJugadoresEnEspera();//obtener jugadores en espera
    Jugador *espera=new Jugador[numE];
    desactivar->exportarJugadoresEnEspera(espera);

    desactivar->desactivar();

    for (int i=0;i<numC;i++)
    {
        Jugador &jugador = conectados[i];//creo una referencia al jugador i
        Servidor *destino= nullptr;
        int max=-1;

        Servidor *aux = primerServidor;
        while(aux!= nullptr)//buscar servidores activos con el mismo juego
        {
            if(aux->estaActivo())
            {
                cadena juego;
                aux->getNombreJuego(juego);
                if(strcmp(juego,nombreJuego)==0)
                {
                    int maxJ = aux->getMaxJugadoresConectados();
                    int conJ = aux->getNumJugadoresConectados();
                    int libres = maxJ-conJ;
                    if(libres > max)
                    {
                        max=libres;
                        destino=aux;
                    }
                }
            }
            aux = aux->getSiguienteServidor();
        }

        if(destino!= nullptr && max>0)
        {
            destino->conectarJugador(jugador);//conector el jugador con referencia
        }
        else
        {
            Servidor *destinoEspera = nullptr;
            int maxEspera = -1;

            aux=primerServidor;
            while(aux!= nullptr)
            {
                if(aux->estaActivo())
                {
                    cadena juego;
                    aux->getNombreJuego(juego);
                    if(strcmp(juego,nombreJuego)==0)
                    {
                        int maxJ = aux->getMaxJugadoresEnEspera();
                        int conJ = aux->getNumJugadoresEnEspera();
                        int libres = maxJ-conJ;
                        if(libres > maxEspera)
                        {
                            maxEspera=libres;
                            destinoEspera=aux;
                        }
                    }
                }
                aux=aux->getSiguienteServidor();
            }

            if(destinoEspera!= nullptr && maxEspera > 0)
            {
                destinoEspera->ponerJugadorEnEspera(jugador);
            }
        }
    }
    delete[] conectados;
    delete[] espera;

    return true;
}



bool GestorServidores::conectarServidor(cadena dS) {
    int pos= getPosicionServidor(dS);
    if(pos==-1)
    {
        cout << "Error, no se encuetnra el sevidor";
        return false;
    }

    Servidor *aux= getPunteroServidor(pos);
    if(!aux->estaActivo())
    {
        if(aux->activar())
            return true;
    }

    return false;
}


bool GestorServidores::realizarMantenimiento(cadena dS) {
    int pos= getPosicionServidor(dS);
    if(pos==-1)
    {
        cout << "Error, no se encuetnra el sevidor";
        return false;
    }

    Servidor *aux= getPunteroServidor(pos);
    if(aux->ponerEnMantenimiento())
    {
        return true;
    }

    return false;
}


bool GestorServidores::eliminarServidor(cadena dS) {
    int pos=getPosicionServidor(dS);
    if(pos==-1)
    {
        cout << "Error, no se encuetnra el sevidor";
        return false;
    }

    Servidor *actual= getPunteroServidor(pos);

    if(actual->estaActivo())
    {
        cout << "El servidor esta activo, no se puede eliminar";
        return false;
    }


    if(pos == 1)
        primerServidor = actual->getSiguienteServidor();
    else
    {
        Servidor *anterior= getPunteroServidor(pos-1);
        anterior->setSiguienteServidor(actual->getSiguienteServidor());
    }
    delete actual;
    numServidores--;
    return true;
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

bool GestorServidores::expulsarJugador(cadena nJ, cadena host) {
    Servidor *aux=primerServidor;
    int cnt=0;
    cadena direccion;

    while(aux!= nullptr)
    {
        aux->getDireccionServidor(direccion);
        if(jugadorConectado(nJ,direccion)|| jugadorEnEspera(nJ,direccion))
        {
            strcpy(host,direccion);
            if(aux->expulsarJugador(nJ))
                return true;
        }
        aux = aux->getSiguienteServidor();
    }
    return false;

}


int GestorServidores::getPosicionServidor(cadena dS) {
    Servidor *aux=primerServidor;
    int cnt=0;


    while(aux!= nullptr)
    {
        cadena direccion;
        aux->getDireccionServidor(direccion);
        if(strcmp(direccion,dS)==0)
        {
            return cnt;
        }
        aux=aux->getSiguienteServidor();
        cnt++;
    }

    return -1;
}


void GestorServidores::mostrarInformacionServidores(int pos) {
    if(pos == -1)
    {
        Servidor *aux=primerServidor;
        int cnt = 1;

        while (aux != nullptr)
        {
            cout << "\nServidor: " << cnt << " :" << endl;
            aux->mostrarInformacion();

            if (aux->estaActivo())
            {
                cout << "\nJugadores conectados: " << endl;
                aux->mostrarJugadoresConectados();

                cout << "\nJugadores en espera: " << endl;
                aux->mostrarJugadoresEnEspera();
            }

            aux=aux->getSiguienteServidor();
            cnt++;
        }
        return;
    }

    if(pos<1 || pos > numServidores)
    {
        cout << "Error, el numero tiene que estar entre 1 y " << numServidores;
        return;
    }

    Servidor *aux2 = getPunteroServidor(pos);
    if(aux2== nullptr)
    {
        cout << "Error, no se ha encontrado el servidor en la posicion indicada";
        return;
    }

    cout << "\nServidor " << pos << " :" << endl;
    aux2->mostrarInformacion();

    if (aux2->estaActivo())
    {
        cout << "\nJugadores conectados: " << endl;
        aux2->mostrarJugadoresConectados();

        cout << "\nJugadores en espera: " << endl;
        aux2->mostrarJugadoresEnEspera();
    }
}


bool GestorServidores::jugadorConectado(cadena nJ, cadena dS) {
    int pos= getPosicionServidor(dS);
    if (pos== -1)
    {
        cout << "Servidor no encontrado";
        return false;
    }

    Servidor *aux= getPunteroServidor(pos);
    int num=aux->getNumJugadoresConectados();

    Jugador *j = new Jugador[num];
    aux->exportarJugadoresConectados(j);

    for(int i=0;i < num;i++)
    {
        if(strcmp(j[i].nombreJugador,nJ)==0)
        {
            delete[] j;
            return true;
        }
    }
    delete[] j;
    return false;
}



bool GestorServidores::jugadorEnEspera(cadena nJ, cadena dS) {

    int pos= getPosicionServidor(dS);
    if (pos== -1)
    {
        cout << "Servidor no encontrado";
        return false;
    }

    Servidor *aux= getPunteroServidor(pos);
    int num=aux->getNumJugadoresEnEspera();

    Jugador *j = new Jugador[num];
    aux->exportarJugadoresEnEspera(j);

    for(int i=0;i < num;i++)
    {
        if(strcmp(j[i].nombreJugador,nJ)==0)
        {
            delete[] j;
            return true;
        }
    }
    delete[] j;
    return false;
}



bool GestorServidores::jugadorConectado(cadena nJ) {
    Servidor *aux=primerServidor;
    int i=0;

    while(aux!= nullptr)
    {
        aux= getPunteroServidor(i);
        if(aux->estaActivo())
        {
            cadena direccion;
            aux->getDireccionServidor(direccion);
            if(jugadorConectado(nJ,direccion))
                return true;
        }

        i++;
    }
    return false;
}


bool GestorServidores::jugadorEnEspera(cadena nJ) {
    Servidor *aux=primerServidor;
    int i=0;

    while(aux!= nullptr)
    {
        aux= getPunteroServidor(i);
        if(aux->estaActivo())
        {
            cadena direccion;
            aux->getDireccionServidor(direccion);
            if(jugadorEnEspera(nJ,direccion))
                return true;
        }

        i++;
    }
    return false;

}












