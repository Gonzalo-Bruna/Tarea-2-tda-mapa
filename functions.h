#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "map.h"

//struct producto
typedef struct producto{

    const char * nombre;
    const char * marca;
    const char * tipo;
    int stock;
    int precio;

} producto;

//funci�n creadora de producto
producto * crearProducto(const char *, const char *,const char *, int, int);

//struct carrito
typedef struct carrito{

    char * nombre;
    List * productos;

} carrito;

//funcion creadora de carrito
carrito * crearCarrito(char *);

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

//busca todos los productos de la marca ingresada
int buscarPorMarca(HashTable *);

//busca el producto con el nombre respectivo y muestra su informaci�n
int buscarPorNombre(HashTable *);

//muestra todos los productos y su informaci�n por pantalla
int mostrarProductos(HashTable *);

//agrega a un carrito un producto que desea a�adir, si el carrito no existe se crea uno, si es que ya hay carritos, los muestra por pantalla
//y pregunta si queire usar uno ya creado o crear uno nuevo
int agregarAlCarrito(HashTable *, List *);

//concreta la compra de un carrito y se libera su memoria
int concretarCompra(List *);
#endif
