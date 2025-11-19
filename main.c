#include "include/TADs.h"


////////////////////////////////////////////////
/*
ESTO ES UN MAIN PROVISORIO ESTABA VIENDO QUE TODO FUNCIONE NADA MAS
*/
////////////////////////////////////////////////


#define MAX_MEDICOS 1000

int main(void) {
    tMedico medicos[MAX_MEDICOS];

    // Primero cargás todo el archivo al array
    int cantidad = cargarMedicosEnArray(medicos, MAX_MEDICOS);

    // Mostrás y borrás
    cantidad = mostrarYBorrarMedico(medicos, cantidad);

    // Si querés ver cómo quedó:
    printf("\nLista luego del borrado:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("DNI: %d  |  Nombre: %s\n", medicos[i].DNI, medicos[i].nombreApellido);
    }

    return 0;
}

