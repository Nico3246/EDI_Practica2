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
    lista(Jugador e);
    bool esvacia();
    int longitud();
    void anadirIzq(Jugador e);
    void anadirDch(Jugador e);
    void eliminarIzq();
    void eliminarDch();
    float observarIzq();
    float observarDch();
    void concatenar(lista l);
    bool pertenece(Jugador e);
    void insertar(int i, Jugador e);
    void eliminar(int i);
    void modificar(int i, Jugador e);
    float observar(int i);
    int posicion(Jugador e);
};

#endif //EDI_PRACTICA2_LISTA_H
