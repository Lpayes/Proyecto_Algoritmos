#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
using namespace std;

struct Curso {
    string codigo;
    string nombre;
    string carrera;
    int creditos;
    float notasPrimerParcial;
    float notasSegundoParcial;
    float notasExamenFinal;
    float notaFinal;
};

struct NotasCurso {
    string codigoCurso;
    float notaFinal;
    string estado;
};

struct Estudiante {
    string codigo;
    string nombres;
    string apellidos;
    string carrera;
    string departamento;
    string municipio;
    string aldea;
    string telefono_personal;
    string telefono_casa;
    string telefono_emergencia;
    string fecha_nacimiento;
    int edad;
    int anio_ingreso;
    string correo;
      vector<Curso> cursos; 
    vector<string> cursosAsignados; 
    vector<NotasCurso> notasCursos; 

    Estudiante(string _nombres, string _apellidos, string _carrera, string _departamento, 
                string _municipio, string _aldea, string _telefono_personal, string _telefono_casa, 
                string _telefono_emergencia, string _fecha_nacimiento, int _anio_ingreso, string _correo, int numEstudiantes) {
        nombres = _nombres;
        apellidos = _apellidos;
        carrera = _carrera;
        departamento = _departamento;
        municipio = _municipio;
        aldea = _aldea;
        telefono_personal = _telefono_personal;
        telefono_casa = _telefono_casa;
        telefono_emergencia = _telefono_emergencia;
        fecha_nacimiento = _fecha_nacimiento;
        anio_ingreso = _anio_ingreso;
        correo = _correo;

        edad = calcularEdad(fecha_nacimiento);
        codigo = to_string(anio_ingreso) + carrera[0] + to_string(numEstudiantes + 1); 
    }

    int calcularEdad(const string& fecha_nacimiento) {
        int dia, mes, anio;
        sscanf(fecha_nacimiento.c_str(), "%d/%d/%d", &dia, &mes, &anio);
        
        time_t t = time(0);
        tm* now = localtime(&t);
        
        int edad = now->tm_year + 1900 - anio;

        if (now->tm_mon + 1 < mes || (now->tm_mon + 1 == mes && now->tm_mday < dia)) {
            edad--;
        }

        return edad;
    }
};

vector<string> departamentos = {
"Jalapa", "Jutiapa"
};

vector<vector<string>> municipios = {
    {"Jalapa", "Mataquescuintla", "San Carlos Alzatate", "San Luis Jilotepeque", "San Manuel Chaparron", "San Pedro Pinula", "Monjas"},
    {"Jutiapa", "Asunción Mita", "El Progreso", "Comapa", "El Adelanto", "Comapa", "Atescatempa", "Yupiltepeque", "Jerez", "San Jose Acatempa", "Moyuta", "Quesada", "Santa Catarina Mita"},
};

int contadorEstudiantes = 0;
vector<Estudiante> estudiantes;


bool validarFecha(const string& fecha) {
    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio);
    
    if (anio < 1800 || anio > 2024) return false; 
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (bisiesto && dia > 29) return false;
        if (!bisiesto && dia > 28) return false;
    }
    return true;
}

string obtenerEntradaObligatoria(const string& mensaje) {
    string entrada;
    do {
        cout << mensaje;
        getline(cin, entrada);
        if (entrada.empty()) {
            cout << "Este campo es obligatorio. Intente de nuevo.\n";
        }
    } while (entrada.empty());
    return entrada;
}
string deleccion;
int seleccionarDepartamento() {
    cout << "Seleccione el departamento:" << endl;
    for (int i = 0; i < departamentos.size(); i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }

    int opcion;
    while (true) {
        cin >> opcion;
        if (cin.fail() || opcion < 1 || opcion > departamentos.size()) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opción no valida. Intente de nuevo: ";
        } else {
            break; 
        }
    }
return opcion - 1; 
}

string obtenerNombreDepartamento(int indiceDepartamento) {
    string nombreDepartamento;

    switch (indiceDepartamento) {
        case 0:
            nombreDepartamento = "Jalapa";
            break;
        case 1:
            nombreDepartamento = "Jutiapa";
            break;
    }

    return nombreDepartamento;
}

string seleccionarMunicipio(int indiceDepartamento) {
    cout << "Seleccione el municipio:" << endl;
    for (int i = 0; i < municipios[indiceDepartamento].size(); i++) {
        cout << i + 1 << ". " << municipios[indiceDepartamento][i] << endl;
    }
    int opcion;
    while (true) {
        cin >> opcion;
        if (cin.fail() || opcion < 1 || opcion > municipios[indiceDepartamento].size()) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opcion no valida. Intente de nuevo: ";
        } else {
            break;
        }
    }
    return municipios[indiceDepartamento][opcion - 1];
}


int seleccionarCarrera() {
    int carreraSeleccionada;

    do {
        cout << "Selecciona una carrera:\n";
        cout << "1. Ingenieria en Sistemas\n";
        cout << "2. Ingenieria Civil\n";
        cout << "Ingresa el numero de la carrera (1-2): ";
        cin >> carreraSeleccionada;
        if (carreraSeleccionada < 1 || carreraSeleccionada > 2) {
            cout << "Seleccion de carrera invalida. Debe ser un numero entre 1 y 2.\n";
        }
    } while (carreraSeleccionada < 1 || carreraSeleccionada > 2); 

    return carreraSeleccionada; 
}
string obtenerNombreCarrera(int _carreraSeleccionada) {
    string carrera;
    
    switch (_carreraSeleccionada) {
        case 1:
            carrera = "Ingenieria en Sistemas";
            break;
        case 2:
            carrera = "Ingenieria Civil";
            break;
    }
    
    return carrera;
}
bool validarTelefono(const string& telefono) {
    if (telefono.length() != 8) {
        return false;
    }

    int i = 0;
    while (i < 8) {
        if (telefono[i] < '0' || telefono[i] > '9') {
            return false;
        }
        i++;
    }
    
    return true;
}

int carreraSeleccionadadd;      
void registrarEstudiante() {
    string nombres, apellidos, carrera, departamento, municipio, aldea, telefono_personal, telefono_casa, telefono_emergencia, fecha_nacimiento;
    int anio_ingreso, indiceDepartamento;
    string correo;
    cout << "-----------------------------------------------------------------\n";
    
    nombres=obtenerEntradaObligatoria("Ingrese los nombres del estudiante: ");
    cout << "-----------------------------------------------------------------\n";
    
    apellidos=obtenerEntradaObligatoria("Ingrese los apellidos del estudiante: ");
    cout << "-----------------------------------------------------------------\n";
    
    carreraSeleccionadadd = seleccionarCarrera();
    carrera = obtenerNombreCarrera(carreraSeleccionadadd);
   
	cout << "-----------------------------------------------------------------\n";	    
    
    indiceDepartamento = seleccionarDepartamento();
    string deleccion = obtenerNombreDepartamento(indiceDepartamento);

    cout << "-----------------------------------------------------------------\n";
    municipio = seleccionarMunicipio(indiceDepartamento);
    cout << "-----------------------------------------------------------------\n";

    do {
        telefono_personal= obtenerEntradaObligatoria("Ingrese el telefono personal (8 digitos): ");
        cout << "-----------------------------------------------------------------\n";
        if (!validarTelefono(telefono_personal)) {
            cout << "Numero de teléfono inválido. Debe contener solo 8 digitos numericos.\n";
        }
    } while (!validarTelefono(telefono_personal));
    
    do {
        telefono_casa= obtenerEntradaObligatoria("Ingrese el teléfono de casa (8 digitos): ");
        cout << "-----------------------------------------------------------------\n";
        if (!validarTelefono(telefono_casa)) {
            cout << "Numero de teléfono invalido. Debe contener solo 8 digitos numericos.\n";
        }
    } while (!validarTelefono(telefono_casa));
    
       do { 
        telefono_emergencia= obtenerEntradaObligatoria("Ingrese el telefono de emergencia (8 digitos): ");
        cout << "-----------------------------------------------------------------\n";
        if (!validarTelefono(telefono_emergencia)) {
            cout << "Numero de telefono invalido. Debe contener solo 8 digitos numericos.\n";
        }
    } while (!validarTelefono(telefono_emergencia));
	   
    fecha_nacimiento= obtenerEntradaObligatoria("Ingrese la fecha de nacimiento (dd/mm/yyyy): ");
    cout << "-----------------------------------------------------------------\n";
    while (!validarFecha(fecha_nacimiento)) {
    	fecha_nacimiento = obtenerEntradaObligatoria("Fecha no válida. Intente de nuevo (dd/mm/yyyy): ");
    }

    cout << "Ingrese el año de ingreso a la universidad: "; 
    while (true) {
        cin >> anio_ingreso;
        cout << "-----------------------------------------------------------------\n";
        if (cin.fail() || anio_ingreso < 1900 || anio_ingreso > 2024) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no valida. Intente de nuevo: ";
        } else {
            break; 
        }
    }
    
    cin.ignore(); 

    correo = obtenerEntradaObligatoria("Ingrese el correo electrónico: "); 
    
    cout << "-----------------------------------------------------------------\n";

     Estudiante estudiante(nombres, apellidos, carrera, departamento, municipio, aldea, 
                          telefono_personal, telefono_casa, telefono_emergencia, 
                          fecha_nacimiento, anio_ingreso, correo, contadorEstudiantes);

    cout << "\nEstudiante registrado con éxito!\n";
    cout << "Codigo asignado: " << estudiante.codigo << endl;
    cout << "Nombre: " << nombres << " " << apellidos << endl;
    cout << "Carrera: " << carrera << endl;
    cout << "Departamento: " << deleccion << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Telefono personal: " << telefono_personal << endl;
    cout << "Telefono de casa: " << telefono_casa << endl;
    cout << "Telefono de emergencia: " << telefono_emergencia << endl;
    cout << "Fecha de nacimiento: " << fecha_nacimiento << endl;
    cout << "Año de ingreso: " << anio_ingreso << endl;
    cout << "Correo electrónico: " << correo << endl;
    cout << "Edad: " << estudiante.edad << endl;
    
    estudiantes.push_back(estudiante);
    contadorEstudiantes++;
    cout << "-----------------------------------------------------------------\n";
}

void inicializarCursosSistemas(vector<vector<Curso>>& cursosSistemas) {
    cursosSistemas[0] = {
        {"SIS101", "Logica de Sistemas", "Ingenieria en Sistemas", 4},
        {"SIS102", "Introduccion a los Sistemas de Computo", "Ingenieria en Sistemas", 3},
        {"SIS103", "Metodología de la Investigacion", "Ingenieria en Sistemas", 4}
    };
    cursosSistemas[1] = {
        {"SIS201", "Precalculo", "Ingenieria en Sistemas", 4},
        {"SIS202", "Matemáticas Discreta", "Ingenieria en Sistemas", 3},
        {"SIS203", "Algoritmos", "Ingenieria en Sistemas", 4}
    };
    cursosSistemas[2] = {
        {"SIS301", "Fisica 1", "Ingenieria en Sistemas", 4},
        {"SIS302", "Programacion 1", "Ingenieria en Sistemas", 3},
        {"SIS303", "Calculo 1", "Ingeniería en Sistemas", 4}
    };
    cursosSistemas[3] = {
        {"SIS401", "Programacion 2", "Ingenieria en Sistemas", 4},
        {"SIS402", "Calculo 2", "Ingeniería en Sistemas", 4},
        {"SIS403", "Proceso Administrativo", "Ingenieria en Sistemas", 3}
    };
    cursosSistemas[4] = {
        {"SIS501", "Programación 3", "Ingenieria en Sistemas", 4},
        {"SIS502", "Emprendedores de negocios", "Ingenieria en Sistemas", 4},
        {"SIS503", "Seguridad Informática", "Ingenieria en Sistemas", 4}
    };
}

void inicializarCursosCivil(vector<vector<Curso>>& cursosCivil) {
    cursosCivil[0] = {
        {"CIV101", "Calculo I", "Ingenieria Civil", 4},
        {"CIV102", "Mecánica de Fluidos", "Ingeniería Civil", 4},
        {"CIV103", "Resistencia de Materiales", "Ingenieria Civil", 4}
    };
    cursosCivil[1] = {
        {"CIV201", "Construccion Civil", "Ingenieria Civil", 4},
        {"CIV202", "Geotecnia", "Ingenieria Civil", 4},
        {"CIV203", "Cálculo II", "Ingenieria Civil", 4}
    };
    cursosCivil[2] = {
        {"CIV301", "Estructuras Metalicas", "Ingenieria Civil", 4},
        {"CIV302", "Diseño de Vias", "Ingenieria Civil", 4},
        {"CIV303", "Cálculo III", "Ingenieria Civil", 4}
    };
    cursosCivil[3] = {
        {"CIV401", "Hidrologia", "Ingenieria Civil", 4},
        {"CIV402", "Ingenieria Sanitaria", "Ingenieria Civil", 4},
        {"CIV403", "Proyectos de Construccion", "Ingenieria Civil", 4}
    };
    cursosCivil[4] = {
        {"CIV501", "Planeacion de Obras", "Ingenieria Civil", 4},
        {"CIV502", "Materiales de Construccion", "Ingenieria Civil", 4},
        {"CIV503", "Metodos Numericos", "Ingenieria Civil", 4}
    };
}
vector<vector<Curso>> cursosSistemas(5);
vector<vector<Curso>> cursosCivil(5);

void asignarCurso(vector<Estudiante>& estudiantes, int carreraSeleccionada) {
	cout << "-----------------------------------------------------------------\n";
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados. No se puede asignar curso.\n";
        return;
    }
    int estudianteSeleccionado;
    do {cout << "Seleccione un estudiante para asignar un curso: " << endl;
    for (int i = 0; i < estudiantes.size(); i++) {
        cout << i + 1 << ". " << estudiantes[i].nombres << " " << estudiantes[i].apellidos 
             << " | Codigo: " << estudiantes[i].codigo << endl;
    }

    cout << "Selecciona un estudiante por nUmero: ";
    cin >> estudianteSeleccionado;

    if (estudianteSeleccionado < 1 || estudianteSeleccionado > estudiantes.size()) {
        cout << "Selección de estudiante inválida, seleccione de nuevo.\n";
    }
    } while (estudianteSeleccionado < 1 || estudianteSeleccionado > estudiantes.size());
    
    cout << "-----------------------------------------------------------------\n";
    
    int carreraSeleccionadad = carreraSeleccionadadd;        
                        
    cout << "Selecciona un semestre \n 0:Primer Semestre \n 1:Segundo Semestre \n 2: Tercer Semestre \n 3: Cuarto Semestre \n 4: Quinto semestre: ";
    int semestreSeleccionada;        
    cin >> semestreSeleccionada;
    cout << "-----------------------------------------------------------------\n";
            
    
    if (carreraSeleccionadad < 1 || carreraSeleccionadad > 2) {
    cout << "Selección de carrera invalida. Debe ser un numero entre 1 y 2.\n";
    return;
}	            
    vector<Curso> cursosElegidos;
    switch (carreraSeleccionadad) {
        case 1:
            cursosElegidos = cursosSistemas[semestreSeleccionada];
            break;
        case 2:
            cursosElegidos = cursosCivil[semestreSeleccionada];
            break;
        default:
            cout << "Seleccion invalida.\n";
            return;
    }
    cout << "-----------------------------------------------------------------\n";

    cout << "Cursos disponibles para la carrera seleccionada:\n";
    for (const auto& curso : cursosElegidos) {
        cout << curso.codigo << ": " << curso.nombre 
             << " (Creditos: " << curso.creditos << ")\n";
    }

    string codigoCursoSeleccionado;
    cout << "Selecciona un curso escribiendo el codigo del curso que quieres tal y como esta en la lista: ";
    cin >> codigoCursoSeleccionado;

    bool cursoEncontrado = false;
    for (const auto& curso : cursosElegidos) {
        if (curso.codigo == codigoCursoSeleccionado) {
            for (const auto& c : estudiantes[estudianteSeleccionado - 1].cursos) {
                if (c.codigo == curso.codigo) {
                    cout << "El estudiante ya esta asignado al curso: " << curso.nombre << endl;
                    return;
                }
            }

            cursoEncontrado = true;
            cout << "Has seleccionado el curso: " << curso.nombre 
                 << " para el estudiante: " << estudiantes[estudianteSeleccionado - 1].nombres << " " 
                 << estudiantes[estudianteSeleccionado - 1].apellidos << endl;

            estudiantes[estudianteSeleccionado - 1].cursos.push_back(curso);
            cout << "Curso registrado correctamente.\n";
            cout << "-----------------------------------------------------------------\n";
            break;
        }
    }

    if (!cursoEncontrado) {
        cout << "Codigo de curso invalido.\n";
    }
}
void registroNotasParciales(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "Seleccione un estudiante para registrar notas parciales: " << endl;
    for (int i = 0; i < estudiantes.size(); i++) {
        cout << i + 1 << ". " << estudiantes[i].nombres << " " << estudiantes[i].apellidos 
             << " | Código: " << estudiantes[i].codigo << endl;
    }

    int estudianteSeleccionado;
    do {
        cout << "Selecciona un estudiante por numero: ";
        cin >> estudianteSeleccionado;

        if (estudianteSeleccionado < 1 || estudianteSeleccionado > estudiantes.size()) {
            cout << "Selección de estudiante invalida. Por favor, seleccione un numero de estudiante valido." << endl;
        }
    } while (estudianteSeleccionado < 1 || estudianteSeleccionado > estudiantes.size());

    Estudiante& estudiante = estudiantes[estudianteSeleccionado - 1];

    if (estudiante.cursos.empty()) {
        cout << "El estudiante no tiene cursos asignados.\n";
        return;
    }

    cout << "Cursos asignados a " << estudiante.nombres << " " << estudiante.apellidos << ":\n";
    for (int i = 0; i < estudiante.cursos.size(); i++) {
        cout << i + 1 << ". " << estudiante.cursos[i].nombre << " (Codigo: " << estudiante.cursos[i].codigo << ")\n";
    }

    int cursoSeleccionado;
    
    do {
        cout << "Selecciona un curso por numero: ";
        cin >> cursoSeleccionado;

        if (cursoSeleccionado < 1 || cursoSeleccionado > estudiante.cursos.size()) {
            cout << "Selección de curso invalida. Por favor, seleccione un numero de curso valido." << endl;
        }
    } while (cursoSeleccionado < 1 || cursoSeleccionado > estudiante.cursos.size());

    Curso& curso = estudiante.cursos[cursoSeleccionado - 1];

    float nota1, nota2, notaExamen;

    do {
        cout << "Ingrese la nota del primer parcial para el curso " << curso.nombre << ": ";
        cin >> nota1;
        if (nota1 < 0 || nota1 > 15) {
            cout << "Nota invalida. Debe estar entre 0 y 15.\n";
        }
    } while (nota1 < 0 || nota1 > 15);

    do {
        cout << "Ingrese la nota del segundo parcial para el curso " << curso.nombre << ": ";
        cin >> nota2;
        if (nota2 < 0 || nota2 > 15) {
            cout << "Nota invalida. Debe estar entre 0 y 15.\n";
        }
    } while (nota2 < 0 || nota2 > 15);

    do {
        cout << "Ingrese la nota del examen final para el curso " << curso.nombre << " (0 a 70): ";
        cin >> notaExamen;
        if (notaExamen < 0 || notaExamen > 70) {
            cout << "Nota invalida. Debe estar entre 0 y 70.\n";
        }
    } while (notaExamen < 0 || notaExamen > 70);

    curso.notasPrimerParcial = nota1;
    curso.notasSegundoParcial = nota2;
    curso.notasExamenFinal = notaExamen;

    curso.notaFinal = nota1 + nota2 + notaExamen;

    cout << "Notas registradas correctamente para el curso: " << curso.nombre << endl;
}
void notaFinalDelCurso(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }
    
    set<string> cursosUnicos;
    for (const auto& estudiante : estudiantes) {
        for (const auto& curso : estudiante.cursos) {
            cursosUnicos.insert(curso.nombre); 
        }
    }

    cout << "Cursos disponibles:\n";
    int indiceCurso = 1;
    map<int, string> cursoMapa;
    for (const auto& curso : cursosUnicos) {
        cout << indiceCurso++ << ". " << curso << endl;
        cursoMapa[indiceCurso - 1] = curso;
    }

    int cursoSeleccionado;
    cout << "Selecciona un curso por número: ";
    cin >> cursoSeleccionado;

    if (cursoSeleccionado < 1 || cursoSeleccionado > cursoMapa.size()) {
        cout << "Selección de curso inválida.\n";
        return;
    }

    string cursoSeleccionadoNombre = cursoMapa[cursoSeleccionado];

    cout << "Estudiantes registrados en el curso " << cursoSeleccionadoNombre << ":\n";
    for (const auto& estudiante : estudiantes) {
        for (const auto& curso : estudiante.cursos) {
            if (curso.nombre == cursoSeleccionadoNombre) {
                cout << "Estudiante: " << estudiante.nombres << " " << estudiante.apellidos 
                     << " | Nota Final: " << curso.notaFinal << endl;
            }
        }
    }
}

void estadoDelCurso(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    set<string> cursosConNotas;
    for (const auto& estudiante : estudiantes) {
        for (const auto& curso : estudiante.cursos) {
            if (curso.notaFinal != -1) { 
                cursosConNotas.insert(curso.nombre);
            }
        }
    }

    if (cursosConNotas.empty()) {
        cout << "No hay notas registradas para ningun curso." << endl;
        return;
    }

    cout << "Cursos con notas registradas:" << endl;
    int index = 1;
    map<int, string> cursosMap; 
    for (const auto& curso : cursosConNotas) {
        cout << index << ". " << curso << endl;
        cursosMap[index] = curso;
        index++;
    }

    int cursoSeleccionado;
    cout << "Seleccione el numero del curso para ver el estado de los estudiantes: ";
    cin >> cursoSeleccionado;

    if (cursosMap.find(cursoSeleccionado) == cursosMap.end()) {
        cout << "Selección invalida." << endl;
        return;
    }

    string cursoElegido = cursosMap[cursoSeleccionado];

    cout << "Estudiantes en el curso " << cursoElegido << ":" << endl;
    bool estudiantesConNotas = false;
    for (const auto& estudiante : estudiantes) {
        for (const auto& curso : estudiante.cursos) {
            if (curso.nombre == cursoElegido && curso.notaFinal != -1) {
                estudiantesConNotas = true;
                cout << "Estudiante: " << estudiante.nombres << endl;
                cout << "Nota final: " << curso.notaFinal << endl;
                if (curso.notaFinal >= 60) {
                    cout << "Estado: Aprobado" << endl;
                } else {
                    cout << "Estado: Reprobado" << endl;
                }
                cout << "-----------------------------" << endl;
            }
        }
    }

    if (!estudiantesConNotas) {
        cout << "No hay estudiantes con notas registradas en este curso." << endl;
    }
}

void controlNotas(vector<Estudiante>& estudiantes) {
    int opcion;
    do {
        cout << "===============================" << endl;
        cout << "Control de Notas" << endl;
        cout << "===============================" << endl;
        cout << "1. Registro de Notas Parciales" << endl;
        cout << "2. Nota Final del Curso" << endl;
        cout << "3. Estado del Curso (Aprobado/Reprobado)" << endl;
        cout << "4. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                registroNotasParciales(estudiantes);
                break;
            case 2:
                notaFinalDelCurso(estudiantes);
                break;
            case 3:controlNotas(estudiantes);
                estadoDelCurso(estudiantes);
                break;
            case 4:
                cout << "Regresando al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;

    } while (opcion != 4);
}
void mostrarMenu() {	
    cout << "================================================================" << endl;
    cout << "Sistema de Registro Universitario" << endl;
    cout << "================================================================" << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Asignar curso" << endl;
    cout << "3. Control de Notas" << endl; 
    cout << "4. Reportes Academicos" << endl;
    cout << "5. Salir" << endl; 
}
int main() {
    inicializarCursosSistemas(cursosSistemas);
    inicializarCursosCivil(cursosCivil);
    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                registrarEstudiante();
                break;
            case 2:
                asignarCurso(estudiantes, carreraSeleccionadadd);
                break;
            case 3: 
		        controlNotas(estudiantes);
                break;
            case 4:

                break;
            case 5:
                cout << "" << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

        cout << endl;

    } while (opcion != 5); 

    return 0;
}