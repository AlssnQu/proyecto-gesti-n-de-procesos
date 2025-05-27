#include <iostream>
#include <string>
#include "lista_enlazada.cpp"
#include "cola_prioridad.cpp"
#include "pila.cpp"

using namespace std;

int main() {
    ListaProcesos lista;
    ColaPrioridad cola;
    PilaMemoria pila;

    int opcion;
    do {
        cout << "\n--- Sistema de Gestión de Procesos ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso por ID\n";
        cout << "4. Modificar prioridad de proceso\n";
        cout << "5. Mostrar lista de procesos\n";
        cout << "6. Encolar proceso en planificador\n";
        cout << "7. Ejecutar proceso del planificador\n";
        cout << "8. Mostrar cola de prioridad\n";
        cout << "9. Asignar memoria a proceso\n";
        cout << "10. Liberar memoria\n";
        cout << "11. Mostrar estado de memoria\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if(opcion == 1) {
            int id, prioridad;
            string nombre;
            cout << "ID: "; cin >> id;
            cout << "Nombre: "; cin.ignore(); getline(cin, nombre);
            cout << "Prioridad: "; cin >> prioridad;
            lista.insertarProceso(id, nombre, prioridad);
            cout << "Proceso agregado.\n";
        } else if(opcion == 2) {
            int id;
            cout << "ID del proceso a eliminar: "; cin >> id;
            lista.eliminarProceso(id);
            cout << "Proceso eliminado si existía.\n";
        } else if(opcion == 3) {
            int id;
            cout << "ID del proceso a buscar: "; cin >> id;
            Proceso* p = lista.buscarPorId(id);
            if(p) {
                cout << "Proceso encontrado: " << p->nombre << ", Prioridad: " << p->prioridad << endl;
            } else {
                cout << "Proceso no encontrado.\n";
            }
        } else if(opcion == 4) {
            int id, prioridad;
            cout << "ID del proceso: "; cin >> id;
            cout << "Nueva prioridad: "; cin >> prioridad;
            lista.modificarPrioridad(id, prioridad);
            cout << "Prioridad modificada.\n";
        } else if(opcion == 5) {
            lista.mostrarProcesos();
        } else if(opcion == 6) {
            int id;
            cout << "ID del proceso a encolar: "; cin >> id;
            Proceso* p = lista.buscarPorId(id);
            if(p) {
                cola.encolar(p->id, p->nombre, p->prioridad);
                cout << "Proceso encolado en planificador.\n";
            } else {
                cout << "Proceso no encontrado en la lista.\n";
            }
        } else if(opcion == 7) {
            cola.desencolar();
        } else if(opcion == 8) {
            cola.mostrarCola();
        } else if(opcion == 9) {
            int idProceso, tamano;
            cout << "ID del proceso: "; cin >> idProceso;
            cout << "Tamaño de memoria a asignar: "; cin >> tamano;
            pila.asignarMemoria(idProceso, tamano);
            cout << "Memoria asignada.\n";
        } else if(opcion == 10) {
            pila.liberarMemoria();
        } else if(opcion == 11) {
            pila.mostrarMemoria();
        }

    } while(opcion != 0);

    return 0;
}