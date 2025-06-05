#include <iostream>
#include "lista_enlazada.cpp"
#include "cola_prioridad.cpp"
#include "pila.cpp"

using namespace std;

void mostrarMenuPrincipal() {
    cout << "\n===== SISTEMA DE GESTIÓN DE PROCESOS =====\n";
    cout << "1. Gestor de Procesos\n";
    cout << "2. Planificador de CPU\n";
    cout << "3. Gestor de Memoria\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

void menuGestorProcesos() {
    int opcion;
    do {
        cout << "\n--- Gestor de Procesos ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // agregarProceso();
                break;
            case 2:
                // eliminarProceso();
                break;
            case 3:
                // mostrarProcesos();
                break;
            case 0:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
void menuPlanificadorCPU() {
    int opcion;
    do {
        cout << "\n--- Planificador de CPU ---\n";
        cout << "1. Agregar tarea\n";
        cout << "2. Ejecutar tarea\n";
        cout << "3. Mostrar tareas\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                encolar();
                break;
            case 2:
                ejecutarTarea();
                break;
            case 3:
                mostrarTareas();
                break;
            case 0:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuGestorMemoria() {
    int opcion;
    PilaMemoria pila; 
    do {
        cout << "\n--- Gestor de Memoria ---\n";
        cout << "1. Reservar memoria\n";
        cout << "2. Liberar memoria\n";
        cout << "3. Mostrar memoria\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                PilaMemoria.reservarMemoria();
                break;
            case 2:
                liberarMemoria();
                break;
            case 3:
                mostrarMemoria();
                break;
            case 0:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
int main() {
    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuGestorProcesos();
                break;
            case 2:
                menuPlanificadorCPU();
                break;
            case 3:
                menuGestorMemoria();
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}