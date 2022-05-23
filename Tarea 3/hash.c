// Se importan todas las librerias necesarias.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

// Utilizaremos las funciones entregadas por el profesor, con algunas modificaciones pertinentes que atañen a la tarea en si.
void insertar_encadenamiento(struct node **tabla, int categoria, atacante key)
{
    // Lista (tabla[categoria]) es vacia.
    // Se realiza el proceso pertinente, es decir, se crea un nuevo nodo (pidiendo memoria dinamica) y luego se realiza el proceso de asignacion de siguiente y el actual.
    if (tabla[categoria] == NULL) { 
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        nuevo_nodo->x = key;
        nuevo_nodo->next = NULL;
        tabla[categoria] = nuevo_nodo; // nuevo nodo pasa a ser el primer nodo
    }

    // Lista (tabla[categoria]) no es vacia.
    // Se realiza el proceso pertinente para aquellos casos en los cuales la lista no es vacia.
    else {
        struct node *it = tabla[categoria];
        if(it->x.nombre == key.nombre) {
            return;
        }

        while(it->next != NULL) {
            if((it->next)->x.nombre == key.nombre) { // caso en que key esta en la tabla (no hay que insertar)

                return;
            }
            it = it->next;
        }
        // Se realiza el procedimiento para insertar el nuevo nodo al final de la lista.
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        nuevo_nodo->x = key;
        nuevo_nodo->next = NULL;
        it->next = nuevo_nodo;
    }
}

// Funcion utilizada para imprimir las listas que fueron llenadas y manipuladas en la tarea.
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

// Funcion utilizada por otras funciones, la cual sirve para intercambiar de lugar nodos.
void swap(struct node *nodo1, struct node *nodo2){

    atacante tmp = nodo1->x;
    nodo1->x = nodo2->x;
    nodo2->x = tmp;
}

// Funcion que ordena la lista, en este caso en particular fue utilizada para ordenar las listas en base a la probabilidad.
void ordenar_lista(struct node *lista)
{
    // Lista vacia.
    if (lista == NULL){ 
        return;
    }

    int swapped = 1; // Indica si hubo algun swap.
    struct node *it = lista;

    while(swapped == 1){
        swapped = 0;
        while (it->next != NULL){
            if(it->x.prob_ataque < it->next->x.prob_ataque) { // Se debe hacer swap.
                swap(it, it->next);
                swapped = 1;
            }
            it = it->next;
        }

        // Se inicializa el iterador it.
        it = lista; 
    }
}

// Funcion utilizada para ordenar alfabeticamente los nombres de aquellos atacantes que tenian probabilidad cero o que tenian igual probabilidad.
void ordenar_lista_Alfabetico(struct node *lista)
{   
    // Lista vacia.
    if (lista == NULL){
        return;
    }

    // Variable que indica si hubo algun swap.
    int swapped = 1; 
    struct node *it = lista;
    while(swapped == 1){
        swapped = 0;
        while (it->next != NULL){
            if(it->x.prob_ataque == it->next->x.prob_ataque){
                if(strcmp(it->x.nombre, it->next->x.nombre) > 0) { // Se debe hacer swap.
                    swap(it, it->next);
                    swapped = 1;
                }
            }
                it = it->next;
            }
        // Se inicializa el iterador it.
        it = lista;
    }
}

// Funcion utilizada para conocer el largo de cada una de las listas (cantidad de nombres).
int largo_hash(struct node *lista){

    // Se crea una estructura nodo que apunta al primer elemento de la lista y se crea una variable que llevara la cuenta de la cantidad de nombres que hay en cada lista.
    int contador = 1;
    struct node *it = lista;

    // Proceso para contar aquellos que son no nulos (para contar los datos que efectivamente estan).
    while(it->next != NULL){
        contador++;
        it = it->next;
    }

    // Se retorna contador, que es el numero de nombres que hay en la lista sobre la cual se aplico la funcion.
    return contador;
}

// Funcion utilizada para conocer el largo de cada una de las listas (cantidad de nombres con probabilidad distinta de cero).
int largo_hash_con_prob(struct node *lista){

    // Se crea una estructura nodo que apunta al primer elemento de la lista y se crea una variable que llevara la cuenta de la cantidad de nombres que hay en cada lista.
    int contador = 1;
    struct node *it = lista;

    // Proceso para contar aquellos nombres que tienen probabilidad distinta de cero.
    while(it->next != NULL){
        if(it->x.prob_ataque != 0) {
            contador++;
        }
        it = it->next;
    }

    // Se retorna contador, que es el numero de nombres con probabilidad distinta de cero que hay en la lista sobre la cual se aplico la funcion.
    return contador;
}

// Funcion utilizada especificamente para el requisito especifico de la categoria tres.
// Seguiremos el consejo del profesor (dicho en clases), que creemos una lista vacia y pusieramos la mitad con aquellos nombres con probabilidad.
// Luego se ingresarian aquellos con probabilidad igual a cero (para que queden efectivamente al medio de la lista).
// Para terminar se ingresarian aquellos nombres faltantes que tenian probabilidad distinta de cero.
struct node * ordenamiento_categoria_3(struct node *lista){

    //Primera lista auxiliar.
    struct node *it = lista;

    //Segunda lista auxiliar.
    struct node *inicio = it;

    //Crearemos una lista temporal (auxiliar), que ira llenando de forma ordenada en base a la lista de la categoria 3.
    struct node *lista_temporal[1];

    // Inicializamos la tabla en null para evitar errores random.
    for (int i = 0; i < 1; ++i) {
        lista_temporal[i] = NULL; 
    }

    // Se crean las variables "Personas_Con_Prob" y "Mitad", las cuales seran necesarias para llenar hasta la mitad con nombres que tienen asignada una probabilidad.
    // Luego a la mitad poner aquellos nombres con probabilidad asignada igual a cero.
    // Y para terminar, se terminara de ingresar aquellos nombres faltantes que tenian probabilidad asociada distinta de cero.
    int Personas_Con_Prob = largo_hash_con_prob(lista);
    int Mitad = Personas_Con_Prob/2;

    // Se crea la variable contador para tener en cuenta aquellos que ya fueron ingresados.
    int Contador = 0;
    while(it->next != NULL){

        // Ingreso de nombres para la primera mitad.
        if (Contador < Mitad){ 

            // Se utiliza la funcion "insertar_encadenamiento" (entregada por profesor) para ingresar el dato a la lista temporal.
            insertar_encadenamiento(lista_temporal, 0, it->x);
        }

        // Ingreso de nombres que tiene probabilidad igual a cero (para quedar en la mitad).
        else if (Contador >= Personas_Con_Prob - 1){

            // Se utiliza la funcion "insertar_encadenamiento" (entregada por profesor) para ingresar el dato a la lista temporal.
            insertar_encadenamiento(lista_temporal, 0, it->x);
        }

        // Se actualiza el it y se agrega una unidad a contador.
        it = it->next;
        Contador++;
    }
    // Se crea la variable contador_2 para tener en cuenta aquellos que ya fueron ingresados.
    int Contador_2 = 0;

    // Se crea una segunda estructura node "it2" que apunta al inicio de la lista
    struct node *it2 = inicio;

    // Ingreso de nombres de aquellos que faltaban en la lista (tienen probabilidad asignada distinta de cero), lo que podriamos llamar como ingreso de nombres a la segunda mitad.
    while(it2->next != NULL){
        if (Contador_2 >= Mitad && Contador_2 < Personas_Con_Prob - 1){
            
            // Se utiliza la funcion "insertar_encadenamiento" (entregada por profesor) para ingresar el dato a la lista temporal.
            insertar_encadenamiento(lista_temporal, 0, it2->x);
        }
        
        // Se actualiza el it y se agrega una unidad a contador.
        it2 = it2->next;
        Contador_2++;
    }

    // Se retorna la lista temporal, la cual es exactamente la lista que se solicita para la categoria tres, por lo tanto, lo ultimo que queda por hacer es hacer que nuestra lista para la categotia tres sea igualada a nuestra lista temporal.
    return lista_temporal[0];
}

