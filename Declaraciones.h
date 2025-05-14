//
// Created by nicob on 08/05/2025.
//

#ifndef EDI_PRACTICA2_DECLARACIONES_H
#define EDI_PRACTICA2_DECLARACIONES_H

#define INCREMENTO 4
typedef char cadena[50];
struct Jugador{
    cadena nombreJugador; //nombre de usuario del un jugador. Es único en el sistema.
    int ID; //código numérico (entero positivo) identificador de un jugador. Es único en el sistema.
    bool activo; //valor lógico que indica si el jugador está o no conectado a un servidor.
    int latencia; //tiempo de respuesta del jugador calculado por el sistema cuando recibe una petición
    //de conexión. Se mide en milisegundos.
    long puntuacion; //puntuación acumulada por el jugador a lo largo de todas las temporadas en las que
    //éste ha participado en el juego
    cadena pais; //nombre del país desde el que se conecta el jugador.
};


#endif //EDI_PRACTICA2_DECLARACIONES_H
