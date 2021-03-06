
/* 
 * File:   Usuario.h
 * Author: Pedro
 *
 * Created on 5 de octubre de 2021, 22:29
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <vector>
#include <complex>
#include "Dosis.h"

/* STRUCT DE COORDENADAS UTM */
struct UTM {
    double latitud = 0;
    double longitud = 0;

    UTM() = default;

    UTM(double _lat, double _long);

    double calcularDistancia(UTM pos);

    friend std::ostream &operator<<(std::ostream &os, const UTM &obj) {
        std::cout << "- Latitud: " << obj.latitud << std::endl
                  << "- Longitud: " << obj.longitud << std::endl;
        return os;
    }
};

/* DEFINICION DE LA CLASE USUARIO */
class Usuario {
private:
    std::string nombre = " ";
    std::string apellidos = " ";
    std::string NSS = " ";
    Fecha fechaNacimiento;
    UTM docimicilio;

public:
    /* CONSTRUCTORES */

    Usuario() = default;

    Usuario(std::string NSS);

    Usuario(std::string nombre, std::string apellidos, std::string NSS, Fecha fechaNacimiento, UTM docimicilio);

    Usuario(const Usuario &orig);

    virtual ~Usuario();

    /* METODOS */

    int edad();

    /* OPERADORES*/

    bool operator==(const Usuario &right) const;

    Usuario &operator=(const Usuario &right);

    bool operator<(const Usuario &right) const;

    friend std::ostream &operator<<(std::ostream &os, const Usuario &obj);

    /* GETTERS Y SETTERS */

    std::string GetNSS() const;

    void SetNSS(std::string NSS);

    std::string GetApellidos() const;

    void SetApellidos(std::string apellidos);

    UTM GetDocimicilio() const;

    void SetDocimicilio(UTM docimicilio);

    Fecha GetFechaNacimiento() const;

    void SetFechaNacimiento(Fecha fechaNacimiento);

    std::string GetNombre() const;

    void SetNombre(std::string nombre);

};

inline std::ostream &operator<<(std::ostream &os, const Usuario &obj) {
    std::cout << "- Nombre: " << obj.nombre + " " + obj.apellidos << endl
              << "- NSS: " << obj.NSS << endl
              << "- Fecha nac: " << obj.fechaNacimiento << endl;
    //std::cout << "- Dosis: " << endl << obj.dosis;
    return os;
}

#endif /* USUARIO_H */

