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
            Sleep(2);
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
    for(seg=0; seg < 6; seg++){ /*For que se usa pasa simular la carga del programa*/
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
            cantidadDePacientesTotalGral = cargarPacientesEnArray(arrayPacientes, MAXPACIENTES, true);
            Sleep(2000);
            break;
        case 5:
            printf("\nPrograma ya cargado y compilado... Iniciando...\n\n");
            Sleep(1000);    
        break;
        }
    }
}

void menu(){
    
    clearScreen();

    printf("\t=============================================\n");
    printf("\t================Menu Principal===============\n");
    printf("\t=============================================\n");

    printf("\n[1] - Agregar paciente");
    printf("\n[2] - Ver cola de Pacientes");
    printf("\n[3] - Ver lista de pacientes por DNI y Nombre");
    printf("\n[4] - Mostrar registro de pacientes");
    printf("\n[5] - Abrir menu de medicos (privado)");
    printf("\n[6] - Cerra programa");
    printf("\n\nOpcion: ");

    switchMenu();
}

#endif
