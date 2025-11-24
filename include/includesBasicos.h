#ifndef BASICOS_H
#define BASICOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


#include "colores.h"

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
    int DNI; 
    double contactoEmergencia; 
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
    while ((c = getchar()) != '\n' && c != EOF);

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
tPaciente paciente, pacienteAnt, mostrarPaciente;

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

#endif /* BASICOS_H */