#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {

    char * nombre;
    char * marca;
    char * tipo;
    int stock;
    int precio;

} producto;

typedef struct{

    List * productos;

} carrito;

#endif
