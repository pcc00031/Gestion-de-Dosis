
/* 
 * File:   GestionVacunas.cpp
 * Author: Pedro Corpas
 */

#include "GestionVacunas.h"

/* CONSTRUCTORES */

/**
 * @brief Constructor por defecto del gestor
 * @post Inicializa dosis y usuarios con los ficheros
 * de texto predeterminados & ordena los vectores
 */
GestionVacunas::GestionVacunas() {
    cargarDosis("dosis2.txt");
    this->dosis.ordenar();
    cargarUsuarios("usuarios2.txt");
    this->listadoNSS.ordenar();
}

/**
 * @brief Constructor parametrizado
 * @post Inicializa los datos con un fichero pasado por parametro
 * @param nombreFichDosis
 * @param nombreFichUsuarios
 */
GestionVacunas::GestionVacunas(std::string nombreFichDosis, std::string nombreFichUsuarios) {
    cargarDosis(nombreFichDosis);
    this->dosis.ordenar();
    cargarUsuarios(nombreFichUsuarios);
    this->listadoNSS.ordenar();
}

/**
 * @brief Constructor copia 
 * @param orig
 */
GestionVacunas::GestionVacunas(const GestionVacunas& orig) :
usuarios(orig.usuarios), dosis(orig.dosis), listadoNSS(orig.listadoNSS) {
}

/*
 * @brief Destructor
 */
GestionVacunas::~GestionVacunas() {
}

/* METODOS */

/**
 * @brief Busca un usuario dado su nss
 * @param nss
 * @return una copia de dicho usuario
 */
Usuario* GestionVacunas::buscarUsuario(std::string nss) {
    Usuario u(nss);
    Usuario *usu = nullptr;
    if (usuarios.buscaR(u, usu)) {
        return usu;
    }
    return usu;
}

/**
 * @brief Busca vacunas de un fabricante
 * y segun su estado
 * @param f
 * @return posicion de dicha vacuna
 * @return -1 en caso de no encontrarla
 */
int GestionVacunas::buscarVacunas(Fabricante &f, Estado & e) {
    for (int i = 0; i < dosis.tam(); i++) {
        if (dosis[i].GetFabricante() == f && dosis[i].getEstado() == e) {
            return i;
        }
    }
    return -1;
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
bool GestionVacunas::administrarDosis(Usuario &u, Fabricante fab) {

    // Si es menor de 13 anios o no se encuentra dentro de los usuarios
    // no se suministra ninguna dosis
    if (u.edad() < 13) {
        return false;
        // En otro caso, realizamos el proceso de vacunacion normal
    } else {
        Estado e = Estado::enAlmacen;
        Dosis *ds = new Dosis();
        *ds = dosis[buscarVacunas(fab, e)];
        dosis[dosis.buscar(*ds)].setEstado(Estado::administrada);
        if (ds->GetFabricante() == u.getDosisRecomendable()) {
            u.addDosis(ds);
            return true;
        } else
            return false;
    }
}

/**
 * @brief Indica el numero de usuarios con pauta completa
 * Teniendo en cuenta a usuarios menores de 13 anios
 * @post Menores de 75 anios con 2 dosis && 
 * mayores de 75 con 3 dosis administradas
 * @return numero de usuarios con pauta completa
 */
int GestionVacunas::pautaCompleta() {
    int contador = 0;
    Usuario *u = new Usuario();
    for (int i = 0; i < listadoNSS.tam(); i++) {
        u = buscarUsuario(listadoNSS[i]);

        if (u->edad() < 75 && u->verDosis().tam() == 2)
            contador++;
        if (u->edad() > 75 && u->verDosis().tam() == 3)
            contador++;
    }
    contador = (contador * 100) / usuarios.numElementos();
    return contador;
}

/**
 * @brief Indica el numero de usuarios con pauta completa
 * Sin contar a usuarios menores de 13 anios
 * @post Menores de 75 anios con 2 dosis && 
 * mayores de 75 con 3 dosis administradas
 * @return numero de usuarios con pauta completa
 */
int GestionVacunas::pautaCompleta2() {
    int contador = 0;
    int cont = 0;
    Usuario *u = new Usuario();
    for (int i = 0; i < listadoNSS.tam(); i++) {
        u = buscarUsuario(listadoNSS[i]);

        if (u->edad() < 13)
            cont++;
        if (u->edad() < 75 && u->verDosis().tam() == 2)
            contador++;
        if (u->edad() > 75 && u->verDosis().tam() == 3)
            contador++;
    }
    contador = (contador * 100) / (usuarios.numElementos() - cont);
    return contador;
}

/**
 * @brief Listado de usuarios con vacunacion no recomendada
 * @return vector de usuarios con pauta no recomendada
 */
VDinamico<Usuario*> GestionVacunas::listadoVacunacionNR() {
    VDinamico<Usuario*> VNR;
    VDinamico<Usuario*> aux = usuarios.recorreInorden();
    for (int i = 0; i < aux.tam(); i++) {
        if (aux[i]->verDosis().tam() > 0 &&
                aux[i]->getDosisRecomendable() != aux[i]->verDosis()[0]->GetFabricante())
            VNR.insertar(aux[i]);
    }
    return VNR;
}

/**
 * @brief Listado de NSS de los usuarios
 * @return vector
 */
VDinamico<string> GestionVacunas::listadoCompletoNSS() {
    return this->listadoNSS;
}

/**
 * @brief Instancia un fichero de dosis en el atributo dosis
 * @param nombreFich
 * @return 
 */
void GestionVacunas::cargarDosis(std::string nombreFich) {

    ifstream is("ficheros/" + nombreFich);
    string palabra;
    int corte = 0;

    int fab = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;

    while (getline(is, palabra)) {
        Dosis d;

        corte = palabra.find(';');
        d.SetId(stoi(palabra.substr(0, corte)));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        d.SetIdLote(stoi(palabra.substr(0, corte)));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        fab = stoi(palabra.substr(0, corte));
        if (fab == 0) {
            d.SetFabricante(Fabricante::Pfizer);
        } else if (fab == 1) {
            d.SetFabricante(Fabricante::Moderna);
        } else if (fab == 2) {
            d.SetFabricante(Fabricante::AstraZeneca);
        } else if (fab == 3) {
            d.SetFabricante(Fabricante::Johnson);
        }
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        dia = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        mes = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        anno = stoi(palabra);
        Fecha f(dia, mes, anno);
        d.SetFechaFabricacion(f);
        f.anadirMeses(2);
        d.SetFechaCaducidad(f);
        this->dosis.insertar(d);
    }
    is.close();

}

/**
 * @brief Funcion para cargar los datos de un fichero de usuarios
 * @return 
 */
void GestionVacunas::cargarUsuarios(std::string nombreFich) {

    ifstream is("ficheros/" + nombreFich);
    string palabra;
    int corte = 0;

    double x = 0;
    double y = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;

    while (getline(is, palabra)) {
        Usuario u;
        std::string aux;

        corte = palabra.find(';');
        u.SetNombre(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        u.SetApellidos(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        u.SetNSS(palabra.substr(0, corte));
        aux = palabra.substr(0, corte);
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        dia = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        mes = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        anno = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        x = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        y = stoi(palabra.substr(0, corte));

        Fecha f(dia, mes, anno);
        UTM pos(x, y);
        u.SetDocimicilio(pos);
        u.SetFechaNacimiento(f);
        this->usuarios.inserta(u);
        this->listadoNSS.insertar(aux);
    }
    is.close();
}

/**
 * @brief Muestra los primeros 'numMostrar' usuarios
 */
void GestionVacunas::verUsuarios(int numMostrar) {
    Usuario *u = new Usuario();
    for (int i = 0; i < numMostrar; i++) {
        u = buscarUsuario(listadoNSS[i]);
        std::cout << *u;
    }
}

/**
 * @brief Muestra las dosis restantes
 * @return numero de rosis restantes
 */
int GestionVacunas::verDosisRestantes() {
    int cont = 0;
    for (int i = 0; i < this->dosis.tam(); i++) {
        if (dosis[i].getEstado() == Estado::enAlmacen)
            cont++;
    }
    return cont;
}

/**
 * @brief Muestra las dosis restantes de un fabricante
 * @param f
 * @return numero de rosis restantes
 */
int GestionVacunas::verDosisRestantes(Fabricante f) {
    int cont = 0;
    for (int i = 0; i < this->dosis.tam(); i++) {
        if (dosis[i].getEstado() == Estado::enAlmacen && dosis[i].GetFabricante() == f)
            cont++;
    }
    return cont;
}

/* OPERADORES*/

GestionVacunas & GestionVacunas::operator=(const GestionVacunas & right) {
    this->dosis = right.dosis;
    this->usuarios = right.usuarios;
    this->listadoNSS = right.listadoNSS;
    return *this;
}