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
        cout << "--------------------------------------------------------------------------PRACTICA 3"
                "--------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------------"
                "-------------------------------------------------------------------------------" << endl << endl;

        // Crear un árbol AVL instanciado a 1000 enteros aleatorios y comprobar que todas las
        // funciones trabajan correctamente.

        int tipoEjecucion = 0;

        cout << "Elija el tipo de ejecucion: " << endl
                << "- Programa de prueba: 1" << endl
                << "- Programa de Gestion de Dosis: 2" << endl;
        cin >> tipoEjecucion;

        switch (tipoEjecucion) {
                /* PROGRAMA DE PRUEBA */
            case 1:
            {
                AVL<int> arbolPrueba;
                while (arbolPrueba.numElementos() != 1000) {
                    int aleatorio = rand() % 1001;
                    arbolPrueba.inserta(aleatorio);
                }
                cout << "Altura arbol prueba: " << arbolPrueba.altura() << endl;
                cout << "Num elementos arbol prueba: " << arbolPrueba.numElementos() << endl;
                cout << "Recorrido inorden: " << endl;
                arbolPrueba.recorreInorden();

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;
            }
                break;

                /* RESOLUCION PRACTICA 3 */
            default:
            case 2:
            {
                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Creacion del gestor de vacunas

                GestionVacunas gv("dosis2.txt", "usuarios2SinTildes.txt");
                int vacunasTotales = gv.verDosisRestantes();

                // Obtencion del listadoNSS

                VDinamico<string> listadoNSS;
                listadoNSS = gv.listadoCompletoNSS();
                cout << "Listado de NSS cargado: " << listadoNSS.tam() << " elementos" << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Administrar primera dosis a todos los usuarios
                // cuyo NSS no termine en '0'

                Usuario *u = new Usuario(); // usuario auxiliar para iterar
                Fabricante f; // tipo fabricante para iterar

                for (int i = 0; i < listadoNSS.tam(); i++) {
                    if (listadoNSS[i].back() != '0') {
                        u = gv.buscarUsuario(listadoNSS[i]);
                        if (u != nullptr) {
                            f = u->getDosisRecomendable();
                            gv.administrarDosis(*u, f);
                        }
                    }
                }

                cout << "Numero de dosis administradas: " << vacunasTotales - gv.verDosisRestantes() << endl << endl;
                cout << "Dosis restantes: " << gv.verDosisRestantes() << endl << endl;
                vacunasTotales = gv.verDosisRestantes();

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Administrar segunda dosis a todos los usuarios
                // cuyo NSS no termine en '0' o en '3'

                for (int i = 0; i < listadoNSS.tam(); i++) {
                    if (listadoNSS[i].back() != '0' && listadoNSS[i].back() != '3') {
                        u = gv.buscarUsuario(listadoNSS[i]);
                        if (u != nullptr) {
                            f = u->getDosisRecomendable();
                            gv.administrarDosis(*u, f);
                        }
                    }
                }

                cout << "Numero de dosis administradas: " << vacunasTotales - gv.verDosisRestantes() << endl << endl;
                cout << "Dosis restantes: " << gv.verDosisRestantes() << endl << endl;
                vacunasTotales = gv.verDosisRestantes();

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Administrar tercera dosis a usuarios
                // mayores de 75 anios
                for (int i = 0; i < listadoNSS.tam(); i++) {
                    u = gv.buscarUsuario(listadoNSS[i]);
                    if (u != nullptr && u->edad() > 75 && u->verDosis().tam() == 2) {
                        f = u->getDosisRecomendable();
                        gv.administrarDosis(*u, f);
                    }
                }

                cout << "Numero de dosis administradas: " << vacunasTotales - gv.verDosisRestantes() << endl << endl;
                cout << "Dosis restantes: " << gv.verDosisRestantes() << endl << endl;
                vacunasTotales = gv.verDosisRestantes();

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Porcentaje de personas con pauta completa

                cout << "El porcentaje de usuarios con pauta completa (con menores de 13 anios) es: " << gv.pautaCompleta() << "%" << endl << endl;
                cout << "El porcentaje de usuarios con pauta completa (sin contar menores de 13 anios) es: " << gv.pautaCompleta2() << "%" << endl << endl;

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Usuarios con vacunacion no recomendada
                VDinamico<Usuario*> usuariosVNR;
                usuariosVNR = gv.listadoVacunacionNR();

                cout << "Usuarios con vacunacion no recomendada: " << usuariosVNR.tam() << endl << endl;
                for (int i = 0; i < usuariosVNR.tam(); i++) {
                    cout << usuariosVNR[i] << endl;
                }

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;

                // Forzar la vacunación de la primera dosis de estos NSS que no han sido aún vacunados
                //con una dosis de Moderna: 1622650940; 1941046560; 1756824615; 1625692780; 1855345010

                f = Fabricante::Moderna;
                u = gv.buscarUsuario("1622650940");
                if (u != nullptr) {
                    gv.administrarDosis(*u, f);
                }

                u = gv.buscarUsuario("1941046560");
                if (u != nullptr) {
                    gv.administrarDosis(*u, f);
                }
                u = gv.buscarUsuario("1756824615");
                if (u != nullptr) {
                    gv.administrarDosis(*u, f);
                }
                u = gv.buscarUsuario("1625692780");
                if (u != nullptr) {
                    gv.administrarDosis(*u, f);
                }
                u = gv.buscarUsuario("1855345010");
                if (u != nullptr) {
                    gv.administrarDosis(*u, f);
                }

                // Usuarios con vacunacion no recomendada
                usuariosVNR = gv.listadoVacunacionNR();

                cout << "Usuarios con vacunacion no recomendada: " << usuariosVNR.tam() << endl << endl;
                cout << "Dosis restantes tras forzar vacuna: " << gv.verDosisRestantes() << endl << endl;

                //gv.verUsuarios(10);

                cout << "-------------------------------------------------------------------------------"
                        "-------------------------------------------------------------------------------" << endl << endl;
                break;
            }
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}