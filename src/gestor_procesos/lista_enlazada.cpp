//Codigo del Gestor de procesos

#include <iostream>
#include <string>
using namespace std;

// Estructura que representa un proceso en la lista
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    string estado;
    Proceso* siguiente;
};

// Clase que gestiona los procesos usando una lista enlazada
class ListaProcesos {
private:
    Proceso* cabeza; // Apunta al primer proceso

public:
    // Constructor
    ListaProcesos() {
        cabeza = nullptr;
    }

    // Inserta un nuevo proceso al final de la lista
    void insertarProceso(int id, string nombre, int prioridad, string estado = "Nuevo") {
        if (buscarPorId(id)) {
            cout << "Error: Ya existe un proceso con el ID " << id << ".\n";
            return;
        }
        if (prioridad < 0) {
            cout << "Error: La prioridad debe ser un número positivo.\n";
            return;
        }

        Proceso* nuevo = new Proceso{id, nombre, prioridad, estado, nullptr};

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Proceso* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }

        cout << "Proceso agregado exitosamente.\n";
    }

    // Elimina un proceso por su ID
    void eliminarProceso(int id) {
        if (cabeza == nullptr) {
            cout << "No hay procesos registrados.\n";
            return;
        }

        if (cabeza->id == id) {
            Proceso* eliminado = cabeza;
            cabeza = cabeza->siguiente;
            delete eliminado;
            cout << "Proceso con ID " << id << " eliminado.\n";
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
            cout << "Proceso con ID " << id << " eliminado.\n";
        } else {
            cout << "No se encontró un proceso con el ID " << id << ".\n";
        }
    }

    // Busca un proceso por su ID
    Proceso* buscarPorId(int id) {
        Proceso* temp = cabeza;
        while (temp != nullptr) {
            if (temp->id == id) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    // Busca un proceso por su nombre
    Proceso* buscarPorNombre(string nombre) {
        Proceso* temp = cabeza;
        while (temp != nullptr) {
            if (temp->nombre == nombre) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    // Modifica la prioridad de un proceso por ID
    void modificarPrioridad(int id, int nuevaPrioridad) {
        if (nuevaPrioridad < 0) {
            cout << "Error: La prioridad debe ser un número positivo.\n";
            return;
        }
        Proceso* proceso = buscarPorId(id);
        if (proceso != nullptr) {
            proceso->prioridad = nuevaPrioridad;
            cout << "Prioridad actualizada correctamente.\n";
        } else {
            cout << "No se encontró el proceso con ID " << id << ".\n";
        }
    }

    // Cambia el estado de un proceso
    void cambiarEstado(int id, string nuevoEstado) {
        Proceso* proceso = buscarPorId(id);
        if (proceso != nullptr) {
            proceso->estado = nuevoEstado;
            cout << "Estado actualizado correctamente.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    // Muestra todos los procesos en la lista
    void mostrarProcesos() {
        if (cabeza == nullptr) {
            cout << "No hay procesos registrados.\n";
            return;
        }

        Proceso* temp = cabeza;
        cout << "Lista de Procesos:\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id
                << ", Nombre: " << temp->nombre
                << ", Prioridad: " << temp->prioridad
                << ", Estado: " << temp->estado << endl;
            temp = temp->siguiente;
        }
    }
};