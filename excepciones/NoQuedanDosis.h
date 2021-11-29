
/* 
 * File:   NoQuedanDosis.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 11:55
 */

#ifndef NOQUEDANDOSIS_H
#define NOQUEDANDOSIS_H

#include <exception>

using namespace std;

class NoQuedanDosis : public exception {
public:

    const char *what() const throw() {
        return "No quedan dosis en el almacen";
    }
};

#endif /* NOQUEDANDOSIS_H */


