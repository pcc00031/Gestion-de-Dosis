
/* 
 * File:   DosisNoSuministradas.h
 * Author: Pedro Corpas
 *
 * Created on 21 de noviembre de 2021, 12:20
 */

#ifndef DOSISNOSUMINISTRADAS_H
#define DOSISNOSUMINISTRADAS_H

using namespace std;

class DosisNoSuministradas : public exception {
public:

    const char *what() const throw() {
        return "Las dosis no han sido suministradas";
    }
};

#endif /* DOSISNOSUMINISTRADAS_H */


