#ifndef BASICOS_H
#define BASICOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define CABEZA_PROGRAMA "- o - o - o - o - o - o - o - o - o - o - o - o - o -\nInicio del Programa\n- o - o - o - o - o - o - o - o - o - o - o - o - o -\n"

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
}tMedico;

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
}tPaciente;

void head(){printf("%s\n", CABEZA_PROGRAMA);}


/*Funcion que sirve para borrar el cmd*/
void clearScreen(){

    char *t = getenv("TERM");
    system((t && strcmp(t, "dumb")) ? "clear" : "cls");

   /*printf("\nClear screen\n");*/
}

/*Funcion que sirve para esperar enter y asi volver al menu correspondiente*/
void esperarEnter(int destino) {
    char buffer[32];

    printf("\n\nPresione ENTER para volver al menú... ");
    /* Da igual si escribe "5" o cualquier cosa, se descarta igual */
    if (!fgets(buffer, sizeof buffer, stdin)) {
        return;     // por si hay EOF/errores
    }

    switch (destino) {
        case 1:
            menu();               // menú principal
            break;
        case 2:
            switchMenuMedicos();  // menú médicos
            break;
        default:
            menu();               // por defecto, menú principal
            break;
    }
}

/* Variables MEDICOS */


FILE *archMed;
#define MAXMEDICOS 100
tMedico arrayDeMedicos[MAXMEDICOS];
int cantidadDeMedicos;

/*Variables PACIENTES */

/*Variables globales para el corte de control */
int cantidadTotalDePacientes, cantidadDePacientesAtencionInmediata, cantidaDePacientesUrgenAlta, cantidadDePacientesMedia, cantidadDePacientesBaja, cantidadDePacientesNoUrgente;
int cantPacSancor, cantPacIOFA, cantPacOSDE, cantPacIOSCOR, cantPacPAMI, cantPacOSECAC, cantPacSwissMedical, cantPacParticular;
int cantPacSinAlta, cantPacDeAlta;
tPaciente paciente, pacienteAnt;
int totalObraSocial;

#define PATH_ArchPacientes "pacientes.dat"

typedef struct nodo{
    tPaciente paciente;
    struct nodo* siguientePaciente;
}tNodoPaciente;

typedef struct{
    tNodoPaciente* principio;
    tNodoPaciente* final;
}tColaPacientes;

FILE * archPacientes;
#define MAXPACIENTES 100
tPaciente arrayPacientes[MAXPACIENTES];

/* total de registros en el archivo (todos, con alta y sin alta) */
int cantidadDePacientesTotalGral;

/* cantidad de pacientes que siguen sin alta (razonDelAlta == "SIN ALTA") */
int cantidadPacientesSinAlta;

tColaPacientes colaPacientes;

#endif
