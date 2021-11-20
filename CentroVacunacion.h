
/* 
 * File:   CentroVacunacion.h
 * Author: Pedro
 *
 * Created on 3 de noviembre de 2021, 12:15
 */

#ifndef CENTROVACUNACION_H
#define CENTROVACUNACION_H

#include <map>
#include <list>
#include "Usuario.h"

class GestionVacunas; // para relacion circular

class CentroVacunacion {
private:
    multimap<std::string, Dosis> dosis;
    list<Usuario*> usuarios;
    int id = 0;
    UTM direccion;
    GestionVacunas *gv;
    void alarmaFaltaDosis(Fabricante f);

public:
    /* CONSTRUCTORES */

    CentroVacunacion();
    CentroVacunacion(int id, UTM direccion);
    CentroVacunacion(const CentroVacunacion& orig);
    virtual ~CentroVacunacion();

    /* METODOS */

    void anadirUsuarioLista(Usuario *u);
    bool administrarDosis(Usuario *u, Fabricante fab);
    void anadirNDosisAlmacen(vector<Dosis> &packDosis);
    int numVacunasTipo(Fabricante f);
    
    int verDosisRestantes(); // metodo auxiliar de comprobacion

    /* OPERADORES */

    CentroVacunacion& operator=(const CentroVacunacion& right);
    bool operator==(const CentroVacunacion& right) const;

    friend std::ostream& operator<<(std::ostream& os, const CentroVacunacion& obj) {
        std::cout << " ID: " << obj.id << std::endl;
        return os;
    }

    /* GETTERS Y SETTERS */

    UTM getDireccion() const;
    void setDireccion(UTM direccion);
    int getId() const;
    void setId(int id);
    void setGv(GestionVacunas* gv);

};

#endif /* CENTROVACUNACION_H */

