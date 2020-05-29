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

void anadirExtensionCSV(char * nombre){

    size_t length = strlen(nombre);
    nombre[length] = '.';
    nombre[length + 1] = 'c';
    nombre[length + 2] = 's';
    nombre[length + 3] = 'v';
    nombre[length + 4] = '\0';

}

int importarProductosCSV(HashTable * productos){

    printf("Para importar productos, ingrese el nombre del archivo (sin incluir extension .csv): ");

    char nombreArchivo[50];
    scanf("%s", nombreArchivo);
    printf("\n");

    anadirExtensionCSV(nombreArchivo);

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

    fclose(fp);

    printf("Los productos han sido exportados de manera exitosa, ");
    system("pause");


    return -1;

}

int exportarProductosCSV(HashTable * productos){

    producto * producto = firstHashTable(productos);
    if(producto == NULL){

        printf("No existen elementos para exportar, por favor ingrese como minimo uno, ");
        system("pause");
        return -1;

    }

    char nombreArchivo[50];
    printf("Por favor ingrese el nombre del archivo que desea ingresar los productos (sin extension .csv)\n");
    printf("Si el archivo no existe sera creado: ");
    scanf("%s", nombreArchivo);

    anadirExtensionCSV(nombreArchivo);

    FILE * fp = fopen(nombreArchivo, "w");

    while(producto != NULL){

        fprintf(fp, "%s,%s,%s,%d,%d\n", producto->nombre, producto->marca, producto->tipo, producto->stock, producto->precio);
        producto = nextHashTable(productos);

    }

    printf("\n");
    printf("Los elementos han sido exportados de manera correcta, ");
    system("pause");

    return -1;
}
