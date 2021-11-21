
/* 
 * File:   Usuario.cpp
 * Author: Pedro Corpas
 */

#include "Usuario.h"

/* CONSTRUCTORES */
UTM::UTM(double _lat, double _long) :
latitud(_lat), longitud(_long) {
}

Usuario::Usuario(std::string NSS) :
NSS(NSS) {
}

Usuario::Usuario(std::string nombre, std::string apellidos, std::string NSS, Fecha fechaNacimiento, UTM docimicilio) :
nombre(nombre), apellidos(apellidos), NSS(NSS),
fechaNacimiento(fechaNacimiento), docimicilio(docimicilio) {
}

Usuario::Usuario(const Usuario& orig) :
nombre(orig.nombre), apellidos(orig.apellidos), NSS(orig.NSS),
fechaNacimiento(orig.fechaNacimiento), docimicilio(orig.docimicilio) {
}

Usuario::~Usuario() {
}

/* METODOS */

/**
 * @brief Calcular distancia entre dos puntos
 * @post La distancia entre dos puntos es la raiz cuadrada de la suma de los cuadrados de
 *           la latitudMayor menos la latitudMenor y la longitudMayor menos la longitudMenor
 * @param pos 
 * @return 
 */

double UTM::calcularDistancia(UTM pos) {
    double cateto1 = 0, cateto2 = 0, distanciaCuadrado = 0, distancia = 0,
            latitudMayor = 0, latitudMenor = 0, longitudMayor = 0, longitudMenor = 0;

    if (pos.latitud > this->latitud) {
        latitudMayor = pos.latitud;
        latitudMenor = this->latitud;
    }
    latitudMenor = pos.latitud;
    latitudMayor = this->latitud;

    if (pos.longitud > this->longitud) {
        longitudMayor = pos.longitud;
        longitudMenor = this->longitud;
    }
    longitudMenor = pos.longitud;
    longitudMayor = this->longitud;

    cateto1 = longitudMayor - longitudMenor;
    cateto2 = latitudMayor - latitudMenor;

    distanciaCuadrado = (cateto1 * cateto1) + (cateto2 * cateto2);

    distancia = sqrt(distanciaCuadrado);

    return distancia;
}

/**
 * @brief calculo de la edad de un usuario
 * @post en base a la fecha actual y la fecha de nacimiento
 * calculamos la edad del usuario
 * @return 
 */
int Usuario::edad() {
    Fecha f; // fecha actual
    // edad en un principio
    int edad = f.verAnio() - this->fechaNacimiento.verAnio();

    // calculo de la edad real en base al mes y dia de nacimiento
    if (this->fechaNacimiento.verMes() > f.verMes()) {
        return edad -= 1;
    } else if (this->fechaNacimiento.verMes() == f.verMes() && this->fechaNacimiento.verDia() < f.verDia()) {
        return edad -= 1;
    } else if (this->fechaNacimiento.verMes() == f.verMes() && this->fechaNacimiento.verDia() >= f.verDia()) {
        return edad;
    } else if (this->fechaNacimiento.verMes() < f.verMes()) {
        return edad;
    }
    return edad;
}

/* OPERADORES*/

Usuario& Usuario::operator=(const Usuario& right) {
    this->NSS = right.NSS;
    this->apellidos = right.apellidos;
    this->docimicilio = right.docimicilio;
    this->fechaNacimiento = right.fechaNacimiento;
    this->nombre = right.nombre;
    return *this;
}

bool Usuario::operator==(const Usuario& right) const {
    if (this->NSS == right.NSS) {
        return true;
    } else return false;
}

bool Usuario::operator<(const Usuario& right) const {
    return right.NSS > this->NSS;
}

/* GETTERS Y SETTERS */

std::string Usuario::GetNSS() const {
    return NSS;
}

void Usuario::SetNSS(std::string NSS) {
    this->NSS = NSS;
}

std::string Usuario::GetApellidos() const {
    return apellidos;
}

void Usuario::SetApellidos(std::string apellidos) {
    this->apellidos = apellidos;
}

UTM Usuario::GetDocimicilio() const {
    return docimicilio;
}

void Usuario::SetDocimicilio(UTM docimicilio) {
    this->docimicilio = docimicilio;
}

Fecha Usuario::GetFechaNacimiento() const {
    return fechaNacimiento;
}

void Usuario::SetFechaNacimiento(Fecha fechaNacimiento) {
    this->fechaNacimiento = fechaNacimiento;
}

std::string Usuario::GetNombre() const {
    return nombre;
}

void Usuario::SetNombre(std::string nombre) {
    this->nombre = nombre;
}
