#include "functions.h"

 producto * crearProducto(const char * nombre, const char * marca, const char * tipo, int stock, int precio){

    producto * nuevo = (producto *) malloc (sizeof(producto));
    nuevo->nombre = nombre;
    nuevo->marca = marca;
    nuevo->tipo = tipo;
    nuevo->stock = stock;
    nuevo->precio = precio;
    return nuevo;

}

carrito * crearCarrito(char * nombre){

    carrito * nuevo = (carrito *) malloc (sizeof(carrito));
    nuevo->nombre = nombre;
    nuevo->productos = createList();
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
    fflush(stdin);
    printf("\n");

    anadirExtensionCSV(nombreArchivo);

    FILE * fp = fopen( nombreArchivo ,"r");
    if (!fp){
        printf("Hubo un error al abrir el arhivo, ");
        system("pause");
        return -1;
    }

    char linea[1024];

    const char * nombreProducto;
    const char * marcaProducto;
    const char * tipoProducto;
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
    int precio;

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

        int stock;
        printf("El producto es nuevo, por favor ingrese el stock que desea agregar: ");
        do{
            scanf("%d", &stock);
            if(stock <= 0) printf("El stock a agregar debe ser mayor que 0\n");
        }while(stock < 0);

        nuevoProducto = crearProducto(nombre, marca, tipo, stock, precio);
        insertHashTable(productos, nombre, nuevoProducto);
        printf("\n");
        printf("El producto ha sido agregado de manera exitosa, con stock %d, ", nuevoProducto->stock);

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

        printf("No existe ningun producto almacenado aun, primero ingrese uno. ");
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

        printf("No existe ningun producto almacenado aun, primero ingrese uno. ");
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

int buscarPorNombre(HashTable * productos){

    producto * product = firstHashTable(productos);
    if(!product){

        printf("aun no existe ningun producto almacenado, primero ingrese uno. ");
        system("pause");
        return -1;

    }

    printf("Por favor, ingrese el nombre del producto que desea buscar: ");
    fflush(stdin);
    char nombre[100];
    scanf("%[^\n]s", nombre);
    fflush(stdin);

    product = searchHashTable(productos, nombre);

    if(!product){

        printf("No existe ningun producto con este nombre, ");
        system("pause");
        return -1;

    }

    printf("\nAqui esta la informacion del producto buscado: \n\n");
    printf("Nombre del producto: %s\n", product->nombre);
    printf("Marca del producto: %s\n", product->marca);
    printf("Tipo del producto: %s\n", product->tipo);
    printf("Stock del producto: %d\n", product->stock);
    printf("Precio del producto: %d\n\n", product->precio);

    system("pause");
    return -1;
}

int mostrarProductos(HashTable * productos){

    producto * product = firstHashTable(productos);
    if(!product){

        printf("No existe ningun producto almacenado aun, primero ingrese uno. ");
        system("pause");
        return -1;

    }

    printf("Aqui esta la informacion de todos los productos almacenados: \n\n");

    while(product != NULL){

        printf("Nombre del producto: %s\n", product->nombre);
        printf("Marca del producto: %s\n", product->marca);
        printf("Tipo del producto: %s\n", product->tipo);
        printf("Stock del producto: %d\n", product->stock);
        printf("Precio del producto: %d\n\n", product->precio);

        product = nextHashTable(productos);
    }


    system("pause");
    return -1;

}

int agregarAlCarrito(HashTable * productos, List * carritos){

    carrito * primerCarrito = first(carritos);
    if(!primerCarrito){ // si es que no existe ningun carrito se pregunta si se desea añadir uno

        int opcion;

        printf("Aun no hay carritos para utilizar, desea crear uno?\n\n");
        do{

            printf("opcion 1: Crear un carrito nuevo\n");
            printf("opcion 2: volver al menu principal\n\n");
            printf("Digite su opcion: ");
            scanf("%d", &opcion);

            if(opcion != 1 && opcion != 2){

                printf("\nDebe ingresar una opcion correcta\n");

            }

            if(opcion == 2) return -1;

        }while(opcion != 1 && opcion != 2);

        char * nombreCarrito = (char *) malloc (50 * sizeof(char));
        printf("Por favor ingrese el nombre del nuevo carrito: ");
        fflush(stdin);
        scanf("%[^\n]s", nombreCarrito);
        fflush(stdin);

        carrito * nuevo = crearCarrito(nombreCarrito);
        pushBack(carritos, nuevo);
        printf("\nEl carrito ha sido creado con exito, que producto desea agregar al carrito?\n");
        char nombreProducto[100];

        do{

            printf("\nIngrese el nombre del producto que desea agregar: ");
            fflush(stdin);
            scanf("%[^\n]s", nombreProducto);
            fflush(stdin);

            producto * product = searchHashTable(productos, nombreProducto);

            if(!product){

                printf("no se ha encontrado ningun producto con este nombre\n\n");

                do{

                    printf("opcion 1: Intentar nuevamente\n");
                    printf("opcion 2: volver al menu principal\n\n");
                    printf("Digite su opcion: ");
                    scanf("%d", &opcion);

                    if(opcion != 1 && opcion != 2){

                        printf("\nDebe ingresar una opcion correcta\n");

                    }

                    if(opcion == 2) return -1;
                    else break;

                }while(opcion != 1 && opcion != 2);

            }
            else{

                if(product->stock > 0){

                    int stock;

                    do{

                        printf("\nEl stock del producto es: %d, que cantidad desea agregar al carrito?\n", product->stock);

                        printf("Digite su respuesta: ");

                        scanf("%d", &stock);
                        if( (product->stock - stock) < 0){

                            printf("\nno puede agregar mas que el stock disponible, intentelo nuevamente\n");

                        }

                    }while( (product->stock - stock) < 0);

                    product->stock = product->stock - stock;
                    pushBack(nuevo->productos, product);
                    printf("\nEl producto ha sido agregado de manera correcta, el nuevo stock es: %d, ", product->stock);
                    break;

                }
                else{

                    printf("\nEl producto que desea comprar no tiene stock disponible\n");
                    return -1;

                }

            }

        }while(1);

    }
    else{

        printf("Estos son los carritos existentes hasta el momento: \n\n");
        int cont = 1;

        while(primerCarrito != NULL){

            printf("carrito %d: %s\n", cont, primerCarrito->nombre);
            cont++;
            primerCarrito = next(carritos);

        }

        int opcion;

        do{

            printf("\nQue desea hacer?\n\n");
            do{

                printf("opcion 1: Utilizar un carrito existente\n");
                printf("opcion 2: Crear un carrito nuevo\n");
                printf("opcion 3: Volver al menu principal\n\n");
                printf("Digite su opcion: ");
                scanf("%d", &opcion);

                if(opcion < 1 || opcion > 3){

                    printf("\nDebe ingresar una opcion correcta\n");

                }

            }while(opcion < 1 || opcion > 3);


            if(opcion == 3) return -1;

            if(opcion == 1){

                char nombreCarrito[50];

                do{

                    printf("Por favor ingrese el nombre del carrito que desea utilizar: ");
                    fflush(stdin);
                    scanf("%[^\n]s", nombreCarrito);
                    fflush(stdin);

                    carrito * carritoExistente = first(carritos);
                    while(carritoExistente){

                        if(strcmp(carritoExistente->nombre, nombreCarrito) == 0) break;

                        carritoExistente = next(carritos);

                    }

                    if (!carritoExistente){

                        printf("\nNo existe ningun carrito con este nombre\n\n");

                        do{

                            printf("opcion 1: Intentar nuevamente\n");
                            printf("opcion 2: volver al menu anterior\n\n");
                            printf("Digite su opcion: ");
                            scanf("%d", &opcion);

                            if(opcion != 1 && opcion != 2){

                                printf("\nDebe ingresar una opcion correcta\n");

                            }

                            if(opcion == 2 || opcion == 1) break;


                        }while(opcion != 1 && opcion != 2);

                        if(opcion == 2) break;

                    }
                    else{

                        do{

                            char nombreProducto[100];
                            printf("\nIngrese el nombre del producto que desea agregar: ");
                            fflush(stdin);
                            scanf("%[^\n]s", nombreProducto);
                            fflush(stdin);

                            producto * product = searchHashTable(productos, nombreProducto);

                            if(!product){

                                printf("no se ha encontrado ningun producto con este nombre\n\n");


                                    printf("opcion 1: Intentar nuevamente\n");
                                    printf("opcion 2: volver al menu anterior\n\n");
                                    printf("Digite su opcion: ");
                                    scanf("%d", &opcion);

                                    if(opcion != 1 && opcion != 2){

                                        printf("\nDebe ingresar una opcion correcta\n");

                                    }

                                    if(opcion == 2) break;

                            }
                            else{

                                if(product->stock > 0){

                                    int stock;

                                    do{

                                        printf("\nEl stock del producto es: %d, que cantidad desea agregar al carrito?\n", product->stock);

                                        printf("Digite su respuesta: ");

                                        scanf("%d", &stock);
                                        if( (product->stock - stock) < 0){

                                            printf("\nno puede agregar mas que el stock disponible, intentelo nuevamente\n");

                                        }

                                    }while( (product->stock - stock) < 0);

                                    product->stock = product->stock - stock;
                                    pushBack(carritoExistente->productos, product);
                                    printf("\nEl producto ha sido agregado de manera correcta, el nuevo stock es: %d, ", product->stock);
                                    system("pause");
                                    return -1;

                                }
                                else{

                                    printf("\nEl producto que desea agregar no tiene stock disponible\n");
                                    return -1;

                                }

                            }

                        }while(1);

                        if(opcion == 2) break;

                    }

                }while(1);

            }
            else if(opcion == 2){

                char * nombreCarrito = (char *) malloc (50 * sizeof(char));

                do{

                    printf("Por favor ingrese el nombre del nuevo carrito: ");
                    fflush(stdin);
                    scanf("%[^\n]s", nombreCarrito);
                    fflush(stdin);

                    carrito * existente = first(carritos);
                    while(existente != NULL){

                        if(strcmp(existente->nombre, nombreCarrito) == 0){

                            printf("\nEl carrito que intenta crear ya existe\n");
                            break;

                        }
                        existente = next(carritos);

                    }

                    if(!existente) break;


                }while(1);

                carrito * nuevo = crearCarrito(nombreCarrito);
                pushBack(carritos, nuevo);
                printf("\nEl carrito ha sido creado con exito, que producto desea agregar al carrito?\n");
                char nombreProducto[100];

                do{

                    printf("\nIngrese el nombre del producto que desea agregar: ");
                    fflush(stdin);
                    scanf("%[^\n]s", nombreProducto);
                    fflush(stdin);

                    producto * product = searchHashTable(productos, nombreProducto);

                    if(!product){

                        printf("no se ha encontrado ningun producto con este nombre\n\n");

                        do{

                            printf("opcion 1: Intentar nuevamente\n");
                            printf("opcion 2: volver al menu principal\n\n");
                            printf("Digite su opcion: ");
                            scanf("%d", &opcion);

                            if(opcion != 1 && opcion != 2){

                                printf("\nDebe ingresar una opcion correcta\n");

                            }

                            if(opcion == 2) return -1;
                            else break;

                        }while(opcion != 1 && opcion != 2);

                    }
                    else{

                        if(product->stock > 0){

                            int stock;

                            do{

                                printf("\nEl stock del producto es: %d, que cantidad desea agregar al carrito?\n", product->stock);

                                printf("Digite su respuesta: ");

                                scanf("%d", &stock);
                                if( (product->stock - stock) < 0){

                                    printf("\nno puede agregar mas que el stock disponible, intentelo nuevamente\n");

                                }

                            }while( (product->stock - stock) < 0);

                            product->stock = product->stock - stock;
                            pushBack(nuevo->productos, product);
                            printf("\nEl producto ha sido agregado de manera correcta, el nuevo stock es: %d, ", product->stock);
                            system("pause");
                            return -1;

                        }
                        else{

                            printf("\nEl producto que desea agregar no tiene stock disponible\n");
                            return -1;

                        }

                    }

                }while(1);


                printf("\nEl producto ha sido agregado de manera correcta, ");

            }

        }while(1);

    }

    system("pause");
    return -1;

}

int concretarCompra(List * carritos){

    carrito * primerCarrito = first(carritos);
    if(!primerCarrito){

        printf("Aun no existe ningun carrito para concretar la compra, ");
        system("pause");
        return -1;

    }

    printf("Esta es la lista de carritos disponibles: \n\n");
    int cont = 1;
    while(primerCarrito){
        printf("carrito %d: %s\n", cont, primerCarrito->nombre);
        primerCarrito = next(carritos);
        cont++;
    }

    char nombreCarrito[100];
    int opcion;

    do{

        printf("\nIngrese el nombre del carrito: ");
        fflush(stdin);
        scanf("%[^\n]s", nombreCarrito);
        fflush(stdin);

        primerCarrito = first(carritos); //volvemos a utilizar la variable para buscar el carrito indicado

        while(primerCarrito){

            if(strcmp(primerCarrito->nombre, nombreCarrito) == 0) break;
            primerCarrito = next(carritos);
        }

        if(!primerCarrito){

            printf("\nNo se ha encontrado el carrito buscado, que desea hacer?\n\n");

            do{


                printf("opcion 1: Intentar nuevamente\n");
                printf("opcion 2: Volver al menu principal\n\n");
                printf("Digite su opcion: ");
                scanf("%d", &opcion);

                if(opcion == 2) return -1;

                if(opcion < 1 || opcion > 2){

                    printf("\nPor favor ingrese una opcion correcta\n\n");

                }

            }while(opcion < 1 || opcion > 2);

        }
        else break;

    }while(1);

    producto * primerProducto = first(primerCarrito->productos);

    if(!primerProducto){

        printf("El carrito seleccionado no contiene ningun producto, primero debe añadir uno, ");
        system("pause");

    }
    else{

        int precioTotal = 0;

        printf("\nEstos son los productos en el carrito seleccionado:\n\n");

        while(primerProducto){

            printf("%s\n", primerProducto->nombre);
            primerProducto = next(primerCarrito->productos);

        }

        printf("\nDesea concretar la compra?\n\n");

        do{

            printf("opcion 1: Concretar la compra\n");
            printf("opcion 2: Volver al menu principal\n\n");
            printf("Digite su opcion: ");
            scanf("%d", &opcion);

            if(opcion == 2) return -1;

            if(opcion < 1 || opcion > 2){

                printf("\nPor favor ingrese una opcion correcta\n\n");

            }

        }while(opcion < 1 || opcion > 2);

        //concretar compra
        printf("\nEl precio a pagar por todos los productos del carrito es: %d\n\n", precioTotal);
        printf("Con cuanto dinero desea pagar?\n");
        int efectivo;

        do{
            printf("Digite su respuesta: ");
            scanf("%d", &efectivo);

            if(efectivo < precioTotal){

                printf("\nEl monto debe ser igual o mayor del total a pagar\n\n");

            }

        }while(efectivo < precioTotal);

        printf("\nLa compra se ha efectuado de manera correcta, ");

        if(efectivo > precioTotal){

            printf("su vuelto es: %d, ", precioTotal - efectivo);

        }

        system("pause");

    }

    return -1;

}
