
/* 
 * File:   TarjetaNoAgregada.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 12:06
 */

#ifndef TARJETANOAGREGADA_H
#define TARJETANOAGREGADA_H

#include <exception>

using namespace std;

class TarjetaNoAgregada {
public:

    const char *what() const throw() {
        return "La tarjeta no ha sido agregada a la lista";
    }
};

#endif /* TARJETANOAGREGADA_H */


