/* 
 * File:   ListaEnlazada.h
 * Author: Pedro Corpas
 *
 * Created on 13 de octubre de 2020, 16:15
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <cstddef>
#include "NodoL.h"
#include "Iterador.h"
#include "Dosis.h"

/* DECLARACION DE LA CLASE */

template<class T>
class ListaEnlazada {
private:
    NodoL<T> *cabecera, *cola;
    int tam;

public:

    /* CONSTRUCTORES */

    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada &orig);
    virtual ~ListaEnlazada();

    /* OPERADORES */

    ListaEnlazada<T>& operator=(const ListaEnlazada<T> &l);
    bool operator<(const ListaEnlazada<T>& right) const;
    // preparado para objetos de tipo dosis 

    friend std::ostream& operator<<(std::ostream& os, const ListaEnlazada &obj) {
        if (obj.tam == 0) {
            std::cout << "  - No hay datos" << endl << endl;
        } else
            std::cout << "  - Total: " << obj.tam << endl;
        for (int i = 0; i < obj.tam; i++) {

            if (i == 0) {
                std::cout << "  - Primera: " << endl << *obj.cabecera->dato << endl;
            }
            if (i == 1) {
                std::cout << "  - Segunda: " << endl << *obj.cabecera->sig->dato << endl;
            }
            if (i == 2) {
                std::cout << "  - Tercera: " << endl << *obj.cabecera->sig->sig->dato << endl;
            }
        }
        return os;
    }

    /* METODOS */

    Iterador<T> iterador(); // iterador al inicio

    // metodos de insercion
    void insertarInicio(T &dato);
    void insertarFinal(T &dato);
    void insertar(Iterador<T> &i, T &dato);
    void insertaOrdenado(T &dato);

    // metodos de borrado
    void borrarInicio();
    void borrarFinal();
    void borra(Iterador<T> &i);

    bool buscar(const T &dato, Iterador<T> &i);

    T& inicio(); // dato en cabecera
    T & final(); // dato en cola

    /* GETTERS Y SETTERS */

    int getTam() const;

};

/* IMPLEMENTACION DE LA CLASE */

/* CONSTRUCTORES */

template<class T>
ListaEnlazada<T>::ListaEnlazada() : cabecera(0), cola(0), tam(0) {
}

/**
 * @brief Constructor copia
 * @param l
 * @return 
 */
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada& orig) {
    NodoL<T> *i = orig.cabecera;

    cabecera = cola = 0;
    tam = orig.tam;

    while (i) {
        NodoL<T> *nuevo;
        nuevo = new NodoL<T>(i->dato, nullptr);

        if (cabecera == nullptr)
            cabecera = nuevo;

        if (cola != nullptr)
            cola->sig = nuevo;

        cola = nuevo;
        i = i->sig;
    }

}

/* OPERADORES */

/**
 * @brief Operador de asignacion
 * @param l
 * @return 
 */
template<class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada<T>& l) {

    if (this != &l) {

        if (cabecera) {
            NodoL<T> *nodo = cabecera;
            while (nodo) {
                cabecera = cabecera->sig;
                delete nodo;
                nodo = cabecera;
            }
            cola = nullptr;
        }
        NodoL<T> *i = l.cabecera;

        this->cabecera = nullptr;
        this->cola = nullptr;
        tam = l.tam;

        while (i) {
            NodoL<T> *nuevo;
            nuevo = new NodoL<T>(i->dato, nullptr);

            if (cabecera == nullptr)
                cabecera = nuevo;

            if (cola != nullptr)
                cola->sig = nuevo;

            cola = nuevo;
            i = i->sig;
        }
    }
    return (*this);
}

template<class T>
bool ListaEnlazada<T>::operator<(const ListaEnlazada<T>& right) const {
    return right > * this;
}

/* METODOS */

/**
 * @brief Iterador apuntando a cabecera
 * @return 
 */
template<class T >
Iterador<T> ListaEnlazada<T>::iterador() {
    return Iterador<T>(cabecera);
}

/**
 * @brief Inserta en cabecera
 * @param dato
 */
template<class T>
void ListaEnlazada<T>::insertarInicio(T & dato) {
    NodoL<T> *nuevo;
    nuevo = new NodoL<T>(dato, cabecera);
    if (cola == 0)
        cola = nuevo;
    tam++;
}

/**
 * @brief Inserta en cola
 * @param dato
 */
template<class T>
void ListaEnlazada<T>::insertarFinal(T & dato) {

    NodoL<T> *nuevo;
    nuevo = new NodoL<T>(dato, 0);

    if (cabecera == 0)
        cabecera = nuevo;
    if (cola != 0)
        cola->sig = nuevo;
    cola = nuevo;
    tam++;
}

/**
 * @brief Inserta apuntando a un iterador
 * @param i
 * @param dato
 */
template<class T>
void ListaEnlazada<T>::insertar(Iterador<T> &i, T & dato) {
    // sin implementar
}

/**
 * @brief Inserta un elemento de forma ordenada
 * @param dato
 */
template<class T>
void ListaEnlazada<T>::insertaOrdenado(T & dato) {
    NodoL<T> *nuevo;
    nuevo = new NodoL<T>(dato, 0);
    NodoL<T> *act;

    if (cabecera == NULL || (cabecera)->dato >= nuevo->dato) {
        nuevo->sig = cabecera;
        cabecera = nuevo;
    } else {
        act = cabecera;
        while (act->sig != NULL &&
                act->sig->dato < nuevo->dato) {
            act = act->sig;
        }
        nuevo->sig = act->sig;
        act->sig = nuevo;
    }
    tam++;
}

/**
 * @brief Borra el elemento de la cabecera
 */
template<class T>
void ListaEnlazada<T>::borrarInicio() {
    if (cabecera != 0) {
        --tam;
        NodoL<T> *borrado = cabecera;
        cabecera = cabecera->sig;
        delete borrado;

        if (cabecera == 0) {
            cola = 0;
        }

    }
}

/**
 * @brief Borra el elemento de la cola
 */
template<class T>
void ListaEnlazada<T>::borrarFinal() {

    NodoL<T> *anterior = 0;
    if (cabecera != cola) {
        --tam;
        anterior = cabecera;
        while (anterior->sig != cola)
            anterior = anterior->sig;

        delete cola;
        cola = anterior;
        if (anterior != 0) {
            anterior->sig = 0;
        } else {
            cabecera = 0;
        }
    }
}

/**
 * @brief Borra un elemento que apunta al iterador
 * @param del
 */
template<class T>
void ListaEnlazada<T>::borra(Iterador<T> &i) {
    NodoL<T> *anterior = 0;
    if (!i.fin()) {
        --tam;
        if (i.nodo == cabecera) {
            borrarInicio();
            i.nodo = cabecera;
            return;
        }
        if (i.nodo == cola) {
            borrarFinal();
            return;
        }

        anterior = cabecera;
        while (anterior->sig != i.nodo) {
            anterior = anterior->sig;
        }
        anterior->sig = i.nodo->sig;
        anterior = i.nodo;
        i.nodo = i.nodo->sig;
        delete anterior;
    }
}

/**
 * @brief Busca una palabra dentro de la lista
 * @param dato
 * @param i
 * @return 
 */
template <class T>
bool ListaEnlazada<T>::buscar(const T &dato, Iterador<T> &i) {

    NodoL<T> *aux;
    aux = cabecera;
    while (aux) {
        if (aux->dato == dato) {
            Iterador<T> k(aux);
            i = k;
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

/**
 * @brief Dato en cabecera
 * @return 
 */
template<class T >
T & ListaEnlazada<T>::inicio() {
    return cabecera->dato;
}

/**
 * @brief Dato en cola
 * @return 
 */
template<class T >
T & ListaEnlazada<T>::final() {
    return cola->dato;
}

/* GETTERS Y SETTERS */

template<class T>
int ListaEnlazada<T>::getTam() const {
    return tam;
}

/* DESTRUCTOR*/

template<class T >
ListaEnlazada<T>::~ListaEnlazada() {
    NodoL<T> *siguiente;
    while (cabecera != NULL) {
        siguiente = cabecera->sig;
        free(cabecera);
        cabecera = siguiente;
    }
    cabecera = NULL;
}

#endif /* LISTAENLAZADA_H */




