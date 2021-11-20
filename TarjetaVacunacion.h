
/* 
 * File:   TarjetaVacunacion.h
 * Author: Pedro
 *
 * Created on 17 de noviembre de 2021, 16:05
 */

#ifndef TARJETAVACUNACION_H
#define TARJETAVACUNACION_H

#include <vector>

#include "Dosis.h"
#include "Usuario.h"

class TarjetaVacunacion {
private:
    std::string id = "";
    bool pautaCompleta = false;
    int idCentroCercano = 0;
    std::vector<Dosis*> dosisAdministradas;
    Usuario *tarjetaUsuario;

public:

    /* CONSTRUCTORES */

    TarjetaVacunacion() = default;
    TarjetaVacunacion(const TarjetaVacunacion& orig);
    virtual ~TarjetaVacunacion();

    /* METODOS */

    UTM getDomicilio();
    void addDosis(Dosis *d);
    std::vector<Dosis*> getDosis();
    std::string pasaporteCovidCode(bool valido);
    Fabricante getDosisRecomendable();
    int dosisPorAdministrar();

    /* OPERADORES */

    TarjetaVacunacion& operator=(const TarjetaVacunacion& right);
    bool operator==(const TarjetaVacunacion& right) const;

    /* GETTERS Y SETTERS */

    void SetTarjetaUsuario(Usuario* tarjetaUsuario);
    Usuario* GetTarjetaUsuario() const;
    void SetIdCentroCercano(int idCentroCercano);
    int GetIdCentroCercano() const;
    void SetPautaCompleta(bool pautaCompleta);
    bool IsPautaCompleta() const;
    void setId(std::string id);
    std::string getId() const;

};

#endif /* TARJETAVACUNACION_H */

