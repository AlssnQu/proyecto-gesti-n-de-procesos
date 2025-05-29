#include <iostream>
#include <string>
using namespace std;

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
};

class ListaProcesos {
private:
    Proceso* cabeza;

public:
    ListaProcesos() {
        cabeza = nullptr;
    }

    void insertarProceso(int id, string nombre, int prioridad) {
        Proceso* nuevo = new Proceso{id, nombre, prioridad, nullptr};
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Proceso* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
    }

    void eliminarProceso(int id) {
        if (cabeza == nullptr) return;
        if (cabeza->id == id) {
            Proceso* eliminado = cabeza;
            cabeza = cabeza->siguiente;
            delete eliminado;
            return;
        }

        Proceso* temp = cabeza;
        while (temp->siguiente != nullptr && temp->siguiente->id != id) {
            temp = temp->siguiente;
        }

        if (temp->siguiente != nullptr) {
            Proceso* eliminado = temp->siguiente;
            temp->siguiente = temp->siguiente->siguiente;
            delete eliminado;
        }
    }

    Proceso* buscarPorId(int id) {
        Proceso* temp = cabeza;
        while (temp != nullptr) {
            if (temp->id == id) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    Proceso* buscarPorNombre(string nombre) {
        Proceso* temp = cabeza;
        while (temp != nullptr) {
            if (temp->nombre == nombre) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* proceso = buscarPorId(id);
        if (proceso != nullptr) {
            proceso->prioridad = nuevaPrioridad;
        }
    }

    void mostrarProcesos() {
        Proceso* temp = cabeza;
        while (temp != nullptr) {
            cout << "ID: " << temp->id
                 << ", Nombre: " << temp->nombre
                 << ", Prioridad: " << temp->prioridad << endl;
            temp = temp->siguiente;
        }
    }
};