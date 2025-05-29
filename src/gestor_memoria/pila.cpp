#include <iostream>
using namespace std;

struct BloqueMemoria {
    int idProceso;
    int tamano;
    BloqueMemoria* siguiente;
};

class PilaMemoria {
private:
    BloqueMemoria* cima;

public:
    PilaMemoria() {
        cima = nullptr;
    }

    // Asignar memoria (agregar al tope) sin usar push 
    void asignarMemoria(int idProceso, int tamano) {
        BloqueMemoria* nuevo = new BloqueMemoria{idProceso, tamano, cima};
        cima = nuevo;
    }

    // Liberar memoria (quitar del tope) sin usar pop 
    void liberarMemoria() {
        if (cima == nullptr) {
            cout << "No hay memoria establecida para liberar.\n";
            return;
        }
        BloqueMemoria* eliminado = cima;
        cima = cima->siguiente;
        cout << "Memoria liberada del proceso ID: " << eliminado->idProceso << endl;
        delete eliminado;
    }

    void mostrarMemoria() {
        BloqueMemoria* temp = cima;
        cout << "Estado de la Memoria (de cima a base):\n";
        while (temp != nullptr) {
            cout << "Proceso ID: " << temp->idProceso << ", Tamaño: " << temp->tamano << endl;
            temp = temp->siguiente;
        }
    }
};