#include <iostream>
#include "cabeceras.h"
#include "../h/GestorServidores.h"

using namespace std;

int menu();
void opcionesMenu(GestorServidores &gestor,int opc);

void mostrarServidor(GestorServidores &gestor);
void crearServidor(GestorServidores &gestor);
void eliminarServidor(GestorServidores &gestor);
void activarServidor(GestorServidores &gestor);
void desactivarServidor(GestorServidores &gestor);
void programarMantenimiento(GestorServidores &gestor);
void conectarJugador(GestorServidores &gestor);
void expulsarJugador(GestorServidores &gestor);





int main()
{
    GestorServidores gestor;
    int opc=0;
    do {
        opc=menu();
        opcionesMenu(gestor,opc);

    }while(opc!=9);

    return 0;
}




int menu() {
    int opc;
    cout << "\nGESTOR DE SERVIDORES v1.0" << endl;
    cout << "=========================================================" << endl;
    cout << "1. Mostrar servidor." << endl;
    cout << "2. Crear servidor." << endl;
    cout << "3. Eliminar servidor." << endl;
    cout << "4. Activar servidor." << endl;
    cout << "5. Desactivasr servidor." << endl;
    cout << "6. Programar mantenimiento de servidor." << endl;
    cout << "7. Conectar jugador." << endl;
    cout << "8. Expulsar jugador." << endl;
    cout << "9. Salir." << endl;
    cout << endl;
    cout << "> Seleccione una opcion: ";
    cin >> opc;
    cin.ignore();

    return opc;
}



void opcionesMenu(GestorServidores &gestor,int opc)
{
    switch (opc)
    {
        case 1:
            mostrarServidor(gestor);
            break;


        case 2: {
            crearServidor(gestor);
            break;
        }

        case 3:
            eliminarServidor(gestor);
            break;


        case 4:
            activarServidor(gestor);
            break;


        case 5:
            desactivarServidor(gestor);
            break;


        case 6:
            programarMantenimiento(gestor);
            break;

        case 7:
            conectarJugador(gestor);
            break;

        case 8:
            expulsarJugador(gestor);
            break;

        case 9:
            cout<<"Saliendo...";
            break;

    }
}






void mostrarServidor(GestorServidores &gestor)
{
    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    if (strcmp(direccion,"ALL")==0)
    {
        gestor.mostrarInformacionServidores(-1);
    }
    else
    {
        int pos=gestor.getPosicionServidor(direccion);
        if(pos==-1)
        {
            cout << "Error, no se ha encontrado el servidor";
        }
        else
            gestor.mostrarInformacionServidores(pos);
    }
}


void crearServidor(GestorServidores &gestor)
{
    cadena direccion,nombreJuego,localizacion;
    int id,puerto,maxC,maxE;
    cout << "Introduce los siguientes datos: " << endl;

    cout << "Direccion del servidor: "; cin.getline(direccion,20);
    cout << "Codigo identificador: "; cin >> id; cin.ignore();
    cout << "Nombre del juego instalado: "; cin.getline(nombreJuego,20);
    cout << "Numero de puerto de escucha: "; cin >> puerto; cin.ignore();
    cout << "Numero maximo de conexiones aceptadas: "; cin >> maxC;
    cout << "Numero maximo de jugadores en espera: "; cin >> maxE;
    cout << "Localización geografica: "; cin.getline(localizacion,20);

    gestor.desplegarServidor(direccion,nombreJuego,id,maxC,maxC,puerto,localizacion);
}


void eliminarServidor(GestorServidores &gestor)
{
    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    gestor.desconetarServidor(direccion);
    gestor.eliminarServidor(direccion);
}


void activarServidor(GestorServidores &gestor)
{
    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    gestor.conectarServidor(direccion);
}


void desactivarServidor(GestorServidores &gestor)
{
    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    gestor.desconetarServidor(direccion);
}


void programarMantenimiento(GestorServidores &gestor)
{
    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    gestor.realizarMantenimiento(direccion);
}


void conectarJugador(GestorServidores &gestor)
{
    Jugador J;
    srand(time(NULL));
    cadena nJ,nombrePais,nombreJuego;
    int id,latencia,puntuacion;

    cout << "Introduce la direccion/hostname del servidor: ";
    cadena direccion;
    cin.getline(direccion, 20);

    cout <<"Introduce el nombre (nick) del jugador: "; cin.getline(nJ,20);

    if(gestor.jugadorConectado(nJ)||gestor.jugadorEnEspera(nJ))
    {
        cout << "Error, el jugador ya esta alojado en un servidor";
        return;
    }

    cout << "Introduce los siguientes datos: " << endl;

    cout << "Introduce el id: "; cin >> id; cin.ignore();
    cout << "Nombre del pais desde el que se conecta: "; cin.getline(nombrePais,20);
    cout << "Nombre del juego al que quiere jugar: "; cin.getline(nombreJuego,20);
    latencia=rand()%500+1;
    puntuacion=rand()%100000;

    J.ID=id;
    strcpy(J.nombreJugador,nJ);
    strcpy(J.pais,nombrePais);
    J.latencia=latencia;
    J.puntuacion=puntuacion;

    gestor.alojarJugador(J,nombreJuego,direccion,J.activo);

}


void expulsarJugador(GestorServidores &gestor)
{
    cadena nJ,direccion;
    cout <<"Introduce el nombre (nick) del jugador: "; cin.getline(nJ,20);

    if(gestor.expulsarJugador(nJ,direccion))
        cout << "Jugador expulsado del servidor " << direccion << endl;
    else
        cout << "Error, el jugador no se encuentra en el sistema";
}