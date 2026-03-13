#include <iostream>
#include <vector>
using namespace std;

// Capacidades maximas para los arreglos de caracteres
const int MAX_NOMBRE = 100, MAX_DIAGNOSTICO = 200, MAX_FECHA = 20, MAX_ESTADO = 20;

// Funciones auxiliares para manejo de cadenas

// Calcula la longitud de una cadena
int longitud(const char* s){
    int l = 0;
    while (s[l]) l++;
    return l;
}

// Copia una cadena en otra
void copiar(char* destino, const char* fuente) {
    while ((*destino++ = *fuente++));
}

// Compara dos cadenas
int comparar(const char* a, const char* b) {
    while (*a && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)(*a) - (unsigned char)(*b);
}

// Busca una subcadena dentro de un texto
const char* encontrar(const char* texto, const char* subcadena) {
    if (!*subcadena) return texto;
    for (int i = 0; texto[i]; i++) {
        int j = 0;
        while (subcadena[j] && texto[i + j] == subcadena[j]) j++;
        if (!subcadena[j]) return &texto[i];
    }
    return NULL;
}

// Estructura para llevar el conteo de diagnósticos en el reporte
struct ContadorDiagnostico {
    char diagnostico[MAX_DIAGNOSTICO];
    int cantidad;
};

// Clase base abstracta Persona
class Persona {
protected:
    char nombre[MAX_NOMBRE];   // Atributo nombre
    int edad;                  // Atributo edad
public:
    // Constructor: inicializa nombre y edad
    Persona(const char* nombre, int edad) : edad(edad) {
        copiar(this->nombre, nombre);
    }

    // Destructor virtual para permitir la correcta liberación de objetos derivados
    virtual ~Persona() {}

    // Metodos de acceso
    const char* getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    void setNombre(const char* n) { copiar(nombre, n); }
    void setEdad(int e) { edad = e; }

    // Metodo virtual puro: obliga a las clases derivadas a implementar su propia
    virtual void mostrar() const = 0;
};

// Clase derivada Paciente (hereda de Persona)
class Paciente : public Persona {
private:
    int id;                         // Identificador unico del paciente
    char diagnostico[MAX_DIAGNOSTICO]; // Diagnostico medico
    char fecha[MAX_FECHA];           // Fecha de atencion
    char estado[MAX_ESTADO];         // Estado: "Atendido" o "En espera"
public:
    // Constructor: llama al constructor de Persona y luego copia los campos especificos
    Paciente(int id, const char* nombre, int edad, const char* diag, const char* fecha, const char* estado)
        : Persona(nombre, edad), id(id) {
        copiar(this->diagnostico, diag);
        copiar(this->fecha, fecha);
        copiar(this->estado, estado);
    }

    // Getters especificos de Paciente
    int getId() const { return id; }
    const char* getDiagnostico() const { return diagnostico; }
    const char* getFecha() const { return fecha; }
    const char* getEstado() const { return estado; }

    // Setters especificos
    void setDiagnostico(const char* d) { copiar(diagnostico, d); }
    void setFecha(const char* f) { copiar(fecha, f); }
    void setEstado(const char* e) { copiar(estado, e); }

    // Implementacion polimorfismo
    void mostrar() const override {
        cout << "ID: " << id << "\nNombre: " << nombre << "\nEdad: " << edad
             << "\nDiagnostico: " << diagnostico << "\nFecha: " << fecha
             << "\nEstado: " << estado << "\n---\n";
    }
};

// LAs funciones del menu
void registrar(vector<Persona*>& lista, int& siguienteId);
void mostrarTodos(const vector<Persona*>& lista);
void buscar(const vector<Persona*>& lista);
void modificar(vector<Persona*>& lista);
void eliminar(vector<Persona*>& lista);
void reporte(const vector<Persona*>& lista);
void liberarMemoria(vector<Persona*>& lista);

// Funcion principal
int main() {
    // Vector de punteros a Persona (almacena objetos de tipo Paciente)
    // Esto permite usar polimorfismo: cada elemento puede ser cualquier clase derivada de Persona.
    vector<Persona*> lista;

    int siguienteId = 1;   // Variable para generar ID

    // 10 registros iniciales
    lista.push_back(new Paciente(siguienteId++, "Elvia Pilamunga", 30, "Gripe", "10/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Sebastian Curillo", 45, "Hipertension", "11/02/2026", "En espera"));
    lista.push_back(new Paciente(siguienteId++, "Diego Curillo", 60, "Diabetes", "12/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Daniel Lopez", 22, "Fractura de brazo", "13/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Jimmy Perez", 55, "Chequeo general", "14/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Leonel Messi", 8, "Infeccion respiratoria", "15/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Isabel Sanchez", 70, "Artritis", "16/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Maria Diaz", 35, "Migrana", "17/02/2026", "En espera"));
    lista.push_back(new Paciente(siguienteId++, "Carlos Torres", 28, "Intoxicacion", "18/02/2026", "Atendido"));
    lista.push_back(new Paciente(siguienteId++, "Elena T.", 50, "Control prenatal", "19/02/2026", "Atendido"));

    int opcion;
    do {
        // Menu de Opciones
        cout << "\n --Menu de Pacientes Atendidos--";
        cout << "\n 1. Nuevo Registro de Paciente";
        cout << "\n 2. Mostrar Todos los Pacientes";
        cout << "\n 3. Buscar Paciente";
        cout << "\n 4. Modificar un Paciente";
        cout << "\n 5. Eliminar Paciente";
        cout << "\n 6. Reporte de los Pacientes";
        cout << "\n 7. Salir" << endl;
        cout << "Ingrese una Opcion: ";
        cin >> opcion;
        //cin.ignore();

        switch (opcion) {
            case 1: registrar(lista, siguienteId); break;
            case 2: mostrarTodos(lista); break;
            case 3: buscar(lista); break;
            case 4: modificar(lista); break;
            case 5: eliminar(lista); break;
            case 6: reporte(lista); break;
            case 7: cout << "Adios\n"; break;
            default: cout << "Opcion invalida\n"; cin.get();
        }
    } while (opcion != 7);

    // Liberar la memoria de todos los objetos creados con new
    liberarMemoria(lista);
    return 0;
}

// Implementación de las funciones del menu

void registrar(vector<Persona*>& lista, int& siguienteId) {
    char nombre[MAX_NOMBRE], diagnostico[MAX_DIAGNOSTICO], fecha[MAX_FECHA], estado[MAX_ESTADO];
    int edad;
    cout << "Nombre: "; cin.getline(nombre, MAX_NOMBRE);
    cout << "Edad: "; cin >> edad; cin.ignore();
    cout << "Diagnostico: "; cin.getline(diagnostico, MAX_DIAGNOSTICO);
    cout << "Fecha (dd/mm/aaaa): "; cin.getline(fecha, MAX_FECHA);
    cout << "Estado (Atendido/En espera): "; cin.getline(estado, MAX_ESTADO);
    // Creacion dinamica de un objeto Paciente y almacenamiento del puntero en el vector
    lista.push_back(new Paciente(siguienteId++, nombre, edad, diagnostico, fecha, estado));
    cout << "Registrado con ID " << siguienteId - 1 << "\n";
    cin.get(); // Pausa
}

// Muestra todos los pacientes. Itera el vector y llama al método mostrar() de cada objeto.
// Gracias al polimorfismo, aunque el vector almacena punteros a Persona,
// se ejecuta la version de mostrar() de la clase Paciente.
void mostrarTodos(const vector<Persona*>& lista) {
    if (lista.empty()) {
        cout << "No hay pacientes.\n";
        return;
    }
    cout << "--- LISTA DE PACIENTES ---\n";
    for (size_t i = 0; i < lista.size(); i++) {
        lista[i]->mostrar(); 
    }
    cout << "------------------------------------------";
    cin.get();
}

// Busca pacientes por ID
void buscar(const vector<Persona*>& lista) {
    if (lista.empty()) {
        cout << "No hay pacientes.\n";
        return;
    }
    int id;
    cout << "Ingrese ID del paciente: ";
    cin >> id;
    cin.ignore();
    bool encontrado = false;
    for (size_t i = 0; i < lista.size(); i++) {
        // dynamic_cast verifica si el objeto es realmente de tipo Paciente
        const Paciente* p = dynamic_cast<const Paciente*>(lista[i]);
        if (p && p->getId() == id) {
            p->mostrar();
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "No se encontró paciente con ID " << id << ".\n";
    cout << "--------------------------------------------";
    cin.get();
}

// Modifica los datos de un paciente existente.
void modificar(vector<Persona*>& lista) {
    if (lista.empty()) {
        cout << "No hay pacientes.\n";
        return;
    }
    int id;
    cout << "ID del paciente a modificar: ";
    cin >> id; cin.ignore();
    for (size_t i = 0; i < lista.size(); i++) {
        Paciente* p = dynamic_cast<Paciente*>(lista[i]);
        if (p && p->getId() == id) {
            cout << "Datos actuales:\n";
            p->mostrar();
            char buffer[MAX_NOMBRE];
            int nuevaEdad;
            cout << "Nuevo nombre (dejar vacio para no cambiar): ";
            cin.getline(buffer, MAX_NOMBRE);
            if (longitud(buffer) > 0) p->setNombre(buffer);
            cout << "Nueva edad (0 para no cambiar): ";
            cin >> nuevaEdad; cin.ignore();
            if (nuevaEdad > 0) p->setEdad(nuevaEdad);
            cout << "Nuevo diagnostico (vacio = no cambiar): ";
            cin.getline(buffer, MAX_DIAGNOSTICO);
            if (longitud(buffer) > 0) p->setDiagnostico(buffer);
            cout << "Nueva fecha (vacio = no cambiar): ";
            cin.getline(buffer, MAX_FECHA);
            if (longitud(buffer) > 0) p->setFecha(buffer);
            cout << "Nuevo estado (vacio = no cambiar): ";
            cin.getline(buffer, MAX_ESTADO);
            if (longitud(buffer) > 0) p->setEstado(buffer);
            cout << "Paciente modificado correctamente.\n";
            cout << "----------------------------------------------";
            cin.get();
            return;
        }
    }
    cout << "No se encontro un paciente con ID " << id << "\n";
    cout << "--------------------------------------";
    cin.get();
}

// Elimina un paciente del vector y libera su memoria.
void eliminar(vector<Persona*>& lista) {
    if (lista.empty()) {
        cout << "No hay pacientes.\n";
        return;
    }
    int id;
    cout << "ID del paciente a eliminar: ";
    cin >> id; cin.ignore();
    for (vector<Persona*>::iterator it = lista.begin(); it != lista.end(); ++it) {
        Paciente* p = dynamic_cast<Paciente*>(*it);
        if (p && p->getId() == id) {
            delete *it;        // Libera la memoria del objeto
            lista.erase(it);   // Elimina el puntero del vector
            cout << "Paciente eliminado.\n";
            cout << "----------------------------------------------------";
            cin.get();
            return;
        }
    }
    cout << "No se encontro un paciente con ID " << id << "\n";
    cout << "----------------------------------------------";
    cin.get();
}

// Genera un reporte con estadasticas: total, atendidos, en espera y frecuencia de diagnosticos.
void reporte(const vector<Persona*>& lista) {
    if (lista.empty()) {
        cout << "No hay pacientes.\n";
        return;
    }
    int total = lista.size();
    int atendidos = 0, espera = 0;
    vector<ContadorDiagnostico> contadores;

    for (size_t i = 0; i < lista.size(); i++) {
        const Paciente* p = dynamic_cast<const Paciente*>(lista[i]);
        if (!p) continue;

        // Contar estados
        if (comparar(p->getEstado(), "Atendido") == 0)
            atendidos++;
        else if (comparar(p->getEstado(), "En espera") == 0)
            espera++;

        // Contar diagnosticos
        const char* diag = p->getDiagnostico();
        bool encontrado = false;
        for (size_t j = 0; j < contadores.size(); j++) {
            if (comparar(contadores[j].diagnostico, diag) == 0) {
                contadores[j].cantidad++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            ContadorDiagnostico nuevo;
            copiar(nuevo.diagnostico, diag);
            nuevo.cantidad = 1;
            contadores.push_back(nuevo);
        }
    }

    cout << "--- REPORTE FINAL ---\n";
    cout << "Total pacientes: " << total << "\n";
    cout << "Atendidos: " << atendidos << "\n";
    cout << "En espera: " << espera << "\n";
    cout << "Diagnosticos:\n";
    for (size_t i = 0; i < contadores.size(); i++) {
        cout << "  " << contadores[i].diagnostico << ": " << contadores[i].cantidad << "\n";
    }
    cout << "------------------------------------------------------";
    cin.get();
}

// Libera toda la memoria asignada dinamicamente para los objetos Persona.
void liberarMemoria(vector<Persona*>& lista) {
    for (size_t i = 0; i < lista.size(); i++) {
        delete lista[i];
    }
    lista.clear();
}
