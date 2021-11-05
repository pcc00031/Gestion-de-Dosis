
/* 
 * File:   GestionVacunas.cpp
 * Author: Pedro Corpas
 */

#include "GestionVacunas.h"
#include "CentroVacunacion.h"

/* CONSTRUCTORES */

/**
 * @brief Constructor por defecto del gestor
 * @post Inicializa dosis y usuarios con los ficheros
 * de texto predeterminados & ordena los vectores
 */
GestionVacunas::GestionVacunas() {
    cargarCentros("centros.txt");
    cargarUsuarios("usuarios.txt");
    cargarDosis("dosis.txt");
    std::sort(this->listadoNSS.begin(), this->listadoNSS.end());

    std::cout << "Total centros: " << centros.size() << endl
            << "Total dosis: " << reservaDosis.size() << endl
            << "Total usuarios: " << usuarios.size() << endl;
}

/**
 * @brief Constructor parametrizado
 * @post Inicializa los datos con los ficheros pasados por parametro
 * @param nombreFichDosis
 * @param nombreFichUsuarios
 * @param nombreFicheCentros
 * 
 */
GestionVacunas::GestionVacunas(std::string nombreFichDosis, std::string nombreFichUsuarios, std::string nombreFicheCentros) {
    cargarCentros(nombreFicheCentros);
    cargarUsuarios(nombreFichUsuarios);
    cargarDosis(nombreFichDosis);
    std::sort(this->listadoNSS.begin(), this->listadoNSS.end());
}

/**
 * @brief Constructor copia 
 * @param orig
 */
GestionVacunas::GestionVacunas(const GestionVacunas& orig) :
usuarios(orig.usuarios), centros(orig.centros), listadoNSS(orig.listadoNSS), reservaDosis(orig.reservaDosis) {
}

/*
 * @brief Destructor
 */
GestionVacunas::~GestionVacunas() {
}

/* METODOS */

/**
 * @brief Distribuye dosis totales entre los centros
 */
void GestionVacunas::distribuirDosis() {
    vector<Dosis> aux;
    vector<Dosis>::iterator it;
    it = reservaDosis.begin();
    int cont = 0;
    // Recorremos primeros 8000 elementos e insertamos en vector auxiliar
    while (cont < 8000) {
        aux.push_back(*it);
        ++it;
        cont++;
    }
    // Borramos de la reserva las 8000 primeras dosis
    reservaDosis.erase(reservaDosis.begin(), it);
    std::cout << "Dosis en reserva: " << this->reservaDosis.size() << endl;
    // Cargamos en el primer centro
    centros[0].cargaDosis(aux);

    // Limpiamos vector auxiliar y realizamos la misma operacion
    // con los demas centros siguiendo criterio establecido en el enunciado

    // Segundo centro

    aux.clear();
    it = reservaDosis.begin();
    cont = 0;
    while (cont < 8200) {
        aux.push_back(*it);
        ++it;
        cont++;
    }
    reservaDosis.erase(reservaDosis.begin(), it);
    std::cout << "Dosis en reserva: " << this->reservaDosis.size() << endl;
    centros[1].cargaDosis(aux);

    // Tercer centro

    aux.clear();
    it = reservaDosis.begin();
    cont = 0;
    while (cont < 8500) {
        aux.push_back(*it);
        ++it;
        cont++;
    }
    reservaDosis.erase(reservaDosis.begin(), it);
    std::cout << "Dosis en reserva: " << this->reservaDosis.size() << endl;
    centros[2].cargaDosis(aux);

    // Cuarto centro

    aux.clear();
    it = reservaDosis.begin();
    cont = 0;
    while (cont < 5000) {
        aux.push_back(*it);
        ++it;
        cont++;
    }
    reservaDosis.erase(reservaDosis.begin(), it);
    std::cout << "Dosis en reserva: " << this->reservaDosis.size() << endl;
    centros[3].cargaDosis(aux);

    // Quinto centro

    aux.clear();
    it = reservaDosis.begin();
    cont = 0;
    while (cont < 50) {
        aux.push_back(*it);
        ++it;
        cont++;
    }
    reservaDosis.erase(reservaDosis.begin(), it);
    std::cout << "Dosis en reserva: " << this->reservaDosis.size() << endl;
    centros[4].cargaDosis(aux);
}

/**
 * @brief Busca un usuario dado su nss
 * @param nss
 * @return dicho usuario
 */
Usuario& GestionVacunas::buscarUsuario(std::string nss) {
    return usuarios.find(nss)->second;
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
 * Teniendo en cuenta a usuarios menores de 13 anios
 * @post Menores de 75 anios con 2 dosis && 
 * mayores de 75 con 3 dosis administradas
 * @return numero de usuarios con pauta completa
 */
int GestionVacunas::pautaCompleta() {
    int contador = 0; // FIXME devuelve int, pero luego se calcula % en float en main
    Usuario u;
    for (int i = 0; i < listadoNSS.size(); i++) {
        u = buscarUsuario(listadoNSS[i]);

        if (u.edad() < 75 && u.getDosis().size() == 2)
            contador++;
        if (u.edad() > 75 && u.getDosis().size() == 3)
            contador++;
    }
    contador = (contador * 100) / usuarios.size();
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
    Usuario u;
    for (int i = 0; i < listadoNSS.size(); i++) {
        u = buscarUsuario(listadoNSS[i]);

        if (u.edad() < 13)
            cont++;
        if (u.edad() < 75 && u.getDosis().size() == 2)
            contador++;
        if (u.edad() > 75 && u.getDosis().size() == 3)
            contador++;
    }
    contador = (contador * 100) / (usuarios.size() - cont);
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
    //
    //    cout << "Centro 1: " << centros[0].verDosisRestantes() << " dosis restantes" << endl
    //            << "Centro 2: " << centros[1].verDosisRestantes() << " dosis restantes" << endl
    //            << "Centro 3: " << centros[2].verDosisRestantes() << " dosis restantes" << endl
    //            << "Centro 4: " << centros[3].verDosisRestantes() << " dosis restantes" << endl
    //            << "Centro 5: " << centros[4].verDosisRestantes() << " dosis restantes" << endl;

    return total;
}


/**
 * @brief Vacuna a un usuario
 * @post Calculamos el centro de vacunacion más cercano al usuario
 * y vacunamos una dosis siguiendo el criterio del centro
 * @param u
 * @return CentroVacunacion donde se vacuna
 */
CentroVacunacion& GestionVacunas::vacunarUsuario(Usuario &u) {
    double menorDistancia, aux = 0;
    // comprobacion del centro mas cercano al domicilio del usuario
    menorDistancia = (u.GetDocimicilio().calcularDistancia(centros[0].getDireccion()));
    int posCentro = 0;

    for (int i = 1; i < centros.size(); i++) {
        aux = u.GetDocimicilio().calcularDistancia(centros[i].getDireccion());
        if (aux < menorDistancia) {
            menorDistancia = aux;
            posCentro = i;
        }
    }
    centros[posCentro].anadirUsuarioLista(u); // Damos de alta al usuario (de forma temporal)
    centros[posCentro].administrarDosis(u, u.getDosisRecomendable()); // Vacunamos
    return centros[posCentro];
}

/**
 * @brief Listado de usuarios con vacunacion no recomendada
 * @return vector de usuarios con pauta no recomendada
 */
vector<Usuario> GestionVacunas::listadoVacunacionNR() {
    vector<Usuario> VNR;
    map<std::string, Usuario>::iterator it;
    it = usuarios.begin();
    while (it != usuarios.end()) {
        if (it->second.getDosis().size() > 0 &&
                it->second.getDosisRecomendable() != it->second.getDosis()[0]->GetFabricante()) {
            VNR.push_back(it->second);
        }
        ++it;
    }
    return VNR;
}

/**
 * @brief
 * @param centro
 * @param f
 */
void GestionVacunas::suministrar100DosisAlCentro(CentroVacunacion &centro) {
    vector<Dosis> suministro;
    vector<Dosis>::iterator it;
    it = reservaDosis.begin();
    int cont = 0;
    // FIXME lo tendremos que hacer con ficheros y eso nose
    if (reservaDosis.size() >= 100) {
        // Recorremos primeros 8000 elementos e insertamos en vector auxiliar
        while (cont < 100) {
            suministro.push_back(*it);
            ++it;
            cont++;
        }
        reservaDosis.erase(reservaDosis.begin(), it);
        centro.anadir100DosisAlmacen(suministro);
    } else std::cout << "No quedan suficientes dosis para suministrar al centro" << endl;
}

/**
 * @brief Listado de NSS de los usuarios
 * @return vector
 */
vector<string> GestionVacunas::listadoCompletoNSS() {
    return this->listadoNSS;
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
        lat = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        lng = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        UTM direccion(lat, lng);
        CentroVacunacion cv(id, direccion);
        this->centros.push_back(cv);
    }
    is.close();
}

/**
 * @brief Instancia un fichero de dosis en el atributo dosis
 * @param nombreFich
 * @return 
 */
void GestionVacunas::cargarDosis(std::string nombreFich) {
    //FIXME carga fichero dosis
    // no se cargan todas las dosis de golpe, sino por ciclos (GestionVacunas::distribuirDosis())
    // cuando se haga la asignacion, dejar fichero abierto para luego, al saltar la alarma,
    // se lean otras 100 dosis
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
        this->reservaDosis.push_back(d);
    }
    is.close();

}

/**
 * @brief Muestra los primeros 'numMostrar' usuarios
 */
void GestionVacunas::verUsuarios(int numMostrar) {
    Usuario u;
    std::cout << " Total usuarios: " << usuarios.size() << endl;
    for (int i = 0; i < numMostrar; i++) {
        u = buscarUsuario(listadoNSS[i]);
        std::cout << u;

        std::cout << "- - Num dosis: " << u.getDosis().size() << endl;
        if (u.getDosis().size() > 0) {
            for (int i = 0; i < u.getDosis().size(); i++) {
                cout << "- Dosis " << i + 1 << ": " << endl;
                cout << *u.getDosis()[i] << endl;
            }
        }
    }
}

/* OPERADORES*/

GestionVacunas & GestionVacunas::operator=(const GestionVacunas & right) {
    this->centros = right.centros;
    this->usuarios = right.usuarios;
    this->listadoNSS = right.listadoNSS;
    this->reservaDosis = right.reservaDosis;
    return *this;
}