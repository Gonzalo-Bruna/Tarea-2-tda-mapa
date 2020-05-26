#ifndef MAP_H
#define MAP_H

typedef struct Pair Pair;

typedef struct HashTable HashTable;

/* Crea una tabla de hash, inicializando buckets con NULL, count en 0, size en el valor pasado por parametro
current - 1, y load factor en el procentaje de ocupacion con respecto a size */
HashTable * createHashTable(long size);

/* Crea un dato tipo Pair inicializado con el key y el value pasado por parametro */
Pair * createPair(const char * key, void * value);

/* stringHash recibe una variable de tipo char y retorna una clave (sin aplicar hashing para calcular su posición) */
unsigned long stringHash(const char * key);

/* linearProbing devuelve la posición en donde insertar un dato con clave key, si la posición está ocupada recorre linealmente
hasta encontrar una posición que esté vacía */
long linearProbing(HashTable * table, const char * key);

/* inserta en la tabla "table" el dato con su valor y clave  */
void insertHashTable(HashTable * table, const char * key, void * value);

/* Busca un dato y lo retorna si es que lo encuentra, en caso contrario retorna NULL */
void * searchHashTable(HashTable * table, const char * key);

/* Elimina un dato de table "table", deja la casilla en donde se encontraba en NULL, también retorna el dato */
void * eraseKeyHashTable(HashTable * table, const char * key);

/* En caso de que la tabla hash supere el loadFactor (factor de carga) se encarga de duplicar su tamaño para evitar colisiones y mejorar su rendimiento */
void enlarge(HashTable * table);

// Retorna el valor del primer dato no nulo de la tabla hash
void * firstHashTable(HashTable * table);

// Retorna el valor del dato no nulo siguiente al current
void * nextHashTable(HashTable * table);

#endif // MAP_H
