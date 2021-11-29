
/* 
 * File:   THashTarjetaVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "THashTarjetaVacunacion.h"

/* CONSTRUCTORES */

THashTarjetaVacunacion::THashTarjetaVacunacion() {
}

/**
 * @brief Constructor parametrizado
 * @param tamTabla
 * @param _th
 */
THashTarjetaVacunacion::THashTarjetaVacunacion(unsigned long tamTabla, int _th) :
tamaf(tamTabla), tabla(tamaf, Entrada()),
tamal(0), maxCol(0), max10(0), sumaColisiones(0), th(_th) {
    prelativo = primo_menor(tamaf);
};

/**
 * @brief Constructor copia
 * @param orig
 */
THashTarjetaVacunacion::THashTarjetaVacunacion(const THashTarjetaVacunacion &orig) :
tamaf(orig.tamaf), tabla(orig.tabla),
tamal(orig.tamal), maxCol(orig.maxCol),
max10(orig.max10), sumaColisiones(orig.sumaColisiones),
th(orig.th), prelativo(orig.prelativo) {
};

/**
 * @brief Destructor
 */
THashTarjetaVacunacion::~THashTarjetaVacunacion() {
    tabla.erase(tabla.begin(), tabla.end());
}

/* METODOS DE ENTRENAMIENTO */

/* NUMEROS PRIMOS */

/**
 * @brief Confirma si un numero es primo o no
 * @param n
 * @return 
 */
bool THashTarjetaVacunacion::esprimo(unsigned n) {
    for (unsigned i = 2; i <= n / 2; ++i)
        if (n % i == 0)
            return false;
    return true;
}

/**
 * @brief Calcula el primo anterior a un numero 
 * @param numero
 * @return 
 */
int THashTarjetaVacunacion::primo_menor(unsigned numero) {
    int i = numero - 1;
    while (!esprimo(i)) {
        --i;
    }
    return i;
}

/**
 * @brief Funcion Hash1 - dispersion doble
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash1(unsigned long clave, int intento) {
    unsigned long posicionfinal;
    // peor FUNCION DE DISPERSION 1
    posicionfinal = (clave + (intento * intento)) % tamaf;
    return posicionfinal;
};

/**
 * @brief Funcion Hash2 - dispersion doble
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash2(unsigned long clave, int intento) {
    unsigned long posicion, posicionfinal;

    posicion = clave % tamaf; //  FUNCION DE DISPERSION 2       
    posicionfinal = (posicion + (intento * (prelativo - (clave % (prelativo))))) % tamaf;
    return posicionfinal;
}

/**
 * @brief Funcion Hash3 - dispersion cuadratica
 * @param str
 * @param intento
 * @return 
 */
unsigned long THashTarjetaVacunacion::hash3(unsigned long clave, int intento) {
    unsigned long posicion, posicionfinal;

    posicion = clave % tamaf; //  FUNCION DE DISPERSION 3       
    posicionfinal = (posicion + (intento * (1 + (clave % (prelativo))))) % tamaf;
    return posicionfinal;
}

/* METODOS */

/**
 * @brief Inserta una tarjeta no repetida en la tabla
 * siguiendo la funcion Hash1
 * @param clave
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::insertar(unsigned long clave, TarjetaVacunacion &t) {
    unsigned intento = 0, pos;
    bool encontrado = false;

    while (!encontrado) {
        if (th == 0)
            pos = hash1(clave, intento);
        else
            if (th == 1)
            pos = hash2(clave, intento);
        else
            pos = hash3(clave, intento);

        if (tabla[pos].marca == Marca::Libre || tabla[pos].marca == Marca::Disponible) {
            tamal++;
            tabla[pos].id = t.getId();
            tabla[pos].dato = t;
            tabla[pos].marca = Marca::Ocupada;
            tabla[pos].clave = clave;

            encontrado = true; //Encontre un sitio libre  
        } else {
            intento++; //No he dado aun con una posicion libre
        }
    }
    if (pos > maxCol) {
        maxCol = intento;
    }
    if (intento > 10)
        max10++;
    //std::cout << "Intentos " << i << std::endl; 
    sumaColisiones += intento;

    return encontrado;
}

/**
 * @brief Busca un elemento en la tabla
 * @param clave
 * @param id
 * @param t
 * @return 
 */
bool THashTarjetaVacunacion::buscar(unsigned long clave, std::string &id, TarjetaVacunacion* &t) {
    unsigned intento = 0, pos = 0;
    bool enc = false;
    while (!enc) {
        if (th == 0)
            pos = hash1(clave, intento);
        else
            if (th == 1)
            pos = hash2(clave, intento);
        else
            pos = hash3(clave, intento);

        if (tabla[pos].marca == Marca::Ocupada && tabla[pos].id == id) {
            //  cout << std::endl << "Buscado con " << i << " intentos." << std::endl;                    
            t = &(tabla[pos].dato);
            enc = true;
        } else {
            if (tabla[pos].marca == Marca::Libre) {
                t = 0;
                break;
            } else
                ++intento; //No he dado aun con su posicion
        }
    }
    return enc;
}

/**
 * @brief Borra un elemento de la tabla
 * @param clave
 * @param id
 * @return 
 */
bool THashTarjetaVacunacion::borrar(unsigned long clave, std::string &id) {
    unsigned intento = 0, pos = 0;
    bool finaliza = false;
    while (!finaliza) {
        if (th == 0)
            pos = hash1(clave, intento);
        else
            if (th == 1)
            pos = hash2(clave, intento);
        else
            pos = hash3(clave, intento);

        if (tabla[pos].marca == Marca::Ocupada && tabla[pos].id == id) {
            //  cout << std::endl << "Borrado con " << i << " intentos." << std::endl;
            tabla[pos].marca = Marca::Disponible; //lo encontre lo borro y salgo del bucle
            finaliza = true;
            tamal--;
        } else {
            if (tabla[pos].marca == Marca::Libre)
                break;
            else
                ++intento; //No he dado aun con su posicion
        }
    }
    return finaliza;
}

/**
 * @brief redispersa la tabla a un nuevo tamaño tam
 * @param tam
 */
void THashTarjetaVacunacion::redispersar(unsigned tam) {

    std::vector<Entrada> copia(tam, Entrada());
    tamaf = tam;
    maxCol = 0;
    max10 = 0;
    sumaColisiones = 0;
    prelativo = primo_menor(tamaf);
    for (int i = 0; i < tabla.size(); i++) {

        unsigned intento = 0, pos;
        bool encontrado = false;
        if (tabla[i].marca == Marca::Ocupada) {
            while (!encontrado) {
                if (th == 0)
                    pos = hash1(tabla[i].clave, intento);
                else
                    if (th == 1)
                    pos = hash2(tabla[i].clave, intento);
                else
                    pos = hash3(tabla[i].clave, intento);

                if (copia[pos].marca == Marca::Disponible) { // || aux[y].marca==2) {                 
                    copia[pos].dato = tabla[i].dato;
                    copia[pos].marca = Marca::Ocupada;
                    copia[pos].clave = tabla[i].clave;
                    copia[pos].dato = tabla[i].dato;
                    encontrado = true; //Encontre un sitio libre  
                } else
                    ++intento; //No he dado aun con una posicion libre
            }
            if (intento > maxCol) {
                maxCol = intento;
            }
            if (i > 10)
                max10++;
            //std::cout << "Intentos " << i << std::endl; 
            sumaColisiones += intento;

        }
    }
    tabla = copia;
}

/* METODOS DE PRUEBA */

/**
 * @brief devuelve el número máximo de colisiones que se han producido 
 * en la operación de inserción más costosa realizada sobre la tabla.
 * @return 
 */
unsigned int THashTarjetaVacunacion::maxColisiones() {
    return this->maxCol;
}

/**
 * @brief devuelve el número de veces que se superan 10 colisiones 
 * al intentar realizar la operación de inserción sobre la tabla de un dato.
 * @return 
 */
unsigned int THashTarjetaVacunacion::numMax10() {
    return max10;
}

/**
 * @brief devuelve el promedio de colisiones por operación de inserción realizada sobre la tabla.
 * @return 
 */
float THashTarjetaVacunacion::promedioColisiones() {
    return (float) sumaColisiones / tamal;
}

/**
 * @brief devuelve el factor de carga de la tabla de dispersión.
 * @return 
 */
float THashTarjetaVacunacion::factorCarga() {
    return (float) tamal / tamaf;
}

/**
 * @brief devuelve el tam de la tabla de dispersion
 * @return 
 */
unsigned int THashTarjetaVacunacion::getTamTabla() {
    return this->tamaf;
}

/**
 * @brief devuelve el numero de tarjetas
 * @return 
 */
unsigned int THashTarjetaVacunacion::numTarjetas() {
    return tamal;
};

/* OPERADORES*/

THashTarjetaVacunacion &THashTarjetaVacunacion::operator=(THashTarjetaVacunacion &thash) {

    if (this != &thash) {
        tamaf = thash.tamaf;
        tabla = thash.tabla;
        tamal = thash.tamal;
        maxCol = thash.maxCol;
        max10 = thash.max10;
        sumaColisiones = thash.sumaColisiones;
        th = thash.th;
        prelativo = thash.prelativo;
    }
    return *this;
}

/* GETTERS Y SETTERS */