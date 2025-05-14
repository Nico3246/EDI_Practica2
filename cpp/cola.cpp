//
// Created by nicob on 08/05/2025.
//

#include "../h/cola.h"
#include "Declaraciones.h"

cola::cola()
{
    elementos=new Jugador[INCREMENTO];
    if (elementos!= nullptr) {
        ne=fin=inicio=0;
        Tama=INCREMENTO;
    }
    else {
        ne=fin=inicio=-1;
        Tama=-1;
    }
}


cola::~cola()
{
    if (elementos!=nullptr)
        delete [] elementos;
    elementos=nullptr;
    ne=fin=inicio=-1;
    Tama=0;
}


void cola::encolar(Jugador e)
{
    if (ne==Tama) {
        Jugador *NuevaZona=new Jugador[Tama+INCREMENTO];
        if (NuevaZona!=nullptr) {
            for (int i=0;i<ne; i++) {
                NuevaZona[i]=elementos[inicio];
                inicio++;
                if (inicio==Tama) // inicio=(inicio+1)%Tama
                    inicio=0;
            }
            inicio=0;
            fin=ne;
            Tama+=INCREMENTO;
            delete [] elementos;
            elementos=NuevaZona;
        }
    };
    if (ne<Tama) {
        elementos[fin]=e;
        fin=(fin+1)%Tama;
        ne++;
    }
}


void cola::desencolar()
{
    inicio++; // inicio=(inicio+1)%Tama;
    if (inicio==Tama)
        inicio=0;
    ne--;
    if (Tama-ne>=INCREMENTO && Tama>INCREMENTO) {
        Jugador *NuevaZona=new Jugador[Tama-INCREMENTO];
        if (NuevaZona!=nullptr) {
            for (int i=0;i<ne; i++) {
                NuevaZona[i]=elementos[inicio++];
                if (inicio==Tama)
                    inicio=0;
            }
            Tama-=INCREMENTO;
            inicio=0;
            fin=Tama;
            delete [] elementos;
            elementos=NuevaZona;
        };
    };
}


bool cola::esvacia()
{
    return (ne==0);
}


Jugador cola::primero()
{
    return elementos[inicio];
}


int cola::longitud()
{
    return ne;
}

