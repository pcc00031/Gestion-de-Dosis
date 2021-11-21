
/* 
 * File:   THashTarjetaVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "THashTarjetaVacunacion.h"

/* CONSTRUCTORES */

THashTarjetaVacunacion::THashTarjetaVacunacion() {
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla) :
tabla(tamTabla, ListaTarjetas()) {
}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion& orig) :
tamTabla(orig.tamTabla), colisiones(orig.colisiones), contadorIntentos(orig.contadorIntentos), intentos(orig.intentos),
medCol(orig.medCol), tabla(orig.tabla) {
}

THashTarjetaVacunacion::~THashTarjetaVacunacion() {
    tabla.erase(tabla.begin(), tabla.end());
}

/* METODOS DE ENTRENAMIENTO */

/**
 * @brief Funcion Hash1 - dispersion doble
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash1(unsigned long str, int intento) {

    unsigned long int hash;
    unsigned long int hash2;

    hash = 5381;
    hash2 = 5381;

    hash2 = (hash2 << 6) + (hash2 << 6) - hash2 + str;

    hash = ((hash << 7) + hash) + str;

    return ((hash + intento) * (hash2 % 14293)) % tabla.size();
};

/**
 * @brief Funcion Hash2 - dispersion doble
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash2(unsigned long str, int intento) {

    unsigned long int hash;
    hash = 5381;

    hash = ((hash << 8) + hash) + str;

    return (hash + (intento * intento)) % tabla.size();
}

/**
 * @brief Funcion Hash3 - dispersion cuadratica
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash3(unsigned long str, int intento) {

    unsigned long int hash;
    unsigned long int hash2;

    hash = 5381;
    hash2 = 5381;

    hash2 = (hash2 << 8) + (hash2 << 5) - hash2 + str;

    hash = ((hash << 6) + hash) + str;

    return ((hash + intento) * (hash2 % 14293)) % tabla.size();
}

/* METODOS */

/**
 * @brief Inserta una tarjeta no repetida en la tabla
 * siguiendo la funcion Hash1
 * @param clave
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::insertar1(unsigned long clave, TarjetaVacunacion &t) {
    for (int intento = 0; intento < 10; intento++) {

        if (tabla[hash1(clave, intento)].size() <= 3) {
            tabla[hash1(clave, intento)].push_back(t);
            contadorIntentos = intento;
            intentos.push_back(contadorIntentos);
            return true;
        } else
            colisiones++;
    }
}

/**
 * @brief Inserta una tarjeta no repetida en la tabla
 * siguiendo la funcion Hash2
 * @param clave
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::insertar2(unsigned long clave, TarjetaVacunacion &t) {
    for (int intento = 0; intento < 10; intento++) {

        if (tabla[hash2(clave, intento)].size() <= 3) {
            tabla[hash2(clave, intento)].push_back(t);
            contadorIntentos = intento;
            intentos.push_back(contadorIntentos);
            return true;
        } else
            colisiones++;
    }
}

/**
 * @brief Inserta una tarjeta no repetida en la tabla
 * siguiendo la funcion Hash3
 * @param clave
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::insertar3(unsigned long clave, TarjetaVacunacion &t) {
    for (int intento = 0; intento < 10; intento++) {

        if (tabla[hash3(clave, intento)].size() <= 3) {
            tabla[hash3(clave, intento)].push_back(t);
            contadorIntentos = intento;
            intentos.push_back(contadorIntentos);
            return true;
        } else
            colisiones++;
    }
}

//TODO comprobar todo de la tabla hash

/**
 * @brief Busca un elemento en la tabla
 * @param clave
 * @param id
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::buscar(unsigned long clave, std::string &id, TarjetaVacunacion &t) {
    //FIXME Si tiene marca de borrado, pasar al siguiente
    //FIXME adaptar a tarjta
    for (int i = 0; i < 5; i++) {
        if (i <= 3) {
            //            typename vector<ListaTarjetas>::iterator iv = tabla.begin() + hash20(clave, i);
            //            typename ListaTarjetas::iterator il = iv->begin();
            //            while (il != iv->end()) {
            //                if (il->getDni() == clave) {
            //                    dni = il->getDni();
            //                    return true;
            //                }
            //                ++il;
            //            }
        }
    }
    return false;
}

/**
 * @brief Borra un elemento de la tabla
 * @param clave
 * @param id
 * @return 
 */
bool THashTarjetaVacunacion::borrar(unsigned long clave, std::string &id) {
    //FIXME Aplicar marca de borrado
    //FIXME adaptar a tarjta
    //    typename vector<ListaTarjetas>::iterator iv =
    //            tabla.begin() + hash1(clave, 0);
    //    typename ListaTarjetas::iterator il = iv->begin();
    //    while (il != iv->end()) {
    //        if (il->getDni() == clave) {
    //            iv->erase(il);
    //            return true;
    //        }
    //        ++il;
    //    }
    return false;
}

/**
 * @brief redispersa la tabla a un nuevo tamaño tam
 * @param tam
 */
void THashTarjetaVacunacion::redispersar(unsigned tam) {
    //    std::vector<ListaTarjetas> aux;
    //    aux.assign(13499, ListaTarjetas());
    //
    //    if (factorCarga() <= 0.6000) {
    //        std::vector<ListaTarjetas> aux;
    //        aux.assign(13499, ListaTarjetas());
    //        colisiones2 = 0;
    //        intentos2.erase(intentos2.begin(), intentos2.end());
    //        contadorIntentos2 = 0;
    //
    //        for (int i = 0; i < tabla.size(); i++) {
    //            for (auto it = tabla[i].begin(); it != tabla[i].end(); ++it) {
    //
    //                if (aux[hash20(it->getDni(), i)].size() <= 3) {
    //                    aux[hash20(it->getDni(), i)].push_back(*it);
    //                    contadorIntentos2 = i;
    //                    intentos2.push_back(contadorIntentos2);
    //                    break;
    //                } else
    //                    colisiones2++;
    //            }
    //        }
    //        tabla.erase(tabla.begin(), tabla.end());
    //        tabla = aux;
    //    }
}

/* METODOS DE PRUEBA */

/**
 * @brief devuelve el número máximo de colisiones que se han producido 
 * en la operación de inserción más costosa realizada sobre la tabla.
 * @return 
 */
unsigned int THashTarjetaVacunacion::maxColisiones() {
    return this->colisiones;
}

/**
 * @brief devuelve el número de veces que se superan 10 colisiones 
 * al intentar realizar la operación de inserción sobre la tabla de un dato.
 * @return 
 */
unsigned int THashTarjetaVacunacion::numMax10() {
    //TODO numMax
    return 0;
}

/**
 * @brief devuelve el promedio de colisiones por operación de inserción realizada sobre la tabla.
 * @return 
 */
unsigned int THashTarjetaVacunacion::promedioColisiones() {
    return this->intentos.back();
}

/**
 * @brief devuelve el factor de carga de la tabla de dispersión.
 * @return 
 */
float THashTarjetaVacunacion::factorCarga() {
    float fc;
    fc = numTarjetas() * 1.0 / tabla.size();
    return fc;
}

/**
 * @brief devuelve el tam de la tabla de dispersion
 * @return 
 */
unsigned int THashTarjetaVacunacion::getTamTabla() {
    return this->tabla.size();
}

/**
 * @brief devuelve el numero de tarjetas
 * @return 
 */
unsigned int THashTarjetaVacunacion::numTarjetas() {
    int total = 0;
    for (int i = 0; i < tabla.size(); i++) {
        for (int j = 1; j < 5; j++) {
            if (tabla[i].size() == j)
                total = total + j;
        }
    };
    return total;
};

/* OPERADORES*/

THashTarjetaVacunacion& THashTarjetaVacunacion::operator=(THashTarjetaVacunacion &thash) {

    if (this == &thash) {
        return *this;
    }
    colisiones = thash.colisiones;
    contadorIntentos = thash.contadorIntentos;
    intentos = thash.intentos;
    medCol = thash.medCol;
    tabla = thash.tabla;
    tamTabla = thash.tamTabla;

    return *this;
}

/* GETTERS Y SETTERS */