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

        gv.distribuirDosis(); //FIXME dejar fichero abierto

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
        int cont, cont1 = 0;
        for (int i = 0; i < listadoNSS.size(); i++) {
            if (listadoNSS[i].back() == '0' ||
                    listadoNSS[i].back() == '2' ||
                    listadoNSS[i].back() == '4' ||
                    listadoNSS[i].back() == '6' ||
                    listadoNSS[i].back() == '8') { // comprobacion par
                u = gv.buscarUsuario(listadoNSS[i]);
                if (u.GetNombre() != " ") {
                    cont++;
                    gv.vacunarUsuario(u);
                    gv.actualizarUsuario(u);
                    if (u.getDosis().size() > 0) {
                        cont1++;
                    }
                }
            }
        }


        cout << "Total: " << cont << " usuarios con NSS par"
                << " - " << cont1 << " usuarios pares vacunados" << endl << endl;

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
        cont = 0;
        cont1 = 0;
        for (int i = 0; i < listadoNSS.size(); i++) {
            u = gv.buscarUsuario(listadoNSS[i]);
            if (u.GetNombre() != " " && u.edad() > 65) {
                cont++;
                gv.vacunarUsuario(u);
                gv.actualizarUsuario(u);
                if (u.getDosis().size() > 1) {
                    for (int i = 0; i < u.getDosis().size(); i++) {
                        cont1++;
                    }
                }
            }
        }
        cout << "Total: " << cont << " usuarios mayores de 65"
                << " - " << cont1 << " vacunados de segunda dosis" << endl << endl;

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

        cont = 0;
        cont1 = 0;
        for (int i = 0; i < listadoNSS.size(); i++) {
            u = gv.buscarUsuario(listadoNSS[i]);
            if (u.GetNombre() == "Eva") {
                cont++;
                gv.vacunarUsuario(u);
                gv.actualizarUsuario(u);
                //cout << u;
                if (u.getDosis().size() > 2) {
                    cont1++;
                    //                    for (int i = 0; i < u.getDosis().size(); i++) {
                    //                        cout << "- Dosis " << i + 1 << ": " << endl;
                    //                        cout << *u.getDosis()[i] << endl;
                    //                    }
                } else {
                    // cout << "- No tiene vacuna administrada" << endl << endl;
                }
            }
        }

        cout << "Total: " << cont << " usuarios con nombre Eva"
                << " - " << cont1 << " evas vacunadas con 3 vacunas" << endl << endl;

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

        // Después de la vacunación, mostrar de nuevo el número total de dosis almacenadas de cada tipo

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

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}