#include "functions.h"

 producto * crearProducto(char * nombre, char * marca, char * tipo, int stock, int precio){

    producto * nuevo = (producto *) malloc (sizeof(producto));
    nuevo->nombre = nombre;
    nuevo->marca = marca;
    nuevo->tipo = tipo;
    nuevo->stock = stock;
    nuevo->precio = precio;
    return nuevo;

}

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

int agregarProducto(HashTable * productos){

    printf("Para agregar productos, se debe agregar la siguiente informacion, \n");

    char * nombre = (char *) malloc (100 * sizeof(char));
    char * marca = (char *) malloc (50 * sizeof(char));
    char * tipo = (char *) malloc (50 * sizeof(char));
    int * precio = (int *) malloc (sizeof(int));

    fflush(stdin);

    printf("Ingrese el nombre del producto: ");
    scanf("%[^\n]s", nombre);
    fflush(stdin);

    producto * nuevoProducto; //se crea un puntero del producto que se agregará
    producto * product = searchHashTable(productos, nombre);

    if(!product){

        printf("Ingrese la marca del producto: ");
        scanf("%[^\n]s", marca);
        fflush(stdin);
        printf("Ingrese el tipo de producto: ");
        scanf("%[^\n]s", tipo);
        fflush(stdin);
        printf("Ingrese su precio: ");
        scanf("%d", &precio);

        int * stock = (int *) malloc (sizeof(int));
        printf("El producto es nuevo, por favor ingrese el stock que desea agregar: ");
        do{
            scanf("%d", &stock);
            if(stock <= 0) printf("El stock a agregar debe ser mayor que 0\n");
        }while(stock < 0);

        nuevoProducto = crearProducto(nombre, marca, tipo, stock, precio);
        insertHashTable(productos, nombre, nuevoProducto);
        printf("\n");
        printf("El producto ha sido agregado de manera exitosa, con stock %d, ", nuevoProducto->stock);
        system("pause");

    }
    else{

        printf("\n");
        printf("El producto que desea agregar ya existe, por favor indique si desea aumentar el stock: ");
        int opcion;
        do{
            printf("\n\n");
            printf("opcion 1: Agregar Stock\n");
            printf("opcion 2: Volver al menu\n");
            printf("\nEscoja una opcion: ");
            scanf("%d", &opcion);

            if(opcion > 2 || opcion < 1) printf("\nPor favor escriba una opcion correcta: ");

        }while(opcion < 1 || opcion > 2);

        if(opcion == 2) return -1;
        else{

            int stock;
            do{

                printf("\nPor favor ingrese el stock que desea agregar, el stock actual es: %d\n", product->stock);
                printf("Stock a agregar: ");
                scanf("%d", &stock);

                if(stock <= 0) printf("\nel stock a agregar debe ser mayor a 0\n");

            }while(stock <= 0);
            product->stock = product->stock + stock;
            printf("\nEl nuevo stock del produto es: %d, ", product->stock);
            system("pause");

        }

    }

    system("pause");

    return -1;
}

int buscarPorTipo(HashTable * productos){

    producto * product = firstHashTable(productos);
    if(!product){

        printf("No existe ningun producto almacenado aun, ");
        system("pause");
        return -1;

    }

    printf("Ingrese el tipo que desea buscar: ");
    char tipo[50];
    scanf("%s", tipo);
    fflush(stdin);

    int cont = 0;

    while(product != NULL){

        if(strcmp(product->tipo, tipo) == 0){

            if(cont == 0) printf("\nEstos productos se han encontrado del tipo %s: \n\n", tipo);

            printf("Nombre del producto: %s\n", product->nombre);
            printf("Marca del producto: %s\n", product->marca);
            printf("Stock del producto: %d\n", product->stock);
            printf("Precio del producto: %d\n\n", product->precio);
            cont++;
        }
        product = nextHashTable(productos);
    }

    if(cont == 0){
        printf("\nNo se ha encontrado ningun producto de este tipo, ");
    }

    system("pause");
    return -1;
}

int buscarPorMarca(HashTable * productos){

    producto * product = firstHashTable(productos);
    if(!product){

        printf("No existe ningun producto almacenado aun, ");
        system("pause");
        return -1;

    }

    printf("Ingrese el tipo que desea buscar: ");
    char marca[50];
    scanf("%s", marca);
    fflush(stdin);

    int cont = 0;

    while(product != NULL){

        if(strcmp(product->marca, marca) == 0){

            if(cont == 0) printf("\nEstos productos se han encontrado de la marca %s: \n\n", marca);

            printf("Nombre del producto: %s\n", product->nombre);
            printf("Tipo del producto: %s\n", product->tipo);
            printf("Stock del producto: %d\n", product->stock);
            printf("Precio del producto: %d\n\n", product->precio);
            cont++;
        }
        product = nextHashTable(productos);
    }

    if(cont == 0){
        printf("\nNo se ha encontrado ningun producto de esta marca, ");
    }

    system("pause");
    return -1;
}


