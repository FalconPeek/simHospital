#ifndef BINARIOMEDICOS_H
#define BINARIOMEDICOS_H

#include "includesBasicos.h"

#define PATH_ArchMed "medicos.dat"



//Prototipos de funciones que hacen corto no se porque...
void menu();
void switchMenuMedicos();
int cargarPacientesEnArray(tPaciente arrayPaci[], int maxPacientes, bool mostrar);
void iniciarCola(tColaPacientes* colaPacientes, bool mostrar);
void agregarPacientes(tColaPacientes* colaPacientes, tPaciente* arrayP, int cantidadPacientes, bool mostrar);
bool colaVacia(tColaPacientes colaPacientes);
int diagnosticarDarAlta(tColaPacientes* pPacientes, tPaciente pArrayPacientes[]);

// Abrir archivo en modo append binario
void iniciarGrabadoArchivo(void){
    archMed = fopen(PATH_ArchMed, "ab");
    if (archMed == NULL) {
        printf("Error al abrir medicos.dat\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Archivo abierto en modo append binario\n");
    }
}
//FUNCIONANDO CORRECTAMENTE

void finalizarGrabadoArchivo(void){
    fclose(archMed);
    printf("\nFin del grabado del medico\nCerrando archivo...\n");
    Sleep(2000);
}
//FUNCIONANDO CORRECTAMENTE

void grabarArchivoMedico(void){
    tMedico inputMedico;

    clearScreen();
    puts("Usted ingreso al menu de Medicos\n");
    puts("Ingrese los datos a grabar");

    printf("\nDNI del medico: ");
    scanf(" %d", &inputMedico.DNI);

    srand(inputMedico.DNI);
    printf("\nMatricula del medico: %d", rand());
    Sleep(1000);

    inputMedico.nroEmpleado = cantidadDeMedicos+1;
    printf("\nNumero de empleado: %d", inputMedico.nroEmpleado);
    Sleep(1000);

    printf("\nNumero de telefono: ");
    scanf(" %d", &inputMedico.nroTelefono);

    // fechaNacimiento es char[] en tMedico
    printf("\nFecha de Nacimiento (formato AAAAMMDD): ");
    scanf(" %8s", inputMedico.fechaNacimiento); // ajusta el 9 al tamanio-1 real

    // sexo puede ser char o char[2]; aca asumo char
    printf("\nSexo del Medico (M/F): ");
    scanf(" %c", &inputMedico.sexo);

    // Domicilio con espacios
    printf("\nDomicilio: ");
    scanf(" %49[^\n]", inputMedico.domicilio);  // ajusta 59 al tamanio-1

    // Correo (normalmente sin espacios)
    printf("\nCorreo Electronico: ");
    scanf(" %49s", inputMedico.e_mail);         // ajusta tamanio

    // Nombre y Apellido con espacios
    printf("\nNombre y Apellido: ");
    scanf(" %49[^\n]", inputMedico.nombreApellido); // ajusta tamanio

    printf("\nLista de especialidades: "
           "\n[1] Dermatologia"
           "\n[2] Oftalmologia"
           "\n[3] Cirugia General"
           "\n[4] Cardiologia"
           "\n[5] Endocrinologia"
           "\n[6] Otorrinolaringologia\n");

    printf("\nEspecialidad: ");
    scanf(" %d", &inputMedico.especialidad);

    printf("\n[1] Tiempo Completo - [2] Medio tiempo\nEstado laboral: ");
    scanf(" %d", &inputMedico.estadoLaboral); // o &inputMedico.estadoLaboral si existe

    fwrite(&inputMedico, sizeof(tMedico), 1, archMed);
    printf("\nMedico %s agregado al archivo!\n", inputMedico.nombreApellido);
}
//FUNCIONANDO CORRECTAMENTE

// Carga todos los medicos del binario en un array y devuelve cuantos cargo
int cargarMedicosEnArray(tMedico arrayMed[], int maxMedicos, bool mostrar){
    int i = 0;
    if(mostrar){
        archMed = fopen(PATH_ArchMed, "rb");
        if (archMed == NULL) {
        printf("\n[ERROR] -> Error al abrir el archivo\n");
        printf("\nCreando archivo... Volviendo al menu principal\n\n");
        archMed = fopen(PATH_ArchMed, "wb"); //Esto deberia crear el archivo med
        Sleep(1000);
        if(archMed != NULL){ printf("\n\nArchivo creado con exitos, nombre archivo: %s\n\n", PATH_ArchMed); }
        Sleep(1000);
        } else {
        printf("Archivo de medicos abierto en modo lectura.(Para cargar en ARRAY)\n");
        }

        while (i < maxMedicos &&
           fread(&arrayMed[i], sizeof(tMedico), 1, archMed) == 1) {
            i++;
        }
        printf("\nTotal de medicos agregados al array: %d\n", i);

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
// TERMINADA Y FUNCIONANDO


// Guarda TODO el array en el archivo binario (sobrescribe)
void guardarMedicosEnArchivo(tMedico medicos[], int cantidad) {
    FILE *f = fopen(PATH_ArchMed, "wb");
    if (f == NULL) {
        printf("Error al abrir medicos.dat para escritura.\n");
        Sleep(1000);
        menu();
    }

    if (cantidad > 0) {
        size_t escritos = fwrite(medicos, sizeof(tMedico), cantidad, f);
        if (escritos != (size_t)cantidad) {
            printf("Error al escribir medicos.dat\n");
        }
    }

    fclose(f);
}
// TERMINADA Y FUNCIONANDO


void mostrarCantidadMedicos(tMedico medicos[], int cantidad){
    int i;
    if (cantidad == 0) {
        printf("\nNo hay medicos cargados.\n");
        Sleep(1500);
        switchMenuMedicos();
    }

    printf("\n===== LISTA DE MEDICOS =====\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s\n",
               i + 1,
               medicos[i].DNI,
               medicos[i].nombreApellido);
    }
    printf("============================\n");
    int scan;
    printf("\n\n\t\tPrecione 1 luego Enter para volver a seleccionar una opcion\t");
    scanf("%d", &scan); if(scan == 1) {switchMenuMedicos();}
}
// TERMINADA Y FUNCIONANDO


// Muestra lista y permite borrar por DNI o nombre.
// Devuelve la NUEVA cantidad de medicos.
int mostrarYBorrarMedico(tMedico medicos[], int cantidad) {
    clearScreen();
    int opcion;
    int idx;
    int i;
    int dniBuscado;
    tString nombreBuscado;
    char confirma;

    if (cantidad == 0) {
        cprintf(COL_YELLOW, "[WARNING] -> No hay medicos cargados.\n");
        Sleep(2500);
        cprintf(COL_BLUE, "Volviendo al menu medicos...");
        return 0;
    }

    printf("\n===== LISTA DE MEDICOS =====\n");
    for (i = 0; i < cantidad; i++) {
        printf("%2d) DNI: %d  |  Nombre: %s\n",
               i + 1,
               medicos[i].DNI,
               medicos[i].nombreApellido);
    }
    printf("============================\n");

    opcion = 0;
    printf("\n¿Como desea borrar?\n");
    printf("[1] Por DNI\n");
    printf("[2] Por Nombre\n");
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
        printf("\nIngrese el nombre COMPLETO del medico a borrar: ");
        scanf(" %49[^\n]", nombreBuscado);

        for (i = 0; i < cantidad; i++) {
            if (strcmp(medicos[i].nombreApellido, nombreBuscado) == 0) {
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
        printf("No se encontro el medico.\n");
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
        printf("Borrado cancelado.\n");
        return cantidad;
    }

    //Correr el array una posicion hacia atras desde idx
    for (i = idx; i < cantidad - 1; i++) {
        medicos[i] = medicos[i + 1];
    }
    cantidad--;

    // Actualizar archivo binario con el nuevo array
    guardarMedicosEnArchivo(medicos, cantidad);

    printf("Medico borrado y archivo actualizado correctamente.\n");
    printf("\nVolviendo al menu medicos!");
    Sleep(2000);
    clearScreen();
    return cantidad;
}
// TERMINADA Y FUNCIONANDO


void grabarMedico(void){
    iniciarGrabadoArchivo();
    grabarArchivoMedico();
    finalizarGrabadoArchivo();
    cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS, false);
}
// TERMINADA Y FUNCIONANDO

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cantidadActualMedicos; //Se usa en linea 286

void switchMenuMedicos(){
    clearScreen();
        /*Escribimos las opciones en pantalla y luego el switch*/
        cprintf(COL_BRIGHT_GREEN, "\t\t*** Menu Medicos ***\n\n");
        //printf("[0] Dar urgencia a pacientes aun no atendidos"); Esto agrega bastante complejidad, vemos si hacemos esta opcion o no una vez terminado todo
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
                cprintf(COL_BRIGHT_RED, "\n[ERROR] -> No hay medicos cargados\n");
                printf("\n\nIngrese 1 y ENTER para volver al menu de medicos: ");
                int i;
                scanf("%d", &i);
                switchMenuMedicos();
            } else {
            /* 
             * 1) Sincronizamos ARRAY de pacientes con el archivo
             * 2) Reconstruimos la cola solo con pacientes NOALTA
             * 3) Atendemos al primero y damos de alta
             * 4) Mostramos cuantos quedan sin alta
             */
            // 1) Cargar pacientes desde el archivo al array global
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, false);
            if (cantidadDePacientesTotalGral == 0) {
                cprintf(COL_BRIGHT_MAGENTA, "\n\nNo hay pacientes cargados en el sistema.\n");
                Sleep(2000);
                switchMenuMedicos();
                break;
            }
            // 2) Reconstruir la cola con los pacientes que siguen con NOALTA
            iniciarCola(&colaPacientes, false);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, false);
            if (colaVacia(colaPacientes)) {
                cprintf(COL_RED, "\n\nNo hay pacientes en espera para dar de alta (ninguno con NOALTA).\n");
                Sleep(2500);
                switchMenuMedicos();
                break;
            }
            // 3) Atender y dar de alta al primero de la cola
            int restantesSinAlta = diagnosticarDarAlta(&colaPacientes, arrayPacientes);
            // 4) Feedback operativo
            if (restantesSinAlta > 0) {
                cprintf(COL_BRIGHT_GREEN, "\n\nQuedan %d pacientes sin dar de alta.\n", restantesSinAlta);
            } else {
                cprintf(COL_BRIGHT_YELLOW, "\n\nNo quedan pacientes pendientes de alta.\n");
            }
            printf("\n\nIngrese 1 y ENTER para volver al menu de medicos: ");
            int i;
            scanf("%d", &i);
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
            puts("Volviendo al menu principal...");
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

    printf("\nAyuda rapida... la password es: lindstrom\n\n");
    tString password = "lindstrom";
    tString passRTA;
    printf("\nUsted eligio el apartado medicos... \nIngrese la contrasenia: ");
    scanf("%15s", passRTA);

    if(strcmp(password, passRTA) == 0){
        clearScreen();
        puts("\nContraseña correcta! Abriendo el menu de medicos...\n");
        switchMenuMedicos();
    } else {
        clearScreen();
        if(intentos < 3){
            printf("\nContrasenia incorrecta! Le quedan %d intentos", 3 - intentos);
            printf("\nEspere 4 segundos para volver a intentar...");
            Sleep(4000); // usar ms
            menuMedicos(intentos+1);
        } else {
            clearScreen();
            puts("\nUsted quedo sin intentos, saliendo al menu principal");
            menu();
        }
    }
}
//FUNCIONANDO CORRECTAMENTE
#endif
