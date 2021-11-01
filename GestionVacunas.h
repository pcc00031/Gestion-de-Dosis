
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

class GestionVacunas {
private:
    AVL<Usuario> usuarios;
    VDinamico<Dosis> dosis;
    VDinamico<string> listadoNSS;
    int buscarVacunas(Fabricante &f, Estado &e);

public:
    /* CONSTRUCTORES*/

    GestionVacunas();
    GestionVacunas(std::string nombreFichDosis, std::string nombreFichUsuarios);
    GestionVacunas(const GestionVacunas& orig);
    virtual ~GestionVacunas();

    /* OPERADORES */

    GestionVacunas& operator=(const GestionVacunas& right);

    /* METODOS */

    Usuario* buscarUsuario(std::string nss);    
    VDinamico<string> listadoCompletoNSS();
    bool administrarDosis(Usuario &u, Fabricante fab);
    int pautaCompleta();
    int pautaCompleta2();
    VDinamico<Usuario*> listadoVacunacionNR();

    /* METODOS DE CARGA DE FICHEROS*/

    void cargarDosis(std::string nombreFich);
    void cargarUsuarios(std::string nombreFich);

    // Visualizado de usuarios
    void verUsuarios(int numMostrar);

    // Informacion de dosis restantes
    int verDosisRestantes();
    int verDosisRestantes(Fabricante f);

};

#endif /* GESTIONVACUNAS_H */

