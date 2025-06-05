//Codigo del Gestor de memoria

#include <iostream>
using namespace std;

// Estructura que representa un bloque de memoria asignado a un proceso
struct BloqueMemoria {
    int idProceso;              // ID del proceso que ocupa el bloque
    int tamano;                 // Tamaño del bloque de memoria asignado
    BloqueMemoria* siguiente;   // Puntero al siguiente bloque (bloque anterior en la pila)
};

class PilaMemoria {
private:
    BloqueMemoria* cima; // Puntero al tope de la pila (último bloque asignado)

public:
    // Constructor: Inicializa la pila vacía
    PilaMemoria() {
        cima = nullptr;
    }

    // Función para asignar memoria (push)
    void asignarMemoria(int idProceso, int tamano) {
        if (idProceso <= 0 || tamano <= 0) {
            cout << "Error, el ID de proceso y tamaño deben ser mayores que cero.\n";
            return;
        }

        BloqueMemoria* nuevo = new BloqueMemoria{idProceso, tamano, cima};
        cima = nuevo;

        cout << "Memoria asignada exitosamente al proceso ID: " << idProceso << " (Tamaño: " << tamano << " unidades).\n";
    }

    // Función para liberar memoria (sin pop)
    void liberarMemoria() {
        if (cima == nullptr) {
            cout << "No hay bloques de memoria para liberar.\n";
            return;
        }

        BloqueMemoria* eliminado = cima;
        cima = cima->siguiente;

        cout << "Memoria liberada del proceso ID: " << eliminado->idProceso << " (Tamaño: " << eliminado->tamano << " unidades).\n";
        delete eliminado;   // 
    }

    // Función para mostrar el estado actual de la pila de memoria
    void mostrarMemoria() {
        if (cima == nullptr) {
            cout << "La pila de memoria está vacía.\n";
            return;
        }

        BloqueMemoria* temp = cima;
        cout << "Estado actual de la memoria (de cima a base):\n";
        while (temp != nullptr) {
            cout << "- Proceso ID: " << temp->idProceso << ", Tamaño: " << temp->tamano << "\n";
            temp = temp->siguiente;
        }
    }
};