#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


typedef enum {
    COL_RESET = 0,
    COL_RED,
    COL_GREEN,
    COL_YELLOW,
    COL_BLUE,
    COL_MAGENTA,
    COL_CYAN,
    COL_WHITE,
    COL_BRIGHT_RED,
    COL_BRIGHT_GREEN,
    COL_BRIGHT_YELLOW,
    COL_BRIGHT_BLUE,
    COL_BRIGHT_MAGENTA,
    COL_BRIGHT_CYAN,
    COL_BRIGHT_WHITE
} tColor;

/*
 * Igual que printf, pero con un parámetro extra para el color.
 * Ejemplo: cprintf(COL_RED, "Error %d\n", codigo);
 */

/*------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>

static const char *color_to_ansi(tColor c) {
    switch (c) {
        case COL_RED:            return "\033[31m";
        case COL_GREEN:          return "\033[32m";
        case COL_YELLOW:         return "\033[33m";
        case COL_BLUE:           return "\033[34m";
        case COL_MAGENTA:        return "\033[35m";
        case COL_CYAN:           return "\033[36m";
        case COL_WHITE:          return "\033[37m";

        case COL_BRIGHT_RED:     return "\033[91m";
        case COL_BRIGHT_GREEN:   return "\033[92m";
        case COL_BRIGHT_YELLOW:  return "\033[93m";
        case COL_BRIGHT_BLUE:    return "\033[94m";
        case COL_BRIGHT_MAGENTA: return "\033[95m";
        case COL_BRIGHT_CYAN:    return "\033[96m";
        case COL_BRIGHT_WHITE:   return "\033[97m";

        case COL_RESET:
        default:                 return "\033[0m";
    }
}

void cprintf(tColor color, const char *fmt, ...) {
    va_list args;

    /* Seteo color */
    fputs(color_to_ansi(color), stdout);

    /* Imprimo como printf normal */
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    /* Reseteo color para no romper el resto de la consola */
    fputs("\033[0m", stdout);
}

/* ================= TIPOS PRIMERO ================= */

typedef char tString[50];

typedef struct {
    int DNI, matricula, nroEmpleado;
    double nroTelefono;
    char fechaNacimiento[9]; /* (AAAAMMDD) 8 caracteres + "\0" */
    char sexo;
    tString domicilio, e_mail, nombreApellido;
    int estadoLaboral; /* [1]-> Tiempo Completo // [2]-> Medio Tiempo */
    int especialidad;
    /*
    Lista de especialidades medicas:
    Dermatologia
    Oftalmologia
    Cirujia General
    Cardiologia
    Endocrinologia
    Otorrinolaringologia
    */
} tMedico;

typedef struct {
    int urgencia;
    /*
    Atencion Inmediata [1]
    Urgencia Alta [2]
    Urgencia Media [3]
    Urgencia Baja [4]
    No Urgente [5]
    */
    tString nombrePaciente, descripcionProblema, alergias, razonDelAlta;
    int tipoDeSangre;
    /*
    [0]-> A+
    [1]-> A-
    [2]-> B+
    [3]-> B-
    [4]-> AB+
    [5]-> AB-
    [6]-> O+
    [7]-> O-
    */
    int contactoEmergencia, DNI;
    int obraSocial;
    /*
    [0]-> Sancor Salud
    [1]-> IOFA
    [2]-> OSDE
    [3]-> IOSCOR
    [4]-> PAMI
    [5]-> OSECAC
    [6]-> Swiss Medical
    [7]-> Particular
    */
} tPaciente;

typedef struct nodo {
    tPaciente paciente;
    struct nodo *siguientePaciente;
} tNodoPaciente;

typedef struct {
    tNodoPaciente *principio;
    tNodoPaciente *final;
} tColaPacientes;

/* ============== PROTOTIPOS DE FUNCION ============== */

/* Menú principal */
void switchMenu(void);
void cargarDatosBase(void);
void menu(void);

/* Médicos */
void iniciarGrabadoArchivo(void);
void finalizarGrabadoArchivo(void);
void grabarArchivoMedico(void);
int  cargarMedicosEnArray(tMedico arrayMed[], int maxMedicos, bool mostrar);
void guardarMedicosEnArchivo(tMedico medicos[], int cantidad);
void mostrarCantidadMedicos(tMedico medicos[], int cantidad);
int  mostrarYBorrarMedico(tMedico medicos[], int cantidad);
void grabarMedico(void);
void switchMenuMedicos(void);
void menuMedicos(int intentos);

/* Pacientes (binarioPacientes) */
void iniciarGrabadoPacientes(void);
void grabarArchivoPaciente(void);
void finalizarGrabadoPaciente(void);
void grabarPaciente(void);
void iniciarCortePacientes(void);
void procesoCortePacientes(void);
void finalizarCortePacientes(void);
void reporteDePacietes(void);
int  cargarPacientesEnArray(tPaciente arrayPaci[], int maxPacientes, bool mostrar);
void mostrarCantidadPacientes(tPaciente array[], int cantidad);

/* Cola de urgencias */
void ordenarPacientesPorUrgencia(tPaciente v[], int n);
void iniciarCola(tColaPacientes *colaPacientes, bool mostrar);
bool colaVacia(tColaPacientes colaPacientes);
void agregarPacientes(tColaPacientes *colaPacientes, tPaciente *arrayP, int cantidadPacientes, bool mostrar);
int  cantidadPacientesEnCola(tColaPacientes colaPacientes);
void visualizarCola(tColaPacientes pPacientes);
void guardarPacientesEnArchivo(tPaciente pPaciente[], int cantidadPacientes);
int  diagnosticarDarAlta(tColaPacientes *pPacientes, tPaciente pArrayPacientes[]);

/* Colores / UI */
static const char *color_to_ansi(tColor c);
void cprintf(tColor color, const char *fmt, ...);

/* Utilidades generales */
void head(void);
void clearScreen(void);
void esperarEnter(int destino);

/* ============== IMPLEMENTACIONES PEQUEÑAS ============== */

/*Funcion que sirve para borrar el cmd*/
void clearScreen(void) {
    char *t = getenv("TERM");
    system((t && strcmp(t, "dumb")) ? "clear" : "cls");
}

/*Funcion que sirve para esperar enter y asi volver al menu correspondiente*/
void esperarEnter(int destino) {
    int c;

    /* 1) Limpiar lo que haya quedado en el buffer
       (por ejemplo el '\n' que dejó un scanf anterior) */
    while ((c = getchar()) != '\n' && c != EOF)
        ;   // no hace nada, sólo consume

    /* 2) Pedir al usuario que pulse Enter */
    printf("\n\nPresione ENTER para volver al menu... ");

    /* 3) Esperar hasta que realmente presione Enter.
       Si escribe "5" y luego Enter, este bucle come el '5'
       y sale recién cuando ve el '\n'. */
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    /* 4) Ir al menú correspondiente */
    switch (destino) {
        case 1:
            menu();
            break;
        case 2:
            switchMenuMedicos();
            break;
    }
}


/* ============== VARIABLES GLOBALES ============== */

/* Variables MEDICOS */
FILE *archMed;
#define MAXMEDICOS 100
tMedico arrayDeMedicos[MAXMEDICOS];
int cantidadDeMedicos;

/*Variables PACIENTES */

/*Variables globales para el corte de control */
int cantidadTotalDePacientes,
    cantidadDePacientesAtencionInmediata,
    cantidaDePacientesUrgenAlta,
    cantidadDePacientesMedia,
    cantidadDePacientesBaja,
    cantidadDePacientesNoUrgente;
int cantPacSancor, cantPacIOFA, cantPacOSDE, cantPacIOSCOR,
    cantPacPAMI, cantPacOSECAC, cantPacSwissMedical, cantPacParticular;
int cantPacSinAlta, cantPacDeAlta;
tPaciente paciente, pacienteAnt;
int totalObraSocial;

#define PATH_ArchPacientes "pacientes.dat"

FILE *archPacientes;
#define MAXPACIENTES 100
tPaciente arrayPacientes[MAXPACIENTES];

/* total de registros en el archivo (todos, con alta y sin alta) */
int cantidadDePacientesTotalGral;

/* cantidad de pacientes que siguen sin alta (razonDelAlta == "SIN ALTA") */
int cantidadPacientesSinAlta;

tColaPacientes colaPacientes;

void switchMenu(){
    int opcion;
    scanf("%d", &opcion);
    switch (opcion){
        case 1:
            grabarPaciente();
            // recargo array desde archivo para incluir el nuevo paciente
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, false);
            // si la cola ya está inicializada, podrías rearmarla
            iniciarCola(&colaPacientes, false);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, false);
            menu();
            break;
        case 2:
            
            visualizarCola(colaPacientes);
        break;
        case 3:
            mostrarCantidadPacientes(arrayPacientes, cantidadDePacientesTotalGral);
        break;
        case 4:
            reporteDePacietes();
        break;
        case 5:
            menuMedicos(0);
        break;
        case 6:
            cprintf(COL_BRIGHT_CYAN, "\n\nCerrando programa...\n\n");
            Sleep(1500);
            exit(EXIT_SUCCESS);
        break;
    }
}

/* Animacion de carga del programa */
void cargarDatosBase(){
    int seg;
    for(seg=0; seg < 8; seg++){ /*For que se usa pasa simular la carga del programa*/
        switch (seg)
        {
        case 0:
        clearScreen();
            cprintf(COL_BRIGHT_CYAN, "\nCargando programa.\n");
            Sleep(1000);
            break;
        case 1:
        clearScreen();
            cprintf(COL_BRIGHT_CYAN, "\nCargando programa..\n");
            Sleep(1000);
            break;
        case 2:
        clearScreen();
            cprintf(COL_BRIGHT_CYAN, "\nCargando programa...\n\nCargando bases de datos.");
            Sleep(1000);
            
            break;
        case 3:
            clearScreen();
            cprintf(COL_BRIGHT_CYAN, "\nCargando bases de datos..\n");
            Sleep(1000);
            
            break;
        case 4:
            clearScreen();
            cprintf(COL_BRIGHT_CYAN, "\nCargando bases de datos...\n");
            cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS, true);
            Sleep(1000);
            break;
        case 5:
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, true);
            Sleep(1500);    
        break;
        case 6:
            iniciarCola(&colaPacientes, true);
            Sleep(1000);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, true);
            Sleep(500);
            if(cantidadDePacientesTotalGral == cantidadPacientesEnCola(colaPacientes)) cprintf(COL_BRIGHT_CYAN, "\nTotalidad de pacientes agregados correctamente\n");
        break;
        case 7:
            cprintf(COL_BRIGHT_CYAN, "\nPrograma ya cargado y compilado... Iniciando...\n\n");
            Sleep(1000);    
        break;
        }
    }
}

void menu(){
    
    clearScreen();

    cprintf(COL_BRIGHT_CYAN, "  =============================================\n");
    cprintf(COL_BRIGHT_CYAN, "  ================Menu Principal===============\n");
    cprintf(COL_BRIGHT_CYAN, "  =============================================\n");

    cprintf(COL_BRIGHT_YELLOW, "\n[1]"); cprintf(COL_RESET, " - Agregar paciente");
    cprintf(COL_BRIGHT_YELLOW, "\n[2]"); cprintf(COL_RESET, " - Ver cola de Pacientes");
    cprintf(COL_BRIGHT_YELLOW, "\n[3]"); cprintf(COL_RESET, " - Ver lista de pacientes por DNI y Nombre");
    cprintf(COL_BRIGHT_YELLOW, "\n[4]"); cprintf(COL_RESET, " - Mostrar registro de pacientes");
    cprintf(COL_BRIGHT_YELLOW, "\n[5]"); cprintf(COL_RESET, " - Abrir menu de medicos (privado)");
    cprintf(COL_BRIGHT_YELLOW, "\n[6]"); cprintf(COL_RESET, " - Cerra programa");
    cprintf(COL_BRIGHT_BLUE, "\n\nOpcion: ");


    switchMenu();
}

#define PATH_ArchMed "medicos.dat"

/*Prototipos de funciones que hacen corto no se porque...*/


/*
int cargarPacientesEnArray(tPaciente arrayPaci[], int maxPacientes, bool mostrar);
void iniciarCola(tColaPacientes* colaPacientes, bool mostrar);
void agregarPacientes(tColaPacientes* colaPacientes, tPaciente* arrayP, int cantidadPacientes, bool mostrar);
bool colaVacia(tColaPacientes colaPacientes);
int diagnosticarDarAlta(tColaPacientes* pPacientes, tPaciente pArrayPacientes[]);
*/

void iniciarGrabadoArchivo(void){
    archMed = fopen(PATH_ArchMed, "ab");
    if (archMed == NULL) {
        cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("Error al abrir medicos.dat\n");
        Sleep(2000);
        switchMenuMedicos();
    } else {
        cprintf(COL_GREEN, "Archivo abierto en modo [Agregar al final] binario\n");
    }
}


void finalizarGrabadoArchivo(void){
    fclose(archMed);
    Sleep(2000);
}


void grabarArchivoMedico(void){
    tMedico inputMedico;

    clearScreen();
    cprintf(COL_BLUE, "Ingrese los datos a grabar");

    printf("\nNombre y Apellido: ");
    scanf(" %49[^\n]", inputMedico.nombreApellido);

    printf("\nDNI del medico: ");
    scanf(" %d", &inputMedico.DNI);

    printf("\nNumero de telefono: ");
    scanf(" %lf", &inputMedico.nroTelefono); /*Lee un Long Float para evitar overflow cuando se ingresan mas caracteres que los que usa int Ej: 3772637968*/

    printf("\nFecha de Nacimiento (formato AAAAMMDD): ");
    scanf(" %8s", inputMedico.fechaNacimiento);

    printf("\nSexo del Medico (M/F): ");
    scanf(" %c", &inputMedico.sexo);

    printf("\nDomicilio: ");
    scanf(" %49[^\n]", inputMedico.domicilio);

    printf("\nCorreo Electronico: ");
    scanf(" %49s", inputMedico.e_mail);
    
    srand(inputMedico.DNI);
    printf("\nMatricula del medico: %d", rand());
    Sleep(1000);

    inputMedico.nroEmpleado = cantidadDeMedicos+1;
    printf("\nNumero de empleado: %d\n", inputMedico.nroEmpleado);
    Sleep(1000);


    printf("\nLista de especialidades: ");
    cprintf(COL_GREEN, "\n[1] "); printf("Dermatologia");
    cprintf(COL_GREEN, "\n[2] "); printf("Oftalmologia");
    cprintf(COL_GREEN, "\n[3] "); printf("Cirugia General");
    cprintf(COL_GREEN, "\n[4] "); printf("Cardiologia");
    cprintf(COL_GREEN, "\n[5] "); printf("Endocrinologia");
    cprintf(COL_GREEN, "\n[6] "); printf("Otorrinolaringologia\n");
    Sleep(1000);

    printf("\nEspecialidad: ");
    scanf(" %d", &inputMedico.especialidad);
    Sleep(1000);

    cprintf(COL_BLUE, "\n[1] "); printf("Tiempo Completo");
    cprintf(COL_BLUE, "\n[2] "); printf("Medio tiempo\nEstado laboral: ");
    scanf(" %d", &inputMedico.estadoLaboral); // o &inputMedico.estadoLaboral si existe
    Sleep(1000);

    fwrite(&inputMedico, sizeof(tMedico), 1, archMed);
    printf("\nMedico %s agregado al archivo!\n", inputMedico.nombreApellido);
}


/* Carga todos los medicos del binario en un array y devuelve cuantos cargo*/
int cargarMedicosEnArray(tMedico arrayMed[], int maxMedicos, bool mostrar){
    int i = 0;
    if(mostrar){
        archMed = fopen(PATH_ArchMed, "rb");
        if (archMed == NULL) {
        cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("Error al abrir el archivo\n");
        cprintf(COL_YELLOW, "\nCreando archivo... Volviendo al menu principal\n\n");
        archMed = fopen(PATH_ArchMed, "wb"); //Esto deberia crear el archivo med
        Sleep(1000);
        if(archMed != NULL){ cprintf(COL_BRIGHT_GREEN, "\n\n[EXITO] -> "); printf("Archivo creado con exitos, nombre archivo: %s\n\n", PATH_ArchMed); }
        Sleep(1000);
        } else {
        cprintf(COL_BRIGHT_GREEN, "Archivo de medicos abierto en modo lectura.\n");
        }

        while (i < maxMedicos &&
           fread(&arrayMed[i], sizeof(tMedico), 1, archMed) == 1) {
            i++;
        }
        cprintf(COL_CYAN, "\nTotal de medicos agregados al array: %d\n", i);

        fclose(archMed);
        Sleep(3000);
        
    } else {
        archMed = fopen(PATH_ArchMed, "rb");
        while (i < maxMedicos &&
           fread(&arrayMed[i], sizeof(tMedico), 1, archMed) == 1) {
            i++;
        }
        fclose(archMed);
    }
    
    return i;
}



/* Guarda TODO el array en el archivo binario (sobrescribe) */
void guardarMedicosEnArchivo(tMedico medicos[], int cantidad) {
    FILE *f = fopen(PATH_ArchMed, "wb");
    if (f == NULL) {
        cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("Error al abrir medicos.dat para escritura.\n");
        Sleep(1000);
        menu();
    }

    if (cantidad > 0) {
        size_t escritos = fwrite(medicos, sizeof(tMedico), cantidad, f);
        if (escritos != (size_t)cantidad) {
            cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("Error al escribir medicos.dat\n");
        }
    }

    fclose(f);
}


void mostrarCantidadMedicos(tMedico medicos[], int cantidad){
    int i;
    if (cantidad == 0) {
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> "); printf("No hay medicos cargados.\n");
        Sleep(1500);
        switchMenuMedicos();
    }

    cprintf(COL_BRIGHT_BLUE, "\n=========== LISTA DE MEDICOS ===========\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s\n",
               i + 1,
               medicos[i].DNI,
               medicos[i].nombreApellido);
    }
    cprintf(COL_BRIGHT_BLUE, "========================================\n");
    esperarEnter(2);
}


/* Muestra lista y permite borrar por DNI o nombre. */
/* Devuelve la NUEVA cantidad de medicos. */
int mostrarYBorrarMedico(tMedico medicos[], int cantidad) {
    int opcion;
    int idx;
    int i;
    int dniBuscado;
    tString nombreBuscado;
    char confirma;

    if (cantidad == 0) {
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("No hay medicos cargados.\n");
        Sleep(2500);
        return 0;
    }

    clearScreen();
    cprintf(COL_BRIGHT_BLUE, "\n=========== LISTA DE MEDICOS ===========\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s\n",
               i + 1,
               medicos[i].DNI,
               medicos[i].nombreApellido);
    }
    cprintf(COL_BRIGHT_BLUE, "========================================\n");

    opcion = 0;
    printf("\n¿Como desea borrar?\n");
    cprintf(COL_CYAN, "[1] "); printf("Por DNI\n");
    cprintf(COL_CYAN, "[2] "); printf("Por Nombre\n");
    printf("Opcion: ");
    scanf(" %d", &opcion);

    idx = -1;  //posicion del medico a borrar

    if (opcion == 1) {
        printf("\nIngrese el DNI del medico a borrar: ");
        scanf(" %d", &dniBuscado);

        for (i = 0; i < cantidad; i++) {
            if (medicos[i].DNI == dniBuscado) {
                idx = i;
                break;
            }
        }
    }
    else if (opcion == 2) {
        printf("\nIngrese el nombre "); cprintf(COL_YELLOW, "COMPLETO"); printf(" del medico a borrar: ");
        scanf(" %49[^\n]", nombreBuscado);

        for (i = 0; i < cantidad; i++) {
            if (strcmp(medicos[i].nombreApellido, nombreBuscado) == 0) {
                idx = i;
                break;
            }
        }
    }
    else {
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("Opcion invalida.\n");
        return cantidad;
    }

    if (idx == -1) {
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("No se encontro el medico.\n");
        return cantidad;
    }

    //Confirmacion
    printf("\nVas a borrar al siguiente medico:\n");
    printf("DNI: %d\nNombre: %s\n",
           medicos[idx].DNI,
           medicos[idx].nombreApellido);

    printf("Confirmar borrado? (s/n): ");
    scanf(" %c", &confirma);

    if (confirma != 's' && confirma != 'S') {
        cprintf(COL_BRIGHT_GREEN, "[EXITO] -> "); printf("Borrado cancelado.\n");
        return cantidad;
    }

    //Correr el array una posicion hacia atras desde idx
    for (i = idx; i < cantidad - 1; i++) {
        medicos[i] = medicos[i + 1];
    }
    cantidad--;

    // Actualizar archivo binario con el nuevo array
    guardarMedicosEnArchivo(medicos, cantidad);

    cprintf(COL_BRIGHT_GREEN, "[EXITO] -> "); printf("Medico borrado y archivo actualizado correctamente.\n");
    printf("\nVolviendo al menu medicos!");
    Sleep(2000);
    clearScreen();
    return cantidad;
}



void grabarMedico(void){
    iniciarGrabadoArchivo();
    grabarArchivoMedico();
    finalizarGrabadoArchivo();
    cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS, false);
}


/*------------------------------------------------------------------------------------------------*/
int cantidadActualMedicos; //Se usa en linea 286

/*Switch para manejo del menu de medicos*/
void switchMenuMedicos(){
    clearScreen();
        /*Escribimos las opciones en pantalla y luego el switch*/
        cprintf(COL_BRIGHT_GREEN, "\t\t*** Menu Medicos ***\n\n");
        /* printf("[0] Dar urgencia a pacientes aun no atendidos"); Esto agrega bastante complejidad, vemos si hacemos esta opcion o no una vez terminado todo */
        cprintf(COL_BLUE, "\n[1] "); printf("-> Atender paciente y Dar de alta");
        cprintf(COL_BLUE, "\n[2] "); printf("-> Agregar Medico");
        cprintf(COL_BLUE, "\n[3] "); printf("-> Mostrar cantidad de medicos");
        cprintf(COL_BLUE, "\n[4] "); printf("-> Borrar medicos de la Base de Datos");
        cprintf(COL_BLUE, "\n[5] "); printf("-> Volver al Menu Principal");
        cprintf(COL_BLUE, "\nOpcion: ");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            if(cantidadDeMedicos == 0){
                cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("No hay medicos cargados\n");
                Sleep(2000);
                switchMenuMedicos();
            } else {
            /* 
             * 1) Sincronizamos ARRAY de pacientes con el archivo
             * 2) Reconstruimos la cola solo con pacientes SIN ALTA
             * 3) Atendemos al primero y damos de alta
             * 4) Mostramos cuantos quedan sin alta
             */
            /* 1) Cargar pacientes desde el archivo al array global*/
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, false);
            if (cantidadDePacientesTotalGral == 0) {
                cprintf(COL_BRIGHT_MAGENTA, "\n\n[WARNING] -> "); printf("hay pacientes cargados en el sistema.\n");
                Sleep(2000);
                switchMenuMedicos();
                break;
            }
            /* 2) Reconstruir la cola con los pacientes que siguen con NOALTA*/
            iniciarCola(&colaPacientes, false);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, false);
            if (colaVacia(colaPacientes)) {
                cprintf(COL_BRIGHT_MAGENTA, "\n\n[WARNING] -> "); printf("No hay pacientes en espera para dar de alta.\n");
                Sleep(2500);
                switchMenuMedicos();
                break;
            }
            /* 3) Atender y dar de alta al primero de la cola*/
            int restantesSinAlta = diagnosticarDarAlta(&colaPacientes, arrayPacientes);
            /* 4) Feedback operativo */
            if (restantesSinAlta > 0) {
                cprintf(COL_BRIGHT_GREEN, "\n\nQuedan %d pacientes para dar de alta.\n", restantesSinAlta);
            } else {
                cprintf(COL_BRIGHT_YELLOW, "\n\nNo quedan pacientes pendientes de alta.\n");
            }
            esperarEnter(2);
            switchMenuMedicos();
            }
            break;
        case 2:
            grabarMedico();
            Sleep(500);
            switchMenuMedicos();
        break;
        case 3:
            mostrarCantidadMedicos(arrayDeMedicos, cantidadDeMedicos);
        break;
        case 4:
            cantidadActualMedicos = cantidadDeMedicos;
            cantidadDeMedicos = mostrarYBorrarMedico(arrayDeMedicos, cantidadActualMedicos);
            switchMenuMedicos();
        break;
        case 5:
            clearScreen();
            cprintf(COL_BRIGHT_CYAN, "Volviendo al menu principal...");
            Sleep(1500);
            menu();
        break;
        }
}

/*Menu del apartado medicos:*/
void menuMedicos(int intentos){

    /*La password es unica solo los medicos la deberian conocer.
    Pero en este caso la vamos a poner en pantalla ya que los profes no saben la contraseña...*/

    clearScreen();

    cprintf(COL_YELLOW, "\nAyuda rapida... la password es: lindstrom\n\n");
    tString password = "lindstrom";
    tString passRTA;
    printf("\nUsted eligio el apartado medicos... \nIngrese la contrasenia: ");
    scanf("%15s", passRTA);

    if(strcmp(password, passRTA) == 0){
        clearScreen();
        cprintf(COL_GREEN, "\nContraseña correcta! Abriendo el menu de medicos...\n");
        switchMenuMedicos();
    } else {
        clearScreen();
        if(intentos < 3){
            cprintf(COL_RED, "\nContrasenia incorrecta! Le quedan %d intentos", 3 - intentos);
            printf("\nEspere 4 segundos para volver a intentar...");
            Sleep(4000); // usar ms
            menuMedicos(intentos+1);
        } else {
            clearScreen();
            printf("\nUsted quedo sin intentos, saliendo al menu principal\n");
            menu();
        }
    }
}

#define PATH_ArchPacientes "pacientes.dat"





/*------------------------------------------------------------------------------------------------
Grabar archivos pacientes
------------------------------------------------------------------------------------------------*/

/*Funcion que inicia el archivo para el grabado*/
void iniciarGrabadoPacientes(){
    archPacientes = fopen(PATH_ArchPacientes, "ab");

    if(archPacientes == NULL){
        cprintf(COL_BRIGHT_RED, "[ERROR] -> No se puede abrir pacientes.dat\n");
        menu();
    } else {
        cprintf(COL_GREEN, "[EXITO] -> Archivo %s listo para grabar pacientes", PATH_ArchPacientes);
    }
}

/*Funcion que graba el archivo de pacientes*/
void grabarArchivoPaciente(){
    tPaciente inputPaciente;

    clearScreen();
    
    cprintf(COL_BRIGHT_CYAN, "Usted ingreso a la opcion para Aniadir un paciente!\n");
    cprintf(COL_BRIGHT_CYAN, "A continuacion... Ingrese los datos de este:\n");
    
    printf("\nNombre del paciente: ");
    scanf(" %49[^\n]", inputPaciente.nombrePaciente);

    printf("\nDescripcion del problema: ");
    scanf(" %49[^\n]", inputPaciente.descripcionProblema);

    printf("\nEl paciente tiene alguna alergia? Respuesta: ");
    scanf(" %49[^\n]", inputPaciente.alergias);

    printf("\nTipo de sangre del paciente: ");
    cprintf(COL_BLUE, "\n[0] "); printf("-> A+");
    cprintf(COL_BLUE, "\n[1] "); printf("-> A-");
    cprintf(COL_BLUE, "\n[2] "); printf("-> B+");
    cprintf(COL_BLUE, "\n[3] "); printf("-> B-");
    cprintf(COL_BLUE, "\n[4] "); printf("-> AB+");
    cprintf(COL_BLUE, "\n[5] "); printf("-> AB-");
    cprintf(COL_BLUE, "\n[6] "); printf("-> O+");
    cprintf(COL_BLUE, "\n[7] "); printf("-> O-\n");
    cprintf(COL_RED, "\nElegir tipo de sangre: ");
    scanf("%d", &inputPaciente.tipoDeSangre);

    printf("\nObra social del paciente: ");
    cprintf(COL_BLUE, "\n[0] "); printf("-> Sancor Salud");
    cprintf(COL_BLUE, "\n[1] "); printf("-> IOFA");
    cprintf(COL_BLUE, "\n[2] "); printf("-> OSDE");
    cprintf(COL_BLUE, "\n[3] "); printf("-> IOSCOR");
    cprintf(COL_BLUE, "\n[4] "); printf("-> PAMI");
    cprintf(COL_BLUE, "\n[5] "); printf("-> OSECAC");
    cprintf(COL_BLUE, "\n[6] "); printf("-> Swiss Medical");
    cprintf(COL_BLUE, "\n[7] "); printf("-> Particular\n");
    printf("\nElegir obra social: ");
    scanf("%d", &inputPaciente.obraSocial);

    printf("\nAlgun contacto de emergencia(NRO TELEFONO): ");
    scanf("%d", &inputPaciente.contactoEmergencia);

    printf("\nDNI del paciente: ");
    scanf("%d", &inputPaciente.DNI);

    printf("\nUrgencia de atencion: (OPCIONES)");
    cprintf(COL_RED, "\n[1] "); printf("-> Atencion Inmediata");
    cprintf(COL_YELLOW, "\n[2] "); printf("-> Urgencia Alta");
    cprintf(COL_MAGENTA, "\n[3] "); printf("-> Urgencia Media");
    cprintf(COL_CYAN, "\n[4] "); printf("-> Urgencia Baja");
    cprintf(COL_GREEN, "\n[5] "); printf("-> No urgente\n");
    printf("\nOpcion a elegir: ");
    scanf("%d", &inputPaciente.urgencia);
    

    /*No se agrega la urgencia porque ahora pasa a la
    fase donde el medico debe evaluar la situacion y
    darle un tipo de urgencia.
    
    Pasamos directamente a grabar el archivo binario*/

    strcpy(inputPaciente.razonDelAlta, "SIN ALTA"); /*Inicializamos con la Flag NO ALTA para saber que a este paciente aun no se le dio el alta*/

    fwrite(&inputPaciente, sizeof(tPaciente), 1, archPacientes);
    cprintf(COL_GREEN, "\n\nPaciente %s agregado al archivo para revision", inputPaciente.nombrePaciente);
}

/*Funcion que cierra el archivo una vez grabado*/
void finalizarGrabadoPaciente(){
    fclose(archPacientes);
    cprintf(COL_GREEN, "\n\nYa se cerro el archivo... \n\nvolviendo al menu principal... \n\n(ESPERANDO 10 SEGUNDOS)");
    Sleep(10000);
}

/*Funcion maestra que comanda el grabado de pacientes en el archivo*/
void grabarPaciente(){
    iniciarGrabadoPacientes();
    grabarArchivoPaciente();
    finalizarGrabadoPaciente();
}

/*Funcion que inicia el corte del archivo de pacientes*/
void iniciarCortePacientes(){
    archPacientes = fopen(PATH_ArchPacientes, "rb");



    if(archPacientes == NULL){
        cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("\nEl programa fallo al abrir el archivo de los pacientes.dat\nVolviendo al menu principal...");
        menu();
    } else {
        if(fread(&paciente, sizeof(tPaciente), 1, archPacientes) == 0){
            cprintf(COL_BRIGHT_MAGENTA, "[WARNING] ->"); printf("No hay ningun paciente cargado\n");
            Sleep(2500);
            menu();
        }
    }

    pacienteAnt = paciente;

    cantidadTotalDePacientes = 0;
    cantidadDePacientesAtencionInmediata = 0;
    cantidadDePacientesBaja = 0;
    cantidadDePacientesMedia = 0;
    cantidaDePacientesUrgenAlta = 0;
    cantidadDePacientesNoUrgente = 0;
    cantPacDeAlta = 0;
    cantPacSinAlta = 0;
    cantPacSancor = 0;
    cantPacIOFA = 0;
    cantPacOSDE = 0;
    cantPacIOSCOR = 0;
    cantPacPAMI = 0;
    cantPacOSECAC = 0;
    cantPacSwissMedical = 0;
    cantPacParticular = 0;
    totalObraSocial = 0;
    clearScreen();
    cprintf(COL_BRIGHT_CYAN, "\t\t\t\t\t*** REPORTE DE PACIENTES ***\n");
    tString nombre, estadoAc, urgencia, nroEmer, dni, social;
    strcpy(nombre, "Nombre Completo");
    strcpy(estadoAc, "Estado Actual");
    strcpy(urgencia, "Urgencia");
    strcpy(nroEmer, "Contacto De Emergencia");
    strcpy(dni, "Documento");
    strcpy(social, "Obra Social");
    printf("\n%-30s %-15s %-15s %-30s %-10s %-15s\n", nombre, estadoAc, urgencia, nroEmer, dni, social);
}

/*Funcion que realiza el corte del archivo de pacientes*/
void procesoCortePacientes(){
    while(!feof(archPacientes)){
        tString estadoActualDelPaciente, ObraSocial, Urgencia;
        while(!feof(archPacientes) && pacienteAnt.DNI == paciente.DNI){
            cantidadTotalDePacientes++;
            switch(paciente.obraSocial){
            case 0:
                cantPacSancor++;
                strcpy(ObraSocial, "Sancor Salud");
            break;
            case 1:
                cantPacIOFA++;
                strcpy(ObraSocial, "IOFA");
            break;
            case 2:
                cantPacOSDE++;
                strcpy(ObraSocial, "OSDE");
            break;
            case 3:
                cantPacIOSCOR++;
                strcpy(ObraSocial, "IOSCOR");
            break;
            case 4:
                cantPacPAMI++;
                strcpy(ObraSocial, "PAMI");
            break;
            case 5:
                cantPacOSECAC++;
                strcpy(ObraSocial, "OSECAC");
            break;
            case 6:
                cantPacSwissMedical++;
                strcpy(ObraSocial, "Swiss Medical");
            break;
            case 7:
                cantPacParticular++;
                strcpy(ObraSocial, "Particular");
            break;
            } /*salimos del switch*/
            switch(paciente.urgencia){
                case 1:
                    cantidadDePacientesAtencionInmediata++;
                    strcpy(Urgencia, "Atencion Inmediata");
                break;
                case 2:
                    cantidaDePacientesUrgenAlta++;
                    strcpy(Urgencia, "Urgencia Alta");
                break;
                case 3:
                    cantidadDePacientesMedia++;
                    strcpy(Urgencia, "Urgencia Media");
                break;
                case 4:
                    cantidadDePacientesBaja++;
                    strcpy(Urgencia, "Urgencia Baja");
                break;
                case 5:
                    cantidadDePacientesNoUrgente++;
                    strcpy(Urgencia, "No urgente");
                break;
            } /*Salimos del switch*/
            switch(strcmp(paciente.razonDelAlta, "SIN ALTA") == 0){
                case 1:
                    cantPacSinAlta++;
                    strcpy(estadoActualDelPaciente, "En espera de alta");
                break;
                default:
                    cantPacDeAlta++;
                    strcpy(estadoActualDelPaciente, "Dado de Alta");
                break;
            }
            printf("\n%-30s %-15s %-15s %-30d %-10d %-15s", paciente.nombrePaciente, estadoActualDelPaciente, Urgencia, paciente.contactoEmergencia, paciente.DNI, ObraSocial);
            fread(&paciente, sizeof(tPaciente), 1, archPacientes);
        }
        pacienteAnt = paciente;
    }
}

/*Funcion que muestra totales luego del corte del archivo de pacientes*/
void finalizarCortePacientes(){
    printf("\n\n--------------------------------------------------------------------------------------------------------------\n");
    printf("Total de pacientes: %d\n", cantidadTotalDePacientes);
    printf("Cantidad de pacientes particulares: %d\n", cantPacParticular);
    totalObraSocial += cantPacSancor + cantPacIOFA + cantPacOSDE + cantPacIOSCOR + cantPacPAMI + cantPacOSECAC + cantPacSwissMedical;
    float porcentajeSinObraSocial = (cantPacParticular * 100) / cantidadTotalDePacientes;
    printf("Porcentaje sin obra social: %.2f\n", porcentajeSinObraSocial);
    printf("Cantidad de pacientes con obra social: %d\n", totalObraSocial);
    printf("Cantidad de pacientes hospitalizados: %d\n", cantPacSinAlta);
    printf("Cantidad de pacientes dados de Alta: %d\n", cantPacDeAlta);
    fclose(archPacientes);
    esperarEnter(1);
}

/*Funcion maestra que comanda el corte del archivo de pacientes*/
void reporteDePacietes(){
    iniciarCortePacientes();
    procesoCortePacientes();
    finalizarCortePacientes();
}

/*Funcion que carga los pacientes en un array*/
int cargarPacientesEnArray(tPaciente arrayPaci[], int maxPacientes, bool mostrar){
    int i = 0;
    if(mostrar){
        archPacientes = fopen(PATH_ArchPacientes, "rb");
        if (archPacientes == NULL) {
            cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("Error al abrir el archivo\n");
            printf("\nCreando archivo... Volviendo al menu principal\n\n");
            archPacientes = fopen(PATH_ArchPacientes, "wb");
            Sleep(1000);
            if(archPacientes != NULL){
                cprintf(COL_GREEN, "\n\nArchivo creado con exito, nombre archivo: %s\n\n", PATH_ArchPacientes);
            }
            Sleep(3000);
            return 0;
        } else {
            cprintf(COL_BRIGHT_GREEN, "[EXITO] -> ");printf("\nArchivo de pacientes abierto en modo lectura.\n");
        }

        while (i < maxPacientes &&
               fread(&arrayPaci[i], sizeof(tPaciente), 1, archPacientes) == 1) {
            i++;
        }
        printf("\nTotal de pacientes agregados al array: %d\n", i);

        fclose(archPacientes);
        Sleep(1500);
        
    } else {
        /* *** MODO SILENCIOSO, SIN PRINTS, PARA USO INTERNO *** */
        archPacientes = fopen(PATH_ArchPacientes, "rb");
        if (archPacientes == NULL){
            return 0;
        }

        while (i < maxPacientes &&
               fread(&arrayPaci[i], sizeof(tPaciente), 1, archPacientes) == 1) {
            i++;
        }

        fclose(archPacientes);
    }

    /* actualizamos contador global del total de registros */
    cantidadDePacientesTotalGral = i;
    return i;
}

/*Funcion que muestra los pacientes del array*/
void mostrarCantidadPacientes(tPaciente array[], int cantidad){
    int i;
    if (cantidad == 0) {
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> "); printf("No hay pacientes cargados.\n");
        Sleep(1500);
        menu();
        return; /* importante para NO seguir ejecutando */
    }
    cprintf(COL_BRIGHT_CYAN, "\n=============== LISTA DE PACIENTES ===============\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %-9d  |  Nombre: %-30s  |  Estado: %-20s\n",
               i + 1,
               array[i].DNI,
               array[i].nombrePaciente,
               array[i].razonDelAlta);  /* <- antes usabas array[1] */
    }
    cprintf(COL_BRIGHT_CYAN, "========================================================================================================\n");
    esperarEnter(1);
}

/*Funcion para ordenar un array por urgencia*/
void ordenarPacientesPorUrgencia(tPaciente v[], int n){
    int i, j;
    tPaciente aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j].urgencia > v[j + 1].urgencia) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

/*Funcion que inicia la cola*/
void iniciarCola(tColaPacientes* colaPacientes, bool mostrar){
    if(mostrar){
        colaPacientes->principio = NULL;
    colaPacientes->final = NULL;
    cprintf(COL_GREEN, "\n[SUCCESS] -> Cola de Pacientes Iniciada...\n");
    Sleep(1000);    
    } else {
        colaPacientes->principio = NULL;
        colaPacientes->final = NULL;
    }
}

/*Funcion para verificar si hay pacientes en la cola*/
bool colaVacia(tColaPacientes colaPacientes){
    return (colaPacientes.principio == NULL && colaPacientes.final == NULL);
}

/*Funcion que agrega pacientes en la cola desde el array creado*/
void agregarPacientes(tColaPacientes* colaPacientes, tPaciente* arrayP, int cantidadPacientes, bool mostrar){
    int i;

    /* Ordenamos el array por urgencia (1 mas urgente, 5 menos) */
    ordenarPacientesPorUrgencia(arrayP, cantidadPacientes);

    for(i=0;i < cantidadPacientes; i++){
        if(strcmp(arrayP[i].razonDelAlta, "SIN ALTA") == 0){
            tNodoPaciente* nuevoPaciente = (tNodoPaciente*) malloc(sizeof(tNodoPaciente));
            nuevoPaciente->paciente = arrayP[i];
            nuevoPaciente->siguientePaciente = NULL;
            if(colaVacia(*colaPacientes)){
                colaPacientes->principio = nuevoPaciente;
                colaPacientes->final = nuevoPaciente;
            } else {
                colaPacientes->final->siguientePaciente = nuevoPaciente;
                colaPacientes->final = nuevoPaciente;
            } 
        } else { continue; }
    }
    if(mostrar) {cprintf(COL_BLUE, "\nSe agregaron %d pacientes a la cola", i);}
} 

/*Funcion que devuelve la cantidad de pacientes en la cola*/
int cantidadPacientesEnCola(tColaPacientes colaPacientes){
    int cantidad = 0;

    if (colaVacia(colaPacientes)) {
        return 0;
    }

    tNodoPaciente* listaPacientes = colaPacientes.principio;
    while (listaPacientes != NULL) {
        cantidad++;
        listaPacientes = listaPacientes->siguientePaciente;
    }

    return cantidad;
}

/*Funcion que se usa para visualizar la cola en orden de urgencia*/
void visualizarCola(tColaPacientes pPacientes){
    cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");
    cprintf(COL_BRIGHT_CYAN, "\t*** Pacientes en espera ***");
    cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");

    if(colaVacia(pPacientes)){
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> ");
        cprintf(COL_BRIGHT_WHITE, "La cola esta vacia...\n");
        Sleep(2000);
        menu();
    } else {
        clearScreen();
        tNodoPaciente* listaPacientes = pPacientes.principio;
        tString NOMBRE, DNI, CODIGO;
        strcpy(NOMBRE, "Nombre Completo");
        strcpy(DNI, "Documento");
        strcpy(CODIGO, "Urgencia");

        cprintf(COL_BRIGHT_CYAN, "%-30s %-10s %s\n", NOMBRE, DNI, CODIGO);
        while (listaPacientes != NULL){
            printf("%-30s\t%-8d\t", 
                listaPacientes->paciente.nombrePaciente,
                listaPacientes->paciente.DNI
            );
            switch(listaPacientes->paciente.urgencia){
                case 1:
                    cprintf(COL_RED, "Atencion Inmediata\n");
                    break;
                case 2:
                    cprintf(COL_YELLOW, "Urgencia Alta\n");
                    break;
                case 3:
                    cprintf(COL_MAGENTA, "Atencion Media\n");
                    break;
                case 4:
                    cprintf(COL_CYAN, "Atencion Baja\n");
                    break;
                case 5:
                    cprintf(COL_GREEN, "No urgente\n");
                    break;
                }
            listaPacientes = listaPacientes->siguientePaciente;
        }
        esperarEnter(1);
    }
}

/*Funciones necesarias para la manipulacion de archivos al momento de desencolar...*/
void guardarPacientesEnArchivo(tPaciente pPaciente[], int cantidadPacientes){
    FILE * arch = fopen(PATH_ArchPacientes, "wb");
    if (arch == NULL){
        cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("No se pudo abrir pacientes.dat para escritura.\n");
        return;
    }

    if(cantidadPacientes > 0) {
        size_t escritos = fwrite(pPaciente, sizeof(tPaciente), cantidadPacientes, arch);
        if(escritos != (size_t)cantidadPacientes){
            cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("Ocurrio un error al guardar el array pacientes en el Archivo...\n");
        }
    }

    fclose(arch);
}


int diagnosticarDarAlta(tColaPacientes* pPacientes, tPaciente pArrayPacientes[]){
    /* 1) Sincronizar array con el archivo SIEMPRE */
    int cantidadActual = cargarPacientesEnArray(pArrayPacientes, MAXPACIENTES, false);

    if(cantidadActual == 0){
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("No hay pacientes cargados en el archivo.\n");
        cantidadPacientesSinAlta = 0;
        return 0;
    }

    /* 2) Si la cola está vacía, solo devolvemos cuántos siguen sin alta*/
    if(colaVacia(*pPacientes)){
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> "); printf("No hay pacientes en la cola para dar de alta.\n");

        int sinAlta = 0;
        int i;
        for (i = 0; i < cantidadActual; i++){
            if (strcmp(pArrayPacientes[i].razonDelAlta, "SIN ALTA") == 0){
                sinAlta++;
            }
        }
        cantidadPacientesSinAlta = sinAlta;
        return sinAlta;
    }

    /* 3) Tomamos el nodo del frente de la cola */
    tNodoPaciente* pacienteADarDeAlta = pPacientes->principio;
    tPaciente *pac = &pacienteADarDeAlta->paciente;

    /* 4) Mostrar info del paciente */
    cprintf(COL_BRIGHT_MAGENTA, "\n\nEmpecemos con la atencion...\n");

    printf("\n[Tipo atencion] -> ");
    switch (pac->urgencia){
        case 1: cprintf(COL_RED,    "ATENCION INMEDIATA"); break;
        case 2: cprintf(COL_YELLOW, "URGENCIA ALTA");      break;
        case 3: cprintf(COL_MAGENTA,"URGENCIA MEDIA");     break;
        case 4: cprintf(COL_CYAN,   "URGENCIA BAJA");      break;
        case 5: cprintf(COL_GREEN,  "NO URGENTE");         break;
    }

    cprintf(COL_BLUE, "\nNombre del Paciente: "); printf("%s", pac->nombrePaciente);
    cprintf(COL_BLUE, "\nAlergias: ");            printf("%s", pac->alergias);

    cprintf(COL_BLUE, "\nTipo de sangre: ");
    switch (pac->tipoDeSangre){
        case 0: printf("A+");  break;
        case 1: printf("A-");  break;
        case 2: printf("B+");  break;
        case 3: printf("B-");  break;
        case 4: printf("AB+"); break;
        case 5: printf("AB-"); break;
        case 6: printf("O+");  break;
        case 7: printf("O-");  break;
    }

    printf("\nContacto Emergencia: %d\tDNI: %d\tObra Social: ", pac->contactoEmergencia, pac->DNI);
    switch (pac->obraSocial){
        case 0: cprintf(COL_BRIGHT_BLUE,    "Sancor Salud");  break;
        case 1: cprintf(COL_BRIGHT_BLUE,    "IOFA");          break;
        case 2: cprintf(COL_BRIGHT_BLUE,    "OSDE");          break;
        case 3: cprintf(COL_BRIGHT_BLUE,    "IOSCOR");        break;
        case 4: cprintf(COL_BRIGHT_BLUE,    "PAMI");          break;
        case 5: cprintf(COL_BRIGHT_BLUE,    "OSECAC");        break;
        case 6: cprintf(COL_BRIGHT_BLUE,    "Swiss Medical"); break;
        case 7: cprintf(COL_BRIGHT_MAGENTA, "Particular");    break;
    }

    printf("\nDescripcion del problema: %s", pac->descripcionProblema);

    /* 5) Buscar este paciente en el array (uso DNI como clave)*/
    int idx = -1;
    int i;
    for (i = 0; i < cantidadActual && idx == -1; i++){
        if (pArrayPacientes[i].DNI == pac->DNI){
            idx = i;
        }
    }

    if (idx == -1){
        cprintf(COL_BRIGHT_RED, "\n\n[ERROR] -> El paciente de la cola no se encontro en el array/archivo. No se registra alta.\n");
    } else {
        /* 6) Pedir razon de alta y guardar en el array (y en el nodo por prolijidad)*/
        printf("\n\nEscriba su razon de Alta: ");
        scanf(" %49[^\n]", pArrayPacientes[idx].razonDelAlta);

        /* mantener coherente la copia en la cola hasta que lo borremos */
        strcpy(pac->razonDelAlta, pArrayPacientes[idx].razonDelAlta);

        /* 7) Guardar array completo en el archivo (incluye el alta recien puesta)*/
        guardarPacientesEnArchivo(pArrayPacientes, cantidadActual);
    }

    /* 8) Desencolar el nodo de la cola */
    if (pPacientes->principio == pPacientes->final){
        /* era el unico*/
        pPacientes->principio = NULL;
        pPacientes->final     = NULL;
    } else {
        pPacientes->principio = pacienteADarDeAlta->siguientePaciente;
    }

    printf("\n\n\tPaciente dado de alta: %s\n", pac->nombrePaciente);


    free(pacienteADarDeAlta);

    /* 9) Recalcular cuantos siguen sin alta*/
    int sinAlta = 0;
    for (i = 0; i < cantidadActual; i++){
        if (strcmp(pArrayPacientes[i].razonDelAlta, "SIN ALTA") == 0){
            sinAlta++;
        }
    }
    cantidadPacientesSinAlta = sinAlta;

    return sinAlta;   /* NUEVA cantidad de pacientes sin alta */
}


int main(void) {
    clearScreen(); /*Borra el cmd*/
    
    cargarDatosBase(); /*Animacion de carga mas carga/creacion de archivos*/

    menu(); /*Menu principal*/
    
    /*No coloco el return 0;
    Porque el programa esta funcionando con exit(EXIT_SUCCESS)
    que cuando se elige sale del programa*/
}