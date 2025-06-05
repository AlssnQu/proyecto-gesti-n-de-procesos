#include <iostream>
#include <string>
using namespace std;

// ==================== Estructuras y Clases ====================

// Estructura para procesos (compartida)
struct Proceso {
    int id;             // Identificador único (número entero)
    string nombre;      // Nombre descriptivo (ej: "Proceso_A")
    int prioridad;      // Nivel de prioridad (mayor valor = más urgente)
    string estado;      // Estado actual: "Nuevo", "Listo", "En espera", etc.
    Proceso* siguiente; // Puntero al siguiente proceso en listas/colas
};

// ----------------- Gestor de Procesos (Lista Enlazada) -----------------
class ListaProcesos {
private:
    Proceso* cabeza;  // Puntero al primer nodo de la lista

public:
    //Constructor: Inicializa una lista vacía.
    ListaProcesos() : cabeza(nullptr) {}

     //prioridad Valor de prioridad (mayor = más importante)
     //estado Estado inicial del proceso (por defecto "Nuevo")

    void insertarProceso(int id, string nombre, int prioridad, string estado = "Nuevo") {
        // Validación de ID único
        if (buscarPorId(id)) {
            cout << "Error: ID " << id << " ya existe.\n";
            return;
        }

        // Creación del nuevo nodo
        Proceso* nuevo = new Proceso{id, nombre, prioridad, estado, nullptr};
        
        // Caso 1: Insertar al inicio (lista vacía o mayor prioridad que cabeza)
        if (!cabeza || prioridad > cabeza->prioridad) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } 
        // Caso 2: Buscar posición adecuada según prioridad
        else {
            Proceso* actual = cabeza;
            // Avanzar mientras exista siguiente nodo y su prioridad sea mayor o igual
            while (actual->siguiente && prioridad <= actual->siguiente->prioridad) {
                actual = actual->siguiente;
            }
            // Insertar el nuevo nodo en la posición encontrada
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso agregado.\n";
    }

     //id Identificador del proceso a eliminar
    void eliminarProceso(int id) {
        // Validar lista vacía
        if (!cabeza) {
            cout << "Lista vacía.\n";
            return;
        }

        // Caso 1: Eliminar el nodo cabeza
        if (cabeza->id == id) {
            Proceso* temp = cabeza;
            cabeza = cabeza->siguiente;  // Actualizar cabeza
            delete temp;  // Liberar memoria
            cout << "Proceso " << id << " eliminado.\n";
            return;
        }

        // Caso 2: Buscar nodo a eliminar
        Proceso* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }

        // Si se encontró el nodo
        if (actual->siguiente) {
            Proceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;  // Reenlazar nodos
            delete temp;  // Liberar memoria
            cout << "Proceso " << id << " eliminado.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

     //id Identificador del proceso a buscar
     // return Puntero al proceso encontrado o nullptr si no existe

    Proceso* buscarPorId(int id) {
        Proceso* temp = cabeza;
        // Recorrer lista hasta encontrar el ID
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->siguiente;
        }
        return nullptr;  // No encontrado
    }

     //nombre Nombre del proceso a buscar
     //return Puntero al proceso encontrado o nullptr si no existe
    Proceso* buscarPorNombre(string nombre) {
        Proceso* temp = cabeza;
        // Recorrer lista hasta encontrar el nombre
        while (temp) {
            if (temp->nombre == nombre) return temp;
            temp = temp->siguiente;
        }
        return nullptr;  // No encontrado
    }

     // id Identificador del proceso
     // nuevaPrioridad: Nuevo valor de prioridad
    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* proc = buscarPorId(id);
        if (proc) {
            proc->prioridad = nuevaPrioridad;
            cout << "Prioridad actualizada.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    //Cambia el estado de un proceso existente.
    // id Identificador del proceso
    // nuevoEstado Nuevo estado del proceso
    void cambiarEstado(int id, string nuevoEstado) {
        Proceso* proc = buscarPorId(id);
        if (proc) {
            proc->estado = nuevoEstado;
            cout << "Estado actualizado.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    /**
     * Muestra todos los procesos en la lista en orden de prioridad.
     * Formato: ID | Nombre | Prioridad | Estado
     */
    void mostrarProcesos() {
        if (!cabeza) {
            cout << "No hay procesos.\n";
            return;
        }

        Proceso* temp = cabeza;
        // Recorrer e imprimir cada proceso
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
/**
 * Clase que implementa una cola de prioridad para gestionar procesos.
 * Los elementos con mayor prioridad se encuentran al frente y son atendidos primero.
 */
class ColaPrioridad {
private: 
    Proceso* frente; // Puntero al primer elemento de la cola (mayor prioridad)

public:
    //Constructor - Inicializa una cola vacía
    ColaPrioridad() : frente(nullptr) {}

    //Añade un nuevo proceso a la cola según su prioridad
    // id Identificador único del proceso
    //nombre Nombre descriptivo del proceso
    // prioridad Valor numérico que determina la prioridad (mayor = más prioritario)
    void encolar(int id, string nombre, int prioridad) {
        // Crear nuevo proceso con estado "En espera"
        Proceso* nuevo = new Proceso{id, nombre, prioridad, "En espera", nullptr};

        // Caso 1: Cola vacía o nueva prioridad mayor que el frente
        if (!frente || prioridad > frente->prioridad) {
            nuevo->siguiente = frente; // El nuevo apunta al antiguo frente
            frente = nuevo;           // Actualizar el frente
        } 
        // Caso 2: Buscar posición adecuada en la cola
        else {
            Proceso* actual = frente;
            // Avanzar mientras haya siguiente y la prioridad sea menor o igual
            while (actual->siguiente && prioridad <= actual->siguiente->prioridad) {
                actual = actual->siguiente;
            }
            // Insertar el nuevo nodo en la posición encontrada
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    //Elimina y procesa el elemento con mayor prioridad (frente de la cola)
    //Muestra información del proceso que se está ejecutando
    void desencolar() {
        // Verificar si la cola está vacía
        if (!frente) {
            cout << "Cola vacía.\n";
            return;
        }

        // Guardar referencia al proceso a eliminar
        Proceso* temp = frente;
        // Avanzar el frente al siguiente proceso
        frente = frente->siguiente;
        
        // Mostrar información del proceso que se ejecuta
        cout << "Ejecutando: " << temp->nombre << " (ID: " << temp->id << ")\n";
        
        // Liberar memoria del proceso eliminado
        delete temp;
    }

    //Muestra todos los procesos en la cola en orden de prioridad
    //Formato: ID | Nombre | Prioridad
    void mostrarCola() {
        // Verificar si la cola está vacía
        if (!frente) {
            cout << "Cola vacía.\n";
            return;
        }

        // Recorrer la cola desde el frente
        Proceso* temp = frente;
        while (temp) {
            // Imprimir detalles del proceso actual
            cout << "ID: " << temp->id 
                 << " | Nombre: " << temp->nombre 
                 << " | Prioridad: " << temp->prioridad << endl;
            // Avanzar al siguiente proceso
            temp = temp->siguiente;
        }
    }
};

// ----------------- Gestor de Memoria (Pila) -----------------
struct BloqueMemoria {
    int id;             // ID del proceso dueño del bloque
    int tamano;         // Tamaño del bloque de memoria (en unidades)
    BloqueMemoria* siguiente; // Puntero al siguiente bloque en la pila
};

//Clase que implementa una estructura de pila (LIFO) para gestión de memoria
 //Cada operación de asignación/liberación trabaja con el bloque en la cima
class PilaMemoria {
private:
    BloqueMemoria* cima;  // Puntero al bloque en la parte superior de la pila

public:
    //Constructor - Inicializa una pila vacía
    PilaMemoria() : cima(nullptr) {}

    // Asigna un nuevo bloque de memoria a la pila
    //id Identificador único del bloque de memoria
     // tamano Tamaño en bytes del bloque a asignar
    void asignarMemoria(int id, int tamano) {
        // Crear nuevo bloque (apunta al actual cima como siguiente)
        BloqueMemoria* nuevo = new BloqueMemoria{id, tamano, cima};
        
        // El nuevo bloque se convierte en la cima
        cima = nuevo;
        
        // Mensaje de confirmación
        cout << "Memoria asignada (ID: " << id << ", Tamaño: " << tamano << ")\n";
    }

    // Libera el bloque de memoria en la cima de la pila
    // Sigue el principio LIFO (Last In, First Out)
    void liberarMemoria() {
        // Verificar si la pila está vacía
        if (!cima) {
            cout << "Pila vacía.\n";
            return;
        }

        // Guardar referencia al bloque a liberar
        BloqueMemoria* temp = cima;
        
        // La nueva cima será el siguiente bloque
        cima = cima->siguiente;
        
        cout << "Liberando bloque (ID: " << temp->id << ", Tamaño: " << temp->tamano << ")\n";
        
        // Eliminar el bloque de memoria
        delete temp;
    }

    //Muestra el contenido actual de la pila de memoria
    // Desde la cima hasta la base
    void mostrarMemoria() {
        // Verificar si la pila está vacía
        if (!cima) {
            cout << "Pila vacía.\n";
            return;
        }

        // Recorrer la pila desde la cima
        BloqueMemoria* temp = cima;
        while (temp) {
            // Mostrar detalles del bloque actual
            cout << "ID: " << temp->id << " | Tamaño: " << temp->tamano << endl;
            
            // Avanzar al siguiente bloque
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