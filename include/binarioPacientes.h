#ifndef BINARIOPACIENTES_H
#define BINARIOPACIENTES_H
#include "includesBasicos.h"

#define ARCHIVO_PACIENTES "pacientes.dat"

//Variables Globales
FILE * archPacientes;
#define MAXPACIENTES 100
tPaciente arrayDePacientes[MAXPACIENTES];
int cantidadDePacientes;

//////////////////////////////////////////////////////////////////////////
//Grabar archivos pacientes
//////////////////////////////////////////////////////////////////////////

void iniciarGrabadoPacientes(){
    archPacientes = fopen(ARCHIVO_PACIENTES, "ab");

    if(archPacientes == NULL){
        printf("Error al abrir pacientes.dat\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Archivo pacientes.dat abierto correctamente en modo append binario");
    }
}

void grabarArchivoPaciente(){
    tPaciente inputPaciente;

    clearScreen();
    
    puts("Usted ingreso a la opcion para Añadir un paciente!");
    puts("A continuacion... Ingrese los datos de este:");
    
    printf("\nNombre del paciente: ");
    scanf(" %49[^\n]", inputPaciente.nombrePaciente);

    printf("\nDescripcion del problema: ");
    scanf(" %49[^\n]", inputPaciente.descripcionProblema);

    printf("\nEl paciente tiene alguna alergia? Respuesta: ");
    scanf(" %49[^\n]", inputPaciente.alergias);

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
    scanf("%d", &inputPaciente.tipoDeSangre);

    printf("\nObra social del paciente: (OPCIONES)");
    printf("\n[0] -> Sancor Salud");
    printf("\n[1] -> IOFA");
    printf("\n[2] -> OSDE");
    printf("\n[3] -> IOSCOR");
    printf("\n[4] -> PAMI");
    printf("\n[5] -> OSECAC");
    printf("\n[6] -> Swiss Medical");
    printf("\n[7] -> Particular");
    scanf("%d", &inputPaciente.obraSocial);

    printf("\nAlgun contacto de emergencia(NRO TELEFONO): ");
    scanf("%d", &inputPaciente.contactoEmergencia);

    printf("\nDNI del paciente: ");
    scanf("%d", &inputPaciente.DNI);

    printf("\nUrgencia de atencion: (OPCIONES)");
    printf("\n[1] -> Atencion Inmediata");
    printf("\n[2] -> Urgencia Alta");
    printf("\n[3] -> Urgencia Media");
    printf("\n[4] -> Urgencia Baja");
    printf("\n[5] -> No urgente");
    scanf("%d", &inputPaciente.urgencia);
    

    /*No se agrega la urgencia porque ahora pasa a la
    fase donde el medico debe evaluar la situacion y
    darle un tipo de urgencia.
    
    Pasamos directamente a grabar el archivo binario*/

    fwrite(&inputPaciente, sizeof(tPaciente), 1, archPacientes);
    printf("\nPaciente %s agregado al archivo para revision", inputPaciente.nombrePaciente);
}

void finalizarGrabadoPaciente(){
    fclose(archPacientes);
    clearScreen();
    printf("Ya se cerro el archivo... volviendo al menu principal");
    Sleep(3);
}

void grabarPaciente(){
    iniciarGrabadoPacientes();
    grabarArchivoPaciente();
    finalizarGrabadoPaciente();
}

/* Carga todos los pacientes del binario en un array y devuelve cuantos cargo */
int cargarPacientesEnArray(tPaciente arrayPac[], int maxPacientes){
    int i = 0;

    archPacientes = fopen(ARCHIVO_PACIENTES, "rb");
    if (archPacientes == NULL) {
        printf("Error al abrir pacientes.dat\n");
        exit(EXIT_FAILURE);
    }

    while (i < maxPacientes &&
           fread(&arrayPac[i], sizeof(tPaciente), 1, archPacientes) == 1) {
        i++;
    }

    fclose(archPacientes);
    printf("Total de pacientes cargados en memoria: %d\n", i);
    Sleep(3);
    clearScreen();
    return i;
}

/* Guarda TODO el array de pacientes en el archivo binario (sobrescribe) */
void guardarPacientesEnArchivo(tPaciente pacientes[], int cantidad) {
    FILE *f = fopen(ARCHIVO_PACIENTES, "wb");
    if (f == NULL) {
        printf("No se pudo abrir pacientes.dat para escritura\n");
        exit(EXIT_FAILURE);
    }

    if (cantidad > 0) {
        fwrite(pacientes, sizeof(tPaciente), cantidad, f);
    }

    fclose(f);
}

// Muestra lista y permite borrar por DNI o nombre. Devuelve la NUEVA cantidad.
int mostrarYBorrarPaciente(tPaciente pacientes[], int cantidad) {
    int i;
    int opcion;
    int idx = -1;
    int dniBuscado;
    tString nombreBuscado;
    char confirma;

    if (cantidad == 0) {
        printf("No hay pacientes cargados.\n");
        return 0;
    }

    printf("\n===== LISTA DE PACIENTES =====\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s\n",
               i + 1,
               pacientes[i].DNI,
               pacientes[i].nombrePaciente);
    }
    printf("==============================\n");

    printf("\n�Como queres borrar?\n");
    printf("[1] Por DNI\n");
    printf("[2] Por Nombre\n");
    printf("Opcion: ");
    scanf(" %d", &opcion);

    if (opcion == 1) {
        printf("\nIngrese el DNI del paciente a borrar: ");
        scanf(" %d", &dniBuscado);

        for (i = 0; i < cantidad; i++) {
            if (pacientes[i].DNI == dniBuscado) {
                idx = i;
                break;
            }
        }
    }
    else if (opcion == 2) {
        printf("\nIngrese el nombre COMPLETO del paciente a borrar: ");
        scanf(" %49[^\n]", nombreBuscado);

        for (i = 0; i < cantidad; i++) {
            if (strcmp(pacientes[i].nombrePaciente, nombreBuscado) == 0) {
                idx = i;
                break;
            }
        }
    }
    else {
        printf("Opcion invalida.\n");
        return cantidad;
    }

    if (idx == -1) {
        printf("No se encontro el paciente.\n");
        return cantidad;
    }

    printf("\nVas a borrar al siguiente paciente:\n");
    printf("DNI: %d\nNombre: %s\n",
           pacientes[idx].DNI,
           pacientes[idx].nombrePaciente);

    printf("�Confirmar borrado? (s/n): ");
    scanf(" %c", &confirma);

    if (confirma != 's' && confirma != 'S') {
        printf("Borrado cancelado.\n");
        return cantidad;
    }

    for (i = idx; i < cantidad - 1; i++) {
        pacientes[i] = pacientes[i + 1];
    }
    cantidad--;

    guardarPacientesEnArchivo(pacientes, cantidad);

    printf("Paciente borrado y archivo actualizado correctamente.\n");
    printf("\nVolviendo al menu principal...\n");
    Sleep(2);
    clearScreen();
    return cantidad;
}
#endif
