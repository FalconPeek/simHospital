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
            printf("Todavia no se programo esta funcion...");
            Sleep(2);
            menu();
        break;
        case 4:
            menuMedicos(0);
        break;
        default: exit(EXIT_SUCCESS);
        break;
    }
}

void simulacionCargaPrograma(){
    int seg;
    for(seg=0; seg < 6; seg++){ /*For que se usa pasa simular la carga del programa*/
        switch (seg)
        {
        case 0:
        clearScreen();
            printf("\nCargando programa.\n");
            Sleep(1);
            break;
        case 1:
        clearScreen();
            printf("\nCargando programa..\n");
            Sleep(1);
            break;
        case 2:
        clearScreen();
            printf("\nCargando programa...\n\nCargando bases de datos.");
            Sleep(1);
            break;
        case 3:
            clearScreen();
            printf("\nCargando bases de datos..\n");
            break;
        case 4:
            clearScreen();
            printf("\nCargando bases de datos...\n");
            Sleep(1);
            break;
        case 5:
            clearScreen();
            printf("\nPrograma ya cargado y compilado... Iniciando...\n\n");
            Sleep(1);    
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
    printf("\n[3] - Mostrar registro de pacientes");
    printf("\n[4] - Abrir menu de medicos (privado)");
    printf("\n[Enter] - Cerra programa");
    printf("\n\nOpcion: ");


}

#endif
