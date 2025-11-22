#ifndef MENU_H
#define MENU_H

void switchMenu(){
    int opcion;
    scanf("%d", &opcion);
    switch (opcion){
        case 1:
            grabarPaciente();
            menu();
        break;
        case 2:
            printf("Todavia no se programo esta opcion...");
            Sleep(2000);
            menu();
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
            printf("\n\nCerrando programa...\n\n");
            Sleep(1500);
            exit(EXIT_SUCCESS);
        break;
    }
}

//Animacion de carga del programa
void cargarAssets(){
    int seg;
    for(seg=0; seg < 7; seg++){ /*For que se usa pasa simular la carga del programa*/
        switch (seg)
        {
        case 0:
        clearScreen();
            printf("\nCargando programa.\n");
            Sleep(1000);
            break;
        case 1:
        clearScreen();
            printf("\nCargando programa..\n");
            Sleep(1000);
            break;
        case 2:
        clearScreen();
            printf("\nCargando programa...\n\nCargando bases de datos.");
            Sleep(1000);
            
            break;
        case 3:
            clearScreen();
            printf("\nCargando bases de datos..\n");
            Sleep(1000);
            
            break;
        case 4:
            clearScreen();
            printf("\nCargando bases de datos...\n");
            cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS, true);
            Sleep(2000);
            break;
        case 5:
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, true);
            Sleep(1500);    
        break;
        case 6:
            printf("\nPrograma ya cargado y compilado... Iniciando...\n\n");
            Sleep(1000);    
        break;
        }
    }
}

void menu(){
    
    clearScreen();

    cprintf(COL_GREEN, "\t=============================================\n");
    cprintf(COL_GREEN, "\t================Menu Principal===============\n");
    cprintf(COL_GREEN, "\t=============================================\n");

    printf("\n[1]"); cprintf(COL_BLUE, " - Agregar paciente");
    printf("\n[2]"); cprintf(COL_BLUE, " - Ver cola de Pacientes");
    printf("\n[3]"); cprintf(COL_BLUE, " - Ver lista de pacientes por DNI y Nombre");
    printf("\n[4]"); cprintf(COL_BLUE, " - Mostrar registro de pacientes");
    printf("\n[5]"); cprintf(COL_BLUE, " - Abrir menu de medicos (privado)");
    printf("\n[6]"); cprintf(COL_BLUE, " - Cerra programa");
    cprintf(COL_BRIGHT_BLUE, "\n\nOpcion: ");


    switchMenu();
}

#endif
