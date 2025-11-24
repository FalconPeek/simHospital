#ifndef BINARIOMEDICOS_H
#define BINARIOMEDICOS_H

#include "includesBasicos.h"
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
        cprintf(COL_BRIGHT_GREEN, "\n\n[EXITO] -> "); printf("Archivo de medicos abierto en modo lectura.\n");
        }

        while (i < maxMedicos &&
           fread(&arrayMed[i], sizeof(tMedico), 1, archMed) == 1) {
            i++;
        }
        cprintf(COL_WHITE, "\nTotal de medicos agregados al array: %d\n", i);

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
    clearScreen();
    cprintf(COL_BRIGHT_BLUE, "\n=========== LISTA DE MEDICOS ===========\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %-30d  |  Nombre: %s\n",
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
        Sleep(3500);
        return cantidad;
    }

    if (idx == -1) {
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("No se encontro el medico.\n");
        Sleep(3500);
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
        cprintf(COL_RED, "[NEGADO] -> "); printf("Borrado cancelado.\n");
        Sleep(3000);
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
#endif