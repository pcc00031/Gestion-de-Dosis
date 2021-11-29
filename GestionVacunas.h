
/* 
 * File:   GestionVacunas.h
 * Author: Pedro
 *
 * Created on 20 de octubre de 2021, 21:53
 */

#ifndef GESTIONVACUNAS_H
#define GESTIONVACUNAS_H

#include "CentroVacunacion.h"
#include "TarjetaVacunacion.h"
#include "THashTarjetaVacunacion.h"
#include <fstream>
#include <algorithm>
#include <optional>
#include <functional>

class GestionVacunas {
private:
    map <std::string, Usuario> usuarios;
    vector <CentroVacunacion> centros;
    vector <string> listadoNSS;
    map <std::string, TarjetaVacunacion> tarjetas;

    bool quedanVacunas = true; ///<  Indica si quedan dosis disponibles
    std::ifstream dosis; ///<  Guarda el estado del fichero de dosis

public:

    /* CONSTRUCTORES*/

    GestionVacunas();

    GestionVacunas(std::string nombreFichUsuarios, std::string nombreFicheCentros);

    GestionVacunas(const GestionVacunas &orig);

    virtual ~GestionVacunas();

    /* OPERADORES */

    GestionVacunas &operator=(const GestionVacunas &right);

    bool operator==(const GestionVacunas &right) const;

    /* METODOS */

    Usuario *buscarUsuario(std::string nss);

    TarjetaVacunacion *buscarTarjeta(std::string id);

    void borrarTarjeta(std::string id);

    CentroVacunacion *buscarCentro(int id);

    vector <string> &listadoCompletoNSS();

    CentroVacunacion *vacunarUsuario(TarjetaVacunacion *t);

    int pautaCompleta();

    int pautaCompletaRecomendable();

    int pasaporteCovid();

    vector<Usuario *> listadoVacunacionNR();

    void suministrarNDosisAlCentro(CentroVacunacion *centro, int nDosis);

    int numTotalVacunasTipo(Fabricante f);

    /* METODOS DE CARGA DE DATOS */

    void cargarUsuarios(std::string nombreFich);

    vector <Dosis> cargarDosis(int numCentro, int numDosis);

    void cargarCentros(std::string nombreFich);

    void cargarTarjetas(std::string id);

    // Visualizado de usuarios
    void verUsuarios(int numMostrar);

    /* GETTERS Y SETTERS */

    void setQuedanVacunas(bool quedanVacunas);

    bool isQuedanVacunas() const;

};

#endif /* GESTIONVACUNAS_H */

