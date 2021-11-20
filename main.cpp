#include <sys/unistd.h>

#include "GestionVacunas.h"

using namespace std;

int main() {
    try {
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------------------------------------------------PRACTICA 5"
                "--------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        int tipoEjecucion = 0;

        cout << "Elija el tipo de ejecucion: " << endl
                << "- Programa de prueba: 1" << endl
                << "- Programa de Gestion de Dosis: 2" << endl;
        cin >> tipoEjecucion;

        switch (tipoEjecucion) {
                // PROGRAMA DE ENTRENAMIENTO
            case 1:
            {


            }

                // RESOLUCION PRACTICA 5
            default:
            case 2:
            {
                // Proceso de iniciacion de la practica anterior

                GestionVacunas gv;
                Usuario *u;
                TarjetaVacunacion *t;
                vector<string> listadoNSS = gv.listadoCompletoNSS();

                gv.suministrarNDosisAlCentro(gv.buscarCentro(1), 8000);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(2), 8200);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(3), 8500);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(4), 5000);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(5), 50);

                cout << endl << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Generacion de Tarjetas de Vacunacion

                int conte = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    gv.cargarTarjetas(listadoNSS[i]);
                }
                cout << "- Tarjetas cargadas: " << conte << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Mostrar factor de carga y tam de la tabla Hash

                cout << "- Factor de carga: " << endl
                        << "- Tam de la tabla: " << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Eliminar las tarjetas de vacunación de todos los usuarios cuyo NSS acabe en ‘0’ de la tabla hash.

                conte = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].back() == '0') { // comprobacion NSS
                        u = gv.buscarUsuario(listadoNSS[i]);
                        if (u != nullptr) {
                            t = gv.buscarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                            if (t != nullptr)
                                gv.borrarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                            conte++;
                        }
                    }
                }

                cout << "- Total tarjetas borradas: " << conte << endl;

                cout << endl << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Añadir las tarjetas de vacunación anteriormente borradas de aquellos usuarios cuyo NSS acabe en ‘30’ a la tabla hash.

                conte = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].at(8) == '3' && listadoNSS[i].back() == '0') {
                        gv.cargarTarjetas(listadoNSS[i]);
                        conte++;
                    }
                }

                cout << "- Tarjetas cargadas: " << conte << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Mostrar el número de colisiones máximo que se han producido al volver a insertar las tarjetas de vacunación.

                cout << "- Total colisiones: " << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Vacunar a todos los usuarios cuyo NSS sea par de la primera dosis y mostrar el
                // número de vacunados. Para ello, se debe obtener su tarjeta de vacunación.

                int cont = 0;

                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].back() % 2 == 0) { // comprobacion par
                        u = gv.buscarUsuario(listadoNSS[i]);
                        t = gv.buscarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                        if (u != nullptr && t != nullptr && t->getId() == u->GetNSS() + "-" + u->GetNombre()) {
                            gv.vacunarUsuario(t);
                            cont++;
                        }
                    }
                }
                cout << "- Total vacunados NSS pares: " << cont << endl << endl;
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

                // Vacunar de la segunda dosis a todos los usuarios que tengan entre 20 y 50 años.

                cont = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].back() % 2 == 0) { // comprobacion par
                        u = gv.buscarUsuario(listadoNSS[i]);

                        if (u != nullptr) {
                            if (u->edad() <= 50 && u->edad() >= 20) { // comprobacion de edad
                                t = gv.buscarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                                if (t != nullptr && t->getId() == u->GetNSS() + "-" + u->GetNombre()) {
                                    gv.vacunarUsuario(t);
                                    cont++;
                                }
                            }
                        }
                    }
                }

                cout << "- Total vacunados segunda dosis: " << cont << endl << endl;
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

                // Vacunar a todos los usuarios cuyo NSS acabe en 2 o 6 que aún no tengan la pautacompleta.

                cont = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].back() == '2' || listadoNSS[i].back() == '6') { // comprobacion NSS
                        u = gv.buscarUsuario(listadoNSS[i]);
                        t = gv.buscarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                        if (u != nullptr && t != nullptr && t->getId() == u->GetNSS() + "-" + u->GetNombre()) {
                            gv.vacunarUsuario(t);
                            cont++;
                        }
                    } // comprobacion pauta completa
                    u = gv.buscarUsuario(listadoNSS[i]);
                    if (u != nullptr) {
                        t = gv.buscarTarjeta(u->GetNSS() + "-" + u->GetNombre());
                        if (t != nullptr && t->dosisPorAdministrar() != 0 && t->getId() == u->GetNSS() + "-" + u->GetNombre()) {
                            gv.vacunarUsuario(t);
                            cont++;
                        }
                    }
                }
                cout << endl << "- Total vacunados sin pauta completa o NSS acabe en 2 o 6: " << cont << endl << endl;
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

                // Comprobar cuántos usuarios tienen pasaporte covid.

                cout << "- Usuarios con pauta completa recomendable: " << gv.pautaCompletaRecomendable() << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // APARTADO PAREJAS:
                // Obtener el número de usuarios que tienen una dosis no recomendada y mostrarlo por pantalla

                vector<Usuario*> listadoVNR = gv.listadoVacunacionNR();
                cout << "- Usuarios con vacunacion no recomendable: " << listadoVNR.size() << endl << endl;
            }
        }

        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}