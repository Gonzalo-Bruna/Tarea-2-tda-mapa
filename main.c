#include <stdio.h>

#include "map.h"
#include "functions.h"

int main(){

    printf("ˇBienvenido a nuestro sistema de organizacion de productos!");

    int opcion;
    HashTable * productos = createHashTable(100);

    do{

        printf("\n");
        printf("Por favor, elija una de las siguientes opciones: ");
        printf("\n");
        printf("\n");
        printf("opcion 1: Importar productos desde un archivo");
        printf("\n");
        printf("opcion 2: Exportar productosa a un archivo csv");
        printf("\n");
        printf("opcion 3: Agregar un producto");
        printf("\n");
        printf("opcion 4: Buscar productos por tipo");
        printf("\n");
        printf("opcion 5: Buscar productos por marca");
        printf("\n");
        printf("opcion 6: Buscar producto por nombre");
        printf("\n");
        printf("opcion 7: Mostrar todos los productos");
        printf("\n");
        printf("opcion 8: Agregar un producto al carrito");
        printf("\n");
        printf("opcion 9: Concretar compra");
        printf("\n");
        printf("opcion 0: Cerrar programa");
        printf("\n");
        printf("\n");

        do{

            printf("por favor escoja una opcion: ");
            scanf("%d", &opcion);
            printf("\n");
            if(opcion < 0 || opcion > 9) printf("La opcion ingresada no es correcta, \n");

        }while( opcion < 0 || opcion > 9 );

        switch(opcion){

            case 1: if (importarProductosCSV(productos) == -1) opcion = -1;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                break;
        }

    }while(opcion == -1);

    system("pause");

    return 0;
}
