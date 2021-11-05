
/* 
 * File:   GestionVacunas.h
 * Author: Pedro
 *
 * Created on 20 de octubre de 2021, 21:53
 */

#ifndef GESTIONVACUNAS_H
#define GESTIONVACUNAS_H

#include <string>
#include "Dosis.h"
#include "Usuario.h"
#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "AVL.h"
#include "CentroVacunacion.h"

//class CentroVacunacion; // para relacion circular

class GestionVacunas {
private:
    map<std::string, Usuario> usuarios;
    vector<CentroVacunacion> centros;
    vector<Dosis> reservaDosis;
    vector<string> listadoNSS;
    int buscarVacunas(Fabricante &f, Estado &e);

public:
    /* CONSTRUCTORES*/

    GestionVacunas();
    GestionVacunas(std::string nombreFichDosis, std::string nombreFichUsuarios, std::string nombreFicheCentros);
    GestionVacunas(const GestionVacunas& orig);
    virtual ~GestionVacunas();

    /* OPERADORES */

    GestionVacunas& operator=(const GestionVacunas& right);

    /* METODOS */

    void distribuirDosis();

    Usuario& buscarUsuario(std::string nss);
    void actualizarUsuario(Usuario &u);
    vector<string> listadoCompletoNSS();
    CentroVacunacion& vacunarUsuario(Usuario &u);

    int pautaCompleta();
    int pautaCompleta2();
    vector<Usuario> listadoVacunacionNR();
    void suministrar100DosisAlCentro(CentroVacunacion &centro);
    int numTotalVacunasTipo(Fabricante f);

    /* METODOS DE CARGA DE FICHEROS*/

    void cargarUsuarios(std::string nombreFich);
    void cargarDosis(std::string nombreFich);
    void cargarCentros(std::string nombreFich);

    // Visualizado de usuarios
    void verUsuarios(int numMostrar);

};

#endif /* GESTIONVACUNAS_H */

