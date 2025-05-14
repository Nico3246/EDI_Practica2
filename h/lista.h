#ifndef EDI_PRACTICA2_LISTA_H
#define EDI_PRACTICA2_LISTA_H
#include <iostream>
#include "Declaraciones.h"

#define INCREMENTO 4

using namespace std;

class lista {
    Jugador *elementos; // elementos de la lista
    int n; // nº de elementos que tiene la lista
    int Tama; // tamaño de la tabla en cada momento
public:
    lista(); // constructor de la clase
    ~lista(); // destructor de la clase
    lista(Jugador e);//
    bool esvacia();//Retorna true si la lista está vacía (n == 0), false en caso contrario.
    int longitud();//Retorna la cantidad actual de elementos en la lista (n).
    void anadirIzq(Jugador e);//Inserta un jugador al inicio de la lista
    void anadirDch(Jugador e);//Inserta un jugador al final de la lista
    void eliminarIzq();//Elimina el jugador en la primera posición de la lista
    void eliminarDch();//Elimina el jugador en la última posición de la lista
    Jugador observarIzq();//Devuelve el jugador en la primera posición sin eliminarlo.
    Jugador observarDch();//Devuelve el jugador en la última posición sin eliminarlo.
    void concatenar(lista l);//Añade todos los jugadores de la lista l al final de la lista actual
    bool pertenece(Jugador e);//Devuelve true si el jugador está en la lista (según nombre)
    void insertar(int i, Jugador e);//Inserta el jugador e en la posición i (1-based).si el arreglo está lleno, aumenta su tamaño en INCREMENTO.
                                    //Luego desplaza a la derecha los elementos desde la posición i-1 y coloca e.
    void eliminar(int i);//Elimina el jugador en la posición i
                        //Desplaza a la izquierda los elementos desde la posición i
                        //Si después de eliminar hay mucha memoria no usada, la reduce.
    void modificar(int i, Jugador e);//Reemplaza el jugador en la posición i con el jugador e
    Jugador observar(int i);//Devuelve el jugador en la posición i sin modificar la lista
    int posicion(Jugador e);//Busca un jugador en la lista comparando el campo nombreJugado,retorna su posición o -1 si no lo encuentra.
};

#endif //EDI_PRACTICA2_LISTA_H
