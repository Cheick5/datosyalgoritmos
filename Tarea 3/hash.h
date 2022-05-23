// Se incluye el archivo .h que contiene las estructuras. 
#include "enemigo.h"

// Se definen los prototipos de todas las funciones utilizadas en la realizacion de la tarea.
void insertar_encadenamiento(struct node **tabla, int N, atacante key);
void imprimir_tabla_encadenamiento(struct node **tabla, int N);
void swap(struct node *nodo1, struct node *nodo2);
void ordenar_lista(struct node *lista);
void ordenar_lista_Alfabetico(struct node *lista);
int largo_hash(struct node *lista);
int largo_hash_con_prob(struct node *lista);
struct node * ordenamiento_categoria_3(struct node *lista);