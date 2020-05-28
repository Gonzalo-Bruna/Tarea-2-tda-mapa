#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//struct producto
typedef struct producto producto;

//struct carrito
typedef struct carrito carrito;

//funcion que duplica un string
char * _strdup (const char *);

//funcion que obtiene un campo de un archivo csv
const char *get_csv_field (char *, int);

#endif
