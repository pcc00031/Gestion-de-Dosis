
/* 
 * File:   CentroVacunacion.cpp
 * Author: Pedro Corpas
 */

#include "CentroVacunacion.h"
#include "GestionVacunas.h"

/* CONSTRUCTORES */

CentroVacunacion::CentroVacunacion() {
}

CentroVacunacion::CentroVacunacion(int id, UTM direccion) :
id(id), direccion(direccion) {
}

CentroVacunacion::CentroVacunacion(const CentroVacunacion& orig) :
direccion(orig.direccion), dosis(orig.dosis), usuarios(orig.usuarios), id(orig.id), gv(orig.gv) {
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

    // En primer lugar comprobamos que el usuario se ha agregadoa a la lista
    if (this->usuarios.front() != &u) {
        return false;
    }
    // Si es menor de 13 anios o tiene ya 3 dosis no se suministra ninguna dosis
    if (u.edad() < 13 || u.getDosis().size() >= 3) {
        return false;
        // En otro caso, realizamos el proceso de vacunacion normal
    } else {
        multimap<std::string, Dosis>::iterator it;
        it = dosis.begin();
        while (it != dosis.end()) {
            if (it->second.GetFabricante() == fab && it->second.getEstado() == Estado::enAlmacen) {
                u.addDosis(&it->second);
                //gv->actualizarUsuario(u);
                it->second.setEstado(Estado::administrada);
                this->usuarios.pop_front(); // borramos al usuario de la lista              
                return true;
            }
            ++it;
        }
        // Si no encontramos dosis compatibles, administramos la primera que encontremos en almacen
        it = dosis.begin();
        while (it != dosis.end()) {
            if (it->second.getEstado() == Estado::enAlmacen) {
                u.addDosis(&it->second);
                it->second.setEstado(Estado::administrada);
                this->usuarios.pop_front(); // borramos al usuario de la lista              
                return false;
            }
            ++it;
        }
        // Si no quedan dosis de ningun tipo en el almacen, salta la alarma

//        alarmaFaltaDosis();
//        administrarDosis(u, u.getDosisRecomendable()); // Tras la alarma el centro recibe 100 nuevas dosis
        //TODO controlar que pasa si no llegan dosis nuevas
        return false;
    }
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
void CentroVacunacion::anadir100DosisAlmacen(vector<Dosis> d) {
    for (int i = 0; i < d.size(); i++) {
        this->dosis.insert(pair<std::string, Dosis>(d[i].fabToString(d[i].GetFabricante()), d[i]));
    }
}

/**
 * @brief Notifica si faltan dosis de un tipo en concreto
 * @param f
 */
void CentroVacunacion::alarmaFaltaDosis() {
    gv->suministrar100DosisAlCentro(*this); //FIXME ignorar fabricante f (pdf)
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
    this->usuarios = right.usuarios;
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
