#ifndef ARBOLMEDICOS_H
#define ARBOLMEDICOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "TADs.h"          // donde esta tMedico
#include "binarioMedicos.h" // donde esta PATH_ArchMed si queres usar cargarDesdeArchivo

/*========================================
=   TIPOS DE DATOS PARA EL ARBOL         =
========================================*/

typedef struct nodoMedico {
    tMedico info;
    struct nodoMedico *hijoIzq;
    struct nodoMedico *hijoDer;
} tNodoMedico;

typedef tNodoMedico tArbolMedico;

/*========================================
=   PROTOTIPOS                           =
========================================*/

void crearArbolMedico(tArbolMedico **pArbol);
bool arbolMedicoVacio(tArbolMedico *pArbol);

/* Inserta ordenado por DNI. 
   Devuelve true si inserto, false si ya existia ese DNI. */
bool insertarMedicoEnArbol(tArbolMedico **pArbol, tMedico med);

/* Carga todos los medicos de un array en el arbol.
   Devuelve cuantos inserto OK. */
int cargarArbolDesdeArrayMedicos(tArbolMedico **pArbol,
                                 tMedico medicos[],
                                 int cantidad);

/* Carga todos los medicos desde medicos.dat al arbol.
   Devuelve cuantos inserto OK. */
int cargarArbolDesdeArchivoMedicos(tArbolMedico **pArbol);

/* Busqueda rapida por DNI (BST). Devuelve puntero al nodo o NULL. */
tArbolMedico* buscarMedicoPorDNI(tArbolMedico *pArbol, int dniBuscado);

/* Recorrido IN-ORDEN solo para debug / listados. */
void visualizarInOrdenMedicos(tArbolMedico *pArbol);

/* Elimina el medico de DNI dado, si existe. */
void eliminarMedicoDelArbol(tArbolMedico **pArbol, int dni);

/* Libera toda la memoria del arbol. */
void liberarArbolMedico(tArbolMedico **pArbol);

/*========================================
=   IMPLEMENTACION                       =
========================================*/

void crearArbolMedico(tArbolMedico **pArbol) {
    *pArbol = NULL;
}

bool arbolMedicoVacio(tArbolMedico *pArbol) {
    return pArbol == NULL;
}

bool insertarMedicoEnArbol(tArbolMedico **pArbol, tMedico med) {
    if (arbolMedicoVacio(*pArbol)) {
        tNodoMedico *nuevo = (tNodoMedico*) malloc(sizeof(tNodoMedico));
        if (nuevo == NULL) {
            printf("Sin memoria para insertar medico.\n");
            return false;
        }
        nuevo->info = med;
        nuevo->hijoIzq = NULL;
        nuevo->hijoDer = NULL;
        *pArbol = nuevo;
        return true;
    }

    if (med.DNI < (*pArbol)->info.DNI) {
        return insertarMedicoEnArbol(&(*pArbol)->hijoIzq, med);
    } else if (med.DNI > (*pArbol)->info.DNI) {
        return insertarMedicoEnArbol(&(*pArbol)->hijoDer, med);
    } else {
        // DNI duplicado
        // printf("Error: ya existe un medico con DNI %d\n", med.DNI);
        return false;
    }
}

int cargarArbolDesdeArrayMedicos(tArbolMedico **pArbol, tMedico medicos[], int cantidad){
	
    int ok = 0;
    for (int i = 0; i < cantidad; i++) {
        if (insertarMedicoEnArbol(pArbol, medicos[i])) {
            ok++;
        }
    }
    return ok;
}

int cargarArbolDesdeArchivoMedicos(tArbolMedico **pArbol) {
    FILE *f = fopen(PATH_ArchMed, "rb");
    if (f == NULL) {
        printf("No se pudo abrir %s para cargar el arbol de medicos.\n", PATH_ArchMed);
        return 0;
    }

    tMedico med;
    int ok = 0;

    while (fread(&med, sizeof(tMedico), 1, f) == 1) {
        if (insertarMedicoEnArbol(pArbol, med)) {
            ok++;
        }
    }

    fclose(f);
    return ok;
}

tArbolMedico* buscarMedicoPorDNI(tArbolMedico *pArbol, int dniBuscado) {
    if (arbolMedicoVacio(pArbol)) {
        return NULL;
    }

    if (dniBuscado < pArbol->info.DNI) {
        return buscarMedicoPorDNI(pArbol->hijoIzq, dniBuscado);
    } else if (dniBuscado > pArbol->info.DNI) {
        return buscarMedicoPorDNI(pArbol->hijoDer, dniBuscado);
    } else {
        return pArbol; // encontrado
    }
}

void visualizarInOrdenMedicos(tArbolMedico *pArbol) {
    if (arbolMedicoVacio(pArbol)) return;

    visualizarInOrdenMedicos(pArbol->hijoIzq);
    printf("DNI: %d | Nombre: %s\n",
           pArbol->info.DNI,
           pArbol->info.nombreApellido);
    visualizarInOrdenMedicos(pArbol->hijoDer);
}

/* Nodo minimo (menor DNI) en un subArbol */
static tArbolMedico* minimoNodoMedico(tArbolMedico *pArbol) {
    if (pArbol == NULL) return NULL;

    while (pArbol->hijoIzq != NULL) {
        pArbol = pArbol->hijoIzq;
    }
    return pArbol;
}

void eliminarMedicoDelArbol(tArbolMedico **pArbol, int dni) {
    tNodoMedico *aux;

    if (arbolMedicoVacio(*pArbol)) {
        // printf("No existe medico con DNI %d en el arbol.\n", dni);
        return;
    }

    if (dni < (*pArbol)->info.DNI) {
        eliminarMedicoDelArbol(&(*pArbol)->hijoIzq, dni);
    } else if (dni > (*pArbol)->info.DNI) {
        eliminarMedicoDelArbol(&(*pArbol)->hijoDer, dni);
    } else {
        // Encontrado
        if ((*pArbol)->hijoIzq == NULL) {
            aux = *pArbol;
            *pArbol = (*pArbol)->hijoDer;
            free(aux);
        } else if ((*pArbol)->hijoDer == NULL) {
            aux = *pArbol;
            *pArbol = (*pArbol)->hijoIzq;
            free(aux);
        } else {
            // dos hijos → reemplazar con mínimo del subArbol derecho
            tNodoMedico *minDer = minimoNodoMedico((*pArbol)->hijoDer);
            (*pArbol)->info = minDer->info;
            eliminarMedicoDelArbol(&(*pArbol)->hijoDer, minDer->info.DNI);
        }
    }
}

void liberarArbolMedico(tArbolMedico **pArbol) {
    if (*pArbol == NULL) return;

    liberarArbolMedico(&(*pArbol)->hijoIzq);
    liberarArbolMedico(&(*pArbol)->hijoDer);

    free(*pArbol);
    *pArbol = NULL;
}

#endif // ARBOLMEDICOS_H
