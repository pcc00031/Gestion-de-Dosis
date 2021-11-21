
/* 
 * File:   TarjetaVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "TarjetaVacunacion.h"
#include "excepciones/DosisNoAdministrada.h"
#include "excepciones/UsuarioNoAgregadoTarjeta.h"
#include "picosha2.h"

/* CONSTRUCTORES */

TarjetaVacunacion::TarjetaVacunacion(const TarjetaVacunacion& orig) :
id(orig.id), dosisAdministradas(orig.dosisAdministradas), idCentroCercano(orig.idCentroCercano),
pautaCompleta(orig.pautaCompleta), tarjetaUsuario(orig.tarjetaUsuario)
//,         pasaporte(orig.pasaporte) 
{
}

TarjetaVacunacion::~TarjetaVacunacion() {
}

/* METODOS */

/**
 * @brief Devuelve el domicilio del usuario
 * @return 
 */
UTM TarjetaVacunacion::getDomicilio() {
    return this->tarjetaUsuario->GetDocimicilio();
}

/**
 * @brief Devuelve las dosis administradas del usuario
 * @return 
 */
std::vector<Dosis*> TarjetaVacunacion::getDosis() {
    return this->dosisAdministradas;
}

/**
 * @brief Agrega una dosis al vector de dosis
 * @param d
 */
void TarjetaVacunacion::addDosis(Dosis *d) {
    this->dosisAdministradas.push_back(d);
    if (this->dosisAdministradas.at(dosisAdministradas.size() - 1)->GetId() != d->GetId())
        throw DosisNoAdministrada();
}

/**
 * @brief Genera un codigo de pasaporte covid 
 * @param valido
 * @return true si tiene pauta completa
 * @return false en caso de que no tener pauta completa y un codigo nulo
 */
std::string TarjetaVacunacion::pasaporteCovidCode(bool valido) {
    //FIXME esta bien?
    if (this->dosisAdministradas[0] == nullptr)
        throw DosisNoAdministrada();

    std::string hash = "";
    Dosis d;
    if (!valido) {
        //this->pasaporte = hash;
        return hash;
    }

    hash = picosha2::hash256_hex_string(this->id
            + d.fabToString(this->dosisAdministradas[0]->GetFabricante())
            + to_string(this->dosisAdministradas.size()));
    //this->pasaporte = hash;
    return hash;
}

/**
 * @brief Comprueba la dosis recomendable para el usuario
 * @return Dosis recomendable en base a su edad
 */
Fabricante TarjetaVacunacion::getDosisRecomendable() {
    int edad = tarjetaUsuario->edad();

    if (edad > 12 && edad <= 40) {
        return Fabricante::Johnson;
    } else if (edad > 40 && edad <= 50) {
        return Fabricante::Moderna;
    } else if (edad > 50 && edad <= 65) {
        return Fabricante::AstraZeneca;
    } else
        return Fabricante::Pfizer;
}

/**
 * @brief Indica el numero de vacunas por administrar
 * @return 
 */
int TarjetaVacunacion::dosisPorAdministrar() {
    Usuario *u = tarjetaUsuario;
    if (u->edad() < 13)
        return 0;
    if (u->edad() < 75)
        return 2 - this->dosisAdministradas.size();
    else return 3 - this->dosisAdministradas.size();
}

/* GETTERS Y SETTERS */

void TarjetaVacunacion::SetTarjetaUsuario(Usuario* tarjetaUsuario) {
    this->tarjetaUsuario = tarjetaUsuario;
    if (this->tarjetaUsuario->GetNSS() != tarjetaUsuario->GetNSS())
        throw UsuarioNoAgregadoTarjeta();
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

void TarjetaVacunacion::setId(std::string id) {
    this->id = id;
}

std::string TarjetaVacunacion::getId() const {
    return id;
}

//std::string TarjetaVacunacion::getPasaporte() const {
//    return pasaporte;
//}

/* OPERADORES */

TarjetaVacunacion& TarjetaVacunacion::operator=(const TarjetaVacunacion& right) {
    this->id = right.id;
    this->dosisAdministradas = right.dosisAdministradas;
    this->idCentroCercano = right.idCentroCercano;
    this->pautaCompleta = right.pautaCompleta;
    this->tarjetaUsuario = right.tarjetaUsuario;
    // this->pasaporte = right.pasaporte;

    return *this;
}

bool TarjetaVacunacion::operator==(const TarjetaVacunacion& right) const {
    if (this->id == right.id) {
        return true;
    } else return false;
}