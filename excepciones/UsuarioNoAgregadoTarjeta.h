
/* 
 * File:   UsuarioNoAgregadoTarjeta.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 12:16
 */

#ifndef USUARIONOAGREGADOTARJETA_H
#define USUARIONOAGREGADOTARJETA_H

using namespace std;

class UsuarioNoAgregadoTarjeta : public exception {
public:

    const char* what() const throw () {
        return "El usuario no ha sido agregado a la tarjeta";
    }
};

#endif /* USUARIONOAGREGADOTARJETA_H */


