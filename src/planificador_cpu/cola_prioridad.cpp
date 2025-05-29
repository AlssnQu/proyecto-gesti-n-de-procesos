#include <iostream>
#include <string>
using namespace std;

struct ProcesoCP {
    int id;
    string nombre;
    int prioridad;
    ProcesoCP* siguiente;
};

class ColaPrioridad {
private:
    ProcesoCP* frente;

public:
    ColaPrioridad() {
        frente = nullptr;
    }

    void encolar(int id, string nombre, int prioridad) {
        ProcesoCP* nuevo = new ProcesoCP{id, nombre, prioridad, nullptr};
        if (frente == nullptr || prioridad > frente->prioridad) {
            
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            ProcesoCP* temp = frente;
            while (temp->siguiente != nullptr && temp->siguiente->prioridad >= prioridad) {
                temp = temp->siguiente;
            }
            nuevo->siguiente = temp->siguiente;

            temp->siguiente = nuevo;
        }
    }

    void desencolar() {
        if (frente == nullptr) {
            cout << "Cola vacía, no hay procesos para ejecutar....\n";
            return;
        }
        ProcesoCP* eliminado = frente;
        frente = frente->siguiente;
        cout << "Ejecutando proceso ID: " << eliminado->id << ", Nombre: " << eliminado->nombre << endl;
        delete eliminado;
    }

    void mostrarCola() {
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