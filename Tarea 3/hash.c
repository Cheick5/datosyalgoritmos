#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "enemigo.h"
#include "hash.h"

/*
 *
 * Función para insertar en una tabla
 *
 * @param tabla es el puntero al puntero de la tabla a insertar
 * @param categoria Categoria del atacante
 * @param key struct del atacante

 */
void insertar_encadenamiento(struct node **tabla, int categoria, atacante key)
{
     // calculamos el valor de la funcion de hash
    if (tabla[categoria] == NULL) { // caso que la lista tabla[categoria] es vacia
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        nuevo_nodo->x = key;
        nuevo_nodo->next = NULL;
        tabla[categoria] = nuevo_nodo; // nuevo nodo pasa a ser el primer nodo
    }
    else { // caso que la lista tabla[categoria] no es vacia
        struct node *it = tabla[categoria];

        /* si el dato del primer nodo es key, no hay que insertar
        Es importante hacer el caso del primero nodo aparte, ya que el while de abajo,
        siempre pregunta por el dato del siguiente nodo,
        luego chequea todos los nodos menos el primero */
        if(it->x.nombre == key.nombre) {
            return;
        }

        /* recorremos la lista
        OJO: esta parte es distinta a la del video de la ayudantia,
        ahora preguntamos por it->next->x == key en vez de it->x == key,
        al preguntar por it->x == key nos saltamos el ultimo dato de la lista
        */
        while(it->next != NULL) {
            if((it->next)->x.nombre == key.nombre) { // caso en que key esta en la tabla (no hay que insertar)

                return;
            }
            it = it->next;
        }
        // insertamos nuevo nodo al final de la lista
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        nuevo_nodo->x = key;
        nuevo_nodo->next = NULL;
        it->next = nuevo_nodo;
    }
}

int buscar_encadenamiento(struct node **tabla, int N, atacante key)
{
//    int i = key % N; // calculamos el valor de la funcion de hash
//    struct node *it = tabla[i];
//    // recorremos la lista
//    while(it != NULL) {
//        if(it->x == key) { // caso en que encontramos key. Retornamos la casilla i
//            return i;
//        }
//        it = it->next;
//    }
//    // aca sabemos que key no esta
//    return -1;
}
void imprimir_tabla_encadenamiento(struct node **tabla, int N)
{
    // para cada casilla i de la tabla, recorremos la lista tabla[i]
    for(int i=0; i<N; i++) {
        struct node *it = tabla[i];
            printf("Categoria = %d | ", i+1);
        while(it != NULL) {

            printf("nombre = %s ", it->x.nombre);
            printf("probabilidad = %f ", it->x.prob_ataque);
            printf("| ");
            it = it->next;
        }
        printf("\n");

    }
}

void swap(struct node *nodo1, struct node *nodo2){

    atacante tmp = nodo1->x;
    nodo1->x = nodo2->x;
    nodo2->x = tmp;
}

void ordenar_lista(struct node *lista)
{
    if (lista == NULL){ // caso lista vacia
        return;
    }

    int swapped = 1; // indica si hubo algun swap
    struct node *it = lista;
    while(swapped == 1){
        swapped = 0;
        while (it->next != NULL){
            if(it->x.prob_ataque > it->next->x.prob_ataque) { // debemos hacer swap
                swap(it, it->next);
                swapped = 1;
            }
            it = it->next;
        }
        it = lista; // inicializamos el iterador it
    }
}