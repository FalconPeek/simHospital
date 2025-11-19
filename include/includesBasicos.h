#ifndef BASICOS_H
#define BASICOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
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
    Atencion Inmediata [0]
    Urgencia Alta [1]
    Urgencia Media [2]
    Urgencia Baja [3]
    No Urgente [4]
    */
    tString nombrePaciente, descripcionProblema, alergias;
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
    */
}tAtencion;

void head(){printf("%s\n", CABEZA_PROGRAMA);}

void clearScreen(void){
    char *t = getenv("TERM");
    system((t && strcmp(t, "dumb")) ? "clear" : "cls");
}

#endif