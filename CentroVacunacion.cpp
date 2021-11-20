
/* 
 * File:   CentroVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "GestionVacunas.h"

/* CONSTRUCTORES */

CentroVacunacion::CentroVacunacion() {
}

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
    //FIXME pasaporte covid?
    if (u == nullptr) // comprobacion previa
        return false;

    // En primer lugar comprobamos que el usuario se ha agregado a la lista
    if (tarjetas.front() != t)
        return false;

    // Si es menor de 13 anios o tiene ya 3 dosis no se suministra ninguna dosis
    if (u->edad() < 13 || t->getDosis().size() >= 3) {
        return false;
        // En otro caso, realizamos el proceso de vacunacion normal
    } else {
        multimap<std::string, Dosis>::iterator it;
        it = dosis.begin();
        while (it != dosis.end()) {
            if (it->second.GetFabricante() == fab && it->second.getEstado() == Estado::enAlmacen) {
                t->addDosis(&it->second);
                it->second.setEstado(Estado::administrada);
                this->tarjetas.pop_front(); // borramos al usuario de la lista      
                //std::cout << "vacunado: " << u->GetNSS() << " en centro: " << this->id << std::endl;
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
                return false;
            }
            ++it;
        }
        // Si no quedan dosis de ningun tipo en el almacen, salta la alarma
        if (gv->isQuedanVacunas()) {
            alarmaFaltaDosis(t->getDosisRecomendable());
            //            it = dosis.begin();
            //            bool nuevasDosis = false;
            //            while (it != dosis.end()) { // comprobamos si el centro ha recibido dosis nuevas
            //                if (it->second.getEstado() == Estado::enAlmacen) {
            //                    nuevasDosis == true;
            //                }
            //                ++it;
            //            }
            //            if(nuevasDosis)
            //                administrarDosis(u, u->getDosisRecomendable());
        }
        it = dosis.begin();
        int cont = 0;
        while (it != dosis.end()) { // comprobamos si el centro ha recibido dosis nuevas
            if (it->second.getEstado() == Estado::enAlmacen) {
                cont++;
            }
            ++it;
        }
        //        std::cout << "mira: " << cont << std::endl;
        //        administrarDosis(u, u->getDosisRecomendable());
        return false;
    }
    // problema de nuestra implementacion: 
    // realizamos hasta 3 bucles para comprobar si hay dosis en almacen
    // ventaja: estan todas las situaciones controladas
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
    for (int i = 0; i < packDosis.size(); i++) {
        this->dosis.insert(pair<std::string, Dosis>(packDosis[i].fabToString(packDosis[i].GetFabricante()), packDosis[i]));
    }
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

void CentroVacunacion::setGv(GestionVacunas* gv) {
    this->gv = gv;
}
