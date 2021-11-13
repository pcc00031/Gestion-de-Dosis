/* 
 * File:   Iterador.h
 * Author: Pedro Corpas
 *
 * Created on 14 de octubre de 2020, 17:23
 */

#ifndef ITERADOR_H
#define ITERADOR_H

#include "NodoL.h"
#include "ListaEnlazada.h"

template<class T>
class Iterador {
private:
    NodoL<T> *nod;
    //friend class ListaEnlazada<T>;

public:

    Iterador(NodoL<T> *aNodo);
    NodoL<T> *nodo;
    bool fin();
    void siguiente();
    T &dato();
};

template<class T>
Iterador<T>::Iterador(NodoL<T> *aNodo) : nodo(aNodo) {
}

template<class T>
bool Iterador<T>::fin() {
    return nodo == 0;
}

template<class T>
void Iterador<T>::siguiente() {
    nodo = nodo->sig;
}

template<class T>
T &Iterador<T>::dato() {
    return nodo->dato;
}


#endif /* ITERADOR_H */

