#ifndef COLAURGENCIA_H
#define COLAURGENCIA_H

#include "includesBasicos.h"


void iniciarCola(tColaPacientes* colaPacientes){
    colaPacientes->principio = NULL;
    colaPacientes->final = NULL;
    cprintf(COL_GREEN, "\n[SUCCESS] -> Cola de Pacientes Iniciada...\n");
    Sleep(1000);
}

bool colaVacia(tColaPacientes colaPacientes){
    return (colaPacientes.principio == NULL && colaPacientes.final == NULL);
}

void agregarPacientes(tColaPacientes* colaPacientes, tPaciente* arrayP, int cantidadPacientes){
    int i;
    for(i=0;i < cantidadPacientes; i++){    
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
    }
    cprintf(COL_BLUE, "\nSe agregaron %d pacientes a la cola", i);
}

int cantidadPacientesEnCola(tColaPacientes colaPacientes){
    int cantidad = 0;
    if(colaVacia){
        return cantidad;
    } else {
        tNodoPaciente* listaPacientes = colaPacientes.principio;

        while(listaPacientes != NULL){
            cantidad++;
        }
        listaPacientes = listaPacientes->siguientePaciente;
    }
    return cantidad;
}

void visualizarCola(tColaPacientes pPacientes){
    cprintf(COL_BRIGHT_MAGENTA, "\n-----------------------------------------\n");
    cprintf(COL_BRIGHT_MAGENTA, "\t*** Pacientes en espera ***");
    cprintf(COL_BRIGHT_MAGENTA, "\n-----------------------------------------\n");

    if(colaVacia(pPacientes)){
        cprintf(COL_BRIGHT_RED, "\n\t[ERROR] -> ");
        cprintf(COL_BRIGHT_WHITE, "La cola esta vacia...\n");
        Sleep(2000);
        menu();
    } else {
        tNodoPaciente* listaPacientes = pPacientes.principio;
        cprintf(COL_BRIGHT_CYAN, "Nombre Completo\tDNI\t\tCodigo Urgencia\n");
        while (listaPacientes != NULL){
            printf("%s\t%d\t%d", 
                listaPacientes->paciente.nombrePaciente,
                listaPacientes->paciente.DNI,
                listaPacientes->paciente.urgencia
            );
            listaPacientes = listaPacientes->siguientePaciente;
        }
        int scan;
        cprintf(COL_BRIGHT_BLUE, "\n\n\t\tPrecione 1 luego Enter para volver al menu...\t");
        scanf("%d", &scan); if(scan == 1) {menu();}
    }
}

#endif