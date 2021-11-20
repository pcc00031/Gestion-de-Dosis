
/* 
 * File:   TarjetaVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "TarjetaVacunacion.h"

/* CONSTRUCTORES */

TarjetaVacunacion::TarjetaVacunacion() {
}

TarjetaVacunacion::TarjetaVacunacion(const TarjetaVacunacion& orig) {
}

TarjetaVacunacion::~TarjetaVacunacion() {
}

/* METODOS */

UTM TarjetaVacunacion::getDomicilio() {

}

std::vector<Dosis*> TarjetaVacunacion::getDosis() {

}

std::string TarjetaVacunacion::pasaporteCovidCode(bool valido) {

}

Fabricante TarjetaVacunacion::getDosisRecomendable() {

}

/* GETTERS Y SETTERS */

void TarjetaVacunacion::SetTarjetaUsuario(Usuario* tarjetaUsuario) {
    this->tarjetaUsuario = tarjetaUsuario;
}

Usuario* TarjetaVacunacion::GetTarjetaUsuario() const {
    return tarjetaUsuario;
}

void TarjetaVacunacion::SetIdCentroCercano(int idCentroCercano) {
    this->idCentroCercano = idCentroCercano;
}

int TarjetaVacunacion::GetIdCentroCercano() const {
    return idCentroCercano;
}

void TarjetaVacunacion::SetPautaCompleta(bool pautaCompleta) {
    this->pautaCompleta = pautaCompleta;
}

bool TarjetaVacunacion::IsPautaCompleta() const {
    return pautaCompleta;
}

void TarjetaVacunacion::SetId(int id) {
    this->id = id;
}

int TarjetaVacunacion::GetId() const {
    return id;
}