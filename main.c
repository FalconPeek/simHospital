#include "include/TADs.h"



int main(void) {
    clearScreen(); /*Borra el cmd*/
    
    cargarDatosBase(); /*Animacion de carga mas carga/creacion de archivos*/

    menu(); /*Menu principal*/
    
    /*No coloco el return 0;
    Porque el programa esta funcionando con exit(EXIT_SUCCESS)
    que cuando se elige sale del programa*/
}

