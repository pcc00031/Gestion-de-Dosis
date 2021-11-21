
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

    unsigned int tamTabla1 = 16603;
    unsigned int tamTabla2 = 15013;

    unsigned int colisiones1 = 0;
    unsigned int colisiones2 = 0;
    unsigned int colisiones3 = 0;

    std::vector<int> intentos1;
    std::vector<int> intentos2;
    std::vector<int> intentos3;


    unsigned int contadorIntentos1 = 0;
    unsigned int contadorIntentos2 = 0;
    unsigned int contadorIntentos3 = 0;

    std::vector<int> medCol;

    typedef std::list<TarjetaVacunacion> ListaTarjetas;
    std::vector<ListaTarjetas> tabla;

    /* FUNCIONES DE DISPERSION */

    unsigned long hash1(unsigned long str, int intento);
    unsigned long hash20(unsigned long str, int intento);
    unsigned long hash30(unsigned long str, int intento);

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
    unsigned int numPalabras();
    void redispersar(unsigned tam);

    /* METODOS DE PRUEBA */

    unsigned int maxColisiones();
    unsigned int numMax10();
    unsigned int promedioColisiones();
    float factorCarga();
    unsigned int tamTabla();
    unsigned int numTarjetas();

    /* OPERADORES */

    THashTarjetaVacunacion& operator=(THashTarjetaVacunacion &thash);
};

#endif /* THASHTARJETAVACUNACION_H */

