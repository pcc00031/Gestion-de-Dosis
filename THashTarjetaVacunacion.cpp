
/* 
 * File:   THashTarjetaVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "THashTarjetaVacunacion.h"

/* CONSTRUCTORES */

THashTarjetaVacunacion::THashTarjetaVacunacion() {
}

THashTarjetaVacunacion::THashTarjetaVacunacion(int tamTabla) {

}

THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion& orig) {
}

THashTarjetaVacunacion::~THashTarjetaVacunacion() {
}

/* METODOS */


bool THashTarjetaVacunacion::insertar(unsigned long clave, TarjetaVacunacion &pal) {

}

bool THashTarjetaVacunacion::buscar(unsigned long clave, std::string &id, TarjetaVacunacion &pal) {

}

bool THashTarjetaVacunacion::borrar(unsigned long clave, std::string &id) {

}

unsigned int THashTarjetaVacunacion::numPalabras() {

}

/**
 * @brief redispersa la tabla a un nuevo tamaño tam
 * @param tam
 */
void THashTarjetaVacunacion::redispersar(unsigned tam) {

}

/* METODOS DE PRUEBA */

/**
 * @brief devuelve el número máximo de colisiones que se han producido 
 * en la operación de inserción más costosa realizada sobre la tabla.
 * @return 
 */
unsigned int THashTarjetaVacunacion::maxColisiones() {

}

/**
 * @brief devuelve el número de veces que se superan 10 colisiones 
 * al intentar realizar la operación de inserción sobre la tabla de un dato.
 * @return 
 */
unsigned int THashTarjetaVacunacion::numMax10() {

}

/**
 * @brief devuelve el promedio de colisiones por operación de inserción realizada sobre la tabla.

 * @return 
 */
unsigned int THashTarjetaVacunacion::promedioColisiones() {

}

/**
 * @brief devuelve el factor de carga de la tabla de dispersión.
 * @return 
 */
float THashTarjetaVacunacion::factorCarga() {

}

/**
 * @brief devuelve el tam de la tabla de dispersion
 * @return 
 */
unsigned int tamTabla() {

}

/* OPERADORES*/

THashTarjetaVacunacion& THashTarjetaVacunacion::operator=(THashTarjetaVacunacion &thash) {

}

/* GETTERS Y SETTERS */