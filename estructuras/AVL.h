
/* 
 * File:   AVL.h
 * Author: Pedro
 *
 * Created on 25 de octubre de 2021, 12:46
 */

#ifndef AVL_H
#define AVL_H

#include "Nodo.h"
#include "VDinamico.h"

template <typename T>
class AVL {
    Nodo<T> *raiz;
private:

    /* METODOS PRIVADOS*/
    int inserta(Nodo<T>* &c, T &dato);
    void rotDecha(Nodo<T>* &p);
    void rotIzqda(Nodo<T>* &p);

    Nodo<T> *buscaClave(T &ele, Nodo<T> *p);
    void copiarNodo(Nodo<T> *pun);
    VDinamico<T*> inorden(Nodo<T> *p, int nivel, VDinamico<T*> &v);
    void recorrerArbolNumElem(Nodo<T> *pun, int &cont);
    void recorrerArbolAltura(Nodo<T> *pun, int &cont, int &alt);
    void destruirNodo(Nodo<T>* &ref);

public:

    /* CONSTRUCTORES*/

    AVL();
    AVL(const AVL& orig);

    /* SOBRECARGA DE OPERADORES*/

    AVL<T> &operator=(const AVL<T> &right);

    /* METODOS PUBLICOS */

    VDinamico<T*> recorreInorden();
    unsigned int numElementos();
    unsigned int altura();
    bool buscaR(T &ele, T* &result);
    bool buscaIt(T& dato, T& result);
    bool inserta(T &dato);
    ~AVL();

};

/* IMPLEMENTACION DE LA CLASE */

/** 
 * @brief Constructor por defecto
 */
template <typename T>
AVL<T>::AVL() {
    raiz = 0;
}

/** 
 * @brief Constructor de copia
 * @param origen
 */
template <typename T>
AVL<T>::AVL(const AVL& origen) {
    copiarNodo(origen.raiz);
}

/** 
 * @brief Operador =
 * @param right
 */
template <typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &right) {
    if (this != &right) {
        destruirNodo(raiz);
        copiarNodo(right.raiz);
    }
    return *this;
}

/** 
 * @brief copia los nodos de un árbol recursivamente
 * @param *pun   
 */
template <typename T>
void AVL<T>::copiarNodo(Nodo<T> *pun) {
    if (pun != nullptr) {
        Nodo<T> *nuevoNodo;
        nuevoNodo = new Nodo<T> (pun->izq, pun->der, pun->dato, pun->bal);
        copiarNodo(nuevoNodo->izq);
        copiarNodo(nuevoNodo->der);
    }
}

/** 
 * @brief  cambia el dato de un nodo rotando hacia la izquierda
 * @param &p  
 */
template <typename T>
void AVL<T>::rotIzqda(Nodo<T>* &p) {
    Nodo<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0)
        q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0)
        r->bal += q->bal;
}

/** 
 * @brief Cambia el dato de un nodo rotando hacia la derecha
 * @param &p  
 */
template <typename T>
void AVL<T>::rotDecha(Nodo<T>* &p) {
    Nodo<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0)
        q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0)
        l->bal -= -q->bal;
}

/** 
 * @brief Inserta un dato en el árbol a través de recursividad
 * @param &p  
 * @post Devuelve 0 en el caso de que el nodo no sea nullptr y 1 si el nodo es nullptr
 */
template <typename T>
int AVL<T>::inserta(Nodo<T>* &c, T &dato) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new Nodo<T>(dato);
        c = p;
        deltaH = 1;
    } else if (p->dato < dato) {
        if (inserta(p->der, dato)) {
            p->bal--;
            if (p->bal == -1)
                deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1)
                    rotDecha(p->der);
                rotIzqda(c);
            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1)
                deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1)
                    rotIzqda(p->izq);
                rotDecha(c);
            }
        }
    }
    return deltaH;
}

/** 
 * @brief Inserta un dato en el árbol
 * @param ele  
 * @post Devuelve true en el caso de que el dato no esté ya en el árbol y false si el dato estaba ya en el árbol
 */
template <typename T>
bool AVL<T>::inserta(T& ele) {
    T *pun;
    bool encontrado = buscaR(ele, pun);

    if (!encontrado) {
        inserta(raiz, ele);
        return true;
    }
    return false;
}

/** 
 * @brief Busca recursivamente un dato en el árbol
 * @param ele
 * @param *p  
 * @post Devuelve nullptr en el caso de que Nodo<T> *p sea nullptr y d
 * evuelve el puntero al dato en el caso de que lo hayamos encontrado
 */

template <typename T>
Nodo<T> *AVL<T>::buscaClave(T &ele, Nodo<T> *p) {
    if (!p)
        return 0;
    else if (ele < p->dato)
        return buscaClave(ele, p->izq);
    else if (p->dato < ele)
        return buscaClave(ele, p->der);
    else
        return p;
}

/** 
 * @brief Busca un dato en el árbol
 * @param ele
 * @param *p  
 * @post Devuelve true en caso de encontrarlo y false en caso contrario
 */
template <typename T>
bool AVL<T>::buscaR(T &ele, T* &result) {
    Nodo<T> *p = buscaClave(ele, raiz);
    if (p) {
        result = &p->dato;
        return true;
    }
    return false;
}

/** 
 * @brief Busca iterativamente un dato en el árbol
 * @param dato
 * @param result 
 * @post Devuelve true en caso de encontrarlo y false en caso contrario
 */
template <typename T>
bool AVL<T>::buscaIt(T& dato, T& result) {
    Nodo<T> *iterador = raiz;
    while (iterador != nullptr) {
        if (iterador->dato < dato)
            iterador = iterador->der;
        else if (dato < iterador->dato)
            iterador = iterador->izq;
        else {
            result = iterador->dato;
            return true;
        }
    }
    return false;
}

/**
 * @brief Recorre el árbol en inorden
 */

template <typename T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> vector = VDinamico<T*>();
    int nivel = 0;
    Nodo<T> *p = raiz;
    return inorden(p, nivel, vector);
}

/** 
 * @brief Recorre recursivamente el árbol en inorden
 * @param *p
 * @param &nivel 
 */
template <typename T>
VDinamico<T*> AVL<T>::inorden(Nodo<T> *p, int nivel, VDinamico<T*> &v) {
    if (p) {
        inorden(p->izq, nivel + 1, v);
        v.insertar(&p->dato);
        inorden(p->der, nivel + 1, v);
    }
    return v;
}

/** 
 * @brief Calcula el numero de elementos de un arbol
 * @param dato
 * @param result 
 * @post  Devuelve el numero de elementos
 */

template <typename T>
unsigned int AVL<T>::numElementos() {
    int cont = 0;
    Nodo<T> *pun = raiz;
    recorrerArbolNumElem(pun, cont);
    return cont;
}

/** 
 * @brief Cuenta recursivamente los elementos de un arbol
 * @param pun
 * @param cont
 */

template <typename T>
void AVL<T>::recorrerArbolNumElem(Nodo<T> *pun, int &cont) {
    if (pun) {
        cont++;
        recorrerArbolNumElem(pun->izq, cont);
        recorrerArbolNumElem(pun->der, cont);
    }
}

/** 
 * @brief Calcula la altura de un arbol
 * @post  Devuelve la altura del arbol
 */
template <typename T>
unsigned int AVL<T>::altura() {
    int alt = 0;
    int cont = 0;
    recorrerArbolAltura(raiz, cont, alt);
    return alt;
}

/** 
 * @brief Cuenta recursivamente los niveles de un arbol
 * @param pun
 * @param cont
 * @param alt
 */
template <typename T>
void AVL<T>::recorrerArbolAltura(Nodo<T> *pun, int &cont, int &alt) {
    if (pun) {
        cont++;
        recorrerArbolAltura(pun->izq, cont, alt);
        recorrerArbolAltura(pun->der, cont, alt);
        cont--;
    } else {
        if (cont > alt)
            alt = cont;
    }
}

/**
 * @brief Destruye un nodo
 * @param ref
 */
template <typename T>
void AVL<T>::destruirNodo(Nodo<T>* &ref) {
    if (ref != nullptr) {
        destruirNodo(ref->izq);
        destruirNodo(ref->der);
        delete ref;
        ref = nullptr;
    }
}

/**
 * @brief Destructor
 */
template <typename T>
AVL<T>::~AVL() {
    destruirNodo(raiz);
}

#endif /* AVL_H */

