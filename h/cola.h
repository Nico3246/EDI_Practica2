//
// Created by nicob on 08/05/2025.
//

#ifndef EDI_PRACTICA2_COLA_H
#define EDI_PRACTICA2_COLA_H
#include "Declaraciones.h"

class cola
{
    Persona *elementos; //elementos de la cola
    int inicio, fin; //principio y fin de la cola
    int Tama; //Capacidad de la tabla
    int ne; //Nº de elementos
public:
    cola(); // constructor de la clase
    ~cola(); // destructor de la clase
    void encolar(Persona e);
    void desencolar();
    bool esvacia();
    Persona primero() ;
    int longitud();
};

#endif //EDI_PRACTICA2_COLA_H
