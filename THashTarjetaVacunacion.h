
/* 
 * File:   THashTarjetaVacunacion.h
 * Author: Pedro
 *
 * Created on 17 de noviembre de 2021, 16:17
 */

#ifndef THASHTARJETAVACUNACION_H
#define THASHTARJETAVACUNACION_H

#include "TarjetaVacunacion.h"

class THashTarjetaVacunacion {
public:
    THashTarjetaVacunacion();
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(const THashTarjetaVacunacion& orig);
    virtual ~THashTarjetaVacunacion();

    /* METODOS */

    bool insertar(unsigned long clave, TarjetaVacunacion &pal); //TODO todo HASH
    bool buscar(unsigned long clave, std::string &id, TarjetaVacunacion &pal);
    bool borrar(unsigned long clave, std::string &id);
    unsigned int numPalabras();
    void redispersar(unsigned tam);

    /* METODOS DE PRUEBA */

    unsigned int maxColisiones();
    unsigned int numMax10();
    unsigned int promedioColisiones();
    float factorCarga();
    unsigned int tamTabla();

    /* OPERADORES */

    THashTarjetaVacunacion& operator=(THashTarjetaVacunacion &thash);
};

#endif /* THASHTARJETAVACUNACION_H */

