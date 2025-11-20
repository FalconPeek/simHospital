#ifndef BINARIOPACIENTES_H
#define BINARIOPACIENTES_H
#include "includesBasicos.h"

#define ARCHIVO_PACIENTES "pacientes.dat"

//Variables Globales
FILE * archPacientes;

//////////////////////////////////////////////////////////////////////////
//Grabar archivos pacientes
//////////////////////////////////////////////////////////////////////////

void iniciarGrabadoPacientes(void){
    archPacientes = fopen(ARCHIVO_PACIENTES, "ab");

    if(archPacientes == NULL){
        printf("Error al abrir pacientes.dat\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Archivo pacientes.dat abierto correctamente en modo append binario");
    }
}

void grabarArchivoPaciente(void){
    tPaciente inputPaciente;

    clearScreen();
    
    puts("Usted ingreso a la opcion para Añadir un paciente!");
    puts("A continuacion... Ingrese los datos de este:");
    
    printf("\nNombre del paciente: ");
    scanf(" %59[^\n]", inputPaciente.nombrePaciente);

    printf("\nDescripcion del problema: ");
    scanf(" %59[^\n]", inputPaciente.descripcionProblema);

    printf("\nEl paciente tiene alguna alergia? Respuesta: ");
    scanf(" %59[^\n]", inputPaciente.alergias);

    printf("\nTipo de sangre del paciente: ");
    printf("\n[0] -> A+");
    printf("\n[1] -> A-");
    printf("\n[2] -> B+");
    printf("\n[3] -> B-");
    printf("\n[4] -> AB+");
    printf("\n[5] -> AB-");
    printf("\n[6] -> O+");
    printf("\n[7] -> O-");
    printf("\n");
    printf("Elegir tipo de sangre: ");
    scanf("%d", inputPaciente.tipoDeSangre);

    printf("\nObra social del paciente: (OPCIONES)");
    printf("\n[0] -> Sancor Salud");
    printf("\n[1] -> IOFA");
    printf("\n[2] -> OSDE");
    printf("\n[3] -> IOSCOR");
    printf("\n[4] -> PAMI");
    printf("\n[5] -> OSECAC");
    printf("\n[6] -> Swiss Medical");
    printf("\n[7] -> Particular");
    scanf("%d", inputPaciente.obraSocial);

    printf("\nAlgun contacto de emergencia(NRO TELEFONO): ");
    scanf("%d", inputPaciente.contactoEmergencia);

    printf("\nDNI del paciente: ");
    scanf("%d", inputPaciente.DNI);

    inputPaciente.urgencia = -1; //Para que se sepa que paciente aun no se le a dado la revision se usa la flag -1

    /*No se agrega la urgencia porque ahora pasa a la
    fase donde el medico debe evaluar la situacion y
    darle un tipo de urgencia.
    
    Pasamos directamente a grabar el archivo binario*/

    fwrite(&inputPaciente, sizeof(tPaciente), 1, archPacientes);
    printf("\nPaciente %s agregado al archivo para revision", inputPaciente.nombrePaciente);
}

void finalizarGrabadoPaciente(void){
    fclose(archPacientes);
    clearScreen();
    printf("Ya se cerro el archivo... volviendo al menu principal");
    sleep(3);
}

void grabarPaciente(void){
    iniciarGrabadoPacientes();
    grabarArchivoPaciente();
    finalizarGrabadoPaciente();
}
#endif