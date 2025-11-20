#ifndef BINARIOMEDICOS_H
#define BINARIOMEDICOS_H

#include "includesBasicos.h"

#define PATH_ArchMed "medicos.dat"

FILE *archMed;

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

void finalizarGrabadoArchivo(void){
    fclose(archMed);
    printf("\nFin del grabado del medico\nCerrando archivo...\n");
}

void grabarArchivoMedico(void){
    tMedico inputMedico;

    clearScreen();
    puts("Usted ingreso al menu de Medicos\n");
    puts("Ingrese los datos a grabar");

    printf("\nDNI del medico: ");
    scanf(" %d", &inputMedico.DNI);

    printf("\nMatricula del medico: ");
    scanf(" %d", &inputMedico.matricula);

    printf("\nNumero de empleado: ");
    scanf(" %d", &inputMedico.nroEmpleado);

    printf("\nNumero de telefono: ");
    scanf(" %d", &inputMedico.nroTelefono);

    // fechaNacimiento es char[] en tMedico
    printf("\nFecha de Nacimiento (formato AAAAMMDD): ");
    scanf(" %9s", inputMedico.fechaNacimiento); // ajusta el 9 al tamanio-1 real

    // sexo puede ser char o char[2]; aca asumo char
    printf("\nSexo del Medico (M/F): ");
    scanf(" %c", &inputMedico.sexo);

    // Domicilio con espacios
    printf("\nDomicilio: ");
    scanf(" %59[^\n]", inputMedico.domicilio);  // ajusta 59 al tamanio-1

    // Correo (normalmente sin espacios)
    printf("\nCorreo Electronico: ");
    scanf(" %59s", inputMedico.e_mail);         // ajusta tamanio

    // Nombre y Apellido con espacios
    printf("\nNombre y Apellido: ");
    scanf(" %59[^\n]", inputMedico.nombreApellido); // ajusta tamanio

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

void grabarMedico(void){
    iniciarGrabadoArchivo();
    grabarArchivo();
    finalizarGrabadoArchivo();
}

// Carga todos los medicos del binario en un array y devuelve cuantos cargo
int cargarMedicosEnArray(tMedico arrayMed[], int maxMedicos){
    archMed = fopen(PATH_ArchMed, "rb");
    if (archMed == NULL) {
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Archivo de medicos abierto en modo lectura.(Para cargar en ARRAY)\n");
    }

    int i = 0;
    while (i < maxMedicos &&
           fread(&arrayMed[i], sizeof(tMedico), 1, archMed) == 1) {
        i++;
    }

    puts("Todos los medicos agregados al array con exito!");
    printf("Total de medicos agregados al array: %d\n", i);

    fclose(archMed);
    return i;
}



// Guarda TODO el array en el archivo binario (sobrescribe)
void guardarMedicosEnArchivo(tMedico medicos[], int cantidad) {
    FILE *f = fopen(PATH_ArchMed, "wb");
    if (f == NULL) {
        printf("Error al abrir medicos.dat para escritura.\n");
        exit(EXIT_FAILURE);
    }

    if (cantidad > 0) {
        size_t escritos = fwrite(medicos, sizeof(tMedico), cantidad, f);
        if (escritos != (size_t)cantidad) {
            printf("Error al escribir medicos.dat\n");
        }
    }

    fclose(f);
}

// Muestra lista y permite borrar por DNI o nombre.
// Devuelve la NUEVA cantidad de medicos.
int mostrarYBorrarMedico(tMedico medicos[], int cantidad) {
    int opcion;
    int idx;
    int i;
    int dniBuscado;
    tString nombreBuscado;
    char confirma;

    if (cantidad == 0) {
        printf("No hay medicos cargados.\n");
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
    printf("\n�Como queres borrar?\n");
    printf("[1] Por DNI\n");
    printf("[2] Por Nombre\n");
    printf("Opcion: ");
    scanf(" %d", &opcion);

    idx = -1;  //posici�n del m�dico a borrar

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

    printf("�Confirmar borrado? (s/n): ");
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
    return cantidad;
}

#endif
