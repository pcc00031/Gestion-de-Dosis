
/* 
 * File:   UsuarioNoEncontrado.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 9:25
 */



#ifndef USUARIONOENCONTRADO_H
#define USUARIONOENCONTRADO_H

#include <exception>

using namespace std;

class UsuarioNoEncontrado : public exception {
public:

    const char *what() const throw() {
        return "El usuario no ha sido encontrado";
    }
};

#endif /* USUARIONOENCONTRADO_H */
