
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
    cargarCentros("centros.txt");
    cargarUsuarios("usuarios.txt");
    std::sort(this->listadoNSS.begin(), this->listadoNSS.end());
}

/**
 * @brief Constructor parametrizado
 * @post Inicializa los datos con los ficheros pasados por parametro
 * @param nombreFichDosis
 * @param nombreFichUsuarios
 * @param nombreFicheCentros
 */
GestionVacunas::GestionVacunas(std::string nombreFichUsuarios, std::string nombreFicheCentros) {
    cargarCentros(nombreFicheCentros);
    cargarUsuarios(nombreFichUsuarios);
    std::sort(this->listadoNSS.begin(), this->listadoNSS.end());
}

/**
 * @brief Constructor copia 
 * @param orig
 */
GestionVacunas::GestionVacunas(const GestionVacunas& orig) :
usuarios(orig.usuarios), centros(orig.centros), listadoNSS(orig.listadoNSS), quedanVacunas(orig.quedanVacunas) {
}

/*
 * @brief Destructor
 */
GestionVacunas::~GestionVacunas() {
    this->dosis.close(); // cerramos solo al terminar la aplicacion
}

/* METODOS */

/**
 * @brief Busca un usuario dado su nss
 * @param nss
 * @return dicho usuario
 */
Usuario * GestionVacunas::buscarUsuario(std::string nss) {
    return &usuarios.find(nss)->second;
}

/**
 * @brief Busca un centro dado su id
 * @param id
 * @return dicho centro
 */
CentroVacunacion* GestionVacunas::buscarCentro(int id) {
    return &centros.at(id - 1);
}

/**
 * @brief Actualizacion de los datos de un usuario
 * @param u
 * @return 
 */
void GestionVacunas::actualizarUsuario(Usuario &u) {
    usuarios.find(u.GetNSS())->second = u;
}

/**
 * @brief Indica el numero de usuarios con pauta completa
 * Sin contar a usuarios menores de 13 anios
 * @post Menores de 75 anios con 2 dosis && 
 * mayores de 75 con 3 dosis administradas
 * @return numero de usuarios con pauta completa
 */
int GestionVacunas::pautaCompleta() {
    int contador = 0;
    map<string, Usuario>::iterator it;
    for (it = usuarios.begin(); it != usuarios.end(); it++) {
        if (it->second.edad() < 75 && it->second.getDosis().size() == 2)
            contador++;
        if (it->second.edad() > 75 && it->second.getDosis().size() == 3)
            contador++;
    }
    return contador;
}

/**
 * @brief Indica el numero de usuarios con pauta completa recomendable
 * Sin contar a usuarios menores de 13 anios
 * @post Menores de 75 anios con 2 dosis && 
 * mayores de 75 con 3 dosis administradas
 * @return numero de usuarios con pauta completa
 */
int GestionVacunas::pautaCompletaRecomendable() {
    int contador = 0;
    int cont = 0;
    Usuario *u;
    for (int i = 0; i < listadoNSS.size(); i++) {
        u = buscarUsuario(listadoNSS[i]);

        if (u->edad() < 13)
            cont++;
        if (u->edad() < 75 && u->getDosis().size() == 2
                && u->getDosis()[0]->GetFabricante() == u->getDosisRecomendable()
                && u->getDosis()[1]->GetFabricante() == u->getDosisRecomendable()) {
            contador++;
            std::cout << *u
                    << "- Dosis: " << endl
                    << " - Primera dosis: " << endl << *u->getDosis()[0]
                    << " - Segunda dosis: " << endl << *u->getDosis()[1] << endl;
        }
        if (u->edad() > 75 && u->getDosis().size() == 3
                && u->getDosis()[0]->GetFabricante() == u->getDosisRecomendable()
                && u->getDosis()[1]->GetFabricante() == u->getDosisRecomendable()
                && u->getDosis()[2]->GetFabricante() == u->getDosisRecomendable()) {
            contador++;
            std::cout << *u
                    << "- Dosis: " << endl
                    << " - Primera dosis: " << endl << *u->getDosis()[0]
                    << " - Segunda dosis: " << endl << *u->getDosis()[1]
                    << " - Tercera dosis: " << endl << *u->getDosis()[2] << endl;

        }
    }
    return contador;
}

/**
 * @brief Muestra el numero total de vacunas de un tipo
 * @param f
 * @return 
 */
int GestionVacunas::numTotalVacunasTipo(Fabricante f) {
    int total = 0;
    for (int i = 0; i < centros.size(); i++) {
        total += centros[i].numVacunasTipo(f);
    }

    return total;
}

/**
 * @brief Vacuna a un usuario
 * @post Calculamos el centro de vacunacion más cercano al usuario
 * y vacunamos una dosis siguiendo el criterio del centro
 * @param u
 * @return CentroVacunacion donde se vacuna
 */
CentroVacunacion * GestionVacunas::vacunarUsuario(Usuario *u) {
    CentroVacunacion *cv;
    double menorDistancia, aux = 0;
    // comprobacion del centro mas cercano al domicilio del usuario
    menorDistancia = (u->GetDocimicilio().calcularDistancia(centros[0].getDireccion()));
    cv = &centros[0];

    for (int i = 1; i < centros.size(); i++) {
        aux = u->GetDocimicilio().calcularDistancia(centros[i].getDireccion());
        if (aux < menorDistancia) {
            menorDistancia = aux;
            cv = &centros[i];
        }
    }
    cv->anadirUsuarioLista(u); // Damos de alta al usuario (de forma temporal)
    cv->administrarDosis(u, u->getDosisRecomendable()); // Vacunamos
    return cv;
}

/**
 * @brief Listado de usuarios con vacunacion no recomendada
 * @return vector de usuarios con pauta no recomendada
 */
vector<Usuario*> GestionVacunas::listadoVacunacionNR() {
    vector<Usuario*> VNR;
    map<std::string, Usuario>::iterator it;
    it = usuarios.begin();
    while (it != usuarios.end()) {
        // Detectamos usuarios con solo 1 vacuna administrada 
        if (it->second.getDosis().size() == 1 &&
                it->second.getDosisRecomendable() != it->second.getDosis()[0]->GetFabricante())
            VNR.push_back(&it->second);
        // Detectamos usuarios con 2 vacunas administradas
        if (it->second.getDosis().size() == 2 && (
                it->second.getDosisRecomendable() != it->second.getDosis()[0]->GetFabricante()
                || it->second.getDosisRecomendable() != it->second.getDosis()[1]->GetFabricante()))
            // si alguna de las 2 es no recomendada, agregamos al listado
            VNR.push_back(&it->second);
        // Detectamos usuarios con 3 vacunas administradas
        if (it->second.getDosis().size() == 3 && (
                it->second.getDosisRecomendable() != it->second.getDosis()[0]->GetFabricante()
                || it->second.getDosisRecomendable() != it->second.getDosis()[1]->GetFabricante()
                || it->second.getDosisRecomendable() != it->second.getDosis()[2]->GetFabricante()))
            // si alguna de las 3 es no recomendada, agregamos al listado
            VNR.push_back(&it->second);
        ++it;
    }
    return VNR;
}

/**
 * @brief Suministra nDosis si las hay al centro especifico
 * @param centro
 * @param f
 */
void GestionVacunas::suministrarNDosisAlCentro(CentroVacunacion *centro, int nDosis) {
    vector<Dosis> suministro;
    suministro = cargarDosis(centro->getId(), nDosis);
    if (suministro.size() < nDosis)
        quedanVacunas = false;
    centro->anadirNDosisAlmacen(suministro);
}

/**
 * @brief Listado de NSS de los usuarios
 * @return vector
 */
vector<string>& GestionVacunas::listadoCompletoNSS() {
    return this->listadoNSS;
}

/**
 * @brief Funcion para cargar los datos de un fichero de usuarios
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

        corte = palabra.find(';');
        anno = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        x = stod(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        y = stod(palabra.substr(0, corte));

        Fecha f(dia, mes, anno);
        UTM pos(x, y);
        u.SetDocimicilio(pos);
        u.SetFechaNacimiento(f);

        this->usuarios.insert(pair<std::string, Usuario>(u.GetNSS(), u));
        this->listadoNSS.push_back(aux);

    }
    is.close();
}

/**
 * @brief Funcion para cargar los datos de un fichero de centros
 * @param nombreFich
 */
void GestionVacunas::cargarCentros(std::string nombreFich) {

    ifstream is("ficheros/" + nombreFich);
    string palabra;
    int corte = 0;

    int id = 0;
    double lat, lng = 0.0;

    while (getline(is, palabra)) {

        corte = palabra.find(';');
        id = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        lat = stod(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        lng = stod(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        UTM direccion(lat, lng);
        CentroVacunacion cv(id, direccion);
        cv.setGv(this);
        this->centros.push_back(cv);
    }
    is.close();
}

/**
 * @brief Leemos numDosis de un fichero de texto y delvovemos los datos de esas dosis
 * @param numCentro
 * @param numDosis
 * @return vector de dosis leidas
 */
vector<Dosis> GestionVacunas::cargarDosis(int numCentro, int numDosis) {
    std::cout << "- Intentando suministrar " << numDosis << " dosis al centro " << numCentro << std::endl;
    if (!dosis.is_open()) {
        dosis.open("ficheros/dosis.txt", std::ifstream::in);
    }
    string palabra;
    int corte = 0;
    vector<Dosis> aux;
    int cont = 0;
    int fab = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;

    while (getline(dosis, palabra)) {
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

        if (cont < numDosis) {
            aux.push_back(d);
            cont++;
        }
        // Cargamos en el centro
        if (cont == numDosis) { //FIXME controlar en el while
            return aux;
        }
    }
}

/**
 * @brief Muestra los primeros 'numMostrar' usuarios
 */
void GestionVacunas::verUsuarios(int numMostrar) {
    Usuario *u;
    std::cout << " Total usuarios: " << usuarios.size() << endl;
    for (int i = 0; i < numMostrar; i++) {
        u = buscarUsuario(listadoNSS[i]);
        std::cout << u;

        std::cout << "- - Num dosis: " << u->getDosis().size() << endl;
        if (u->getDosis().size() > 0) {
            for (int i = 0; i < u->getDosis().size(); i++) {

                cout << "- Dosis " << i + 1 << ": " << endl;
                cout << *u->getDosis()[i] << endl;
            }
        }
    }
}

/* GETTERS Y SETTERS */

void GestionVacunas::setQuedanVacunas(bool quedanVacunas) {
    this->quedanVacunas = quedanVacunas;
}

bool GestionVacunas::isQuedanVacunas() const {
    return quedanVacunas;
}

/* OPERADORES*/

GestionVacunas & GestionVacunas::operator=(const GestionVacunas & right) {
    this->centros = right.centros;
    this->usuarios = right.usuarios;
    this->listadoNSS = right.listadoNSS;
    this->quedanVacunas = right.quedanVacunas;

    return *this;
}

bool GestionVacunas::operator==(const GestionVacunas & right) const {
    if (this->centros == right.centros &&
            this->listadoNSS == right.listadoNSS &&
            this->usuarios == right.usuarios) {
        return true;
    } else return false;
}