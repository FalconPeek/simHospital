#ifndef MENU_H
#define MENU_H

#include "includesBasicos.h"
#include "colores.h"

void switchMenu(){
    int opcion;
    scanf("%d", &opcion);
    switch (opcion){
        case 1:
            grabarPaciente();
            // recargo array desde archivo para incluir el nuevo paciente
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, false);
            // si la cola ya está inicializada, podrías rearmarla
            iniciarCola(&colaPacientes, false);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, false);
            menu();
            break;
        case 2:
            visualizarCola(colaPacientes);
        break;
        case 3:
            mostrarCantidadPacientes(arrayPacientes, cantidadDePacientesTotalGral);
        break;
        case 4:
            reporteDePacietes();
        break;
        case 5:
            menuMedicos(0);
        break;
        case 6:
            cprintf(COL_BRIGHT_WHITE, "\n\nCerrando programa...\n\n");
            Sleep(1500);
            exit(EXIT_SUCCESS);
        break;
    }
}

/* Animacion de carga del programa */
void cargarDatosBase(){
    int seg;
    for(seg=0; seg < 8; seg++){ /*For que se usa pasa simular la carga del programa*/
        switch (seg)
        {
        case 0:
        clearScreen();
            cprintf(COL_BRIGHT_WHITE, "\nCargando programa.\n");
            Sleep(1000);
            break;
        case 1:
        clearScreen();
            cprintf(COL_BRIGHT_WHITE, "\nCargando programa..\n");
            Sleep(1000);
            break;
        case 2:
        clearScreen();
            cprintf(COL_BRIGHT_WHITE, "\nCargando programa...\n\nCargando bases de datos.");
            Sleep(1000);
            
            break;
        case 3:
            clearScreen();
            cprintf(COL_BRIGHT_WHITE, "\nCargando bases de datos..\n");
            Sleep(1000);
            
            break;
        case 4:
            clearScreen();
            cprintf(COL_BRIGHT_WHITE, "\nCargando bases de datos...\n");
            cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS, true);
            Sleep(1000);
            break;
        case 5:
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, true);
            Sleep(1500);    
        break;
        case 6:
            iniciarCola(&colaPacientes, true);
            Sleep(1000);
            agregarPacientes(&colaPacientes, arrayPacientes, cantidadDePacientesTotalGral, true);
            Sleep(500);
            if(cantidadDePacientesTotalGral == cantidadPacientesEnCola(colaPacientes)) cprintf(COL_BRIGHT_WHITE, "\nTotalidad de pacientes agregados correctamente\n");
        break;
        case 7:
            cprintf(COL_BRIGHT_WHITE, "\nPrograma ya cargado y compilado... Iniciando...\n\n");
            Sleep(1000);    
        break;
        }
    }
}

void menu(){
    
    clearScreen();

    cprintf(COL_BRIGHT_GREEN, "\t=============================================\n");
    cprintf(COL_BRIGHT_GREEN, "\t================Menu Principal===============\n");
    cprintf(COL_BRIGHT_GREEN, "\t=============================================\n");

    cprintf(COL_BRIGHT_WHITE, "\n[1]"); cprintf(COL_RESET, " - Agregar paciente");
    cprintf(COL_BRIGHT_WHITE, "\n[2]"); cprintf(COL_RESET, " - Ver cola de Pacientes");
    cprintf(COL_BRIGHT_WHITE, "\n[3]"); cprintf(COL_RESET, " - Ver lista de pacientes por DNI y Nombre");
    cprintf(COL_BRIGHT_WHITE, "\n[4]"); cprintf(COL_RESET, " - Mostrar registro de pacientes");
    cprintf(COL_BRIGHT_WHITE, "\n[5]"); cprintf(COL_RESET, " - Abrir menu de medicos (privado)");
    cprintf(COL_BRIGHT_WHITE, "\n[6]"); cprintf(COL_RESET, " - Cerra programa");
    cprintf(COL_BRIGHT_BLUE, "\n\nOpcion: ");


    switchMenu();
}

#endif
