#ifndef BINARIOPACIENTES_H
#define BINARIOPACIENTES_H
#include "includesBasicos.h"






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
    
    cprintf(COL_BRIGHT_WHITE, "Usted ingreso a la opcion para Aniadir un paciente!\n");
    cprintf(COL_MAGENTA, "A continuacion... Ingrese los datos de este:\n");
    
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
    clearScreen();
    archPacientes = fopen(PATH_ArchPacientes, "rb");



    if(archPacientes == NULL){
        cprintf(COL_BRIGHT_RED, "[ERROR] -> "); printf("\nEl programa fallo al abrir el archivo de los pacientes.dat\nVolviendo al menu principal...");
        menu();
    } else {
        if(fread(&paciente, sizeof(tPaciente), 1, archPacientes) == 0){
            cprintf(COL_BRIGHT_MAGENTA, "[WARNING] ->"); printf("No hay ningun paciente cargado\n"); cprintf(COL_BRIGHT_YELLOW, "VOLVIENDO AL MENU...");
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
    cprintf(COL_BRIGHT_WHITE, "\t\t\t\t\t*** REPORTE DE PACIENTES ***\n");
    tString nombre, estadoAc, urgencia, nroEmer, dni, social;
    strcpy(nombre, "Nombre Completo");
    strcpy(estadoAc, "Estado Actual");
    strcpy(urgencia, "Urgencia");
    strcpy(nroEmer, "Contacto De Emergencia");
    strcpy(dni, "Documento");
    strcpy(social, "Obra Social");
    printf("\n%-30s %-15s %-15s %-30s %-10s %-15s\n", nombre, estadoAc, urgencia, nroEmer, dni, social);
    printf("------------------------------ --------------- --------------- ------------------------------ ---------- ---------------\n");
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
            printf("%-30s %-15s %-15s %-30d %-10d %-15s\n", paciente.nombrePaciente, estadoActualDelPaciente, Urgencia, paciente.contactoEmergencia, paciente.DNI, ObraSocial);
            fread(&paciente, sizeof(tPaciente), 1, archPacientes);
        }
        pacienteAnt = paciente;
    }
}

/*Funcion que muestra totales luego del corte del archivo de pacientes*/
void finalizarCortePacientes(){
    printf("\n--------------------------------------------------------------------------------------------------------------\n");
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
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("\nNo hay pacientes cargados.\n");
        Sleep(1500);
        menu();
        return; /* importante para NO seguir ejecutando */
    }
    cprintf(COL_BRIGHT_WHITE, "\n=============== LISTA DE PACIENTES ===============\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %-9d  |  Nombre: %-30s  |  Estado: %-20s\n",
               i + 1,
               array[i].DNI,
               array[i].nombrePaciente,
               array[i].razonDelAlta);  /* <- antes usabas array[1] */
    }
    cprintf(COL_BRIGHT_WHITE, "========================================================================================================\n");
    esperarEnter(1);
}

#endif