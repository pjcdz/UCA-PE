#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_nodo {
    char* producto;
    float precio;
    int codigo;
    struct s_nodo* sig;
};

typedef struct s_nodo* t_nodo;

struct s_nodoAux {
    char producto[50];
    float precio;
    int codigo;
};

typedef struct s_nodoAux t_nodoAux;

// ################### CargarArchivoEnLista ######################################################################################

void appendUltimo (t_nodo* ls, char* producto, float precio, int codigo) {
    if (*ls == NULL) {
        *ls = malloc(sizeof(struct s_nodo));
        (*ls)->producto = malloc( strlen(producto) + 1 );

        strcpy((*ls)->producto, producto);
        (*ls)->precio = precio;
        (*ls)->codigo = codigo;

        (*ls)->sig = NULL;
    } else {
        appendUltimo( &((*ls)->sig), producto, precio, codigo);
    }
}

void appendOrdenadoCodigo (t_nodo *ls, char* producto, float precio, int codigo) {
    t_nodo aux = NULL;

    if (*ls == NULL) {
        *ls = malloc(sizeof(struct s_nodo));
        (*ls)->producto = malloc( strlen(producto) + 1 );

        strcpy( (*ls)->producto, producto );
        (*ls)->precio = precio;
        (*ls)->codigo = codigo;

        (*ls)->sig = NULL;
    } else {
        if ( (*ls)->codigo < codigo && (*ls)->codigo != -1) {
            aux = malloc(sizeof(struct s_nodo));
            aux->producto = malloc( strlen(producto) + 1 );
            aux->sig = (*ls);

            strcpy( aux->producto, producto );
            aux->precio = precio;
            aux->codigo = codigo;

            (*ls) = aux;
        } else {
            appendOrdenadoCodigo( &((*ls)->sig), producto, precio, codigo );
        }
    }
}

void appendOrdenadoNombre (t_nodo* ls, char* producto, float precio, int codigo) {
    t_nodo aux = NULL;

    if (*ls == NULL) {
        *ls = malloc(sizeof(struct s_nodo));
        (*ls)->producto = malloc( strlen(producto) + 1 );

        strcpy((*ls)->producto, producto);
        (*ls)->precio = precio;
        (*ls)->codigo = codigo;

        (*ls)->sig = NULL;
    } else {
        if ( strcmp( (*ls)->producto, producto ) > 0 && (*ls)->codigo != -1 ) {
            aux = malloc(sizeof(struct s_nodo));
            aux->producto = malloc( strlen(producto) + 1 );
            aux->sig = (*ls);

            strcpy(aux->producto, producto);
            aux->precio = precio;
            aux->codigo = codigo;

            (*ls) = aux;
        } else {
            appendOrdenadoNombre( &((*ls)->sig), producto, precio, codigo );
        }
    }
}

void appendPrimero(t_nodo* ls, char* producto, float precio, int codigo) {
    t_nodo aux = malloc(sizeof(struct s_nodo));
    aux->producto = malloc( strlen(producto) + 1 );
    aux->sig = (*ls);

    strcpy(aux->producto, producto);
    aux->precio = precio;
    aux->codigo = codigo;

    (*ls) = aux;
}

int leerArchCargaLs (t_nodo* ls, char* archivo) {
    FILE* arch;
    arch = fopen(archivo, "r");

    if ( arch == NULL ) {
        return -1;
    }

    t_nodoAux aux;
    int r = fscanf(arch, "%[^,], %f, %d\n", aux.producto, &aux.precio, &aux.codigo);

    while (r != EOF) {
        // printf("%-16s | %7.01f | %6d\n", aux.producto, aux.precio, aux.codigo);
        appendUltimo( ls, aux.producto, aux.precio, aux.codigo);
        // appendOrdenadoCodigo( ls, aux.producto, aux.precio, aux.codigo);
        // appendOrdenadoNombre( ls, aux.producto, aux.precio, aux.codigo);
        // appendPrimero( ls, aux.producto, aux.precio, aux.codigo);
        r = fscanf(arch, "%[^,], %f, %d\n", aux.producto, &aux.precio, &aux.codigo);
    }

    aux.producto[0] = '\0';
    aux.precio = -1;
    aux.codigo = -1;
    appendUltimo( ls, aux.producto, aux.precio, aux.codigo);

    return 0;
}

// ################### ImprimirLista ######################################################################################

void imprimirRecursivo(t_nodo ls) {
    if (ls != NULL && ls->codigo != -1) {
        printf("%-16s | %7.01f | %6d\n", ls->producto, ls->precio, ls->codigo);
        imprimirRecursivo( ls->sig );
    }
}

// void imprimirIterativo(t_nodo ls) {
//     while (ls != NULL && ls->codigo != -1) {
//         printf("%-16s | %7.01f | %6d\n", ls->producto, ls->precio, ls->codigo);
//         ls = ls->sig;
//     }
// }

// ################### EliminarDeLaLista ######################################################################################

void eliminar1Codigo (t_nodo *ls, int codigo) {
    t_nodo aux = NULL;
    if (*ls != NULL) {
        if ( (*ls)->codigo == codigo ) {
            aux = (*ls);
            (*ls) = (*ls)->sig;
            free(aux);
        } else {
            eliminar1Codigo ( &((*ls)->sig), codigo);
        }   
    }
}

void eliminar1Producto (t_nodo *ls, char* producto) {
    t_nodo aux = NULL;
    if (*ls != NULL) {
        if ( strcmp( (*ls)->producto, producto ) == 0 ) {
            aux = (*ls);
            (*ls) = (*ls)->sig;
            free(aux);
        } else {
            eliminar1Producto ( &((*ls)->sig), producto );
        }
    }
}

void eliminarTodasCodigo (t_nodo* ls, int codigo) {
    t_nodo aux = NULL;
    if (*ls != NULL) {
        if ( (*ls)->codigo == codigo ) {
            aux = (*ls);
            (*ls) = (*ls)->sig;
            free(aux);
            eliminarTodasCodigo( &(*ls), codigo );
        } else {
            eliminarTodasCodigo( &((*ls)->sig), codigo );
        }
    }
}

void eliminarTodasProducto (t_nodo* ls, char* producto) {
    t_nodo aux = NULL;
    if (*ls != NULL) {
        if ( strcmp( (*ls)->producto, producto ) == 0 ) {
            aux = (*ls);
            (*ls) = (*ls)->sig;
            free(aux);
            eliminarTodasProducto( &(*ls), producto );
        } else {
            eliminarTodasProducto( &((*ls)->sig), producto );
        }
    }
}

void eliminarRangoPrecios (t_nodo* ls, float min, float max ) {
    t_nodo aux = NULL;
    if (*ls != NULL) {
        if ( (*ls)->precio >= min && (*ls)->precio <= max ) {
            aux = (*ls);
            (*ls) = (*ls)->sig;
            free(aux);
            eliminarRangoPrecios( &(*ls), min, max );
        } else {
            eliminarRangoPrecios( &((*ls)->sig), min, max );
        }
    }
}

// ################### BuscarEnLista ######################################################################################<

void buscarCodigo (t_nodo* ls, t_nodo* resultado, int codigo) {
    if (*ls != NULL) {
        if ( (*ls)->codigo == codigo ) {
            appendUltimo(&(*resultado), (*ls)->producto, (*ls)->precio, (*ls)->codigo);
            buscarCodigo ( &((*ls)->sig), &(*resultado), codigo);
        } else {
            buscarCodigo ( &((*ls)->sig), &(*resultado), codigo);
        }
    }
}

void buscarRangoPrecios (t_nodo* ls, t_nodo* resultado, float min, float max) {
    if (*ls != NULL) {
        if ( (*ls)->precio >= min && (*ls)->precio <= max ) {
            appendUltimo( &(*resultado), (*ls)->producto, (*ls)->precio, (*ls)->codigo );
            buscarRangoPrecios ( &((*ls)->sig), &(*resultado), min, max);
        } else {
            buscarRangoPrecios ( &((*ls)->sig), &(*resultado), min, max);
        }
    }
}

int vocales ( char* producto ) {
    int num = 0;
    int i = 0;
    while ( i < (strlen(producto) + 1) ) {
        if ( producto[i] == 'a' || producto[i] == 'e' || producto[i] == 'i' ||
            producto[i] == 'o' || producto[i] == 'u' || producto[i] == 'A' || 
            producto[i] == 'E' || producto[i] == 'I' || producto[i] == 'O' || 
            producto[i] == 'U' ) {
            num++;
        }
        i++;
    }

    return num;
}

int vocalesRecursivo ( char* str ) {
    if ( *str != '\0' ) {
        int esVocal =  (*str == 'a' || *str == 'e' || *str == 'i' || 
                        *str == 'o' || *str == 'u' || *str == 'A' || 
                        *str == 'E' || *str == 'I' || *str == 'O' || 
                        *str == 'U');

        return esVocal + vocalesRecursivo( str+1 );
    }
}

void busquedaPorCaracteristica (t_nodo *ls, t_nodo *resultado) {
    if (*ls != NULL) {
        // if ( vocales( (*ls)->producto ) == 2) {
        if ( vocalesRecursivo( (*ls)->producto ) == 2) {
            appendUltimo( &(*resultado), (*ls)->producto, (*ls)->precio, (*ls)->codigo );
            busquedaPorCaracteristica( &((*ls)->sig), &(*resultado) );
        } else {
            busquedaPorCaracteristica( &((*ls)->sig), &(*resultado) );
        }
    }
}

// ################### Main ######################################################################################<

int main() {
    t_nodo ls = NULL;

    // ################### Lectura y carga ###################
    leerArchCargaLs(&ls, "06-parcial-datos.csv");
    imprimirRecursivo(ls);
    // imprimirIterativo(ls);

    // ################### Eliminar ###################
    printf("-----------------------------------\n");
    eliminar1Codigo(&ls, 9999);
    // eliminar1Producto(&ls, "Regla 30");
    // eliminarTodasCodigo(&ls, 1024);
    // eliminarTodasProducto(&ls, "Lapicera Bic");
    // eliminarRangoPrecios(&ls, 5, 20);
    imprimirRecursivo(ls);

    // ################### Busqueda ###################
    // printf("-----------------------------------\n");
    // t_nodo resultado = NULL;
    // // buscarCodigo(&ls, &resultado, 1024);
    // // buscarRangoPrecios(&ls, &resultado, 5, 20);
    // // printf("test: %d", vocales("palabra"));
    // busquedaPorCaracteristica(&ls, &resultado);
    // imprimirRecursivo(resultado);

    return 0;
}