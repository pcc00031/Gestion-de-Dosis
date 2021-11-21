
/* 
 * File:   DosisNoAdministrada.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 12:12
 */

#ifndef DOSISNOADMINISTRADA_H
#define DOSISNOADMINISTRADA_H


using namespace std;

class DosisNoAdministrada : public exception {
public:

    const char* what() const throw () {
        return "La dosis no ha sido administrada";
    }
};

#endif /* DOSISNOADMINISTRADA_H */


