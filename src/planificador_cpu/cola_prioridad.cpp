//Codigo del Planificador de CPU

#include <iostream>
#include <string>
using namespace std;

/// Estructura que representa un proceso en la cola de prioridad
struct ProcesoCP {
    int id;      // Identificador único del proceso
    string nombre;      // Nombre del proceso
    int prioridad;      // Nivel de prioridad (mayor valor = más prioridad)
    ProcesoCP* siguiente;       // Puntero al siguiente proceso en la cola
};

// Clase que representa una cola de prioridad
class ColaPrioridad {
private:
    ProcesoCP* frente; // Apunta al proceso con mayor prioridad (al frente de la cola)

public:
    ColaPrioridad() {       // Constructor: inicializa la cola vacía
        frente = nullptr;
    }

    // Inserta un nuevo proceso en la cola según su prioridad (mayor prioridad adelante)
    void encolar(int id, string nombre, int prioridad) {
        if (nombre.empty() || prioridad < 0) {
            cout << "Datos inválidos. No se pudo encolar el proceso.\n";
            return;
        }

        ProcesoCP* nuevo = new ProcesoCP{id, nombre, prioridad, nullptr};

        // Si la cola está vacía o la nueva prioridad es mayor, insertar al inicio
        if (frente == nullptr || prioridad > frente->prioridad) {
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            // Buscar la posición correcta para insertar
            ProcesoCP* temp = frente;
            while (temp->siguiente != nullptr && temp->siguiente->prioridad >= prioridad) {
                temp = temp->siguiente;
            }
            nuevo->siguiente = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }

    // Elimina y ejecuta el proceso con mayor prioridad (al frente de la cola)
    void desencolar() {
        if (frente == nullptr) {
            cout << "Cola vacía, no hay procesos para ejecutar.\n";
            return;
        }

        ProcesoCP* eliminado = frente;
        frente = frente->siguiente;

        cout << "Ejecutando proceso ID: " << eliminado->id << ", Nombre: " << eliminado->nombre << endl;

        delete eliminado; // Liberar memoria del proceso ejecutado
    }

    // Muestra todos los procesos en la cola en orden de ejecución
    void mostrarCola() {
        if (frente == nullptr) {
            cout << "La cola está vacía.\n";
            return;
        }

        ProcesoCP* temp = frente;
        cout << "Cola de Prioridad:\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id
                 << ", Nombre: " << temp->nombre
                 << ", Prioridad: " << temp->prioridad << endl;
            temp = temp->siguiente;
        }
    }
};
