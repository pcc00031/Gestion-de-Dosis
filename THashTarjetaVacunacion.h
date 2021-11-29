
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

/* ENUM CLASS PARA MARCAR LA TABLA */
enum class Marca {
    Libre, Ocupada, Disponible
};

class THashTarjetaVacunacion {
private:

    class Entrada {
    public:
        unsigned long clave;
        std::string id;
        Marca marca;
        TarjetaVacunacion dato;

        Entrada() : marca(Marca::Libre), clave(0), id(""), dato(TarjetaVacunacion()) {
        }

        ~Entrada() {
        };
    };

    int th;
    unsigned long tamaf;
    unsigned long tamal;
    unsigned long maxCol;
    unsigned long max10;
    unsigned long sumaColisiones;
    unsigned long prelativo;
    std::vector<Entrada> tabla;

    /* FUNCIONES DE DISPERSION */

    unsigned long hash1(unsigned long clave, int intento);
    unsigned long hash2(unsigned long clave, int intento);
    unsigned long hash3(unsigned long clave, int intento);

    /* FUNCIONES DE NUMEROS PRIMOS */

    bool esprimo(unsigned n);
    int primo_menor(unsigned numero);

public:

    /* CONSTRUCTORES */

    THashTarjetaVacunacion();
    THashTarjetaVacunacion(unsigned long tamTabla, int _th);
    THashTarjetaVacunacion(const THashTarjetaVacunacion &orig);
    virtual ~THashTarjetaVacunacion();

    /* METODOS */

    bool insertar(unsigned long clave, TarjetaVacunacion &t);
    bool buscar(unsigned long clave, std::string &id, TarjetaVacunacion* &t);
    bool borrar(unsigned long clave, std::string &id);
    void redispersar(unsigned tam);

    /* METODOS DE PRUEBA */

    unsigned int maxColisiones();
    unsigned int numMax10();
    float promedioColisiones();
    float factorCarga();
    unsigned int getTamTabla();
    unsigned int numTarjetas();

    /* OPERADORES */

    THashTarjetaVacunacion &operator=(THashTarjetaVacunacion &thash);
};

#endif /* THASHTARJETAVACUNACION_H */

