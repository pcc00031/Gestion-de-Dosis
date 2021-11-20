
/* 
 * File:   GestionVacunas.h
 * Author: Pedro
 *
 * Created on 20 de octubre de 2021, 21:53
 */

#ifndef GESTIONVACUNAS_H
#define GESTIONVACUNAS_H

#include "CentroVacunacion.h"
#include <fstream>
#include <algorithm>

class GestionVacunas {
private:
    map<std::string, Usuario> usuarios;
    vector<CentroVacunacion> centros;
    vector<string> listadoNSS;

    bool quedanVacunas = true; ///<  Indica si quedan dosis disponibles
    std::ifstream dosis; ///<  Guarda el estado del fichero de dosis

public:

    /* CONSTRUCTORES*/

    GestionVacunas();
    GestionVacunas(std::string nombreFichUsuarios, std::string nombreFicheCentros);
    GestionVacunas(const GestionVacunas& orig);
    virtual ~GestionVacunas();

    /* OPERADORES */

    GestionVacunas& operator=(const GestionVacunas& right);
    bool operator==(const GestionVacunas& right) const;

    /* METODOS */

    Usuario* buscarUsuario(std::string nss);
    CentroVacunacion* buscarCentro(int id);
    void actualizarUsuario(Usuario &u);
    vector<string>& listadoCompletoNSS();
    CentroVacunacion* vacunarUsuario(Usuario *u);

    int pautaCompleta();
    int pautaCompletaRecomendable();
    vector<Usuario*> listadoVacunacionNR();
    void suministrarNDosisAlCentro(CentroVacunacion *centro, int nDosis);
    int numTotalVacunasTipo(Fabricante f);

    /* METODOS DE CARGA DE FICHEROS*/

    void cargarUsuarios(std::string nombreFich);
    vector<Dosis> cargarDosis(int numCentro, int numDosis);
    void cargarCentros(std::string nombreFich);

    // Visualizado de usuarios
    void verUsuarios(int numMostrar);

    /* GETTERS Y SETTERS */

    void setQuedanVacunas(bool quedanVacunas);
    bool isQuedanVacunas() const;

};

#endif /* GESTIONVACUNAS_H */

