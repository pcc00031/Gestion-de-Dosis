#include <iostream>
#include <fstream>
#include <string>
#include "VDinamico.h"
#include "Dosis.h"
#include "Usuario.h"
#include "ListaEnlazada.h"
#include "GestionVacunas.h"

using namespace std;

int main() {
    try {
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------------------------------------------------PRACTICA 4"
                "--------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Creacion del gestor de vacunas

        GestionVacunas gv;

        // Distribucion de vacunas a los centros

        gv.suministrarNDosisAlCentro(gv.buscarCentro(1), 8000);
        gv.suministrarNDosisAlCentro(gv.buscarCentro(2), 8200);
        gv.suministrarNDosisAlCentro(gv.buscarCentro(3), 8500);
        gv.suministrarNDosisAlCentro(gv.buscarCentro(4), 5000);
        gv.suministrarNDosisAlCentro(gv.buscarCentro(5), 50);

        cout << endl << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Mostrar numero de dosis total almacenadas de cada tipo

        cout << " - Numero total de vacunas Pfizer: "
                << gv.numTotalVacunasTipo(Fabricante::Pfizer) << endl;
        cout << " - Numero total de vacunas AstraZeneca: "
                << gv.numTotalVacunasTipo(Fabricante::AstraZeneca) << endl;
        cout << " - Numero total de vacunas Johnson: "
                << gv.numTotalVacunasTipo(Fabricante::Johnson) << endl;
        cout << " - Numero total de vacunas Moderna: "
                << gv.numTotalVacunasTipo(Fabricante::Moderna) << endl << endl;

        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Vacunar a todos los usuarios cuyo NSS sea par 

        Usuario u;
        vector<string> listadoNSS = gv.listadoCompletoNSS();
        for (int i = 0; i < listadoNSS.size(); i++) {
            if (listadoNSS[i].back() % 2 == 0) { // comprobacion par
                u = gv.buscarUsuario(listadoNSS[i]);
                if (u.GetNombre() != " ") {
                    gv.vacunarUsuario(u);
                    gv.actualizarUsuario(u); //FIXME cambiar
                    if (u.getDosis().size() > 0) {
                    }
                }
            }
        }

        cout << " - Numero total de vacunas Pfizer: "
                << gv.numTotalVacunasTipo(Fabricante::Pfizer) << endl;
        cout << " - Numero total de vacunas AstraZeneca: "
                << gv.numTotalVacunasTipo(Fabricante::AstraZeneca) << endl;
        cout << " - Numero total de vacunas Johnson: "
                << gv.numTotalVacunasTipo(Fabricante::Johnson) << endl;
        cout << " - Numero total de vacunas Moderna: "
                << gv.numTotalVacunasTipo(Fabricante::Moderna) << endl << endl;


        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Vacunar a todos los usuarios con más de 65 años.

        for (int i = 0; i < listadoNSS.size(); i++) {
            u = gv.buscarUsuario(listadoNSS[i]);
            if (u.GetNombre() != " " && u.edad() > 65) {
                gv.vacunarUsuario(u);
                gv.actualizarUsuario(u);
                if (u.getDosis().size() > 1) {
                }
            }
        }

        cout << " - Numero total de vacunas Pfizer: "
                << gv.numTotalVacunasTipo(Fabricante::Pfizer) << endl;
        cout << " - Numero total de vacunas AstraZeneca: "
                << gv.numTotalVacunasTipo(Fabricante::AstraZeneca) << endl;
        cout << " - Numero total de vacunas Johnson: "
                << gv.numTotalVacunasTipo(Fabricante::Johnson) << endl;
        cout << " - Numero total de vacunas Moderna: "
                << gv.numTotalVacunasTipo(Fabricante::Moderna) << endl << endl;

        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Vacunar a todas las usuarias que se llaman Eva, mostrar su nombre completo y el id y
        // la dirección del centro donde han sido vacunadas.

        cout << "*** INFORMACION VACUNACION DE USUARIOS LLAMADOS EVA ***" << endl;

        CentroVacunacion cv;
        for (int i = 0; i < listadoNSS.size(); i++) {
            u = gv.buscarUsuario(listadoNSS[i]);
            if (u.GetNombre() == "Eva") {
                cv = gv.buscarCentro(gv.vacunarUsuario(u).getId());
                cout << "CENTRO DE VACUNACION: " << cv.getId() << endl
                        << "- Direccion: " << endl << cv.getDireccion()
                        << endl << "DATOS VACUNADO:" << endl;
                gv.actualizarUsuario(u);
                cout << u << endl
                        << "-------------------------------------------------------------------------------" << endl << endl;
            }
        }

        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        cout << " - Numero total de vacunas Pfizer: "
                << gv.numTotalVacunasTipo(Fabricante::Pfizer) << endl;
        cout << " - Numero total de vacunas AstraZeneca: "
                << gv.numTotalVacunasTipo(Fabricante::AstraZeneca) << endl;
        cout << " - Numero total de vacunas Johnson: "
                << gv.numTotalVacunasTipo(Fabricante::Johnson) << endl;
        cout << " - Numero total de vacunas Moderna: "
                << gv.numTotalVacunasTipo(Fabricante::Moderna) << endl << endl;

        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Mostrar a todos los usuarios a los que se les ha administrado la pauta completa con las dosis recomendadas.

        cout << "Lista de usuarios con pauta recomendable: " << endl << endl;
        int pautaRecomendable = gv.pautaCompletaRecomendable();
        cout << "Usuarios con vacunacion no recomendable: " << gv.listadoVacunacionNR().size() << endl;
        cout << "Usuarios con pauta completa recomendable: " << pautaRecomendable << endl;
        cout << "Usuarios con pauta completa no recomendable: " << gv.pautaCompleta() << endl << endl;
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}