#ifndef BINARIOPACIENTES_H
#define BINARIOPACIENTES_H

#include "includesBasicos.h"
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
    scanf("%lf", &inputPaciente.contactoEmergencia);

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
    cprintf(COL_WHITE, "\n\nPaciente %s agregado al archivo para revision", inputPaciente.nombrePaciente);
    mostrarPaciente = inputPaciente;
}

/*Funcion que cierra el archivo una vez grabado*/
void finalizarGrabadoPaciente(){

    cprintf(COL_BRIGHT_MAGENTA, "\n\nFinalizando carga de paciente...\n");
    Sleep(1000);
    printf("\n[Tipo atencion] -> ");
    switch (mostrarPaciente.urgencia){
        case 1: cprintf(COL_RED,    "ATENCION INMEDIATA"); break;
        case 2: cprintf(COL_YELLOW, "URGENCIA ALTA");      break;
        case 3: cprintf(COL_MAGENTA,"URGENCIA MEDIA");     break;
        case 4: cprintf(COL_CYAN,   "URGENCIA BAJA");      break;
        case 5: cprintf(COL_GREEN,  "NO URGENTE");         break;
    }

    cprintf(COL_WHITE, "\nNombre del Paciente: "); cprintf(COL_BRIGHT_YELLOW, "%s", mostrarPaciente.nombrePaciente);
    cprintf(COL_WHITE, "\nAlergias: ");            cprintf(COL_BRIGHT_YELLOW, "%s", mostrarPaciente.alergias);

    cprintf(COL_WHITE, "\nTipo de sangre: ");
    switch (mostrarPaciente.tipoDeSangre){
        case 0: cprintf(COL_BRIGHT_YELLOW, "A+");  break;
        case 1: cprintf(COL_BRIGHT_YELLOW, "A-");  break;
        case 2: cprintf(COL_BRIGHT_YELLOW, "B+");  break;
        case 3: cprintf(COL_BRIGHT_YELLOW, "B-");  break;
        case 4: cprintf(COL_BRIGHT_YELLOW, "AB+"); break;
        case 5: cprintf(COL_BRIGHT_YELLOW, "AB-"); break;
        case 6: cprintf(COL_BRIGHT_YELLOW, "O+");  break;
        case 7: cprintf(COL_BRIGHT_YELLOW, "O-");  break;
    }

    printf("\nContacto Emergencia: "); cprintf(COL_BRIGHT_YELLOW, "%.0lf", mostrarPaciente.contactoEmergencia);
    printf("\nDNI: "); cprintf(COL_BRIGHT_YELLOW, "%d", mostrarPaciente.DNI);
    printf("\nObra Social: ");
    switch (mostrarPaciente.obraSocial){
        case 0: cprintf(COL_BRIGHT_BLUE,    "Sancor Salud");  break;
        case 1: cprintf(COL_BRIGHT_BLUE,    "IOFA");          break;
        case 2: cprintf(COL_BRIGHT_BLUE,    "OSDE");          break;
        case 3: cprintf(COL_BRIGHT_BLUE,    "IOSCOR");        break;
        case 4: cprintf(COL_BRIGHT_BLUE,    "PAMI");          break;
        case 5: cprintf(COL_BRIGHT_BLUE,    "OSECAC");        break;
        case 6: cprintf(COL_BRIGHT_BLUE,    "Swiss Medical"); break;
        case 7: cprintf(COL_BRIGHT_MAGENTA, "Particular");    break;
    }

    printf("\nDescripcion del problema: "); cprintf(COL_BRIGHT_YELLOW, "%s\n" , mostrarPaciente.descripcionProblema);

    fclose(archPacientes);

    /*Hacemos una copia de esperarEnter()
    Solamente para esperar al enter pero sin volver al menu...*/

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
    printf("\n%-30s ", nombre);cprintf(COL_YELLOW, "|"); printf(" %-20s ", estadoAc);cprintf(COL_YELLOW, "|"); printf(" %-20s ", urgencia);cprintf(COL_YELLOW, "|"); printf(" %-30s ", nroEmer);cprintf(COL_YELLOW, "|"); printf(" %-10s ", dni);cprintf(COL_YELLOW, "|"); printf(" %-15s\n", social);
    printf("------------------------------------------------------------------------------------------------------------------------------------------");
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
            printf("\n%-30s ", paciente.nombrePaciente);cprintf(COL_YELLOW, "|"); printf(" %-20s ", estadoActualDelPaciente);cprintf(COL_YELLOW, "|"); 
            switch(paciente.urgencia){
                case 1:
                    cantidadDePacientesAtencionInmediata++;
                    strcpy(Urgencia, "Atencion Inmediata");
                    cprintf(COL_RED, " %-20s ", Urgencia);
                break;
                case 2:
                    cantidaDePacientesUrgenAlta++;
                    strcpy(Urgencia, "Urgencia Alta");
                    cprintf(COL_YELLOW, " %-20s ", Urgencia);
                break;
                case 3:
                    cantidadDePacientesMedia++;
                    strcpy(Urgencia, "Urgencia Media");
                    cprintf(COL_MAGENTA, " %-20s ", Urgencia);
                break;
                case 4:
                    cantidadDePacientesBaja++;
                    strcpy(Urgencia, "Urgencia Baja");
                    cprintf(COL_CYAN, " %-20s ", Urgencia);
                break;
                case 5:
                    cantidadDePacientesNoUrgente++;
                    strcpy(Urgencia, "No urgente");
                    cprintf(COL_GREEN, " %-20s ", Urgencia);
                break;
            }
            /*printf(" %-20s ", Urgencia);*/
            cprintf(COL_YELLOW, "|"); printf(" %-30.0lf ", paciente.contactoEmergencia);cprintf(COL_YELLOW, "|"); printf(" %-10d ", paciente.DNI);cprintf(COL_YELLOW, "|"); printf(" %-15s", ObraSocial);
            fread(&paciente, sizeof(tPaciente), 1, archPacientes);
        }
        pacienteAnt = paciente;
    }
}

/*Funcion que muestra totales luego del corte del archivo de pacientes*/
void finalizarCortePacientes(){
    printf("\n\n------------------------------------------------------------------------------------------------------------------------------------------\n");
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
                cprintf(COL_WHITE, "\n\nArchivo creado con exito, nombre archivo: %s\n\n", PATH_ArchPacientes);
            }
            Sleep(3000);
            return 0;
        } else {
            cprintf(COL_BRIGHT_GREEN, "[EXITO] -> ");printf("Archivo de pacientes abierto en modo lectura.\n");
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
        return;
    }
    clearScreen();
    cprintf(COL_BRIGHT_CYAN, "\n=============== LISTA DE PACIENTES ===============\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %-9d  |  Nombre: %-30s  |  Estado: %-20s\n",
               i + 1,
               array[i].DNI,
               array[i].nombrePaciente,
               array[i].razonDelAlta);
    }
    cprintf(COL_BRIGHT_CYAN, "==================================================\n");
    esperarEnter(1);
}

#endif