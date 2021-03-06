
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
                GestionVacunas gv;
                THashTarjetaVacunacion tabla1(15383, 0);
                THashTarjetaVacunacion tabla2(15383, 1);
                THashTarjetaVacunacion tabla3(15383, 2);

                vector <string> listadoNSS = gv.listadoCompletoNSS();
                Usuario *u;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    TarjetaVacunacion t;
                    u = gv.buscarUsuario(listadoNSS[i]);
                    t.setId(u->GetNSS() + "-" + u->GetNombre());
                    tabla1.insertar(stol(u->GetNSS()), t);
                    tabla2.insertar(stol(u->GetNSS()), t);
                    tabla3.insertar(stol(u->GetNSS()), t);
                }
                cout << "*ESTADISTICAS HASH1 - TAM TABLA: 15383*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla1.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla1.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla1.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla1.promedioColisiones() << endl << endl;

                cout << "*ESTADISTICAS HASH2 - TAM TABLA: 15383*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla2.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla2.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla2.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla2.promedioColisiones() << endl << endl;

                cout << "*ESTADISTICAS HASH3 - TAM TABLA: 15383*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla3.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla3.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla3.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla3.promedioColisiones() << endl << endl;

                THashTarjetaVacunacion tabla4(14713, 0);
                THashTarjetaVacunacion tabla5(14713, 1);
                THashTarjetaVacunacion tabla6(14713, 2);

                for (int i = 0; i < listadoNSS.size(); i++) {
                    TarjetaVacunacion t;
                    u = gv.buscarUsuario(listadoNSS[i]);
                    t.setId(u->GetNSS() + "-" + u->GetNombre());
                    tabla4.insertar(stol(u->GetNSS()), t);
                    tabla5.insertar(stol(u->GetNSS()), t);
                    tabla6.insertar(stol(u->GetNSS()), t);
                }

                cout << "*ESTADISTICAS HASH1 - TAM TABLA: 14713*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla4.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla4.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla4.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla4.promedioColisiones() << endl << endl;

                cout << "*ESTADISTICAS HASH2 - TAM TABLA: 14713*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla5.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla5.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla5.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla1.promedioColisiones() << endl << endl;

                cout << "*ESTADISTICAS HASH3 - TAM TABLA: 14713*" << endl;
                cout << "- Numero tarjetas insertadas: " << tabla6.numTarjetas() << endl;
                cout << "- Factor carga: " << tabla6.factorCarga() << endl;
                cout << "- Maximo Colisiones: " << tabla6.maxColisiones() << endl;
                cout << "- Promedio colisiones: " << tabla6.promedioColisiones() << endl << endl;
            }
                break;

                // RESOLUCION PRACTICA 5
            default:
            case 2:
            {
                // Proceso de iniciacion de la practica anterior

                GestionVacunas gv;
                Usuario *u;
                TarjetaVacunacion *t;
                vector <string> listadoNSS = gv.listadoCompletoNSS();

                gv.suministrarNDosisAlCentro(gv.buscarCentro(1), 8000);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(2), 8200);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(3), 8500);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(4), 5000);
                gv.suministrarNDosisAlCentro(gv.buscarCentro(5), 50);

                cout << endl << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------"
                        << endl << endl;

                // Generacion de Tarjetas de Vacunacion

                int conte = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    gv.cargarTarjetas(listadoNSS[i]);
                }
                cout << "- Tarjetas cargadas: " << conte << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Mostrar factor de carga y tam de la tabla Hash

                cout << "- Factor de carga: " << endl
                        << "- Tam de la tabla: " << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Eliminar las tarjetas de vacunaci??n de todos los usuarios cuyo NSS acabe en ???0??? de la tabla hash.

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
                        "-------------------------------------------------------------------------------"
                        << endl << endl;

                // A??adir las tarjetas de vacunaci??n anteriormente borradas de aquellos usuarios cuyo NSS acabe en ???30??? a la tabla hash.

                conte = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].at(8) == '3' && listadoNSS[i].back() == '0') {
                        gv.cargarTarjetas(listadoNSS[i]);
                        conte++;
                    }
                }

                cout << "- Tarjetas cargadas: " << conte << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Mostrar el n??mero de colisiones m??ximo que se han producido al volver a insertar las tarjetas de vacunaci??n.

                cout << "- Total colisiones: " << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Vacunar a todos los usuarios cuyo NSS sea par de la primera dosis y mostrar el
                // n??mero de vacunados. Para ello, se debe obtener su tarjeta de vacunaci??n.

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
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Vacunar de la segunda dosis a todos los usuarios que tengan entre 20 y 50 a??os.

                cont = 0;
                for (int i = 0; i < listadoNSS.size(); i++) {
                    if (listadoNSS[i].back() % 2 == 0) { // comprobacion par para vacunar segunda dosis
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
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Vacunar a todos los usuarios cuyo NSS acabe en 2 o 6 que a??n no tengan la pautacompleta.

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
                        if (t != nullptr && t->dosisPorAdministrar() != 0 &&
                                t->getId() == u->GetNSS() + "-" + u->GetNombre()) {
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
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // Comprobar cu??ntos usuarios tienen pasaporte covid.

                cout << "- Usuarios con pasaporte covid: " << gv.pasaporteCovid() << endl;
                cout << "- Usuarios con pauta completa recomendable: " << gv.pautaCompletaRecomendable() << endl
                        << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl
                        << endl;

                // APARTADO PAREJAS:
                // Obtener el n??mero de usuarios que tienen una dosis no recomendada y mostrarlo por pantalla

                vector < Usuario * > listadoVNR = gv.listadoVacunacionNR();
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