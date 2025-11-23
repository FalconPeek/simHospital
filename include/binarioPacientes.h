#ifndef BINARIOPACIENTES_H
#define BINARIOPACIENTES_H
#include "includesBasicos.h"

#define PATH_ArchPacientes "pacientes.dat"




//////////////////////////////////////////////////////////////////////////
//Grabar archivos pacientes
//////////////////////////////////////////////////////////////////////////

void iniciarGrabadoPacientes(){
    archPacientes = fopen(PATH_ArchPacientes, "ab");

    if(archPacientes == NULL){
        cprintf(COL_BRIGHT_RED, "[ERROR] -> No se puede abrir pacientes.dat\n");
        menu();
    } else {
        printf("Archivo pacientes.dat abierto correctamente en modo append binario");
    }
}

void grabarArchivoPaciente(){
    tPaciente inputPaciente;

    clearScreen();
    
    puts("Usted ingreso a la opcion para Aniadir un paciente!");
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
    printf("\n[7] -> O-\n");
    printf("\nElegir tipo de sangre: ");
    scanf("%d", &inputPaciente.tipoDeSangre);

    printf("\nObra social del paciente: (OPCIONES)");
    printf("\n[0] -> Sancor Salud");
    printf("\n[1] -> IOFA");
    printf("\n[2] -> OSDE");
    printf("\n[3] -> IOSCOR");
    printf("\n[4] -> PAMI");
    printf("\n[5] -> OSECAC");
    printf("\n[6] -> Swiss Medical");
    printf("\n[7] -> Particular\n");
    printf("\nElegir obra social: ");
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
    printf("\n[5] -> No urgente\n");
    printf("\nOpcion a elegir: ");
    scanf("%d", &inputPaciente.urgencia);
    

    /*No se agrega la urgencia porque ahora pasa a la
    fase donde el medico debe evaluar la situacion y
    darle un tipo de urgencia.
    
    Pasamos directamente a grabar el archivo binario*/

    strcpy(inputPaciente.razonDelAlta, "NOALTA"); //Inicializamos con la Flag NOALTA para saber que a este paciente aun no se le dio el alta

    fwrite(&inputPaciente, sizeof(tPaciente), 1, archPacientes);
    printf("\n\nPaciente %s agregado al archivo para revision", inputPaciente.nombrePaciente);
}

void finalizarGrabadoPaciente(){
    fclose(archPacientes);
    printf("\n\nYa se cerro el archivo... \n\nvolviendo al menu principal... (ESPERANDO 10 SEGUNDOS)");
    Sleep(10000);
}

void grabarPaciente(){
    iniciarGrabadoPacientes();
    grabarArchivoPaciente();
    finalizarGrabadoPaciente();
}



//Variables globales para el corte de control
int cantidadTotalDePacientes, cantidadDePacientesAtencionInmediata, cantidaDePacientesUrgenAlta, cantidadDePacientesMedia, cantidadDePacientesBaja, cantidadDePacientesNoUrgente;
int cantPacSancor, cantPacIOFA, cantPacOSDE, cantPacIOSCOR, cantPacPAMI, cantPacOSECAC, cantPacSwissMedical, cantPacParticular;
int cantPacSinAlta, cantPacDeAlta;
tPaciente paciente, pacienteAnt;
int totalObraSocial;



void iniciarCortePacientes(){
    clearScreen();
    archPacientes = fopen(PATH_ArchPacientes, "rb");



    if(archPacientes == NULL){
        printf("\nEl programa fallo al abrir el archivo de los pacientes.dat\nVolviendo al menu principal...");
        menu();
    } else {
        fread(&paciente, sizeof(tPaciente), 1, archPacientes);
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
    printf("\t\t\t*** REPORTE DE PACIENTES ***\n");
    printf("\nNombre y Apellido\tEstado Actual\t\tUrgencia\t\tContacto De Emergencia\tDNI\tObra Social\n");
}
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
            switch(strcmp(paciente.razonDelAlta, "NOALTA") == 0){
                case 1:
                    cantPacSinAlta++;
                    strcpy(estadoActualDelPaciente, "En espera de alta");
                break;
                default:
                    cantPacDeAlta++;
                    strcpy(estadoActualDelPaciente, "Dado de Alta");
                break;
            }
            printf("%s\t\t%s\t%s\t%d\t%d\t%s\n", paciente.nombrePaciente, estadoActualDelPaciente, Urgencia, paciente.contactoEmergencia, paciente.DNI, ObraSocial);
            fread(&paciente, sizeof(tPaciente), 1, archPacientes);
        }
        pacienteAnt = paciente;
    }
}

void finalizarCortePacientes(){
    printf("\n-------------------------------------------------------------------------------------------\n");
    printf("Total de pacientes: %d\n", cantidadTotalDePacientes);
    printf("Cantidad de pacientes particulares: %d\n", cantPacParticular);
    totalObraSocial += cantPacSancor + cantPacIOFA + cantPacOSDE + cantPacIOSCOR + cantPacPAMI + cantPacOSECAC + cantPacSwissMedical;
    float porcentajeSinObraSocial = (cantPacParticular * 100) / cantidadTotalDePacientes;
    printf("Porcentaje sin obra social: %.2f\n", porcentajeSinObraSocial);
    printf("Cantidad de pacientes con obra social: %d\n", totalObraSocial);
    printf("Cantidad de pacientes hospitalizados: %d\n", cantPacSinAlta);
    printf("Cantidad de pacientes dados de Alta: %d\n", cantPacDeAlta);
    fclose(archPacientes);
    int scan;
    printf("\n\n\t\tPrecione 1 luego Enter para volver al menu...\t");
    scanf("%d", &scan); if(scan == 1) {menu();}
}

void reporteDePacietes(){
    iniciarCortePacientes();
    procesoCortePacientes();
    finalizarCortePacientes();
}



int cargarPacientesEnArray(tPaciente arrayPaci[], int maxPacientes, bool mostrar){
    int i = 0;
    if(mostrar){
        archPacientes = fopen(PATH_ArchPacientes, "rb");
        if (archPacientes == NULL) {
            printf("\n[ERROR] -> Error al abrir el archivo\n");
            printf("\nCreando archivo... Volviendo al menu principal\n\n");
            archPacientes = fopen(PATH_ArchPacientes, "wb");
            Sleep(1000);
            if(archPacientes != NULL){
                printf("\n\nArchivo creado con exito, nombre archivo: %s\n\n", PATH_ArchPacientes);
            }
            Sleep(3000);
            return 0;
        } else {
            printf("\nArchivo de pacientes abierto en modo lectura. (Para cargar en ARRAY)\n");
        }

        while (i < maxPacientes &&
               fread(&arrayPaci[i], sizeof(tPaciente), 1, archPacientes) == 1) {
            i++;
        }
        printf("\nTotal de pacientes agregados al array: %d\n", i);

        fclose(archPacientes);
        Sleep(1500);
        
    } else {
        // *** MODO SILENCIOSO, SIN PRINTS, PARA USO INTERNO ***
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

    // actualizamos contador global del total de registros
    cantidadDePacientesTotalGral = i;
    return i;
}


void mostrarCantidadPacientes(tPaciente array[], int cantidad){
    int i;
    if (cantidad == 0) {
        printf("\nNo hay pacientes cargados.\n");
        Sleep(1500);
        menu();
        return; // importante para NO seguir ejecutando
    }
    printf("\n===== LISTA DE PACIENTES =====\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s  |  Estado: %s\n",
               i + 1,
               array[i].DNI,
               array[i].nombrePaciente,
               array[i].razonDelAlta);  // <- antes usabas array[1]
    }
    printf("============================\n");
    int scan;
    printf("\n\n\t\tPrecione 1 luego Enter para volver a seleccionar una opcion\t");
    scanf("%d", &scan);
    if (scan == 1) {
        menu();
    }
}

#endif