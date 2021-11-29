
/* 
 * File:   CentroNoEncontrado.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 11:14
 */


#ifndef CENTRONOENCONTRADO_H
#define CENTRONOENCONTRADO_H

using namespace std;

class CentroNoEncontrado : public exception {
public:

    const char *what() const throw() {
        return "El centro no ha sido encontrado";
    }
};

#endif /* CENTRONOENCONTRADO_H */


