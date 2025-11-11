#include "includesBasicos.h"




//Varibles Globales
FILE * archivo;



//Funciones->
void iniciarGrabadoArchivo(){
    archivo = fopen("medicos.dat", "ab");

    if(archivo == NULL){
        printf("Error al abrir medicos.dat");
        exit(EXIT_FAILURE);
    } else {
        printf("Archivo abierto en modo Add Binarie");
    };   
}

void grabarArchivo(){
    tMedico inputMedico;

    clearScreen();

    
}

void finalizarGrabadoArchivo(){

}

