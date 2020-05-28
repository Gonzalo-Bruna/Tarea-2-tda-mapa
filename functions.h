#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//struct producto
typedef struct {

    char * nombre;
    char * marca;
    char * tipo;
    int stock;
    int precio;

} producto;

//struct carrito
typedef struct{

    List * productos;

} carrito;

//funcion que duplica un string
char * _strdup (const char *s);

//funcion que obtiene un campo de un archivo csv
const char *get_csv_field (char * tmp, int i);



#endif
