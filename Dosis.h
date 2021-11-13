
/* 
 * File:   Dosis.h
 * Author: Pedro
 *
 * Created on 21 de septiembre de 2021, 16:44
 */

#ifndef DOSIS_H
#define DOSIS_H

#include <ostream>
#include <iostream>
#include "fecha.h"

/* ENUM CLASS PARA EL TIPO FABRICANTE */
enum class Fabricante {
    Pfizer,
    Moderna,
    AstraZeneca,
    Johnson
};

/**
 * @brief Convierte un tipo Fabricante a cadena 
 * @param os
 * @param f
 * @return 
 */
inline std::ostream& operator<<(std::ostream & os, const Fabricante f) {
    switch (f) {
        case Fabricante::Pfizer:
            std::cout << "Pfizer";
            break;
        case Fabricante::Moderna:
            std::cout << "Moderna";
            break;
        case Fabricante::AstraZeneca:
            std::cout << "AstraZeneca";
            break;
        case Fabricante::Johnson:
            std::cout << "Johnson";
            break;
dafault:
            std::cout << "Vacuna no reconocida";
            break;
    }
    return os;
}

/* ENUM CLASS PARA EL TIPO ESTADO */
enum class Estado {
    administrada,
    enAlmacen
};

/**
 * @brief Convierte un tipo Estado a cadena 
 * @param os
 * @param e
 * @return 
 */
inline std::ostream& operator<<(std::ostream & os, const Estado e) {
    switch (e) {
        case Estado::administrada: std::cout << "Administrada";
            break;
        case Estado::enAlmacen: std::cout << "En Almacen";
            break;
        default:
            std::cout << "Estado no definido";
    }
    return os;
}

/* DEFINICION DE LA CLASE DOSIS */

class Dosis {
private:
    int id = 0;
    int idLote = 0;
    Fabricante fabricante;
    Estado estado;
    Fecha fechaFabricacion;
    Fecha fechaCaducidad;

public:

    /* CONSTRUCTORES Y DESTRUCTOR */

    Dosis();
    Dosis(int id, int idLote, Fecha fechaFabricacion, Fecha fechaCaducidad);
    Dosis(const Dosis& orig);
    virtual ~Dosis();

    /* METODOS */

    string fabToString(const Fabricante &f);

    /* OPERADORES */

    Dosis& operator=(const Dosis& right);
    bool operator!=(const Dosis& right) const;
    bool operator<(const Dosis& right) const;
    bool operator<=(const Dosis& right) const;
    bool operator==(const Dosis& right) const;
    bool operator>(const Dosis& right) const;
    bool operator>=(const Dosis& right) const;
    friend std::ostream& operator<<(std::ostream& os, const Dosis& obj);

    /* GETTERS Y SETTERS */

    Fecha GetFechaCaducidad() const;
    void SetFechaCaducidad(Fecha fechaCaducidad);
    Fecha GetFechaFabricacion() const;
    void SetFechaFabricacion(Fecha fechaFabricacion);
    int GetId() const;
    void SetId(int id);
    int GetIdLote() const;
    void SetIdLote(int idLote);
    Fabricante GetFabricante() const;
    void SetFabricante(Fabricante fabricante);
    Estado getEstado() const;
    void setEstado(Estado estado);

};

inline std::ostream& operator<<(std::ostream& os, const Dosis& obj) {
    std::cout << "   - ID: " << obj.id << std::endl
            << "   - Fabricante: " << obj.fabricante << std::endl
            << "   - Fecha Fab: " << obj.fechaFabricacion << std::endl;
    return os;
}

#endif /* DOSIS_H */

