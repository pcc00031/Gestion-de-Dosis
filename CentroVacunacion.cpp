
/* 
 * File:   CentroVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "GestionVacunas.h"
#include "excepciones/UsuarioNoEncontrado.h"
#include "excepciones/NoQuedanDosis.h"
#include "excepciones/TarjetaNoAgregada.h"
#include "excepciones/DosisNoSuministradas.h"

/* CONSTRUCTORES */

CentroVacunacion::CentroVacunacion(int id, UTM direccion) :
id(id), direccion(direccion) {
}

CentroVacunacion::CentroVacunacion(const CentroVacunacion& orig) :
direccion(orig.direccion), dosis(orig.dosis), tarjetas(orig.tarjetas), id(orig.id), gv(orig.gv) {
}

CentroVacunacion::~CentroVacunacion() {
}

/* METODOS */

/**
 * @brief Agrega un usuario a la lista del centro
 * @param u
 */
void CentroVacunacion::anadirTarjetaLista(TarjetaVacunacion *t) {
    tarjetas.push_front(t);
    if (tarjetas.front()->getId() != t->getId()) {
        throw TarjetaNoAgregada();
    }
}

/**
 * @brief Administra una dosis a un usuario
 * @post Administra una dosis que este en el almacen
 * y que, a priori, sea compatible con la edad del usuario
 * @param u
 * @param fab
 * @return true: si la dosis es compatible con el usuario
 * false: si no es compatible
 */
bool CentroVacunacion::administrarDosis(TarjetaVacunacion *t, Fabricante fab) {
    Usuario *u = t->GetTarjetaUsuario();

    // En primer lugar comprobamos que el usuario se ha agregado a la lista
    if (u == nullptr || tarjetas.front() != t)
        throw UsuarioNoEncontrado();

    // Si es menor de 13 anios o ya tiene pauta completa
    if (u->edad() < 13 || t->dosisPorAdministrar() == 0)
        return false;

    // comprobamos que existan dosis en el almacen
    if (verDosisRestantes() == 0) {
        if (!gv->isQuedanVacunas())
            throw NoQuedanDosis();
        alarmaFaltaDosis(t->getDosisRecomendable()); // si no existen y quedan vacunas por leer, salta alarma
        gv->vacunarUsuario(t); // intentamos vacunar de nuevo //FIXME cambiar a administrarDosis()
    }

    // En otro caso, realizamos el proceso de vacunacion normal  
    multimap<std::string, Dosis>::iterator it;
    it = dosis.begin();
    while (it != dosis.end()) {
        if (it->second.GetFabricante() == fab && it->second.getEstado() == Estado::enAlmacen) {
            t->addDosis(&it->second);
            it->second.setEstado(Estado::administrada);
            this->tarjetas.pop_front(); // borramos al usuario de la lista      
            //std::cout << "vacunado: " << u->GetNSS() << " en centro: " << this->id << std::endl;
            if (t->dosisPorAdministrar() == 0) // asignamos pauta completa (por defecto 'false')
                t->SetPautaCompleta(true);
            return true;
        }
        ++it;
    }

    // Si no encontramos dosis compatibles, administramos la primera que encontremos en almacen
    it = dosis.begin();
    while (it != dosis.end()) {
        if (it->second.getEstado() == Estado::enAlmacen) {
            t->addDosis(&it->second);
            it->second.setEstado(Estado::administrada);
            this->tarjetas.pop_front(); // borramos al usuario de la lista  
            //std::cout << "vacunado: " << u->GetNSS() << " en centro: " << this->id << std::endl;
            if (t->dosisPorAdministrar() == 0) // asignamos pauta completa (por defecto 'false')
                t->SetPautaCompleta(true);
            return false;
        }
        ++it;
    }
    return false;
}

/**
 * @brief Muestra las dosis restantes de un fabricante en el almacen
 * @param f
 * @return numero de rosis restantes
 */
int CentroVacunacion::numVacunasTipo(Fabricante f) {
    Dosis aux; // para convertir fabricante a string
    int cont = 0;
    multimap<std::string, Dosis>::iterator it;
    it = dosis.begin();
    while (it != dosis.end()) {
        if (it->first == aux.fabToString(f) && it->second.getEstado() == Estado::enAlmacen)
            cont++;
        ++it;
    }
    return cont;
}

/**
 * @brief Recibe 100 nuevas dosis
 */
void CentroVacunacion::anadirNDosisAlmacen(vector<Dosis> &packDosis) {
    long unsigned int tamDosis = dosis.size();
    for (int i = 0; i < packDosis.size(); i++) {
        this->dosis.insert(pair<std::string, Dosis>(packDosis[i].fabToString(packDosis[i].GetFabricante()), packDosis[i]));
    }
    if (tamDosis + packDosis.size() != dosis.size())
        throw DosisNoSuministradas();
    std::cout << " - Dosis suministradas en centro " << this->id << ": " << packDosis.size() << std::endl;
}

/**
 * @brief Notifica si faltan dosis de un tipo en concreto
 * @param f
 */
void CentroVacunacion::alarmaFaltaDosis(Fabricante f) {
    std::cout << "- ALARMA: no quedan dosis de " << f << " en el centro " << this->id << std::endl;
    gv->suministrarNDosisAlCentro(this, 100);
}

/**
 * @brief Muestra las dosis restantes
 * @return numero de rosis restantes
 */
int CentroVacunacion::verDosisRestantes() {
    int cont = 0;
    multimap<std::string, Dosis>::iterator it;
    it = dosis.begin();
    while (it != dosis.end()) {
        if (it->second.getEstado() == Estado::enAlmacen)
            cont++;
        ++it;
    }
    return cont;
}

/* OPERADORES*/

CentroVacunacion & CentroVacunacion::operator=(const CentroVacunacion & right) {
    this->direccion = right.direccion;
    this->dosis = right.dosis;
    this->id = right.id;
    this->tarjetas = right.tarjetas;
    this->gv = right.gv;

    return *this;
}

bool CentroVacunacion::operator==(const CentroVacunacion & right) const {
    if (this->id == right.id) {
        return true;
    } else return false;
}

/* GETTERS Y SETTERS */

UTM CentroVacunacion::getDireccion() const {

    return direccion;
}

void CentroVacunacion::setDireccion(UTM direccion) {

    this->direccion = direccion;
}

int CentroVacunacion::getId() const {

    return id;
}

void CentroVacunacion::setId(int id) {
    this->id = id;
}

void CentroVacunacion::setGv(GestionVacunas * gv) {
    this->gv = gv;
}
