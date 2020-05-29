#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "map.h"

//struct producto
typedef struct producto{

    char * nombre;
    char * marca;
    char * tipo;
    int stock;
    int precio;

} producto;

//funci�n creadora de producto
producto * crearProducto(char *, char *, char *, int, int);

//struct carrito
typedef struct carrito{

    List * productos;

} carrito;

//funcion que duplica un string
char * _strdup (const char *);

//funcion que obtiene un campo de un archivo csv
const char *get_csv_field (char *, int);

//funcion que a�ade la extension .csv a un archivo
void anadirExtensionCSV(char *);

//funci�n que importa los productos desde un archivo csv y los guarda en un mapa, retorna -1 en caso de haber un error o querer volver al men�
int importarProductosCSV(HashTable *);

//exporta los productos ingresados anteriormente a un archivo .csv
int exportarProductosCSV(HashTable *);

//agrega un producto de manera manual
int agregarProducto(HashTable *);

//busca todos los productos del tipo ingresado
int buscarPorTipo(HashTable *);


#endif
