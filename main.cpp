#include <iostream>
#include <string>
using namespace std;

// ==================== Estructuras y Clases ====================

// Estructura para procesos (compartida)
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    string estado;
    Proceso* siguiente;
};

// ----------------- Gestor de Procesos (Lista Enlazada) -----------------
class ListaProcesos {
private:
    Proceso* cabeza;

public:
    ListaProcesos() : cabeza(nullptr) {}

    void insertarProceso(int id, string nombre, int prioridad, string estado = "Nuevo") {
        if (buscarPorId(id)) {
            cout << "Error: ID " << id << " ya existe.\n";
            return;
        }

        Proceso* nuevo = new Proceso{id, nombre, prioridad, estado, nullptr};
        
        if (!cabeza || prioridad > cabeza->prioridad) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else {
            Proceso* actual = cabeza;
            while (actual->siguiente && prioridad <= actual->siguiente->prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso agregado.\n";
    }

    void eliminarProceso(int id) {
        if (!cabeza) {
            cout << "Lista vacía.\n";
            return;
        }

        if (cabeza->id == id) {
            Proceso* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cout << "Proceso " << id << " eliminado.\n";
            return;
        }

        Proceso* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }

        if (actual->siguiente) {
            Proceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            cout << "Proceso " << id << " eliminado.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    Proceso* buscarPorId(int id) {
        Proceso* temp = cabeza;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    Proceso* buscarPorNombre(string nombre) {
        Proceso* temp = cabeza;
        while (temp) {
            if (temp->nombre == nombre) return temp;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* proc = buscarPorId(id);
        if (proc) {
            proc->prioridad = nuevaPrioridad;
            cout << "Prioridad actualizada.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    void cambiarEstado(int id, string nuevoEstado) {
        Proceso* proc = buscarPorId(id);
        if (proc) {
            proc->estado = nuevoEstado;
            cout << "Estado actualizado.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    void mostrarProcesos() {
        if (!cabeza) {
            cout << "No hay procesos.\n";
            return;
        }

        Proceso* temp = cabeza;
        while (temp) {
            cout << "ID: " << temp->id 
                 << " | Nombre: " << temp->nombre 
                 << " | Prioridad: " << temp->prioridad 
                 << " | Estado: " << temp->estado << endl;
            temp = temp->siguiente;
        }
    }
};

// ----------------- Planificador de CPU (Cola Prioridad) -----------------
class ColaPrioridad {
private: 
    Proceso* frente;

public:
    ColaPrioridad() : frente(nullptr) {}

    void encolar(int id, string nombre, int prioridad) {
        Proceso* nuevo = new Proceso{id, nombre, prioridad, "En espera", nullptr};
        
        if (!frente || prioridad > frente->prioridad) {
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            Proceso* actual = frente;
            while (actual->siguiente && prioridad <= actual->siguiente->prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    void desencolar() {
        if (!frente) {
            cout << "Cola vacía.\n";
            return;
        }

        Proceso* temp = frente;
        frente = frente->siguiente;
        cout << "Ejecutando: " << temp->nombre << " (ID: " << temp->id << ")\n";
        delete temp;
    }

    void mostrarCola() {
        if (!frente) {
            cout << "Cola vacía.\n";
            return;
        }

        Proceso* temp = frente;
        while (temp) {
            cout << "ID: " << temp->id 
                 << " | Nombre: " << temp->nombre 
                 << " | Prioridad: " << temp->prioridad << endl;
            temp = temp->siguiente;
        }
    }
};

// ----------------- Gestor de Memoria (Pila) -----------------
struct BloqueMemoria {
    int id;
    int tamano;
    BloqueMemoria* siguiente;
};

class PilaMemoria {
private:
    BloqueMemoria* cima;

public:
    PilaMemoria() : cima(nullptr) {}

    void asignarMemoria(int id, int tamano) {
        BloqueMemoria* nuevo = new BloqueMemoria{id, tamano, cima};
        cima = nuevo;
        cout << "Memoria asignada (ID: " << id << ", Tamaño: " << tamano << ")\n";
    }

    void liberarMemoria() {
        if (!cima) {
            cout << "Pila vacía.\n";
            return;
        }

        BloqueMemoria* temp = cima;
        cima = cima->siguiente;
        cout << "Liberando bloque (ID: " << temp->id << ", Tamaño: " << temp->tamano << ")\n";
        delete temp;
    }

    void mostrarMemoria() {
        if (!cima) {
            cout << "Pila vacía.\n";
            return;
        }

        BloqueMemoria* temp = cima;
        while (temp) {
            cout << "ID: " << temp->id << " | Tamaño: " << temp->tamano << endl;
            temp = temp->siguiente;
        }
    }
};

// ==================== Menús y Main ====================
ListaProcesos listaProcesos;
ColaPrioridad colaCPU;
PilaMemoria pilaMemoria;

void menuGestorProcesos() {
    int opcion;
    do {
        cout << "\n--- Gestor de Procesos ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Modificar prioridad\n";
        cout << "4. Cambiar estado\n";
        cout << "5. Buscar por ID\n";
        cout << "6. Buscar por nombre\n";
        cout << "7. Mostrar todos\n";
        cout << "8. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        int id, prioridad;
        string nombre, estado;
        Proceso* encontrado;

        switch (opcion) {
            case 1:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Prioridad: "; cin >> prioridad;
                listaProcesos.insertarProceso(id, nombre, prioridad);
                break;
            case 2:
                cout << "ID a eliminar: "; cin >> id;
                listaProcesos.eliminarProceso(id);
                break;
            case 3:
                cout << "ID: "; cin >> id;
                cout << "Nueva prioridad: "; cin >> prioridad;
                listaProcesos.modificarPrioridad(id, prioridad);
                break;
            case 4:
                cout << "ID: "; cin >> id;
                cout << "Nuevo estado: "; cin >> estado;
                listaProcesos.cambiarEstado(id, estado);
                break;
            case 5:
                cout << "ID: "; cin >> id;
                encontrado = listaProcesos.buscarPorId(id);
                if (encontrado) cout << "Encontrado: " << encontrado->nombre << endl;
                else cout << "No encontrado.\n";
                break;
            case 6:
                cout << "Nombre: "; cin >> nombre;
                encontrado = listaProcesos.buscarPorNombre(nombre);
                if (encontrado) cout << "Encontrado: ID " << encontrado->id << endl;
                else cout << "No encontrado.\n";
                break;
            case 7:
                listaProcesos.mostrarProcesos();
                break;
            case 8:
                cout << "Adios, vuelva pronto.";
                break;
        }
    } while (opcion != 8);
}

void menuPlanificadorCPU() {
    int opcion;
    do {
        cout << "\n--- Planificador CPU ---\n";
        cout << "1. Agregar tarea\n";
        cout << "2. Ejecutar tarea\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        int id, prioridad;
        string nombre;

        switch (opcion) {
            case 1:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Prioridad: "; cin >> prioridad;
                colaCPU.encolar(id, nombre, prioridad);
                break;
            case 2:
                colaCPU.desencolar();
                break;
            case 3:
                colaCPU.mostrarCola();
                break;
            case 4:
                cout << "Adios, vuelva pronto.";
                break;
        }
    } while (opcion != 4);
}

void menuGestorMemoria() {
    int opcion;
    do {
        cout << "\n--- Gestor de Memoria ---\n";
        cout << "1. Reservar memoria\n";
        cout << "2. Liberar memoria\n";
        cout << "3. Mostrar pila\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        int id, tamano;

        switch (opcion) {
            case 1:
                cout << "ID proceso: "; cin >> id;
                cout << "Tamaño: "; cin >> tamano;
                pilaMemoria.asignarMemoria(id, tamano);
                break;
            case 2:
                pilaMemoria.liberarMemoria();
                break;
            case 3:
                pilaMemoria.mostrarMemoria();
                break;
            case 4:
                cout << "Adios, vuelva pronto.";
                break;
        }
    } while (opcion != 4);
}

int main() {
    int opcion;
    do {
        cout << "\n===== Sistema de Gestión =====\n";
        cout << "1. Gestor de Procesos\n";
        cout << "2. Planificador CPU\n";
        cout << "3. Gestor de Memoria\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
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
            case 4:
                cout << "Adios, vuelva pronto.";
                break;
        }
    } while (opcion != 4);

    return 0;
}