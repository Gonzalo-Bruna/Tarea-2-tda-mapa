#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//struct producto
typedef struct producto producto;

//función creadora de producto
producto * crearProducto(char *, char *, char *, int, int);

//struct carrito
typedef struct carrito carrito;

//funcion que duplica un string
char * _strdup (const char *);

//funcion que obtiene un campo de un archivo csv
const char *get_csv_field (char *, int);

//funcion que añade la extension .csv a un archivo
void anadirExtensionCSV(char *);

//función que importa los productos desde un archivo csv y los guarda en un mapa, retorna -1 en caso de haber un error o querer volver al menú
int importarProductosCSV(HashTable *);

//exporta los productos ingresados anteriormente a un archivo .csv
int exportarProductosCSV(HashTable *);

//agrega un producto de manera manual
int agregarProducto(HashTable *);


#endif
