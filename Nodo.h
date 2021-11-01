
/* 
 * File:   Nodo.h
 * Author: Pedro
 *
 * Created on 24 de octubre de 2021, 16:35
 */

#ifndef NODO_H
#define NODO_H

template <typename U>
class Nodo {
public:
    Nodo<U> *izq, *der;
    U dato;
    char bal; //balance de un nodo dentro del arbol (nunca puede ser más de 1)

    Nodo(U &ele) : izq(0), der(0), bal(0), dato(ele) {
    }

    Nodo(Nodo *aizq = nullptr, Nodo *ader = nullptr, U adato = 0, char abal = 0) :
    izq(aizq),
    der(ader),
    dato(adato),
    bal(abal) {
    }
};

#endif /* NODO_H */

