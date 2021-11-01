/* 
 * File:   VDinamico.h
 * Author: Pedro Corpas
 *
 * Created on 5 de octubre de 2019, 10:17
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>
#include <typeinfo>

/* DECLARACION DE LA CLASE */

template<class T>
class VDinamico {
private:

    T *v; // ----> Vector
    int tamal; // --> Taman-o logico
    int tamaf; // --> Taman-o fisico

public:

    /* CONSTRUCTORES */

    VDinamico(); // Constructor por defecto
    VDinamico(unsigned int tam); // Constructor parametrizado
    VDinamico(const VDinamico& origen); // Constructor copia
    VDinamico(const VDinamico& origen, unsigned // Contructor copia parcial
            int posicionInicial, unsigned int numElementos);

    /* OPERADORES */

    VDinamico<T>& operator=(const VDinamico& right);
    T&operator[](int pos);
    bool operator!=(const VDinamico<T>& right) const;
    bool operator<(const VDinamico<T>& right) const;
    bool operator<=(const VDinamico<T>& right) const;
    bool operator==(const VDinamico<T>& right) const;
    bool operator>(const VDinamico<T>& right) const;
    bool operator>=(const VDinamico<T>& right) const;

    friend std::ostream& operator<<(std::ostream& os, const VDinamico<T>& obj) {
        return os;
    }

    /* METODOS */

    void insertar(const T& dato, unsigned int pos = UINT_MAX);
    T borrar(unsigned int pos = UINT_MAX);
    void ordenar();
    void ordenarRev();
    int buscar(T & dato);
    int busquedaBin(T& dato);
    int lee(unsigned pos);
    void escribe(unsigned pos, int dato);
    void aumenta(int dato); // Inserción por la derecha
    int disminuye(); // Eliminar dato por la derecha
    void datosVector();

    /* GETTERS Y SETTERS */

    unsigned int tam() const;
    unsigned int tamf() const;
    T* getV() const;

    /* DESTRUCTOR */

    virtual ~VDinamico();

};

/* IMPLEMENTACION DE LA CLASE */
/* CONSTRUCTORES */

/**
 * @brief Constructor por defecto
 */
template<class T>
VDinamico<T>::VDinamico() : tamaf(1), tamal(0) {
    v = new T[tamaf];

};

/**
 * @brief Constructor parametrizado
 * @post Inicializa un VDinamico, el tamaño lógico será proporcionado por el usuario y el
 * físico será la potencia de 2 siguiente a este tamanio lógico
 * @param tam
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int tam) : tamal(0) {
    int potencia = 1;
    while (tam > potencia) {
        potencia = potencia * 2;
    }
    tamaf = potencia;
    v = new T[tamaf];
};

/**
 * @brief Constructor copia
 * @post Crea una copia de 
 * @param orig
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig) : tamaf(orig.tamaf),
tamal(orig.tamal), v(orig.v) {
};

/**
 * @brief Constructor copia parcial
 * @post Crea una copia parcial
 * @param orig
 * @param inicio
 * @param num
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& orig, unsigned int inicio, unsigned int num) :
VDinamico<T>::VDinamico(num) {
    if (inicio >= orig.tamal || inicio + num > orig.tamal)
        throw std::out_of_range("{VDinamico::operator[]} El parametro insertado está fuera de rango");
    for (int i = 0; i < num; i++) {
        this->v[i] = orig.v[inicio];
        inicio++;
    }
};

/* OPERADORES*/

/**
 * @brief Operador []
 * @post Sobrecarga del operador []
 * @param pos
 * @return 
 */
template<class T >
T & VDinamico<T>::operator[](int pos) {
    if (pos >= tamal)
        throw std::out_of_range("[VDinamico::operator[]] El parametro insertado está fuera de rango");
    return v[pos];
};

/**
 * @brief Operador de asignación
 * @post Sobrecarga del operador de asignación
 * @param right
 * @return 
 */
template<class T >
VDinamico<T>& VDinamico<T>::operator=(const VDinamico<T>& orig) {
    if (this == &orig) {
        return *this;
    }
    this->tamaf = orig.tamaf;
    this->tamal = orig.tamal;
    v = new T[tamaf];
    for (int i = 0; i < tamaf; i++) {
        v[i] = orig.v[i];
    }
    return *this;

}

template<class T>
bool VDinamico<T>::operator!=(const VDinamico<T>& right) const {
    bool result = !(*this == right);
    return result;
}

template<class T>
bool VDinamico<T>::operator<(const VDinamico<T>& right) const {
    return right > * this;
}

template<class T>
bool VDinamico<T>::operator<=(const VDinamico<T>& right) const {
    return !(*this > right);
}

template<class T>
bool VDinamico<T>::operator==(const VDinamico<T>& right) const {
    if (this->tamaf == right.tamaf &&
            this->tamal == right.tamal &&
            this->v == right.v) {
        return true;
    } else return false;
}

template<class T>
bool VDinamico<T>::operator>(const VDinamico<T>& right) const {
    return right < *this;
}

template<class T>
bool VDinamico<T>::operator>=(const VDinamico<T>& right) const {
    return !(right > * this);
}

/* METODOS */

/**
 * @brief Insertar
 * @post Inserta un dato en la posición indicada, sino se indica el dato, la inserción será realizada al final
 * del vector
 * @throw 
 * @param dato
 * @param pos
 */
template<class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
    if (pos >= tamal && pos != UINT_MAX)
        throw std::out_of_range("[VDinamico::insertar] El parametro insertado está fuera de rango");
    if (tamaf <= tamal) {
        T *vaux;
        vaux = new T[tamaf = tamaf * 2];
        for (int i = 0; i < tamal; i++)
            vaux[i] = v[i];
        delete []v;
        v = vaux;
    }
    if (pos == UINT_MAX) {
        v[tamal] = dato;
        tamal++;
    } else if (pos < tamal) {
        for (unsigned i = tamal - 1; i >= pos; i--) {
            v[i + 1] = v[i];
        }
        v[pos] = dato;
        tamal++;
    }
}

/**
 * @brief Borrar
 * @post Borra un dato de la posicion, sino se indica el dato, se borrará el último elemento del vector
 * @throw 
 * @param unsigned int pos
 * @return 
 */
template<class T>
T VDinamico<T>::borrar(unsigned int pos) {
    T aux;
    if (pos == UINT_MAX) {
        aux = v[tamal];
        tamal--;
    } else {
        aux = v[pos];
        for (int i = pos; i < tamal - 1; i++) {
            v[i] = v[i + 1];
        }
        tamal--;
    }

    if (tamal * 3 < tamal) {
        T *vaux = new T [tamal = tamal / 2];

        for (int i = 0; i < tamal; i++)
            vaux[i] = v[i];

        delete [] v;
        v = vaux;
    }
    return aux;
};

/**
 * @brief Función para ordenar un vector
 * @post Ordena el vector atendiendo al nombre del cliente
 * @throw 
 */
template<class T>
void VDinamico<T>::ordenar() {
    std::sort(v, v + tamal);
};

/**
 * @brief Ordena un vector al contrario
 */
template<class T>
void VDinamico<T>::ordenarRev() {
    std::sort(v, v + tamal, std::greater<T>());
};

/**
 * @brief Busqueda binaria
 * @post Busca un dato en el vector utilizando búsqueda binaria o dicotómica y devolviendo
   la posición del dato. 
 * @param dato
 * @return 
 */
template<class T>
int VDinamico<T>::busquedaBin(T & dato) {
    int first = 0;
    int last = tamal - 1;
    int middle = (first + last) / 2;
    while (first <= last) {
        if (v[middle] < dato) {
            first = middle + 1;

        } else if (v[middle] == dato) {
            return middle;
        } else {
            last = middle - 1;
        }
        middle = (first + last) / 2;
    }
    if (first > last) {
        return -1;
    }
    return -1;
}

/**
 * @brief Busca un dato 
 * @param dato
 * @return 
 */
template<class T>
int VDinamico<T>::buscar(T & dato) {
    for (int i = 0; i < tamal; i++) {
        if (v[i] == dato) {
            return i;
        }
    }
    return -1;
}

/* GETTERS Y SETTERS */

template<class T>
unsigned int VDinamico<T>::tam() const {
    return tamal;
};

template<class T>
unsigned int VDinamico<T>::tamf() const {
    return tamaf;
};

template<class T >
T * VDinamico<T>::getV() const {
    return v;
}

/**
 * @brief Muestra los principales datos de un vector
 */
template<class T>
void VDinamico<T>::datosVector() {

    std::cout << "**** DATOS DEL VECTOR ****" << std::endl;
    std::cout << "  - Taman-o fisico: " << tamf() << std::endl;
    std::cout << "  - Taman-o logico: " << tam() << std::endl;
    std::cout << "  - Vector: " << "{";
    if (tamal >= 75) {
        for (int i = 0; i < 75; i++) {
            std::cout << v[i] << ", ";
        }
        std::cout << "... , " << v[tamal - 1] << "}" << std::endl << std::endl;
    } else {
        for (int i = 0; i < tamal - 1; i++) {

            std::cout << v[i] << ", ";
        }
        std::cout << v[tamal - 1] << "}" << std::endl << std::endl;
    }
}

/**
 * @brief Destructor
 */
template<class T >
VDinamico<T>::~VDinamico() {
};

#endif /* VDINAMICO_H */

