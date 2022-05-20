#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void imprimir_tabla_encadenamiento(struct node **tabla, int N)
{
    // para cada casilla i de la tabla, recorremos la lista tabla[i]
    for(int i = 0; i < N; i++) {
        struct node *it = tabla[i];
            printf("Categoria = %d | \n", i+1);
        while(it != NULL) {

            printf("nombre = %s ", it->x.nombre);
            printf("probabilidad = %f ", it->x.prob_ataque);
            printf("| ");
            printf("\n");

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
            if(it->x.prob_ataque < it->next->x.prob_ataque) { // debemos hacer swap
                swap(it, it->next);
                swapped = 1;
            }
            it = it->next;
        }
        it = lista; // inicializamos el iterador it
    }
}

void ordenar_lista_Alfabetico(struct node *lista)
{
    if (lista == NULL){ // caso lista vacia
        return;
    }

    int swapped = 1; // indica si hubo algun swap
    struct node *it = lista;
    while(swapped == 1){
        swapped = 0;
        while (it->next != NULL){
            if(it->x.prob_ataque == it->next->x.prob_ataque){
                if(strcmp(it->x.nombre, it->next->x.nombre) > 0) { // debemos hacer swap
                    swap(it, it->next);
                    swapped = 1;
                }
            }
                it = it->next;
            }
        it = lista; // inicializamos el iterador it
    }
}

int largo_hash(struct node *lista){

    int contador = 1;
    struct node *it = lista;
    while(it->next != NULL){
        contador++;
        it = it->next;
    }
    return contador;

}

int largo_hash_con_prob(struct node *lista){

    int contador = 1;
    struct node *it = lista;
    while(it->next != NULL){
        if(it->x.prob_ataque != 0) {
            contador++;
        }
        it = it->next;
    }
    return contador;

}


struct node * ordenamiento_categoria_3(struct node *lista){

    struct node *it = lista;//Primera lista auxiliar
    struct node *inicio = it;//Segunda lista auxiliar




    //Crear una lista temporal o auxiliar, que sera la que iran llenando de forma
    //ordenada en base a la lista de la categoria 3
//    struct node *lista_temporal=(struct node *)malloc(sizeof(struct node));
    struct node *lista_temporal[1];

    for (int i = 0; i < 1; ++i) {
        lista_temporal[i] = NULL; //Inicializamos la tabla en null para evitar errores random
    }

    int tope=largo_hash_con_prob(lista);
    int mitad=tope/2;


    int n=0;
    while(it!=NULL){
        if (n<mitad){ //Primera mitad
            insertar_encadenamiento(lista_temporal,0,it->x);
        }

        else if (n>=tope-1){ // prob = 0
            insertar_encadenamiento(lista_temporal,0,it->x);
        }
            it=it->next;
        n++;
    }
    n=0;
    struct node *it2=inicio;
    while(it2!=NULL){
        if (n>=mitad && n<tope-1){ //segunda mitad

            // n>=mitad && n<tope

            insertar_encadenamiento(lista_temporal,0,it2->x);
        }
        n++;
        it2=it2->next;
    }

    return lista_temporal[0];

}

