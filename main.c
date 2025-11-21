#include "include/TADs.h"


////////////////////////////////////////////////
/*
ESTO ES UN MAIN PROVISORIO ESTABA VIENDO QUE TODO FUNCIONE NADA MAS
*/
////////////////////////////////////////////////



int main(void) {

    cantidadDeMedicos = cargarMedicosEnArray(arrayDeMedicos, MAXMEDICOS);
    cantidadDePacientes = cargarPacientesEnArray(arrayDePacientes, MAXPACIENTES);

    simulacionCargaPrograma();

    menu();
    return 0;
}

