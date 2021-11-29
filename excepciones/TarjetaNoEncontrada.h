
/* 
 * File:   TarjetaNoEncontrada.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 11:19
 */

#ifndef TARJETANOENCONTRADA_H
#define TARJETANOENCONTRADA_H

#include <exception>

using namespace std;

class TarjetaNoEncontrada {
public:

    const char *what() const throw() {
        return "La tarjeta no ha sido encontrado";
    }
};

#endif /* TARJETANOENCONTRADA_H */


