#include <iostream>
#include "cabeceras.h"
#include "../h/GestorServidores.h"

using namespace std;

void crearJugador(Jugador &j, const char* nombre, int id, int latencia, int puntuacion, const char* pais) {
    strcpy(j.nombreJugador, nombre);
    j.ID = id;
    j.latencia = latencia;
    j.puntuacion = puntuacion;
    strcpy(j.pais, pais);
}

int main() {
    GestorServidores gestor;

    // Desplegar servidores
    gestor.desplegarServidor((char*)"192.168.1.1", (char*)"JuegoX", 101, 3, 2, 4000, (char*)"España");
    gestor.desplegarServidor((char*)"192.168.1.2", (char*)"JuegoX", 102, 2, 1, 4001, (char*)"Francia");
    gestor.desplegarServidor((char*)"192.168.1.3", (char*)"JuegoY", 103, 2, 2, 4002, (char*)"Alemania");

    // Activar servidores
    gestor.conectarServidor((char*)"192.168.1.1");
    gestor.conectarServidor((char*)"192.168.1.2");

    // Crear jugadores
    Jugador j1, j2, j3, j4, j5, j6, j7;
    crearJugador(j1, "Ana", 1, 20, 1000, "España");
    crearJugador(j2, "Luis", 2, 15, 1100, "España");
    crearJugador(j3, "Clara", 3, 50, 900, "Italia");
    crearJugador(j4, "Leo", 4, 40, 1050, "España");
    crearJugador(j5, "Sara", 5, 25, 1000, "Francia");
    crearJugador(j6, "Nico", 6, 30, 970, "España");
    crearJugador(j7, "Julia", 7, 60, 930, "Alemania");

    // Alojar jugadores
    char direccion[50];
    bool enEspera;
    gestor.alojarJugador(j1, (char*)"JuegoX", direccion, enEspera);
    gestor.alojarJugador(j2, (char*)"JuegoX", direccion, enEspera);
    gestor.alojarJugador(j3, (char*)"JuegoX", direccion, enEspera);
    gestor.alojarJugador(j4, (char*)"JuegoX", direccion, enEspera);
    gestor.alojarJugador(j5, (char*)"JuegoX", direccion, enEspera);
    gestor.alojarJugador(j6, (char*)"JuegoX", direccion, enEspera);

    // Mostrar información de todos los servidores
    cout << "\n--- Información inicial de todos los servidores ---\n";
    gestor.mostrarInformacionServidores(-1);

    // Expulsar jugador
    cout << "\n--- Expulsar jugador Clara ---\n";
    char host[50];
    gestor.expulsarJugador((char*)"Clara", host);

    // Verificación de conexión
    cout << "\n¿Está conectado Ana?: " << (gestor.jugadorConectado((char*)"Ana") ? "Sí" : "No") << endl;
    cout << "¿Está en espera Nico?: " << (gestor.jugadorEnEspera((char*)"Nico") ? "Sí" : "No") << endl;

    // Poner en mantenimiento servidor 192.168.1.2
    gestor.realizarMantenimiento((char*)"192.168.1.2");

    // Desconectar servidor 192.168.1.1 (redistribuirá jugadores)
    gestor.desconetarServidor((char*)"192.168.1.1");

    // Mostrar información tras desconexión
    cout << "\n--- Información tras desconexión de servidor 192.168.1.1 ---\n";
    gestor.mostrarInformacionServidores(-1);

    // Intentar eliminar servidor activo (fallo esperado)
    cout << "\nIntentando eliminar servidor activo 192.168.1.2...\n";
    gestor.eliminarServidor((char*)"192.168.1.2");

    // Eliminar servidor en mantenimiento
    cout << "\nEliminando servidor en mantenimiento 192.168.1.2...\n";
    gestor.eliminarServidor((char*)"192.168.1.2");

    // Mostrar información final
    cout << "\n--- Información final de servidores ---\n";
    gestor.mostrarInformacionServidores(-1);

    return 0;
}
