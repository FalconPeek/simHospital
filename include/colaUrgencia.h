#ifndef COLAURGENCIA_H
#define COLAURGENCIA_H

#include "includesBasicos.h"

/*Funcion para ordenar un array por urgencia*/
void ordenarPacientesPorUrgencia(tPaciente v[], int n){
    int i, j;
    tPaciente aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j].urgencia > v[j + 1].urgencia) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

/*Funcion que inicia la cola*/
void iniciarCola(tColaPacientes* colaPacientes, bool mostrar){
    if(mostrar){
        colaPacientes->principio = NULL;
    colaPacientes->final = NULL;
    cprintf(COL_GREEN, "\n[EXITO] -> "); printf("Cola de Pacientes Iniciada...\n");
    Sleep(1000);    
    } else {
        colaPacientes->principio = NULL;
        colaPacientes->final = NULL;
    }
}

/*Funcion para verificar si hay pacientes en la cola*/
bool colaVacia(tColaPacientes colaPacientes){
    return (colaPacientes.principio == NULL && colaPacientes.final == NULL);
}

/*Funcion que agrega pacientes en la cola desde el array creado*/
void agregarPacientes(tColaPacientes* colaPacientes, tPaciente* arrayP, int cantidadPacientes, bool mostrar){
    int i;

    /* Ordenamos el array por urgencia (1 mas urgente, 5 menos) */
    ordenarPacientesPorUrgencia(arrayP, cantidadPacientes);

    for(i=0;i < cantidadPacientes; i++){
        if(strcmp(arrayP[i].razonDelAlta, "SIN ALTA") == 0){
            tNodoPaciente* nuevoPaciente = (tNodoPaciente*) malloc(sizeof(tNodoPaciente));
            nuevoPaciente->paciente = arrayP[i];
            nuevoPaciente->siguientePaciente = NULL;
            if(colaVacia(*colaPacientes)){
                colaPacientes->principio = nuevoPaciente;
                colaPacientes->final = nuevoPaciente;
            } else {
                colaPacientes->final->siguientePaciente = nuevoPaciente;
                colaPacientes->final = nuevoPaciente;
            } 
        } else { continue; }
    }
    if(mostrar) {cprintf(COL_GREEN, "\nSe agregaron %d pacientes a la cola", i);}
} 

/*Funcion que devuelve la cantidad de pacientes en la cola*/
int cantidadPacientesEnCola(tColaPacientes colaPacientes){
    int cantidad = 0;

    if (colaVacia(colaPacientes)) {
        return 0;
    }

    tNodoPaciente* listaPacientes = colaPacientes.principio;
    while (listaPacientes != NULL) {
        cantidad++;
        listaPacientes = listaPacientes->siguientePaciente;
    }

    return cantidad;
}

/*Funcion que se usa para visualizar la cola en orden de urgencia*/
void visualizarCola(tColaPacientes pPacientes){
    cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");
    cprintf(COL_BRIGHT_CYAN, "\t*** Pacientes en espera ***");
    cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");

    if(colaVacia(pPacientes)){
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> ");
        cprintf(COL_BRIGHT_WHITE, "La cola esta vacia...\n");
        Sleep(2000);
        menu();
    } else {
        clearScreen();

        cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");
        cprintf(COL_BRIGHT_CYAN, "\t*** Pacientes en espera ***");
        cprintf(COL_BRIGHT_CYAN, "\n-----------------------------------------\n");

        tNodoPaciente* listaPacientes = pPacientes.principio;
        tString NOMBRE, DNI, CODIGO;
        strcpy(NOMBRE, "Nombre Completo");
        strcpy(DNI, "Documento");
        strcpy(CODIGO, "Urgencia");

        cprintf(COL_BRIGHT_CYAN, "%-30s %-10s %-15s\n", NOMBRE, DNI, CODIGO);
        while (listaPacientes != NULL){
            printf("%-30s %-10d", 
                listaPacientes->paciente.nombrePaciente,
                listaPacientes->paciente.DNI
            );
            switch(listaPacientes->paciente.urgencia){
                case 1:
                    cprintf(COL_RED, " Atencion Inmediata\n");
                    break;
                case 2:
                    cprintf(COL_YELLOW, " Urgencia Alta\n");
                    break;
                case 3:
                    cprintf(COL_MAGENTA, " Atencion Media\n");
                    break;
                case 4:
                    cprintf(COL_CYAN, " Atencion Baja\n");
                    break;
                case 5:
                    cprintf(COL_GREEN, " No urgente\n");
                    break;
                }
            listaPacientes = listaPacientes->siguientePaciente;
        }
        esperarEnter(1);
    }
}

/*Funciones necesarias para la manipulacion de archivos al momento de desencolar...*/
void guardarPacientesEnArchivo(tPaciente pPaciente[], int cantidadPacientes){
    FILE * arch = fopen(PATH_ArchPacientes, "wb");
    if (arch == NULL){
        cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("No se pudo abrir pacientes.dat para escritura.\n");
        return;
    }

    if(cantidadPacientes > 0) {
        size_t escritos = fwrite(pPaciente, sizeof(tPaciente), cantidadPacientes, arch);
        if(escritos != (size_t)cantidadPacientes){
            cprintf(COL_BRIGHT_RED, "\n[ERROR] -> "); printf("Ocurrio un error al guardar el array pacientes en el Archivo...\n");
        }
    }

    fclose(arch);
}


int diagnosticarDarAlta(tColaPacientes* pPacientes, tPaciente pArrayPacientes[]){
    /* 1) Sincronizar array con el archivo SIEMPRE */
    int cantidadActual = cargarPacientesEnArray(pArrayPacientes, MAXPACIENTES, false);

    if(cantidadActual == 0){
        cprintf(COL_BRIGHT_MAGENTA, "[WARNING] -> "); printf("No hay pacientes cargados en el archivo.\n");
        cantidadPacientesSinAlta = 0;
        return 0;
    }

    /* 2) Si la cola está vacía, solo devolvemos cuántos siguen sin alta*/
    if(colaVacia(*pPacientes)){
        cprintf(COL_BRIGHT_MAGENTA, "\n[WARNING] -> "); printf("No hay pacientes en la cola para dar de alta.\n");

        int sinAlta = 0;
        int i;
        for (i = 0; i < cantidadActual; i++){
            if (strcmp(pArrayPacientes[i].razonDelAlta, "SIN ALTA") == 0){
                sinAlta++;
            }
        }
        cantidadPacientesSinAlta = sinAlta;
        return sinAlta;
    }

    /* 3) Tomamos el nodo del frente de la cola */
    tNodoPaciente* pacienteADarDeAlta = pPacientes->principio;
    tPaciente *pac = &pacienteADarDeAlta->paciente;

    /* 4) Mostrar info del paciente */
    cprintf(COL_BRIGHT_MAGENTA, "\n\nEmpecemos con la atencion...\n");

    printf("\n[Tipo atencion] -> ");
    switch (pac->urgencia){
        case 1: cprintf(COL_RED,    "ATENCION INMEDIATA"); break;
        case 2: cprintf(COL_YELLOW, "URGENCIA ALTA");      break;
        case 3: cprintf(COL_MAGENTA,"URGENCIA MEDIA");     break;
        case 4: cprintf(COL_CYAN,   "URGENCIA BAJA");      break;
        case 5: cprintf(COL_GREEN,  "NO URGENTE");         break;
    }

    cprintf(COL_BLUE, "\nNombre del Paciente: "); printf("%s", pac->nombrePaciente);
    cprintf(COL_BLUE, "\nAlergias: ");            printf("%s", pac->alergias);

    cprintf(COL_BLUE, "\nTipo de sangre: ");
    switch (pac->tipoDeSangre){
        case 0: printf("A+");  break;
        case 1: printf("A-");  break;
        case 2: printf("B+");  break;
        case 3: printf("B-");  break;
        case 4: printf("AB+"); break;
        case 5: printf("AB-"); break;
        case 6: printf("O+");  break;
        case 7: printf("O-");  break;
    }

    printf("\nContacto Emergencia: %d\nDNI: %d\nObra Social: ", pac->contactoEmergencia, pac->DNI);
    switch (pac->obraSocial){
        case 0: cprintf(COL_BRIGHT_BLUE,    "Sancor Salud");  break;
        case 1: cprintf(COL_BRIGHT_BLUE,    "IOFA");          break;
        case 2: cprintf(COL_BRIGHT_BLUE,    "OSDE");          break;
        case 3: cprintf(COL_BRIGHT_BLUE,    "IOSCOR");        break;
        case 4: cprintf(COL_BRIGHT_BLUE,    "PAMI");          break;
        case 5: cprintf(COL_BRIGHT_BLUE,    "OSECAC");        break;
        case 6: cprintf(COL_BRIGHT_BLUE,    "Swiss Medical"); break;
        case 7: cprintf(COL_BRIGHT_MAGENTA, "Particular");    break;
    }

    printf("\nDescripcion del problema: %s", pac->descripcionProblema);

    /* 5) Buscar este paciente en el array (uso DNI como clave)*/
    int idx = -1;
    int i;
    for (i = 0; i < cantidadActual && idx == -1; i++){
        if (pArrayPacientes[i].DNI == pac->DNI){
            idx = i;
        }
    }

    if (idx == -1){
        cprintf(COL_BRIGHT_RED, "\n\n[ERROR] -> "); printf("El paciente de la cola no se encontro en el array/archivo. No se registra alta.\n");
    } else {
        /* 6) Pedir razon de alta y guardar en el array (y en el nodo por prolijidad)*/
        printf("\n\nEscriba su razon de Alta: ");
        scanf(" %49[^\n]", pArrayPacientes[idx].razonDelAlta);

        /* mantener coherente la copia en la cola hasta que lo borremos */
        strcpy(pac->razonDelAlta, pArrayPacientes[idx].razonDelAlta);

        /* 7) Guardar array completo en el archivo (incluye el alta recien puesta)*/
        guardarPacientesEnArchivo(pArrayPacientes, cantidadActual);
    }

    /* 8) Desencolar el nodo de la cola */
    if (pPacientes->principio == pPacientes->final){
        /* era el unico*/
        pPacientes->principio = NULL;
        pPacientes->final     = NULL;
    } else {
        pPacientes->principio = pacienteADarDeAlta->siguientePaciente;
    }

    printf("\n\n\tPaciente dado de alta: %s\n", pac->nombrePaciente);


    free(pacienteADarDeAlta);

    /* 9) Recalcular cuantos siguen sin alta*/
    int sinAlta = 0;
    for (i = 0; i < cantidadActual; i++){
        if (strcmp(pArrayPacientes[i].razonDelAlta, "SIN ALTA") == 0){
            sinAlta++;
        }
    }
    cantidadPacientesSinAlta = sinAlta;

    return sinAlta;   /* NUEVA cantidad de pacientes sin alta */
}



#endif