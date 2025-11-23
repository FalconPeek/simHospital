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
    int DNI, matricula, nroEmpleado, nroTelefono;
    char fechaNacimiento[9]; //(AAAAMMDD) 8 caracteres + "\0"
	char sexo; 
    tString domicilio, e_mail, nombreApellido;
    int estadoLaboral; // [1]-> Tiempo Completo // [2]-> Medio Tiempo
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

void clearScreen(void){

    char *t = getenv("TERM");
    system((t && strcmp(t, "dumb")) ? "clear" : "cls");

   //printf("\nClear screen\n");
}

//Variables MEDICOS
FILE *archMed;
#define MAXMEDICOS 100
tMedico arrayDeMedicos[MAXMEDICOS];
int cantidadDeMedicos;

//Variables PACIENTES

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

// total de registros en el archivo (todos, con alta y sin alta)
int cantidadDePacientesTotalGral;

// cantidad de pacientes que siguen sin alta (razonDelAlta == "NOALTA")
int cantidadPacientesSinAlta;

tColaPacientes colaPacientes;

#endif
