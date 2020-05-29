#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "map.h"
#include "functions.h"

struct producto{

    char * nombre;
    char * marca;
    char * tipo;
    int stock;
    int precio;

};

producto * crearProducto(char * nombre, char * marca, char * tipo, int stock, int precio){

    producto * nuevo = (producto *) malloc (sizeof(producto));
    nuevo->nombre = nombre;
    nuevo->marca = marca;
    nuevo->tipo = tipo;
    nuevo->stock = stock;
    nuevo->precio = precio;
    return nuevo;

}

struct carrito{

    List * productos;

};

char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

int importarProductosCSV(HashTable * productos){

    printf("Para importar productos, ingrese el nombre del archivo incluyendo su extension: ");

    char nombreArchivo[50];
    scanf("%s", nombreArchivo);
    printf("\n");

    FILE * fp = fopen( nombreArchivo ,"r");
    if (!fp){
        printf("Hubo un error al abrir el arhivo, ");
        system("pause");
        return -1;
    }

    char linea[1024];

    char * nombreProducto;
    char * marcaProducto;
    char * tipoProducto;
    int stockProducto;
    int precioProducto;

    while (fgets(linea, 1023 ,fp) != NULL){

        nombreProducto = get_csv_field(linea, 1);
        marcaProducto = get_csv_field(linea, 2);
        tipoProducto = get_csv_field(linea, 3);
        stockProducto = atoi(get_csv_field(linea, 4));
        precioProducto = atoi (get_csv_field(linea, 5));

        producto * nuevo = crearProducto(nombreProducto, marcaProducto, tipoProducto, stockProducto, precioProducto);
        insertHashTable(productos, nombreProducto, nuevo);

    }

    printf("Los productos han sido exportados de manera exitosa, ");
    system("pause");

    return -1;

}
