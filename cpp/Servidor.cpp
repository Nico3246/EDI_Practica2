#include "../h/Servidor.h"

#include "cabeceras.h"

Servidor::Servidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG) {
    strcpy(direccionServidor,dS);
    strcpy(nombreJuego,nJ);
    id=i;
    maxJugadoresConectados=mxL;
    maxJugadoresEnEspera=mxC;
    puerto=p;
    strcpy(localizacionGeografica,lG);
    strcpy(estado,"INACTIVO");
}

int Servidor::getId() {
    return id;
}

void Servidor::getDireccionServidor(cadena dS) {
    strcpy(dS,direccionServidor);
}


void Servidor::setSiguienteServidor(Servidor *pS) {
    siguienteServidor=pS;
}

Servidor* Servidor::getSiguienteServidor() {
    return siguienteServidor;
}

bool Servidor::conectarJugador(Jugador j) {

    int cant=jugadoresConectados.longitud();
    Jugador aux;

    if(cant<maxJugadoresConectados)
    {
        for(int i=0;i<cant;i++)
        {
            aux=jugadoresConectados.observar(i);
            if(j.puntuacion<aux.puntuacion)
            {
                jugadoresConectados.insertar(i,j);
                return true;
            }
        }
        jugadoresConectados.anadirDch(j);
        return true;
    }
    return false;
}


bool Servidor::ponerJugadorEnEspera(Jugador j) {
    int contC=jugadoresConectados.longitud();
    int contE=jugadoresEnEspera.longitud();

    if(contC==maxJugadoresConectados && contE<maxJugadoresEnEspera)
    {
        jugadoresEnEspera.encolar(j);
        return true;
    }
    return false;
}



void Servidor::mostrarJugadoresConectados() {
    Jugador aux;
    cout<<"\n" << setw(20) << "Nombre" << setw(20) << "Identificador" << setw(10) << "Ping" << setw(20) << "Puntuacion global" << setw(15) << "Pais" << endl;
    cout<<"-------------------------------------------------------------------------------------\n";
    for(int i=0;i<jugadoresConectados.longitud();i++)
    {
        aux=jugadoresConectados.observar(i);
        cout << setw(20) << aux.nombreJugador << setw(20) << aux.ID << setw(10) << aux.latencia << setw(20) << aux.puntuacion << setw(15) << aux.pais <<endl;
    }
}


void Servidor::mostrarJugadoresEnEspera() {
    Jugador aux;
    int tam=jugadoresEnEspera.longitud();

    cout<<"\n" << setw(20) << "Nombre" << setw(20) << "Identificador" << setw(10) << "Ping" << setw(20) << "Puntuacion global" << setw(15) << "Pais" << endl;
    cout<<"-------------------------------------------------------------------------------------\n";

    for(int i=0;i<tam;i++)
    {
        aux=jugadoresEnEspera.primero();
        jugadoresEnEspera.desencolar();
        cout << setw(20) << aux.nombreJugador << setw(20) << aux.ID << setw(10) << aux.latencia << setw(20) << aux.puntuacion << setw(15) << aux.pais <<endl;
        jugadoresEnEspera.encolar(aux);
    }
}


bool Servidor::estaActivo() {
    if(strcmp(estado,"ACTIVO")==0)
        return true;

    return false;
}


bool Servidor::activar() {
    if(strcmp(estado,"ACTIVO")!=0)
    {
        strcpy(estado,"ACTIVO");
        return true;
    }
    return false;
}


bool Servidor::desactivar() {
    if(strcmp(estado,"ACTIVO")==0){
        while(!jugadoresConectados.esvacia())
        {
            jugadoresConectados.eliminarDch();
        }
        while(!jugadoresEnEspera.esvacia())
        {
            jugadoresEnEspera.desencolar();
        }
        strcpy(estado,"INACTIVO");
        return true;
    }
    else if(strcmp(estado,"MANTENIMIENTO")==0){
        strcpy(estado,"INACTIVO");
        return true;
    }

    return false;
}



bool Servidor::ponerEnMantenimiento() {
    if(strcmp(estado,"INACTIVO")==0)
    {
        strcpy(estado,"MANTENIMIENTO");
        return true;
    }
    return false;
}


void Servidor::mostrarInformacion() {
    int latencia=0,cnt=0;
    Jugador aux;

    for(int i=0;i<jugadoresConectados.longitud();i++)
    {
        aux=jugadoresConectados.observar(i);
        latencia+=aux.latencia;
        cnt++;
    }
    latencia=latencia/cnt;

    cout << setw(20) << "Direccion" << setw(20) << "Identificador" << setw(15) << "estado" << setw(28) << "jugadores conectados" << setw(28) << "jugadores en espera" << setw(10) << "puerto" << setw(20) << "latencia media" << setw(25) << "localizacion geografica" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(20) << direccionServidor << setw(20) << id << setw(15) << estado << setw(10) << jugadoresConectados.longitud() << "/" << maxJugadoresConectados << setw(10) << jugadoresEnEspera.longitud() << "/" << maxJugadoresEnEspera << setw(10) << puerto << setw(20) <<  latencia << setw(25) << localizacionGeografica << endl;
}


bool Servidor::expulsarJugador(cadena nombre) {
    Jugador aux;
    bool encontrado=false;

    for(int i=0;i<jugadoresConectados.longitud();i++)
    {
        if(strcmp(jugadoresConectados.observar(i).nombreJugador,nombre)==0)
        {
            jugadoresConectados.eliminar(i);
            encontrado = true;

            if(!jugadoresEnEspera.esvacia())
            {
                aux=jugadoresEnEspera.primero();
                jugadoresEnEspera.desencolar();
                conectarJugador(aux);
            }
            return true;
        }
    }

    int tam=jugadoresEnEspera.longitud();

    for(int i=0;i<tam;i++)
    {
        aux=jugadoresEnEspera.primero();
        jugadoresEnEspera.desencolar();

        if(strcmp(aux.nombreJugador,nombre)==0) {
            encontrado = true;
        }
        else
            jugadoresEnEspera.encolar(aux);
    }

    if(!encontrado)
        cout<<"No se ha encontrado al jugador\n";

    return encontrado;
}



void Servidor::getNombreJuego(cadena nJ) {
    strcpy(nJ,nombreJuego);
}


int Servidor::getPuerto() {
    return puerto;
}



void Servidor::getLocalizacionGeografica(cadena lG) {
    strcpy(lG,localizacionGeografica);
}


int Servidor::getMaxJugadoresConectados() {
    return maxJugadoresConectados;
}


int Servidor::getMaxJugadoresEnEspera() {
    return maxJugadoresEnEspera;
}


int Servidor::getNumJugadoresConectados() {
    return jugadoresConectados.longitud();
}


int Servidor::getNumJugadoresEnEspera() {
    return jugadoresEnEspera.longitud();
}


void Servidor::exportarJugadoresConectados(Jugador *conectados) {
    for(int i=0;i<jugadoresConectados.longitud();i++)
    {
        conectados[i]=jugadoresConectados.observar(i);
    }
}


void Servidor::exportarJugadoresEnEspera(Jugador *enEspera) {
    int tam=jugadoresEnEspera.longitud();
    for(int i=0;i<tam;i++)
    {
        enEspera[i]=jugadoresEnEspera.primero();
        jugadoresEnEspera.desencolar();
        jugadoresEnEspera.encolar(enEspera[i]);
    }
}
















