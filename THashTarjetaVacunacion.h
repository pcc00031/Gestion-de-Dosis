
/* 
 * File:   THashTarjetaVacunacion.h
 * Author: Pedro
 *
 * Created on 17 de noviembre de 2021, 16:17
 */

#ifndef THASHTARJETAVACUNACION_H
#define THASHTARJETAVACUNACION_H

#include "TarjetaVacunacion.h"
#include <vector>
#include <list>

class THashTarjetaVacunacion {
private:

    unsigned int tamTabla = 14713;
    unsigned int colisiones = 0;
    std::vector<int> intentos;
    unsigned int contadorIntentos = 0;

    std::vector<int> medCol;

    typedef std::list<TarjetaVacunacion> ListaTarjetas;
    std::vector<ListaTarjetas> tabla;

    /* FUNCIONES DE DISPERSION */

    unsigned long hash1(unsigned long str, int intento);
    unsigned long hash2(unsigned long str, int intento);
    unsigned long hash3(unsigned long str, int intento);

public:
    THashTarjetaVacunacion();
    THashTarjetaVacunacion(int tamTabla);
    THashTarjetaVacunacion(const THashTarjetaVacunacion& orig);
    virtual ~THashTarjetaVacunacion();

    /* METODOS */

    bool insertar1(unsigned long clave, TarjetaVacunacion &t);
    bool insertar2(unsigned long clave, TarjetaVacunacion &t);
    bool insertar3(unsigned long clave, TarjetaVacunacion &t);
    
    bool buscar(unsigned long clave, std::string &id, TarjetaVacunacion &t);
    bool borrar(unsigned long clave, std::string &id);
    void redispersar(unsigned tam);

    /* METODOS DE PRUEBA */

    unsigned int maxColisiones();
    unsigned int numMax10();
    unsigned int promedioColisiones();
    float factorCarga();
    unsigned int getTamTabla();
    unsigned int numTarjetas();

    /* OPERADORES */

    THashTarjetaVacunacion& operator=(THashTarjetaVacunacion &thash);
};

#endif /* THASHTARJETAVACUNACION_H */

