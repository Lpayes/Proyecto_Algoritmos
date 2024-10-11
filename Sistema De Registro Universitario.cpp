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
    "Guatemala", "Sacatepéquez", "Chimaltenango", "Escuintla", "Santa Rosa", "Sololá", "Totonicapán",
    "Quetzaltenango", "Suchitepéquez", "Retalhuleu", "San Marcos", "Huehuetenango", "Quiché",
    "Baja Verapaz", "Alta Verapaz", "Petén", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
};

vector<vector<string>> municipios = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Amatitlán"},
    {"Antigua Guatemala", "Jocotenango", "Ciudad Vieja", "Sumpango", "Santo Domingo Xenacoj"},
    // Añade más municipios según el departamento
    {"Chimaltenango", "San José Poaquil", "San Juan Comalapa", "Tecpán Guatemala", "Patzún"},
    {"Escuintla", "Santa Lucía Cotzumalguapa", "La Gomera", "Tiquisate", "Palín"},
    {"Cuilapa", "Barberena", "Santa María Ixhuatán", "Oratorio", "San Juan Tecuaco"},
    {"Sololá", "Panajachel", "San José Chacayá", "Santa Catarina Ixtahuacán", "Santa Cruz La Laguna"},
    {"Totonicapán", "San Andrés Xecul", "Momostenango", "San Francisco El Alto", "San Cristóbal Totonicapán"},
    {"Quetzaltenango", "Salcajá", "Olintepeque", "Almolonga", "Cabricán"},
    {"Mazatenango", "San Bernardino", "Chicacao", "Patulul", "San José El Ídolo"},
    {"Retalhuleu", "San Sebastián", "Santa Cruz Muluá", "Champerico", "El Asintal"},
    {"San Marcos", "Ayutla", "San Pedro Sacatepéquez", "Sibinal", "Tejutla"},
    {"Huehuetenango", "Chiantla", "Malacatancito", "Cuilco", "San Sebastián Huehuetenango"},
    {"Santa Cruz del Quiché", "Chichicastenango", "Zacualpa", "Joyabaj", "San Pedro Jocopilas"},
    {"Salamá", "San Jerónimo", "Purulhá", "Rabinal", "Cubulco"},
    {"Cobán", "Santa Cruz Verapaz", "San Pedro Carchá", "San Juan Chamelco", "Tactic"},
    {"Flores", "San Benito", "Santa Ana", "San Andrés", "La Libertad"},
    {"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"},
    {"Zacapa", "Teculután", "Río Hondo", "Gualán", "Usumatlán"},
    {"Chiquimula", "Jocotán", "Camotán", "Olopa", "Quezaltepeque"},
    {"Jalapa", "Moyuta", "San Carlos Alzatate", "San Luis Jilotepeque", "San Manuel Chaparrón"},
    {"Jutiapa", "Asunción Mita", "Atescatempa", "Comapa", "El Adelanto"},
    {"Sanarate", "Guastatoya", "Morazán", "San Agustín Acasaguastlán", "San Antonio La Paz"}
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

int seleccionarDepartamento() {
    cout << "Seleccione el departamento:" << endl;
    for (int i = 0; i < departamentos.size(); i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }

    int opcion;
    while (true) {
        cin >> opcion;
        if (cin.fail() || opcion < 1 || opcion > departamentos.size()) { 
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opción no válida. Intente de nuevo: ";
        } else {
            break; 
        }
    }
return opcion - 1; 
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
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opción no válida. Intente de nuevo: ";
        } else {
            break;
        }
    }
    return municipios[indiceDepartamento][opcion - 1];
}

void registrarEstudiante() {
    string nombres, apellidos, carrera, departamento, municipio, aldea, telefono_personal, telefono_casa, telefono_emergencia, fecha_nacimiento;
    int anio_ingreso, indiceDepartamento;
    string correo;

    cout << "Ingrese los nombres del estudiante: "; 
    getline(cin, nombres);
    
    cout << "Ingrese los apellidos del estudiante: "; 
    getline(cin, apellidos);
    
indiceDepartamento = seleccionarDepartamento();
municipio = seleccionarMunicipio(indiceDepartamento);
    cout << ""; 
    getline(cin, telefono_emergencia);

    cout << "Ingrese el teléfono personal: "; 
    getline(cin, telefono_personal);
    
    cout << "Ingrese el teléfono de casa: "; 
    getline(cin, telefono_casa);
    
        cout << "Ingrese el teléfono emergencia: "; 
  getline(cin, telefono_emergencia);
    
    
    cout << "Ingrese la fecha de nacimiento (dd/mm/yyyy): "; 
    getline(cin, fecha_nacimiento);
    while (!validarFecha(fecha_nacimiento)) {
        cout << "Fecha no válida. Intente de nuevo (dd/mm/yyyy): ";
        getline(cin, fecha_nacimiento);
    }

    cout << "Ingrese el año de ingreso a la universidad: "; 
    while (true) {
        cin >> anio_ingreso;
        if (cin.fail() || anio_ingreso < 1900 || anio_ingreso > 2024) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida. Intente de nuevo: ";
        } else {
            break; 
        }
    }
    
    cin.ignore(); 

    cout << "Ingrese el correo electrónico: "; 
    getline(cin, correo);

     Estudiante estudiante(nombres, apellidos, carrera, departamento, municipio, aldea, 
                          telefono_personal, telefono_casa, telefono_emergencia, 
                          fecha_nacimiento, anio_ingreso, correo, contadorEstudiantes);

    cout << "\nEstudiante registrado con éxito!\n";
    cout << "Código asignado: " << estudiante.codigo << endl;
    cout << "Nombre: " << nombres << " " << apellidos << endl;
    cout << "Carrera: " << carrera << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Teléfono personal: " << telefono_personal << endl;
    cout << "Teléfono de casa: " << telefono_casa << endl;
    cout << "Teléfono de emergencia: " << telefono_emergencia << endl;
    cout << "Fecha de nacimiento: " << fecha_nacimiento << endl;
    cout << "Año de ingreso: " << anio_ingreso << endl;
    cout << "Correo electrónico: " << correo << endl;
    cout << "Edad: " << estudiante.edad << endl;
    
    estudiantes.push_back(estudiante);
    contadorEstudiantes++;
}

void inicializarCursosSistemas(vector<vector<Curso>>& cursosSistemas) {
    cursosSistemas[0] = {
        {"SIS101", "Programación I", "Ingeniería en Sistemas", 4},
        {"SIS102", "Matemáticas I", "Ingeniería en Sistemas", 3},
        {"SIS103", "Física I", "Ingeniería en Sistemas", 4}
    };
    cursosSistemas[1] = {
        {"SIS201", "Estructuras de Datos", "Ingeniería en Sistemas", 4},
        {"SIS202", "Matemáticas II", "Ingeniería en Sistemas", 3},
        {"SIS203", "Física II", "Ingeniería en Sistemas", 4}
    };
    cursosSistemas[2] = {
        {"SIS301", "Base de Datos", "Ingeniería en Sistemas", 4},
        {"SIS302", "Matemáticas III", "Ingeniería en Sistemas", 3},
        {"SIS303", "Redes de Computadoras", "Ingeniería en Sistemas", 4}
    };
    cursosSistemas[3] = {
        {"SIS401", "Ingeniería de Software", "Ingeniería en Sistemas", 4},
        {"SIS402", "Sistemas Operativos", "Ingeniería en Sistemas", 4},
        {"SIS403", "Cálculo IV", "Ingeniería en Sistemas", 3}
    };
    cursosSistemas[4] = {
        {"SIS501", "Inteligencia Artificial", "Ingeniería en Sistemas", 4},
        {"SIS502", "Desarrollo Web", "Ingeniería en Sistemas", 4},
        {"SIS503", "Seguridad Informática", "Ingeniería en Sistemas", 4}
    };
}

void inicializarCursosCivil(vector<vector<Curso>>& cursosCivil) {
    cursosCivil[0] = {
        {"CIV101", "Cálculo I", "Ingeniería Civil", 4},
        {"CIV102", "Mecánica de Fluidos", "Ingeniería Civil", 4},
        {"CIV103", "Resistencia de Materiales", "Ingeniería Civil", 4}
    };
    cursosCivil[1] = {
        {"CIV201", "Construcción Civil", "Ingeniería Civil", 4},
        {"CIV202", "Geotecnia", "Ingeniería Civil", 4},
        {"CIV203", "Cálculo II", "Ingeniería Civil", 4}
    };
    cursosCivil[2] = {
        {"CIV301", "Estructuras Metálicas", "Ingeniería Civil", 4},
        {"CIV302", "Diseño de Vías", "Ingeniería Civil", 4},
        {"CIV303", "Cálculo III", "Ingeniería Civil", 4}
    };
    cursosCivil[3] = {
        {"CIV401", "Hidrología", "Ingeniería Civil", 4},
        {"CIV402", "Ingeniería Sanitaria", "Ingeniería Civil", 4},
        {"CIV403", "Proyectos de Construcción", "Ingeniería Civil", 4}
    };
    cursosCivil[4] = {
        {"CIV501", "Planeación de Obras", "Ingeniería Civil", 4},
        {"CIV502", "Materiales de Construcción", "Ingeniería Civil", 4},
        {"CIV503", "Métodos Numéricos", "Ingeniería Civil", 4}
    };
}

void inicializarCursosDerecho(vector<vector<Curso>>& cursosDerecho) {
    cursosDerecho[0] = {
        {"DRE101", "Introducción al Derecho", "Derecho", 4},
        {"DRE102", "Derecho Civil", "Derecho", 4},
        {"DRE103", "Derecho Penal", "Derecho", 4}
    };
    cursosDerecho[1] = {
        {"DRE201", "Derecho Administrativo", "Derecho", 4},
        {"DRE202", "Derecho Internacional", "Derecho", 4},
        {"DRE203", "Derecho Constitucional", "Derecho", 4}
    };
    cursosDerecho[2] = {
        {"DRE301", "Derecho Laboral", "Derecho", 4},
        {"DRE302", "Derecho Mercantil", "Derecho", 4},
        {"DRE303", "Derecho Procesal", "Derecho", 4}
    };
    cursosDerecho[3] = {
        {"DRE401", "Derecho Tributario", "Derecho", 4},
        {"DRE402", "Ética Profesional", "Derecho", 4},
        {"DRE403", "Derecho Ambiental", "Derecho", 4}
    };
    cursosDerecho[4] = {
        {"DRE501", "Derecho Notarial", "Derecho", 4},
        {"DRE502", "Criminología", "Derecho", 4},
        {"DRE503", "Litigación Oral", "Derecho", 4}
    };
}

void inicializarCursosPsicologia(vector<vector<Curso>>& cursosPsicologia) {
    cursosPsicologia[0] = {
        {"PSI101", "Psicología General", "Psicología", 4},
        {"PSI102", "Psicología del Desarrollo", "Psicología", 4},
        {"PSI103", "Psicología Social", "Psicología", 4}
    };
    cursosPsicologia[1] = {
        {"PSI201", "Psicología Clínica", "Psicología", 4},
        {"PSI202", "Neuropsicología", "Psicología", 4},
        {"PSI203", "Psicología Educativa", "Psicología", 4}
    };
    cursosPsicologia[2] = {
        {"PSI301", "Psicología Organizacional", "Psicología", 4},
        {"PSI302", "Psicología del Deporte", "Psicología", 4},
        {"PSI303", "Psicología Comunitaria", "Psicología", 4}
    };
    cursosPsicologia[3] = {
        {"PSI401", "Evaluación Psicológica", "Psicología", 4},
        {"PSI402", "Terapia Cognitivo-Conductual", "Psicología", 4},
        {"PSI403", "Psicoterapia", "Psicología", 4}
    };
    cursosPsicologia[4] = {
        {"PSI501", "Psicología Forense", "Psicología", 4},
        {"PSI502", "Intervención Psicológica", "Psicología", 4},
        {"PSI503", "Psicología Positiva", "Psicología", 4}
    };
}

void asignarCurso(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados. No se puede asignar curso.\n";
        return;
    }

    cout << "Seleccione un estudiante para asignar un curso: " << endl;
    for (int i = 0; i < estudiantes.size(); i++) {
        cout << i + 1 << ". " << estudiantes[i].nombres << " " << estudiantes[i].apellidos 
             << " | Código: " << estudiantes[i].codigo << endl;
    }

    int estudianteSeleccionado;
    cout << "Selecciona un estudiante por número: ";
    cin >> estudianteSeleccionado;

    if (estudianteSeleccionado < 1 || estudianteSeleccionado > estudiantes.size()) {
        cout << "Selección de estudiante inválida.\n";
        return;
    }

    vector<vector<Curso>> cursosSistemas(5);
    vector<vector<Curso>> cursosCivil(5);
    vector<vector<Curso>> cursosDerecho(5);
    vector<vector<Curso>> cursosPsicologia(5);

    inicializarCursosSistemas(cursosSistemas);
    inicializarCursosCivil(cursosCivil);
    inicializarCursosDerecho(cursosDerecho);
    inicializarCursosPsicologia(cursosPsicologia);

    int carreraSeleccionada, semestreSeleccionado;

    cout << "Selecciona una carrera:\n";
    cout << "1. Ingeniería en Sistemas\n";
    cout << "2. Ingeniería Civil\n";
    cout << "3. Derecho\n";
    cout << "4. Psicología\n";
    cout << "Ingresa el número de la carrera (1-4): ";
    cin >> carreraSeleccionada;

    cout << "Selecciona un semestre (0-4): ";
    cin >> semestreSeleccionado;

    vector<Curso> cursosElegidos;
    switch (carreraSeleccionada) {
        case 1:
            cursosElegidos = cursosSistemas[semestreSeleccionado];
            break;
        case 2:
            cursosElegidos = cursosCivil[semestreSeleccionado];
            break;
        case 3:
            cursosElegidos = cursosDerecho[semestreSeleccionado];
            break;
        case 4:
            cursosElegidos = cursosPsicologia[semestreSeleccionado];
            break;
        default:
            cout << "Selección inválida.\n";
            return;
    }

    cout << "Cursos disponibles para la carrera seleccionada:\n";
    for (const auto& curso : cursosElegidos) {
        cout << curso.codigo << ": " << curso.nombre 
             << " (Créditos: " << curso.creditos << ")\n";
    }

    string codigoCursoSeleccionado;
    cout << "Selecciona un curso por código: ";
    cin >> codigoCursoSeleccionado;

    bool cursoEncontrado = false;
    for (const auto& curso : cursosElegidos) {
        if (curso.codigo == codigoCursoSeleccionado) {
            for (const auto& c : estudiantes[estudianteSeleccionado - 1].cursos) {
                if (c.codigo == curso.codigo) {
                    cout << "El estudiante ya está asignado al curso: " << curso.nombre << endl;
                    return;
                }
            }

            cursoEncontrado = true;
            cout << "Has seleccionado el curso: " << curso.nombre 
                 << " para el estudiante: " << estudiantes[estudianteSeleccionado - 1].nombres << " " 
                 << estudiantes[estudianteSeleccionado - 1].apellidos << endl;

            estudiantes[estudianteSeleccionado - 1].cursos.push_back(curso);
            cout << "Curso registrado correctamente.\n";
            break;
        }
    }

    if (!cursoEncontrado) {
        cout << "Código de curso inválido.\n";
    }
}

void mostrarMenu() {
    cout << "===============================" << endl;
    cout << "Sistema de Registro Universitario" << endl;
    cout << "===============================" << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Asignar curso" << endl;
    cout << "3. Control de Notas" << endl; 
    cout << "4. Reportes Académicos" << endl;
    cout << "5. Salir" << endl; 
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                registrarEstudiante();
                break;
            case 2:
                asignarCurso(estudiantes);
                break;
            case 3:
                break;
            case 4:

                break;
            case 5:
                cout << "" << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;

    } while (opcion != 5); 

    return 0;
}