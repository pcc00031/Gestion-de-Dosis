
/* 
 * File:   Dosis.cpp
 * Author: Pedro Corpas
 * 
 * Created on 21 de septiembre de 2021, 16:44
 */

#include "Dosis.h"

/* CONSTRUCTORES */

Dosis::Dosis() {
    this->estado = Estado::enAlmacen;
}

Dosis::Dosis(int id, int idLote, Fecha fechaFabricacion, Fecha fechaCaducidad) :
id(id), idLote(idLote), fechaFabricacion(fechaFabricacion), fechaCaducidad(fechaCaducidad) {
    this->estado = Estado::enAlmacen;
}

Dosis::Dosis(const Dosis& orig) :
id(orig.id), fabricante(orig.fabricante), idLote(orig.idLote),
fechaCaducidad(orig.fechaCaducidad), fechaFabricacion(orig.fechaFabricacion), estado(orig.estado) {
}

/* METODOS */

string Dosis::fabToString(const Fabricante &f) {
    string fab;
    switch (f) {
        case Fabricante::Pfizer: fab = "Pfizer";
            break;
        case Fabricante::Moderna: fab = "Moderna";
            break;
        case Fabricante::AstraZeneca: fab = "AstraZeneca";
            break;
        case Fabricante::Johnson: fab = "Johnson";
            break;
    }
    return fab;
}

/* OPERADORES */

Dosis& Dosis::operator=(const Dosis& right) {

    this->id = right.id;
    this->fabricante = right.fabricante;
    this->fechaCaducidad = right.fechaCaducidad;
    this->fechaFabricacion = right.fechaFabricacion;
    this->idLote = right.idLote;
    this->estado = right.estado;

    return *this;
}

bool Dosis::operator!=(const Dosis& right) const {
    if (this->id == right.id) {
        return false;
    } else return true;
}

bool Dosis::operator<(const Dosis& right) const {

    return right.fechaFabricacion > this->fechaFabricacion;
}

bool Dosis::operator<=(const Dosis& right) const {

    return right.id >= this->id; // Reuse greater than operator
}

bool Dosis::operator==(const Dosis& right) const {
    if (this->id == right.id) {
        return true;
    } else return false;
}

bool Dosis::operator>(const Dosis& right) const {

    return right.fechaFabricacion < this->fechaFabricacion;
}

bool Dosis::operator>=(const Dosis& right) const {

    return right.id <= this->id; // Reuse greater than operator
}

/* GETTERS Y SETTERS */

Fecha Dosis::GetFechaCaducidad() const {

    return fechaCaducidad;
}

void Dosis::SetFechaCaducidad(Fecha fechaCaducidad) {

    this->fechaCaducidad = fechaCaducidad;
}

Fecha Dosis::GetFechaFabricacion() const {

    return fechaFabricacion;
}

void Dosis::SetFechaFabricacion(Fecha fechaFabricacion) {

    this->fechaFabricacion = fechaFabricacion;
}

int Dosis::GetId() const {

    return id;
}

void Dosis::SetId(int id) {

    this->id = id;
}

int Dosis::GetIdLote() const {

    return idLote;
}

void Dosis::SetIdLote(int idLote) {

    this->idLote = idLote;
}

Fabricante Dosis::GetFabricante() const {

    return fabricante;
}

void Dosis::SetFabricante(Fabricante fabricante) {

    this->fabricante = fabricante;
}

Estado Dosis::getEstado() const {

    return estado;
}

void Dosis::setEstado(Estado estado) {

    this->estado = estado;
}

Dosis::~Dosis() {
}
