
/* 
 * File:   CentroVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "CentroVacunacion.h"

/* CONSTRUCTORES */

CentroVacunacion::CentroVacunacion() {
}

CentroVacunacion::CentroVacunacion(int id, UTM direccion) :
id(id), direccion(direccion) {
}

CentroVacunacion::CentroVacunacion(const CentroVacunacion& orig) {
}

CentroVacunacion::~CentroVacunacion() {
}

/* METODOS */

/**
 * @brief Metodo que carga dosis iniciales a un centro
 * @param d
 */
void CentroVacunacion::cargaDosis(vector<Dosis> d) {
    for (int i = 0; i < d.size(); i++) {
        this->dosis.insert(pair<std::string, Dosis>(d[i].fabToString(d[i].GetFabricante()), d[i]));
    }
    std::cout << " Dosis cargadas: " << this->dosis.size() << std::endl;
}

/**
 * @brief Agrega un usuario a la lista del centro
 * @param u
 */
void CentroVacunacion::anadirUsuarioLista(Usuario &u) {
    usuarios.push_back(&u);
}

/**
 * @brief Administra una dosis a un usuario
 * @post Administra una dosis que este en el almacen
 * y que sea compatible con la edad del usuario
 * @param u
 * @param fab
 * @return true: si la dosis es compatible con el usuario
 * false: si no es compatible
 */
bool CentroVacunacion::administrarDosis(Usuario &u, Fabricante fab) {

    // Si es menor de 13 anios no se suministra ninguna dosis
    if (u.edad() < 13) {
        return false;
        // En otro caso, realizamos el proceso de vacunacion normal
    } else {
        multimap<std::string, Dosis>::iterator it;
        it = dosis.begin();
        while (it != dosis.end()) {
            if (it->second.GetFabricante() == fab && it->second.getEstado() == Estado::enAlmacen) {
                u.addDosis(&it->second);
                it->second.setEstado(Estado::administrada);
                return true;
            } else {
                return false;
                //TODO si no hay dosis compatibles -> alarma?
            }
            ++it;
        }

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
 * @brief //FIXME  que?
 */
void CentroVacunacion::anadir100DosisAlmacen(){
    
}

/**
 * @brief Notifica si faltan dosis de un tipo en concreto
 * @param f
 */
void CentroVacunacion::alarmaFaltaDosis(Fabricante f){
    
}

/**
 * @brief Muestra las dosis restantes
 * @return numero de rosis restantes
 */
//int GestionVacunas::verDosisRestantes() {
//    int cont = 0;
//    for (int i = 0; i < this->dosis.tam(); i++) {
//
//        if (dosis[i].getEstado() == Estado::enAlmacen)
//            cont++;
//    }
//    return cont;
//}

/* OPERADORES*/

CentroVacunacion & CentroVacunacion::operator=(const CentroVacunacion & right) {
    this->direccion = right.direccion;
    this->dosis = right.dosis;
    this->id = right.id;
    this->usuarios = right.usuarios;
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
